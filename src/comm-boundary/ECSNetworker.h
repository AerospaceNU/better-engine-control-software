//
// Created by Noah Haggerty on 4/1/2021.
//

#ifndef ENGINECONTROLSYSTEM_NETWORKER_H
#define ENGINECONTROLSYSTEM_NETWORKER_H

#include "ParsingHelpers.h"

#include "ecs/IECS.h"
#include "ICommBoundary.h"

#include "sequencer/ISequence.h"
#include <set>
#include <json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "utils-and-constants/ThreadQueue.h"
#include <thread>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> conList;

class ECSNetworker: public ICommBoundary {
public:
	explicit ECSNetworker();

    void run();

    void reportState(ECSState& curState) override;
    void reportRedlines(std::tuple<ECSRedLineResponse, IRedline*>) override;
    void reportSensorData(SensorData data) override;
    void reportMessage(std::string msg) override;

    void acceptECS(IECS& ecs) override;

	// may not be own method, checks if message from web socket contains all expected info in
	// expected format
	// bool isParsable();


    // gives ECS control for tasks that require continuity (like sequences)
    //void stepECS();

	bool dead = false;

private:
    // receives web socket message and adds to stack
    void onMessage(websocketpp::connection_hdl handle, server::message_ptr message);

    void onOpen(websocketpp::connection_hdl hdl) {
        this->connections.insert(hdl);
    }

    void onClose(websocketpp::connection_hdl hdl) {
        this->connections.erase(hdl);
    }

    void executeMessage(json message);

    void broadcast(std::string message);

    //intialization of webSocketServer, called in constructor in anotehr thread
	void startServer();

    json getValveReport(SensorData& data);

    json getPressureReport(SensorData& data);

    json getLoadCellReport(SensorData& data);

    json getTemperatureReport(SensorData& data);

    ThreadQueue<json> incomingMessageQueue;
    IECS* myECS;

	server webSocketServer;
	conList connections;

    std::thread serverThread;
};

#endif // ENGINECONTROLSYSTEM_NETWORKER_H