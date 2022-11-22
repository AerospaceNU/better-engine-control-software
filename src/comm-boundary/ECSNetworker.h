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
 * This object is responsible for both connections from operator -> ECS and
 * ECS -> operator
 *  - NOTE: I tried to break it up into separate objects, but a major difficulty is in the websockets
 *  Only one server can be connected to a given port, so we can't break it into two separate components
 *  sharing the same port
 *
 *
 * This object is currently not thread-safe
 */
class ECSNetworker: public ICommBoundary {
public:
	explicit ECSNetworker(std::queue<json> queue = {});

    ECSNetworker(const ECSNetworker& other) = delete;

    ECSNetworker(ECSNetworker&& other) = delete;

    ECSNetworker& operator=(ECSNetworker&& other) = delete;

    ~ECSNetworker();



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
    void reportRedlines(std::pair<ECSRedLineResponse, const IRedline*>) override;
    void reportSensorData(SensorData data, bool isCalibrated) override;
    void reportMessage(std::string msg) override;

    void acceptECS(IECS& ecs);

private:
    // receives web socket message and adds to queue
    void onMessage(websocketpp::connection_hdl handle, server::message_ptr message);

    void onOpen(websocketpp::connection_hdl hdl);

    void onClose(websocketpp::connection_hdl hdl);

    /**
     * Read and parses command, and dispatches to IECS if appropriate
     * @param message json representing the message
     */
    void executeMessage(json message);

    /**
     * Helper function, sends message to all operators
     * @param message message.
     */
    void broadcast(const std::string& message);

    //intialization of webSocketServer, called in constructor in anotehr thread

    ThreadQueue<json> incomingMessageQueue;
    ThreadQueue<std::string> outgoingMessageQueue;
    IECS* myECS;

	server webSocketServer;
	conList connections;

    std::thread serverThread;
};

#endif // ENGINECONTROLSYSTEM_NETWORKER_H