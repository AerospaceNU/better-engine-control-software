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
//     std::function<int(const SensorData &)> loxTankDucerSelector = [](
//             const SensorData &data) { return data.orificeDownstreamDucer; };
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::OPEN,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED,
                                              ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FILLRedlines = make_vector_unique<IRedline>(
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FILLEDConfig = CommandData(ECSValveState::OPEN,
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
    std::vector<std::unique_ptr<IRedline>> KERO_FILLEDRedlines = make_vector_unique<IRedline>(
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
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

    CommandData LOX_FILLConfig = CommandData(ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
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
    std::vector<std::unique_ptr<IRedline>> LOX_FILLEDRedlines = make_vector_unique<IRedline>(
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::OPEN,
                                                    ECSValveState::CLOSED,
                                                    ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_FLOW_closedRedlines = make_vector_unique<IRedline>(
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::OPEN),
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FLOW_closedRedlines = make_vector_unique<IRedline>(
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
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
        //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_TANK_PURGERedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_TANK_PURGERedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
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
    std::vector<std::unique_ptr<IRedline>> ALL_TANK_PURGERedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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

   CommandData LOX_FLUTTER_ClosedConfig = CommandData(ECSValveState::CLOSED,
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
    std::vector<std::unique_ptr<IRedline>> LOX_FLUTTER_ClosedRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
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

    CommandData LOX_FLUTTER_OpenConfig = CommandData(ECSValveState::OPEN,
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
    std::vector<std::unique_ptr<IRedline>> LOX_FLUTTER_OpenRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
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

    CommandData KERO_FLUTTER_OpenConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FLUTTER_OpenRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_FLUTTER_ClosedConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_FLUTTER_ClosedRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KERO_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KERO_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::OPEN,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED);
        std::vector<std::unique_ptr<IRedline>> LOX_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            //     RedlineFactory("orificeDownstreamDucer", loxTankDucerSelector, 0, 15),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxDrip", loxDripSelector, ECSValveState::CLOSED),
            RedlineFactory("kerDrip", kerDripSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerOrifice", kerOrificeSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));
}
const ECSState ONLINE_SAFE_D = ECSState("ONLINE_SAFE_D", std::move(ONLINE_SAFE_DRedlines), ONLINE_SAFE_DConfig,
                                        ONLINE_SAFE_DConfig);

const ECSState KERO_FILL = ECSState("KERO_FILL", std::move(KERO_FILLRedlines), KERO_FILLConfig, KERO_FILLConfig);

const ECSState KERO_POST_FILL = ECSState("KERO_FILLED", std::move(KERO_FILLEDRedlines), KERO_FILLEDConfig,
                                      KERO_FILLEDConfig);

const ECSState LOX_FILL = ECSState("LOX_FILL", std::move(LOX_FILLRedlines), LOX_FILLConfig, LOX_FILLConfig);

const ECSState LOX_POST_FILL = ECSState("LOX_FILLED", std::move(LOX_FILLEDRedlines), LOX_FILLEDConfig, LOX_FILLEDConfig);

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

const ECSState LOX_TANK_PURGE = ECSState("LOX_TANK_PURGE", std::move(LOX_TANK_PURGERedlines), LOX_TANK_PURGEConfig,
                                          LOX_TANK_PURGEConfig);

const ECSState KERO_TANK_PURGE = ECSState("KERO_TANK_PURGE", std::move(KERO_TANK_PURGERedlines), KERO_TANK_PURGEConfig,
                                           KERO_TANK_PURGEConfig);

const ECSState ALL_TANK_PURGE = ECSState("ALL_TANK_PURGE", std::move(ALL_TANK_PURGERedlines), ALL_TANK_PURGEConfig,
                                         ALL_TANK_PURGEConfig);

const ECSState LOX_FLUTTER_closed = ECSState("LOX_FLUTTER_Closed", std::move(LOX_FLUTTER_ClosedRedlines),
                                              LOX_FLUTTER_ClosedConfig, LOX_FLUTTER_ClosedConfig);

const ECSState LOX_FLUTTER_open = ECSState("LOX_FLUTTER_Open", std::move(LOX_FLUTTER_OpenRedlines),
                                            LOX_FLUTTER_OpenConfig, LOX_FLUTTER_OpenConfig);

const ECSState KERO_FLUTTER_open = ECSState("KERO_FLUTTER_Open", std::move(KERO_FLUTTER_OpenRedlines),
                                              KERO_FLUTTER_OpenConfig, KERO_FLUTTER_OpenConfig);

const ECSState KERO_FLUTTER_closed = ECSState("KERO_FLUTTER_Closed", std::move(KERO_FLUTTER_ClosedRedlines),
                                               KERO_FLUTTER_ClosedConfig, KERO_FLUTTER_ClosedConfig);

const ECSState KERO_PRESSURIZING = ECSState("KERO_PRESSURIZING", std::move(KERO_PRESSURIZINGRedlines),
                                   KERO_PRESSURIZINGConfig, KERO_PRESSURIZINGConfig);

const ECSState LOX_PRESSURIZING = ECSState("LOX_PRESSURIZING", std::move(LOX_PRESSURIZINGRedlines),
                                   LOX_PRESSURIZINGConfig, LOX_PRESSURIZINGConfig);



/**
 * From here on, this part is not auto-generated
*/
RelatTimedSequence ALL_FLOW = RelatTimedSequence({{0, ALL_FLOW_closed}, {500, ALL_FLOW_open}});
RelatTimedSequence KERO_FLOW = RelatTimedSequence({{0, KERO_FLOW_closed}, {1000, KERO_FLOW_open}});
RelatTimedSequence FIRE_3_SECONDS = RelatTimedSequence({{0, ALL_FLOW_closed}, {500, ALL_FLOW_open}, {3500, ONLINE_SAFE_D}});
RelatTimedSequence FIRE_5_SECONDS = RelatTimedSequence({{0, ALL_FLOW_closed}, {500, ALL_FLOW_open}, {5500, ONLINE_SAFE_D}});
RelatTimedSequence KERO_FLUTTER_3_SECONDS_SEQUENCE = RelatTimedSequence({{0, KERO_PRESSURIZING}, {500, KERO_FLUTTER_closed}, {1000, KERO_FLUTTER_open}, {4000, KERO_FLUTTER_closed}, {4500, KERO_PRESSURIZING}});
RelatTimedSequence LOX_FLUTTER_3_SECONDS_SEQUENCE = RelatTimedSequence({{0, LOX_PRESSURIZING}, {500, LOX_FLUTTER_closed}, {1000, LOX_FLUTTER_open}, {4000, LOX_FLUTTER_closed}, {4500, LOX_PRESSURIZING}});
