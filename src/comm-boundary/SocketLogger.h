#ifndef ENGINECONTROLSYSTEM_NETWORKER_H
#define ENGINECONTROLSYSTEM_NETWORKER_H

#include "ICommBoundary.h"

#include <set>
#include <json.hpp>

// flags to switch off use of RTTI (typeid in this case) for whatever asio lib websocketpp is using
#define ASIO_NO_TYPEID
// this makes websocketpp look for the standalone asio lib, not boost asio
#define ASIO_STANDALONE
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#undef ASIO_STANDALONE
#undef ASIO_NO_TYPEID

#include "utils/ThreadQueue.h"

#include "logger/Logger.h"
#include <etl/vector.h>

// forward declaration lmao
class IECS;

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> conList;

/**
 * An implementation of ICommBoundary using json and websockets.
 *
 * This object is responsible for both connections from operator -> ECS and
 * ECS -> operator
 *  - NOTE: I tried to break it up into separate objects, but a major difficulty is in the websockets
 *  Only one server can be connected to a given port, so we can't break it into two separate components
 *  sharing the same port
 *
 *  This object will log everything it tries to send locally on a text file as well
 *
 * The overriden ICommBoundary methods are thread-safe
 */
class SocketLogger: public ICommBoundary {
public:
	explicit SocketLogger(Logger logger = Logger{}, std::queue<json> queue = {});

    SocketLogger(const SocketLogger& other) = delete;

    SocketLogger(SocketLogger&& other) = delete;

    SocketLogger& operator=(SocketLogger&& other) = delete;

    ~SocketLogger() override;

    /**
     * Processes incoming message queue from operator.
     * Dispatches messages and sends to stored IECS object
     */
    void processIncoming();

    /**
     * Processes outgoing message queue to operator in addition
     * to logging each message on the ECS side.
     */
    void processOutgoing();

    void reportState(ECSState& curState) override;
    void reportRedlines(etl::vector<RedlineResponsePacket, 45> redlineReports) override;
    void reportSensorData(SensorData data, bool isCalibrated) override;
    void reportMessage(std::string msg) override;

    /**
     * Stores which IECS object to call methods on
     * @param ecs ecs object
     */
    void acceptECS(IECS& ecs);

private:
    /**
     * Receives web socket message and adds to incoming queue as JSON obj
     * @param handle imma be real chief i have no clue but it breaks otherwise, so don't change it
     * @param message imma be real chief i have no clue but it breaks otherwise, so don't change it
     */
    void onMessage(websocketpp::connection_hdl handle, server::message_ptr message);

    /**
     * Called on new connection in websocket, stores in set
     * @param hdl handle to new connection
     */
    void onOpen(websocketpp::connection_hdl hdl);

    /**
     * Called when connection is closed, removes from set
     * @param hdl handle to soon to be removed handle
     */
    void onClose(websocketpp::connection_hdl hdl);

    /**
     * Read and parses command, and dispatches to IECS if appropriate
     * @param message json representing the message
     */
    void executeMessage(const json& message);

    /**
     * Helper function, sends message to all operators
     * @param message message.
     */
    void broadcast(const std::string& message);

    ThreadQueue<json> incomingMessageQueue;
    ThreadQueue<std::string> outgoingMessageQueue;

    Logger logger;

    IECS* myECS;

	server webSocketServer;
	conList connections;

    std::thread serverThread;
};

#endif // ENGINECONTROLSYSTEM_NETWORKER_H
