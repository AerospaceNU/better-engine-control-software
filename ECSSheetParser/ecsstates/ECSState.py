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

    def get_construction_parts(self, modifiers: list[str] = None) -> tuple[str, str]:
        if modifiers is None:
            modifiers = []

        modifier_str = " ".join(modifiers)

        constructor_paras = ""

        commanddata_name = f"{self.name}Config"
        constructor_paras += f"CommandData {commanddata_name} = {CommandData(self.ecsstate_data.effectorsList).get_construction()};" + "\n"

        redlines_name = f"{self.name}Redlines"
        constructor_paras += f"etl::vector<std::unique_ptr<IRedline>, 45> {redlines_name} = "
        constructor_paras += "make_vector_unique<IRedline>(" + "\n"
        constructor_paras += ", \n".join(RedlineFactory.constructRedline(sensor.name, f"{sensor.name}Selector", sensor.low, sensor.high)
                            for sensor in self.ecsstate_data.sensorsList)
        constructor_paras += ", \n"
        constructor_paras += ", \n".join(RedlineFactory.constructRedline(effector.name, f"{effector.name}Selector", "ECSValveState::" + effector.config)
                            for effector in self.ecsstate_data.effectorsList)
        constructor_paras += ");\n"

        constructor_call = f'{modifier_str} ECSState {self.name} = ECSState("{self.name}", std::move({redlines_name}), {commanddata_name}, {commanddata_name});\n'

        return constructor_paras, constructor_call


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