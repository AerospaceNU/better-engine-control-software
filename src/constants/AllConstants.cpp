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
            const SensorData &data) { return data.loxTankDucer; };
    std::function<int(const SensorData &)> kerTankDucerSelector = [](
            const SensorData &data) { return data.kerTankDucer; };
    std::function<int(const SensorData &)> purgeDucerSelector = [](const SensorData &data) { return data.purgeDucer; };
    std::function<int(const SensorData &)> loxInletDucerSelector = [](
            const SensorData &data) { return data.loxInletDucer; };
    std::function<int(const SensorData &)> kerInletDucerSelector = [](
            const SensorData &data) { return data.kerInletDucer; };
    std::function<int(const SensorData &)> kerPintleDucerSelector = [](
            const SensorData &data) { return data.kerPintleDucer; };
    std::function<int(const SensorData &)> loxVenturiSelector = [](const SensorData &data) { return data.loxVenturi; };
    std::function<int(const SensorData &)> kerVenturiSelector = [](const SensorData &data) { return data.kerVenturi; };
    std::function<int(const SensorData &)> loadCellSelector = [](const SensorData &data) { return data.loadCell; };
    std::function<int(const SensorData &)> pneumaticDucerSelector = [](
            const SensorData &data) { return data.pneumaticDucer; };
    std::function<int(const SensorData &)> loxRegDucerSelector = [](
            const SensorData &data) { return data.loxRegDucer; };
    std::function<int(const SensorData &)> kerRegDucerSelector = [](
            const SensorData &data) { return data.kerRegDucer; };
    std::function<int(const SensorData &)> n2pressDucerSelector = [](
            const SensorData &data) { return data.n2pressDucer; };
    std::function<int(const SensorData &)> loxTankTCSelector = [](const SensorData &data) { return data.loxTankTC; };
    std::function<int(const SensorData &)> kerInletTCSelector = [](const SensorData &data) { return data.kerInletTC; };
    std::function<int(const SensorData &)> kerOutletTCSelector = [](
            const SensorData &data) { return data.kerOutletTC; };
    std::function<int(const SensorData &)> miscTCSelector = [](const SensorData &data) { return data.miscTC; };
    std::function<ECSValveState(const SensorData &)> loxVentSelector = [](
            const SensorData &data) { return data.loxVent; };
    std::function<ECSValveState(const SensorData &)> loxPressurantSelector = [](
            const SensorData &data) { return data.loxPressurant; };
    std::function<ECSValveState(const SensorData &)> loxFlowSelector = [](
            const SensorData &data) { return data.loxFlow; };
    std::function<ECSValveState(const SensorData &)> loxPurgeSelector = [](
            const SensorData &data) { return data.loxPurge; };
    std::function<ECSValveState(const SensorData &)> kerVentSelector = [](
            const SensorData &data) { return data.kerVent; };
    std::function<ECSValveState(const SensorData &)> kerPressurantSelector = [](
            const SensorData &data) { return data.kerPressurant; };
    std::function<ECSValveState(const SensorData &)> kerFlowSelector = [](
            const SensorData &data) { return data.kerFlow; };
    std::function<ECSValveState(const SensorData &)> kerPurgeSelector = [](
            const SensorData &data) { return data.kerPurge; };

    CommandData ONLINE_SAFEConfig = CommandData(ECSValveState::OPEN,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::OPEN,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED,
                                                ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ONLINE_SAFERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_FILLConfig = CommandData(ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 30),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 30),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_POST_FILLConfig = CommandData(ECSValveState::OPEN,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_POST_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 30),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 30),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FILLConfig = CommandData(ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 20),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_POST_FILLConfig = CommandData(ECSValveState::OPEN,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_POST_FILLRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_READY_TO_PRESSURIZEConfig = CommandData(ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED,
                                                            ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_READY_TO_PRESSURIZERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 200),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 30),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_PRESSURIZINGConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_PRESSURIZINGRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 30),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_FLOWConfig = CommandData(ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_FLOWRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 550, 800),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 550, 900),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 550, 900),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 150),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 150),
            RedlineFactory("loadCell", loadCellSelector, 650, 850),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FLOWConfig = CommandData(ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FLOWRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 550, 800),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 50),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 150),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_FLOWConfig = CommandData(ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::CLOSED,
                                             ECSValveState::OPEN,
                                             ECSValveState::OPEN,
                                             ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_FLOWRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 50),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 550, 900),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 550, 900),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 150),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_GRAV_FLOWConfig = CommandData(ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::OPEN,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED,
                                                  ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_GRAV_FLOWRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 200),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 50),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 50),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 80),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_ENGINE_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_ENGINE_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 350),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 50),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 50),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_ENGINE_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN);
    std::vector<std::unique_ptr<IRedline>> KER_ENGINE_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 50),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 350),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 350),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::OPEN));

    CommandData ALL_ENGINE_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN);
    std::vector<std::unique_ptr<IRedline>> ALL_ENGINE_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 350),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 350),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 350),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 0, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 0, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::OPEN));

    CommandData PRESSURIZED_ALL_ENGINE_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                                 ECSValveState::OPEN,
                                                                 ECSValveState::CLOSED,
                                                                 ECSValveState::OPEN,
                                                                 ECSValveState::CLOSED,
                                                                 ECSValveState::OPEN,
                                                                 ECSValveState::CLOSED,
                                                                 ECSValveState::OPEN);
    std::vector<std::unique_ptr<IRedline>> PRESSURIZED_ALL_ENGINE_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 350),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 350),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 350),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::OPEN),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::OPEN));

    CommandData LOX_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_TANK_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 350),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 50),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 50),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 150),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 150),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_TANK_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 50),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 350),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 350),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 150),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 150),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData ALL_TANK_PURGEConfig = CommandData(ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::CLOSED,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::OPEN,
                                                   ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> ALL_TANK_PURGERedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 350),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 350),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 350),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 150),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 150),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::OPEN),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::OPEN),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FLUTTER_CLOSEDConfig = CommandData(ECSValveState::CLOSED,
                                                       ECSValveState::OPEN,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FLUTTER_CLOSEDRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData LOX_FLUTTER_OPENConfig = CommandData(ECSValveState::OPEN,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> LOX_FLUTTER_OPENRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 550, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 0, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::OPEN),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_FLUTTER_CLOSEDConfig = CommandData(ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::OPEN,
                                                       ECSValveState::CLOSED,
                                                       ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_FLUTTER_CLOSEDRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));

    CommandData KER_FLUTTER_OPENConfig = CommandData(ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::OPEN,
                                                     ECSValveState::CLOSED,
                                                     ECSValveState::CLOSED);
    std::vector<std::unique_ptr<IRedline>> KER_FLUTTER_OPENRedlines = make_vector_unique<IRedline>(
            RedlineFactory("loxTankDucer", loxTankDucerSelector, 0, 800),
            RedlineFactory("kerTankDucer", kerTankDucerSelector, 550, 900),
            RedlineFactory("purgeDucer", purgeDucerSelector, 200, 500),
            RedlineFactory("loxInletDucer", loxInletDucerSelector, 0, 30),
            RedlineFactory("kerInletDucer", kerInletDucerSelector, 0, 30),
            RedlineFactory("kerPintleDucer", kerPintleDucerSelector, 0, 30),
            RedlineFactory("loxVenturi", loxVenturiSelector, 0, 10),
            RedlineFactory("kerVenturi", kerVenturiSelector, 0, 10),
            RedlineFactory("loadCell", loadCellSelector, 0, 30),
            RedlineFactory("pneumaticDucer", pneumaticDucerSelector, 90, 140),
            RedlineFactory("loxRegDucer", loxRegDucerSelector, 550, 800),
            RedlineFactory("kerRegDucer", kerRegDucerSelector, 550, 900),
            RedlineFactory("n2pressDucer", n2pressDucerSelector, 1000, 2000),
            RedlineFactory("loxTankTC", loxTankTCSelector, -1000, 1000),
            RedlineFactory("kerInletTC", kerInletTCSelector, -1000, 1000),
            RedlineFactory("kerOutletTC", kerOutletTCSelector, -1000, 1000),
            RedlineFactory("miscTC", miscTCSelector, -1000, 1000),
            RedlineFactory("loxVent", loxVentSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPressurant", loxPressurantSelector, ECSValveState::CLOSED),
            RedlineFactory("loxFlow", loxFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("loxPurge", loxPurgeSelector, ECSValveState::CLOSED),
            RedlineFactory("kerVent", kerVentSelector, ECSValveState::OPEN),
            RedlineFactory("kerPressurant", kerPressurantSelector, ECSValveState::OPEN),
            RedlineFactory("kerFlow", kerFlowSelector, ECSValveState::CLOSED),
            RedlineFactory("kerPurge", kerPurgeSelector, ECSValveState::CLOSED));
}
const ECSState ONLINE_SAFE = ECSState("ONLINE_SAFE", std::move(ONLINE_SAFERedlines), ONLINE_SAFEConfig,
                                      ONLINE_SAFEConfig);

const ECSState KER_FILL = ECSState("KER_FILL", std::move(KER_FILLRedlines), KER_FILLConfig, KER_FILLConfig);

const ECSState KER_POST_FILL = ECSState("KER_POST_FILL", std::move(KER_POST_FILLRedlines), KER_POST_FILLConfig,
                                        KER_POST_FILLConfig);

const ECSState LOX_FILL = ECSState("LOX_FILL", std::move(LOX_FILLRedlines), LOX_FILLConfig, LOX_FILLConfig);

const ECSState LOX_POST_FILL = ECSState("LOX_POST_FILL", std::move(LOX_POST_FILLRedlines), LOX_POST_FILLConfig,
                                        LOX_POST_FILLConfig);

const ECSState ALL_READY_TO_PRESSURIZE = ECSState("ALL_READY_TO_PRESSURIZE", std::move(ALL_READY_TO_PRESSURIZERedlines),
                                                  ALL_READY_TO_PRESSURIZEConfig, ALL_READY_TO_PRESSURIZEConfig);

const ECSState ALL_PRESSURIZING = ECSState("ALL_PRESSURIZING", std::move(ALL_PRESSURIZINGRedlines),
                                           ALL_PRESSURIZINGConfig, ALL_PRESSURIZINGConfig);

const ECSState LOX_PRESSURIZING = ECSState("LOX_PRESSURIZING", std::move(LOX_PRESSURIZINGRedlines),
                                           LOX_PRESSURIZINGConfig, LOX_PRESSURIZINGConfig);

const ECSState KER_PRESSURIZING = ECSState("KER_PRESSURIZING", std::move(KER_PRESSURIZINGRedlines),
                                           KER_PRESSURIZINGConfig, KER_PRESSURIZINGConfig);

const ECSState ALL_FLOW = ECSState("ALL_FLOW", std::move(ALL_FLOWRedlines), ALL_FLOWConfig, ALL_FLOWConfig);

const ECSState LOX_FLOW = ECSState("LOX_FLOW", std::move(LOX_FLOWRedlines), LOX_FLOWConfig, LOX_FLOWConfig);

const ECSState KER_FLOW = ECSState("KER_FLOW", std::move(KER_FLOWRedlines), KER_FLOWConfig, KER_FLOWConfig);

const ECSState LOX_GRAV_FLOW = ECSState("LOX_GRAV_FLOW", std::move(LOX_GRAV_FLOWRedlines), LOX_GRAV_FLOWConfig,
                                        LOX_GRAV_FLOWConfig);

const ECSState LOX_ENGINE_PURGE = ECSState("LOX_ENGINE_PURGE", std::move(LOX_ENGINE_PURGERedlines),
                                           LOX_ENGINE_PURGEConfig, LOX_ENGINE_PURGEConfig);

const ECSState KER_ENGINE_PURGE = ECSState("KER_ENGINE_PURGE", std::move(KER_ENGINE_PURGERedlines),
                                           KER_ENGINE_PURGEConfig, KER_ENGINE_PURGEConfig);

const ECSState ALL_ENGINE_PURGE = ECSState("ALL_ENGINE_PURGE", std::move(ALL_ENGINE_PURGERedlines),
                                           ALL_ENGINE_PURGEConfig, ALL_ENGINE_PURGEConfig);

const ECSState PRESSURIZED_ALL_ENGINE_PURGE = ECSState("PRESSURIZED_ALL_ENGINE_PURGE",
                                                       std::move(PRESSURIZED_ALL_ENGINE_PURGERedlines),
                                                       PRESSURIZED_ALL_ENGINE_PURGEConfig,
                                                       PRESSURIZED_ALL_ENGINE_PURGEConfig);

const ECSState LOX_TANK_PURGE = ECSState("LOX_TANK_PURGE", std::move(LOX_TANK_PURGERedlines), LOX_TANK_PURGEConfig,
                                         LOX_TANK_PURGEConfig);

const ECSState KER_TANK_PURGE = ECSState("KER_TANK_PURGE", std::move(KER_TANK_PURGERedlines), KER_TANK_PURGEConfig,
                                         KER_TANK_PURGEConfig);

const ECSState ALL_TANK_PURGE = ECSState("ALL_TANK_PURGE", std::move(ALL_TANK_PURGERedlines), ALL_TANK_PURGEConfig,
                                         ALL_TANK_PURGEConfig);

const ECSState LOX_FLUTTER_CLOSED = ECSState("LOX_FLUTTER_CLOSED", std::move(LOX_FLUTTER_CLOSEDRedlines),
                                             LOX_FLUTTER_CLOSEDConfig, LOX_FLUTTER_CLOSEDConfig);

const ECSState LOX_FLUTTER_OPEN = ECSState("LOX_FLUTTER_OPEN", std::move(LOX_FLUTTER_OPENRedlines),
                                           LOX_FLUTTER_OPENConfig, LOX_FLUTTER_OPENConfig);

const ECSState KER_FLUTTER_CLOSED = ECSState("KER_FLUTTER_CLOSED", std::move(KER_FLUTTER_CLOSEDRedlines),
                                             KER_FLUTTER_CLOSEDConfig, KER_FLUTTER_CLOSEDConfig);

const ECSState KER_FLUTTER_OPEN = ECSState("KER_FLUTTER_OPEN", std::move(KER_FLUTTER_OPENRedlines),
                                           KER_FLUTTER_OPENConfig, KER_FLUTTER_OPENConfig);

/**
 * SEQUENCES ARE CURRENTLY NOT AUTOMATICALLY GENERATED, REFRAIN FROM DELETING THEM
 *
 * DO NOT MOVE THESE BEFORE THE STATES ARE INITIALIZED
 */
RelatTimedSequence LOX_VENT_FLUTTER_x5{{
                                               {0, LOX_FLUTTER_CLOSED},
                                               {500, LOX_FLUTTER_OPEN},
                                               {500, LOX_FLUTTER_CLOSED},
                                               {500, LOX_FLUTTER_OPEN},
                                               {500, LOX_FLUTTER_CLOSED},
                                               {500, LOX_FLUTTER_OPEN},
                                               {500, LOX_FLUTTER_CLOSED},
                                               {500, LOX_FLUTTER_OPEN},
                                               {500, LOX_FLUTTER_CLOSED},
                                               {500, LOX_FLUTTER_OPEN},
                                               {500, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence KER_VENT_FLUTTER_x5{{
                                               {0, KER_FLUTTER_CLOSED},
                                               {500, KER_FLUTTER_OPEN},
                                               {500, KER_FLUTTER_CLOSED},
                                               {500, KER_FLUTTER_OPEN},
                                               {500, KER_FLUTTER_CLOSED},
                                               {500, KER_FLUTTER_OPEN},
                                               {500, KER_FLUTTER_CLOSED},
                                               {500, KER_FLUTTER_OPEN},
                                               {500, KER_FLUTTER_CLOSED},
                                               {500, KER_FLUTTER_OPEN},
                                               {500, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence FIRE_3s{{
                                   {0, KER_FLOW},
                                   {150, ALL_FLOW},
                                   {3000, KER_FLOW},
                                   {250, KER_ENGINE_PURGE},
                                   {3000, ALL_ENGINE_PURGE},
                                   {3000, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence FIRE_15s{{
                                    {0, KER_FLOW},
                                    {150, ALL_FLOW},
                                    {15000, KER_FLOW},
                                    {250, KER_ENGINE_PURGE},
                                    {3000, ALL_ENGINE_PURGE},
                                    {3000, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence PURGE_ABORT{{
                                       {0, KER_FLOW},
                                       {250, KER_ENGINE_PURGE},
                                       {3000, ALL_ENGINE_PURGE},
                                       {3000, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence NO_PURGE_ABORT{{
                                          {0, KER_FLOW},
                                          {1000, ALL_READY_TO_PRESSURIZE}}};

RelatTimedSequence ONLINE_SAFE_ABORT{{
                                             {0, ONLINE_SAFE}}};