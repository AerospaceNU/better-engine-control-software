class CommandData:
    def __init__(self, list_of_effectors, total_data):
        self.effectors_to_state_dict = {}

        for effector in list_of_effectors:
            self.effectors_to_state_dict[effector] = total_data[effector]

    def __repr__(self):
        return str(self)

    def __str__(self):
        # we are relying on the fact that dict preserves insertion order
        return f'CommandData({self.generate_effector_params()})'

    def generate_effector_params(self):
        separator = ",\n"

        # we are relying on the fact that dict preserves insertion order to generate in the right order
        return separator.join(f"ECSValveState::{state}" for _, state in self.effectors_to_state_dict.items())

    # //REMOTELY CONTROLLED VALVES
    # ECSValveState loxVent = ECSValveState::INVALID;
    # ECSValveState kerVent = ECSValveState::INVALID;
    # ECSValveState loxDrip = ECSValveState::INVALID;
    # ECSValveState kerDrip = ECSValveState::INVALID;
    # ECSValveState loxPressurant = ECSValveState::INVALID;
    # ECSValveState kerPressurant = ECSValveState::INVALID;
    # ECSValveState loxFlow = ECSValveState::INVALID;
    # ECSValveState kerFlow = ECSValveState::INVALID;
    # ECSValveState loxPurge = ECSValveState::INVALID;
    # ECSValveState kerPurge = ECSValveState::INVALID;
