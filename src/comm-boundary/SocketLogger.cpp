#include "SocketLogger.h"
#include "ParsingHelpers.h"
#include <thread>
#include <utility>

// anonymous namespace for helper functions
namespace{
    /**
     * Helper function, parses valves in sensor data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
     /*
      * This function should hit all the valve fields in SensorData
      */
    json getValveReport(SensorData &data) {
        static_assert(SensorData::majorVersion == 3,
                "Function not updated from SensorData change, please update this function and the static_assert");
        json valveReport;

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxVent);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxVent"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerVent);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerVent"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxPressurant);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxPressurant"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerPressurant);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerPressurant"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxFlow);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxFlow"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerFlow);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerFlow"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxPurge);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxPurge"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerPurge);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerPurge"] = curReport;
        }

//    {
//        json curReport;
//        curReport["valveState"] = "CLOSED";
//        curReport["timeStamp"] = getTimeStamp();
//
//        valveReport["loxN2Ducer"] = curReport;
//    }
//
//    {
//        json curReport;
//        curReport["valveState"] = "CLOSED";
//        curReport["timeStamp"] = getTimeStamp();
//
//        valveReport["kerN2Ducer"] = curReport;
//    }

        return valveReport;
    }

    /**
     * Helper function, parses pressure sensors in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
     /*
      * This function should hit all the fields containing data from pressure sensors
      * (this is not directly documented in SensorData, ask for documentation from
      * prop software lead or prop directly)
      */
    json getPressureReport(SensorData &data) {
        static_assert(SensorData::majorVersion == 3,
                "Function not updated from SensorData change, please update this function and the static_assert");
        json pressureReport;

        {
            json curReport;
            curReport["sensorReading"] = data.loxTankDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxTankDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerTankDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerTankDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.purgeDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["purgeDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxInletDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxInletDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerInletDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerInletDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerPintleDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerPintleDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxVenturi;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxVenturi"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerVenturi;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerVenturi"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.pneumaticDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["pneumaticDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxRegDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxRegDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerRegDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerRegDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.n2pressDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["n2pressDucer"] = curReport;
        }

        return pressureReport;
    }

    /**
     * Helper function, parses load cell sensors in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
    * This function should hit all the fields containing data from loadcell sensors
    * (this might not be directly documented in SensorData, if so ask for documentation from
    * prop software lead or prop directly)
    */
    json getLoadCellReport(SensorData &data) {
        static_assert(SensorData::majorVersion == 3,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        json loadCellReport;

        {
            json curReport;
            curReport["sensorReading"] = data.loadCell;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            loadCellReport["loadCell"] = curReport;
        }

        return loadCellReport;
    }

    /**
     * Helper function, parses thermocouples in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
    * This function should hit all the fields containing data from thermocouples (sensors that measure temp)
    * (this is not directly documented in SensorData, ask for documentation from
    * prop software lead or prop directly)
    */
    json getTemperatureReport(SensorData &data) {
        static_assert(SensorData::majorVersion == 3,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        json tempReport;

        {
            json curReport;
            curReport["sensorReading"] = data.loxTankTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["loxTankTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerInletTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["kerInletTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerOutletTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["kerOutletTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.miscTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["miscTC"] = curReport;
        }

        return tempReport;
    }
}


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
    this->webSocketServer.stop_perpetual();
    this->webSocketServer.stop_listening();

    for (auto& conn: this->connections) {
        this->webSocketServer.close(conn, websocketpp::close::status::normal, "Success");
    }

    this->serverThread.join();
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

void SocketLogger::executeMessage(json message) {
    std::string command; //ugly initialization outside for scope, can refactor?
    try {
        command = message["command"];
    }
    catch(json::exception&){
        this->reportMessage("Failed parse from JSON data, 'command' tag is not specified");
        return;
    }

	//messageType command = stringToMessageTypeMap[message["command"]];
    if (command == "SET_ACTIVE_ELEMENTS") {
        try {
            /*
             * This section of code should hit all the fields
             * in CommandData
             */
            static_assert(CommandData::majorVersion == 2,
                          "Function not updated from CommandData change, please update this function and the static_assert");

            CommandData newOverrideCom;
            json overrideElements = message["activeElements"];

            newOverrideCom.loxPressurant = stringToValveState(overrideElements["loxPressurant"]);
            newOverrideCom.kerPressurant = stringToValveState(overrideElements["kerPressurant"]);

            newOverrideCom.loxPurge = stringToValveState(overrideElements["loxPurge"]);
            newOverrideCom.kerPurge = stringToValveState(overrideElements["kerPurge"]);

            newOverrideCom.loxVent = stringToValveState(overrideElements["loxVent"]);
            newOverrideCom.kerVent = stringToValveState(overrideElements["kerVent"]);

            newOverrideCom.loxFlow = stringToValveState(overrideElements["loxFlow"]);
            newOverrideCom.kerFlow = stringToValveState(overrideElements["kerFlow"]);

            this->myECS->acceptOverrideCommand(newOverrideCom);
        }
        catch (std::invalid_argument&) {
            this->reportMessage("Invalid valve state from manual override command!");
        }
        catch (json::exception&) {
            this->reportMessage("Failed parse from JSON data to CommandData on manual override, missing field?");
        }
	}
	else if (command == "SET_STATE") {
        std::string newStateCommand;

        try {
            newStateCommand = message["newState"];
        }
        catch(json::exception&){
            this->reportMessage("Bad json read on state transition, 'newState' tag not found");
            return;
        }

        try {
            std::cout << "Entering set state in networker " << newStateCommand << std::endl;

            this->myECS->acceptStateTransition(stringToECSState(newStateCommand));
        }
        catch (std::invalid_argument&){
            json returnReport;
            returnReport["command"] = "STATE_TRANSITION_ERROR";
            returnReport["timeStamp"] = getTimeStamp();
            returnReport["failedTransition"] = newStateCommand;

            std::cout << "Failed new state change to \"" << newStateCommand << "\", is not valid name" << std::endl;

            this->broadcast(returnReport.dump());
        }
    }
    else if (command == "START_SEQUENCE") {
        std::string desiredSequence;
        try {
            desiredSequence = message["sequence"];
        }
        catch(json::exception&){
            this->reportMessage("Bad json read on sequence start, 'sequence' tag not found");
            return;
        }

        try{
            this->myECS->acceptStartSequence(stringToSequence(desiredSequence));
        }
        catch (std::invalid_argument&){
            std::string msg;
            msg += "Requested sequence: [";
            msg += desiredSequence + "] ";
            msg += "is not a valid sequence";

            this->reportMessage(msg);
        }
    }
    else if (command == "ABORT_SEQUENCE") {
        this->myECS->acceptAbortSequence();
    }
    else {
        this->reportMessage("Unsupported command tag!");
    }
}

void SocketLogger::reportState(ECSState &curState) {
    json state;
    state["command"] = "STATE_TRANSITION";
    state["newState"] = curState.getName();

    this->outgoingMessageQueue.push(state.dump(4));
}

void SocketLogger::reportRedlines(std::vector<RedlineResponsePacket> redlineReports) {
    json report;
    report["command"] = "REDLINE_REPORT";

    json inner_dict;
    for (auto& packet: redlineReports){

        json curReport;

        switch(packet.response){
            case ECSRedLineResponse::ABORT:
                curReport["report"] = "ABORT";
                break;
            case ECSRedLineResponse::WARN:
                curReport["report"] = "WARN";
                break;
            case ECSRedLineResponse::SAFE:
                curReport["report"] = "SAFE";
                break;
        }

        inner_dict[packet.redlineName] = curReport;
    }

    report["redlines"] = inner_dict;

    this->outgoingMessageQueue.push(report.dump(4));
}

void SocketLogger::reportSensorData(SensorData data, bool isCalibrated) {
    json report;
    report["command"] = "DATA";
    report["timeStamp"] = getTimeStamp();

    if (isCalibrated) {
        report["calibrated?"] = "true";
    }
    else {
        report["calibrated?"] = "false";
    }

    json dataReport;
    dataReport["valves"] = ::getValveReport(data);
    dataReport["pressureSensors"] = ::getPressureReport(data);
    dataReport["loadCellSensors"] = ::getLoadCellReport(data);
    dataReport["tempSensors"] = ::getTemperatureReport(data);

    report["data"] = dataReport;

    this->outgoingMessageQueue.push(report.dump(4));
}

void SocketLogger::reportMessage(std::string msg) {
    json report;
    report["statement"] = msg;
    report["command"] = "MESSAGE";
    this->outgoingMessageQueue.push(report.dump(4));
}

void SocketLogger::processIncoming() {
    while (this->incomingMessageQueue.size() > 0) {
        // Processing messages from the ground system
        auto message = this->incomingMessageQueue.front();
        this->incomingMessageQueue.pop();

        this->executeMessage(message);
    }
}

void SocketLogger::processOutgoing() {
    while (this->outgoingMessageQueue.size() > 0) {
        auto message = this->outgoingMessageQueue.front();
        this->outgoingMessageQueue.pop();

        //TODO: log as well
        this->broadcast(message);
    }
}

void SocketLogger::acceptECS(IECS &ecs) {
    this->myECS = &ecs;
}


