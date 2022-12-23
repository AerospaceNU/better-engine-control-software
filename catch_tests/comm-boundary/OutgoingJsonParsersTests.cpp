//
// Created by kevin on 12/23/2022.
//

#include "../catch.hpp"
#include "comm-boundary/OutgoingJsonParsers.h"

TEST_CASE("JSON parse for ECSState back to operator", "[unit]"){
    ECSState state{"Boogle", {}, CommandData{}, CommandData{}};

    json expectedOutput = {
            {"command", "STATE_TRANSITION"},
            {"newState", "Boogle"}
    };

    json result = parseECSState(state);
    expectedOutput["timeStamp"] = result.at("timeStamp");

    REQUIRE(parseECSState(state) == expectedOutput);
}

TEST_CASE("JSON parse for redlines back to operator", "[unit]"){
    std::vector<RedlineResponsePacket> resultList = {RedlineResponsePacket{ECSRedLineResponse::SAFE, "line1"},
                                                     RedlineResponsePacket{ECSRedLineResponse::ABORT, "line2"},
                                                     RedlineResponsePacket{ECSRedLineResponse::WARN, "line3"}};

    /*
     * The json library will read
     * {"report, "SAFE"}
     *
     * as a list, not a map
     *
     * So we have to set up the maps manually
     */
    json firstPair;
    firstPair["report"] = "SAFE";

    json secondPair;
    secondPair["report"] = "ABORT";

    json thirdPair;
    thirdPair["report"] = "WARN";
    //sanity check
    REQUIRE(thirdPair.at("report") == "WARN");

    json expectedOutput = {
            {"command", "REDLINE_REPORT"},
            {"redlines", {
                    {"line1",
                     firstPair},
                    {"line2",
                     secondPair},
                    {"line3",
                     thirdPair}
            }}
    };

    json result = parseRedlines(resultList);
    expectedOutput["timeStamp"] = result.at("timeStamp");

    REQUIRE(result == expectedOutput);
}

TEST_CASE("JSON parse for SensorData back to operator", "[unit]"){
    /*
     * This one is kept vague and abstract to avoid needing to
     * repair it after every SensorData change
     */
    SensorData data;

    SECTION("Checking uncalibrated"){
        json result = parseSensorData(data, false);

        REQUIRE(result.at("command") == "DATA");
        REQUIRE(result.at("calibrated?") == "false");
        REQUIRE(result.contains("timeStamp"));



        json dataDict = result.at("data");

        SECTION("Checking loadCell section of json dict"){
            json loadCellDict = dataDict.at("loadCellSensors");

            for(auto& sensorDict: loadCellDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking pressureSensors section of json dict"){
            json pressSensDict = dataDict.at("pressureSensors");

            for(auto& sensorDict: pressSensDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking tempSensors section of json dict"){
            json tempSensDict = dataDict.at("tempSensors");

            for(auto& sensorDict: tempSensDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking valves section of json dict"){
            json valveDict = dataDict.at("valves");

            for(auto& sensorDict: valveDict){
                REQUIRE(sensorDict.contains("valveState"));
            }
        }
    }

    SECTION("Checking calibrated"){
        json result = parseSensorData(data, true);

        REQUIRE(result.at("command") == "DATA");
        REQUIRE(result.at("calibrated?") == "true");
        REQUIRE(result.contains("timeStamp"));


        json dataDict = result.at("data");

        SECTION("Checking loadCell section of json dict"){
            json loadCellDict = dataDict.at("loadCellSensors");

            for(auto& sensorDict: loadCellDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking pressureSensors section of json dict"){
            json pressSensDict = dataDict.at("pressureSensors");

            for(auto& sensorDict: pressSensDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking tempSensors section of json dict"){
            json tempSensDict = dataDict.at("tempSensors");

            for(auto& sensorDict: tempSensDict){
                REQUIRE(sensorDict.contains("sensorReading"));
                REQUIRE(sensorDict.contains("unit"));
            }
        }

        SECTION("Checking valves section of json dict"){
            json valveDict = dataDict.at("valves");

            for(auto& sensorDict: valveDict){
                REQUIRE(sensorDict.contains("valveState"));
            }
        }
    }
}

TEST_CASE("JSON parse for general message back to operator", "[unit]"){
    std::string msg = "Hi everyone";

    json expectedOutput = {
            {"command", "MESSAGE"},
            {"statement", "Hi everyone"}
    };

    json result = parseMessage(msg);
    expectedOutput["timeStamp"] = result.at("timeStamp");
    REQUIRE(parseMessage(msg) == expectedOutput);
}
