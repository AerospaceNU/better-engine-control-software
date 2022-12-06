from model.StateData import StateData
from ecsstates.CommandData import CommandData
import ecsstates.redlines.RedlineFactory as RedlineFactory


class ECSState:
    def __init__(self, ecsstate_data: StateData):
        self.name: str = ecsstate_data.name
        self.ecsstate_data: StateData = ecsstate_data

    def get_declaration(self, modifiers: list[str] = None):
        if modifiers is None:
            modifiers = []

        modifier_str = " ".join(modifiers)
        return f"{modifier_str} ECSState {self.name};"

    def get_construction(self, modifiers: list[str] = None):
        if modifiers is None:
            modifiers = []

        modifier_str = " ".join(modifiers)

        result = ""

        result += "namespace {" + "\n"
        commanddata_name = f"{self.name}Config"
        result += f"CommandData {commanddata_name} = {CommandData(self.ecsstate_data.effectorsList).get_construction()};" + "\n"

        redlines_name = f"{self.name}Redlines"
        result += f"std::vector<std::unique_ptr<IRedline>> {redlines_name} = "
        result += "make_vector_unique<IRedline>(" + "\n"
        result += ", \n".join(RedlineFactory.constructRedline(sensor.name, f"{sensor.name}Selector", sensor.low, sensor.high)
                            for sensor in self.ecsstate_data.sensorsList)
        result += ", \n"
        result += ", \n".join(RedlineFactory.constructRedline(effector.name, f"{effector.name}Selector", "ECSValveState::" + effector.config)
                            for effector in self.ecsstate_data.effectorsList)
        result += ");\n"
        result += "}\n"

        result += f'{modifier_str} ECSState {self.name} = ECSState("{self.name}", std::move({redlines_name}), {commanddata_name}, {commanddata_name});\n'

        return result


# ECSState(std::string
# name, std::vector < IRedline * > & redlines, const
# CommandData & config, ECSState & failState);
#
# std::string
# name;
# std::vector < IRedline * > & redlines;
# CommandData
# config;
# ECSState & failState;