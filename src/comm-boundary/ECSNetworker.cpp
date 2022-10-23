#include "ECSNetworker.h"
#include "ParsingHelpers.h"
#include <thread>

// anonymous namespace for helper functions
namespace{
    /**
     * Helper function, parses valves in sensor data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    json getValveReport(SensorData &data) {
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
            curReport["valveState"] = valveStateToString(data.loxDrip);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxDrip"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerDrip);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerDrip"] = curReport;
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
    json getPressureReport(SensorData &data) {
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
            curReport["sensorReading"] = data.pnematicsDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["pneumaticDucer"] = curReport;
        }

        return pressureReport;
    }

    /**
     * Helper function, parses load cell sensors in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    json getLoadCellReport(SensorData &data) {
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
    json getTemperatureReport(SensorData &data) {
        json tempReport;

        {
            json curReport;
            curReport["sensorReading"] = data.loxTank1;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["tank1Thermo"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxTank2;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["tank2Thermo"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxTank3;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["tank3Thermo"] = curReport;
        }

        {
            json curReport;
            //curReport["label"] = "loxDripLine";
            curReport["sensorReading"] = data.loxDripLine;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            //TODO: recheck sensor names, cuz wtf is this
            tempReport["manifoldInletThermo"] = curReport;
        }

        {
            json curReport;
            //curReport["label"] = "outsideThroat";
            curReport["sensorReading"] = data.outsideThroat;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["manifoldOutletThermo"] = curReport;
        }

        {
            json curReport;
            //curReport["label"] = "nozzle";
            curReport["sensorReading"] = data.nozzle;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            tempReport["nozzle"] = curReport;
        }

        return tempReport;
    }
}


ECSNetworker::ECSNetworker(std::queue<json> temp) :
        incomingMessageQueue(std::move(temp)),
        myECS(nullptr),
        webSocketServer{},
        connections{}
{
    serverThread = std::thread(&ECSNetworker::startServer, this);
    serverThread.detach();
}

void ECSNetworker::startServer() {
	this->webSocketServer.set_message_handler(websocketpp::lib::bind(&ECSNetworker::onMessage, this,
		websocketpp::lib::placeholders::_1,
		websocketpp::lib::placeholders::_2));

	this->webSocketServer.set_access_channels(websocketpp::log::alevel::none);
	this->webSocketServer.set_error_channels(websocketpp::log::elevel::all);

	this->webSocketServer.set_open_handler(bind(&ECSNetworker::onOpen, this, websocketpp::lib::placeholders::_1));
	this->webSocketServer.set_close_handler(bind(&ECSNetworker::onClose, this, websocketpp::lib::placeholders::_1));

    this->webSocketServer.set_reuse_addr(true);

	this->webSocketServer.init_asio();
	this->webSocketServer.listen(9002);
	this->webSocketServer.start_accept();

	this->webSocketServer.run();
}

void ECSNetworker::onMessage(websocketpp::connection_hdl handle, server::message_ptr serializedMessage) {
	std::string messageString = serializedMessage->get_payload();
	json messageJson = json::parse(messageString);

	incomingMessageQueue.push(messageJson);
}

void ECSNetworker::executeMessage(json message) {
    std::string command; //ugly initialization outside for scope, can refactor?
    try {
        command = message["command"];
    }
    catch(json::exception& e){
        //TODO: send message when exception is thrown
        return;
    }

	//messageType command = stringToMessageTypeMap[message["command"]];

	if (command == "BEGIN") {
		; // begin sending "DATA" messages
	}
	else if (command == "FINISH") {
		; // send "STOPPED" message
	}
	else if (command == "SETUP") {
		; // send "READY" message
	}
	else if (command == "SET_ACTIVE_ELEMENTS") {
        try {
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

            newOverrideCom.loxDrip = stringToValveState(overrideElements["loxDrip"]);
            newOverrideCom.kerDrip = stringToValveState(overrideElements["kerDrip"]);

            this->myECS->acceptOverrideCommand(newOverrideCom);
        }
        catch (std::invalid_argument& e) {
            //TODO: send message when exception is thrown
        }
        catch (json::exception& e) {
            //TODO: send message when exception is thrown
        }
	}

	else if (command == "SET_STATE") { // send "STATE_TRANSITION" message
        std::string newStateCommand = message["newState"];

	    std::cout << "Entering set state in networker " << newStateCommand << std::endl;

        try {
            this->myECS->acceptStateTransition(stringToECSState(newStateCommand));
        }
        catch (...){ //TODO, which exception to throw and catch
            json returnReport;
            returnReport["command"] = "STATE_TRANSITION_ERROR";
            returnReport["timeStamp"] = getTimeStamp();
            returnReport["failedTransition"] = newStateCommand;

            std::cout << "Failed new state change to \"" << newStateCommand << "\", is not valid name" << std::endl;

            this->broadcast(returnReport.dump());
        }
    }

	else if (command == "DATA") { // CANNOT AND SHOULD NOT RECIEVE THIS COMMAND
		message["data"];
	}
	else if (command == "READY") { // CANNOT AND SHOULD NOT RECIEVE THIS COMMAND
		;
	}
	else if (command == "STATE_TRANSITION") { // CANNOT AND SHOULD NOT RECIEVE THIS COMMAND
		message["transition"];
	}
	else if (command == "STOPPED") { // CANNOT AND SHOULD NOT RECIEVE THIS COMMAND
		message["statistics"];
	}

    else if (command == "START_SEQUENCE") {
        std::string desiredSequence;

        try {
            this->myECS->acceptSequence(stringToSequence(desiredSequence));
        }
        catch (...){ //TODO, which exception to throw and catch
            std::cout << "Requested sequence not defined" << std::endl;
            //TODO: send some message back to operator
        }
    }

    else if (command == "ABORT_SEQUENCE") {
        //TODO
        //this->myECS->abortSequence();
    }
}

void ECSNetworker::broadcast(std::string message) {
	for (auto it : this->connections) {
		this->webSocketServer.send(it, message, websocketpp::frame::opcode::text);
	}
}

void ECSNetworker::reportState(ECSState &curState) {
    json state;
    state["command"] = "STATE_TRANSITION";
    state["newState"] = curState.name;
    this->broadcast(state.dump(4));
}

void ECSNetworker::reportRedlines(std::pair<ECSRedLineResponse, const IRedline *> redlinePair) {
    json report;
    report["command"] = "REDLINE_REPORT";

    ECSRedLineResponse res = redlinePair.first;
    const IRedline* redline = redlinePair.second;

    switch(res){
        case ECSRedLineResponse::ABORT:
            report["report"] = "ABORT";
            break;
        case ECSRedLineResponse::WARN:
            report["report"] = "WARN";
            break;
        case ECSRedLineResponse::SAFE:
            report["report"] = "SAFE";
            break;
    }

    report["redlineName"] = redline->getName();

    this->broadcast(report.dump(4));
}

void ECSNetworker::reportSensorData(SensorData data, bool isCalibrated) {
    //std::cout << "Receivec data!";
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
    //dataReport["ECSState"] = "bruh";
    dataReport["valves"] = ::getValveReport(data);
    dataReport["pressureSensors"] = ::getPressureReport(data);
    dataReport["loadCellSensors"] = ::getLoadCellReport(data);
    dataReport["tempSensors"] = ::getTemperatureReport(data);

    report["data"] = dataReport;

    //std::cout << report.dump(4) << std::endl;
    this->broadcast(report.dump(4));
}

void ECSNetworker::reportMessage(std::string msg) {
    json report;
    report["statement"] = msg;
    report["command"] = "MESSAGE";
    this->broadcast(report.dump(4));
}

void ECSNetworker::run() {
    while (this->incomingMessageQueue.size() > 0) {
        // Processing messages from the ground system
        json message = this->incomingMessageQueue.front();
        this->incomingMessageQueue.pop();

        // wtf is this????????
        // std::cout << message.dump(4) << std::endl;

        this->executeMessage(message);
    }
}


void ECSNetworker::acceptECS(IECS &ecs) {
    this->myECS = &ecs;
}


