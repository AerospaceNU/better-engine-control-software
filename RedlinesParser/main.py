import SheetParser
import RedlinesGenerator

from ECSState import ECSState
from CommandData import CommandData

INPUT_FILE = "input.csv"

if __name__ == "__main__":
    ecsstate_data = SheetParser.parse_csv(INPUT_FILE)

    RedlinesGenerator.generate_ecsstate_redlines(ecsstate_data)

    effector_names = ["loxVent",
                      "kerVent",
                      "loxDrip",
                      "kerDrip",
                      "loxPressurant",
                      "kerPressurant",
                      "loxFlow",
                      "kerFlow",
                      "loxPurge",
                      "kerPurge"]

    name_to_ecsstate_dict = {}

    for ecs_state, data in ecsstate_data.items():
        name_to_ecsstate_dict[ecs_state] = ECSState(ecs_state,
                                                    f"{ecs_state}_REDLINES",
                                                    CommandData(effector_names, data))

    print("\nPRINTING DECLARATIONS")
    for ecs_state in name_to_ecsstate_dict:
        print(f"extern ECSState {ecs_state};")

    print("\nPRINTING DEFINITIONS")
    for state_name, state_object in name_to_ecsstate_dict.items():
        print(f"extern ECSState {state_name} = {state_object};")


