from model import Effector


class CommandData:
    def __init__(self, effector_list: list[Effector]):
        self.effector_list: list[Effector] = effector_list

    def get_construction(self):
        return f'CommandData({self.generate_effector_params()})'

    def _constructor_def(self):
        result = ""
        result += "CommandData("
        result += ", ".join(f"ECSValveState {effector.name}_" for effector in self.effector_list)
        result += "):\n"

        result += ",\n".join(f"{effector.name}({effector.name}_)"
                          for effector in self.effector_list)
        result += "{}\n"
        return result

    def get_definition(self):
        result = ""
        result += "struct CommandData {\n"
        result += self._constructor_def()
        result += "CommandData() = default;\n"
        result += "CommandData(const SensorData &) = delete;\n"
        result += "CommandData &operator=(const SensorData &) = delete;\n"

        result += "\n".join(f"ECSValveState {effector.name} = ECSValveState::INVALID;"
                          for effector in self.effector_list)
        result += "\n}"

        return result

    def generate_effector_params(self):
        separator = ",\n"

        # we are relying on the fact that dict preserves insertion order to generate in the right order
        return separator.join(f"ECSValveState::{effector.config}" for effector in self.effector_list)
