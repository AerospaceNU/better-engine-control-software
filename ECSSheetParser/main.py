import SheetParser
from redlines import RedlinesGenerator

from ecsstates import StateGenerator

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

    StateGenerator.generate_states(ecsstate_data, effector_names)


