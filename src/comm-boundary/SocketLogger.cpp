#include "SocketLogger.h"
#include "ecs/IECS.h"
#include "ParsingHelpers.h"
#include <thread>
#include <utility>
#include "IncomingJsonParsers.h"
#include "OutgoingJsonParsers.h"

SocketLogger::SocketLogger(Logger logger_, std::queue<json> temp) :
        incomingMessageQueue(std::move(temp)),
        outgoingMessageQueue(),
        logger(std::move(logger_)),
        myECS(nullptr),
        webSocketServer{},
        connections{}
{
    this->webSocketServer.set_message_handler(websocketpp::lib::bind(&SocketLogger::onMessage, this,
                                                                     websocketpp::lib::placeholders::_1,
                                                                     websocketpp::lib::placeholders::_2));

    this->webSocketServer.set_access_channels(websocketpp::log::alevel::none);
    this->webSocketServer.set_error_channels(websocketpp::log::elevel::all);

    this->webSocketServer.set_reuse_addr(true);

    this->webSocketServer.set_open_handler(bind(&SocketLogger::onOpen, this, websocketpp::lib::placeholders::_1));
    this->webSocketServer.set_close_handler(bind(&SocketLogger::onClose, this, websocketpp::lib::placeholders::_1));

    this->webSocketServer.init_asio();
    this->webSocketServer.listen(9002);
    this->webSocketServer.start_perpetual();
    this->webSocketServer.start_accept();

    this->serverThread = std::thread(&server::run, &this->webSocketServer);
}

SocketLogger::~SocketLogger()
{
    /*
     * NOTE: when destructing, you will see messages like
     * [2022-11-21 00:15:49] [info] asio handle_accept error: asio.system:995 (The I/O operation has been aborted because of either a thread exit or an application request.)
     * [2022-11-21 00:15:49] [info] Error getting remote endpoint: asio.system:10009 (The file handle supplied is not valid.)
     * [2022-11-21 00:15:49] [info] asio async_shutdown error: asio.system:10009 (The file handle supplied is not valid.)
     * [2022-11-21 00:15:49] [error] handle_accept error: The I/O operation has been aborted because of either a thread exit or an application request.
     * [2022-11-21 00:15:49] [info] Stopping acceptance of new connections because the underlying transport is no longer listening.
     *
     * in the console
     *
     * they seem worrying, but the author of the library says that it is expected behavior
     * https://github.com/zaphoyd/websocketpp/issues/556
     * if it was an actual issue, it will throw an error, not just log
     *
     * i noted that another project has the same issue
     * https://github.com/sony/nmos-cpp/blob/master/Development/cpprest/ws_listener_impl.cpp
     * at line 405 ish
     */
    try {
        this->webSocketServer.stop_perpetual();
        this->webSocketServer.stop_listening();

        for (auto &conn: this->connections) {
            this->webSocketServer.close(conn, websocketpp::close::status::normal, "Success");
        }

        this->serverThread.join();
    }
    catch (const std::exception& e){
        this->logger.write("SocketLogger destructor threw with: ");
        this->logger.write(e.what());
    }
    catch (...) {
        this->logger.write("SocketLogger destructor threw with non-object exception!");
    }
}

// for some dogshit reason, removing the handle parameter from the signature makes "set_message_handler"
// freak out with some template error
void SocketLogger::onMessage(
        [[maybe_unused]] websocketpp::connection_hdl handle,
        server::message_ptr serializedMessage) {
	std::string messageString = serializedMessage->get_payload();

    try {
        json messageJson = json::parse(messageString);
        this->incomingMessageQueue.push(messageJson);
    }
    catch(json::exception&){
        this->reportMessage("Failed to parse received string from websocket into a JSON object");
    }
}

void SocketLogger::onOpen(websocketpp::connection_hdl hdl) {
    this->connections.insert(std::move(hdl));
}

void SocketLogger::onClose(websocketpp::connection_hdl hdl) {
    this->connections.erase(hdl);
}

void SocketLogger::broadcast(const std::string& message) {
    for (auto& it : this->connections) {
        this->webSocketServer.send(it, message, websocketpp::frame::opcode::text);
    }
}

void SocketLogger::executeMessage(const json& message) {
    try {
        parseJSONFromOperator(message, *(this->myECS));
    }
    catch(const std::invalid_argument& e){
        this->reportMessage(e.what());
    }
}

void SocketLogger::reportState(ECSState &curState) {
    this->outgoingMessageQueue.push(parseECSState(curState).dump(4));
}

void SocketLogger::reportRedlines(std::vector<RedlineResponsePacket> redlineReports) {
    this->outgoingMessageQueue.push(parseRedlines(redlineReports).dump(4));
}

void SocketLogger::reportSensorData(SensorData data, bool isCalibrated) {
    this->outgoingMessageQueue.push(parseSensorData(data, isCalibrated).dump(4));
}

void SocketLogger::reportMessage(std::string msg) {
    this->outgoingMessageQueue.push(parseMessage(msg).dump(4));
}

void SocketLogger::processIncoming() {
    while (this->incomingMessageQueue.size() > 0) {
        auto message = this->incomingMessageQueue.front();
        this->incomingMessageQueue.pop();

        this->executeMessage(message);
    }
}

void SocketLogger::processOutgoing() {
    while (this->outgoingMessageQueue.size() > 0) {
        auto message = this->outgoingMessageQueue.front();
        this->outgoingMessageQueue.pop();

        this->logger.write(message);
        this->broadcast(message);
    }
}

void SocketLogger::acceptECS(IECS &ecs) {
    this->myECS = &ecs;
}

