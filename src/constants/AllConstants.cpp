//
// Created by kevin on 5/27/2022.
//

#include "watchdog/redlines/ValveRedline.h"
#include "watchdog/redlines/IntWithinRedline.h"
#include "AllECSStates.h"
#include "AllSequences.h"

/**
 * NOTE: ALL THESE CONSTANTS MUST BE CONSTRUCTED IN THE SAME FILE, THIS ONE
 *
 * It makes sense that we would want to do something like
 *
 * AllECSStatesConstruction.cpp
 * AllSequencesConstruction.cpp
 *
 * keeping it separate bc the header files are separate.
 *
 * But, C++ doesn't define what order files are compiled
 *
 * So if it tries to compile the sequences (which need ecsstates) first before the
 * actual ecsstates constructions, we will be fucked
 */

/**
 * Everything below down to the sequences construction is
 * generated automatically
 */



namespace {
    std::function<int(const SensorData &)> loxTankDucerSelector = [](
            const SensorData &data) { return data.orificeDownstreamDucer; };
    std::function<ECSValveState(const SensorData &)> loxVentSelector = [](
            const SensorData &data) { return data.loxVent; };
    std::function<ECSValveState(const SensorData &)> kerVentSelector = [](
            const SensorData &data) { return data.kerVent; };
    std::function<ECSValveState(const SensorData &)> loxDripSelector = [](
            const SensorData &data) { return data.loxDrip; };
    std::function<ECSValveState(const SensorData &)> kerDripSelector = [](
            const SensorData &data) { return data.kerDrip; };
    std::function<ECSValveState(const SensorData &)> loxPressurantSelector = [](
            const SensorData &data) { return data.loxPressurant; };
    std::function<ECSValveState(const SensorData &)> kerPressurantSelector = [](
            const SensorData &data) { return data.kerPressurant; };
    std::function<ECSValveState(const SensorData &)> loxFlowSelector = [](
            const SensorData &data) { return data.loxFlow; };
    std::function<ECSValveState(const SensorData &)> kerFlowSelector = [](
            const SensorData &data) { return data.kerFlow; };
    std::function<ECSValveState(const SensorData &)> kerOrificeSelector = [](
            const SensorData &data) { return data.kerOrifice; };
    std::function<ECSValveState(const SensorData &)> loxPurgeSelector = [](
            const SensorData &data) { return data.loxPurge; };
    std::function<ECSValveState(const SensorData &)> kerPurgeSelector = [](
            const SensorData &data) { return data.kerPurge; };

    CommandData ONLINE_SAFE_DConfig = CommandData(ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ONLINE_SAFE_DRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::OPEN),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FILLConfig = CommandData(ECSValveState::OPEN,
                                              ECSValveState::OPEN,
                                              ECSValveState::OPEN,
                                              ECSValveState::OPEN,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::OPEN),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FILLEDConfig = CommandData(ECSValveState::OPEN,
                                                ECSValveState::OPEN,
                                                ECSValveState::OPEN,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FILLEDRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::OPEN),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FILLConfig = CommandData(ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::OPEN),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FILLEDConfig = CommandData(ECSValveState::OPEN,
                                               ECSValveState::OPEN,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED,
                                               ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FILLEDRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_READY_TO_PRESSURIZEConfig = CommandData(ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_READY_TO_PRESSURIZERedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_FLOW_closedConfig = CommandData(ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_FLOW_closedRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_FLOW_openConfig = CommandData(ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_FLOW_openRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FLOW_closedConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FLOW_closedRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FLOW_openConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FLOW_openRedlines = make_vector_unique<IRedline>(
            RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));
}
const ECSState ONLINE_SAFE_D = ECSState("ONLINE_SAFE_D", std::move(ONLINE_SAFE_DRedlines), ONLINE_SAFE_DConfig,
                                        ONLINE_SAFE_DConfig);

const ECSState KERO_FILL = ECSState("KERO_FILL", std::move(KERO_FILLRedlines), KERO_FILLConfig, KERO_FILLConfig);

const ECSState KERO_FILLED = ECSState("KERO_FILLED", std::move(KERO_FILLEDRedlines), KERO_FILLEDConfig,
                                      KERO_FILLEDConfig);

const ECSState LOX_FILL = ECSState("LOX_FILL", std::move(LOX_FILLRedlines), LOX_FILLConfig, LOX_FILLConfig);

const ECSState LOX_FILLED = ECSState("LOX_FILLED", std::move(LOX_FILLEDRedlines), LOX_FILLEDConfig, LOX_FILLEDConfig);

const ECSState ALL_READY_TO_PRESSURIZE = ECSState("ALL_READY_TO_PRESSURIZE", std::move(ALL_READY_TO_PRESSURIZERedlines),
                                                  ALL_READY_TO_PRESSURIZEConfig, ALL_READY_TO_PRESSURIZEConfig);

const ECSState ALL_PRESSURIZING = ECSState("ALL_PRESSURIZING", std::move(ALL_PRESSURIZINGRedlines),
                                           ALL_PRESSURIZINGConfig, ALL_PRESSURIZINGConfig);

const ECSState ALL_FLOW_closed = ECSState("ALL_FLOW_closed", std::move(ALL_FLOW_closedRedlines), ALL_FLOW_closedConfig,
                                          ALL_FLOW_closedConfig);

const ECSState ALL_FLOW_open = ECSState("ALL_FLOW_open", std::move(ALL_FLOW_openRedlines), ALL_FLOW_openConfig,
                                        ALL_FLOW_openConfig);

const ECSState KERO_FLOW_closed = ECSState("KERO_FLOW_closed", std::move(KERO_FLOW_closedRedlines),
                                           KERO_FLOW_closedConfig, KERO_FLOW_closedConfig);

const ECSState KERO_FLOW_open = ECSState("KERO_FLOW_open", std::move(KERO_FLOW_openRedlines), KERO_FLOW_openConfig,
                                         KERO_FLOW_openConfig);



/**
 * From here on, this part is not auto-generated
*/
RelatTimedSequence ALL_FLOW = RelatTimedSequence({{0, ALL_FLOW_closed}, {500, ALL_FLOW_open}});
RelatTimedSequence KERO_FLOW = RelatTimedSequence({{0, KERO_FLOW_closed}, {1000, KERO_FLOW_open}});
