#ifndef ENGINECONTROLSYSTEM_NETWORKER_H
#define ENGINECONTROLSYSTEM_NETWORKER_H

#include "ecs/IECS.h"
#include "ICommBoundary.h"

#include <set>
#include <json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "utils/ThreadQueue.h"

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> conList;

/**
 * An implementation of ICommBoundary using json and websockets.
 *
 * This object is a place holder until we create a replacement
 *
 * This object is thread-safe
 */
class ECSNetworker: public ICommBoundary {
public:
	explicit ECSNetworker();

    /**
     * Processing incoming message queue from server.
     * Dispatches messages and sends to stored IECS object
     */
    void run();

    void reportState(ECSState& curState) override;
    void reportRedlines(std::pair<ECSRedLineResponse, const IRedline*>) override;
    void reportSensorData(SensorData data) override;
    void reportMessage(std::string msg) override;

    void acceptECS(IECS& ecs);

	//bool dead = false;

private:
    // receives web socket message and adds to stack
    void onMessage(websocketpp::connection_hdl handle, server::message_ptr message);

    void onOpen(websocketpp::connection_hdl hdl) {
        this->connections.insert(hdl);
    }

    void onClose(websocketpp::connection_hdl hdl) {
        this->connections.erase(hdl);
    }

    /**
     * Read and parses command, and dispatches to IECS if appropriate
     * @param message json representing the message
     */
    void executeMessage(json message);

    /**
     * Helper function, sends message to all operators
     * @param message message.
     */
    void broadcast(std::string message);

    //intialization of webSocketServer, called in constructor in anotehr thread
	void startServer();

//    /**
//     * Helper function, parses valves in sensor data into json for sending back
//     * @param data sensor data to read
//     * @return json object
//     */
//    json getValveReport(SensorData& data);
//
//    /**
//     * Helper function, parses pressure sensors in data into json for sending back
//     * @param data sensor data to read
//     * @return json object
//     */
//    json getPressureReport(SensorData& data);
//
//    /**
//     * Helper function, parses load cell sensors in data into json for sending back
//     * @param data sensor data to read
//     * @return json object
//     */
//    json getLoadCellReport(SensorData& data);
//
//    /**
//     * Helper function, parses thermocouples in data into json for sending back
//     * @param data sensor data to read
//     * @return json object
//     */
//    json getTemperatureReport(SensorData& data);

    ThreadQueue<json> incomingMessageQueue;
    IECS* myECS;

	server webSocketServer;
	conList connections;

    std::thread serverThread;
};

#endif // ENGINECONTROLSYSTEM_NETWORKER_H