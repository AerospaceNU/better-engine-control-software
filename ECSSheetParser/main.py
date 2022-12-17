import SheetParser
from ecsstates.CommandData import CommandData
from ecsstates.SensorData import SensorData
from ecsstates.ECSState import ECSState
from ecsstates.ECSStatesBigConstructor import get_all_ecsstate_construction

INPUT_FILE = "input.csv"

if __name__ == "__main__":
    states_list = SheetParser.parse_csvs("State Sets - ALL_STATES.csv", "State Sets - WATCHDOG REDLINES.csv")

    print("\nPRINTING COMMANDDATA STRUCT DEFINITION")
    print(CommandData(states_list[0].effectorsList).get_definition())

    print("\nPRINTING SENSORDATA STRUCT DEFINITION")
    print(SensorData(states_list[0].sensorsList).get_definition())

    print("\nPRINTING DECLARATIONS")
    for state in states_list:
        print(ECSState(state).get_declaration(["const", "extern"]))

    print("\nPRINTING DEFINITIONS")
    print(get_all_ecsstate_construction(states_list, ["const"]))


