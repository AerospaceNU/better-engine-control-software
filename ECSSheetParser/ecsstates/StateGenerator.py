from ecsstates.CommandData import CommandData
from ecsstates.ECSState import ECSState


def generate_states(ecsstate_data, effector_list):
    name_to_ecsstate_dict = {}

    for ecs_state, data in ecsstate_data.items():
        name_to_ecsstate_dict[ecs_state] = ECSState(ecs_state,
                                                    f"{ecs_state}_REDLINES",
                                                    CommandData(effector_list, data))

    print("\nPRINTING DECLARATIONS")
    for ecs_state in name_to_ecsstate_dict:
        print(f"extern ECSState {ecs_state};")

    print("\nPRINTING DEFINITIONS")
    for state_name, state_object in name_to_ecsstate_dict.items():
        print(f"extern ECSState {state_name} = {state_object};")