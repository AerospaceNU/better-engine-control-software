from ecsstates.ECSState import ECSState
from model.StateData import StateData


def get_accessor_lambda_definition(field_name: str):
    return f"[](const SensorData &data) {{return data.{field_name};}};"


def get_all_ecsstate_construction(state_list: list[StateData], modifiers: list[str]):
    lambda_function_list = []

    for sensor in state_list[0].sensorsList:
        lambda_function_list.append(
            f"std::function<int(const SensorData &)> {sensor.name}Selector = "
            f"{get_accessor_lambda_definition(sensor.name)}"
        )

    for effector in state_list[0].effectorsList:
        lambda_function_list.append(
            f"std::function<ECSValveState(const SensorData &)> {effector.name}Selector = "
            f"{get_accessor_lambda_definition(effector.name)}"
        )

    all_constructor_params = []
    all_constructor_calls = []

    ecsstate_list = [ECSState(state) for state in state_list]
    for params, actual_call in (ecsstate.get_construction_parts(modifiers) for ecsstate in ecsstate_list):
        all_constructor_params.append(params)
        all_constructor_calls.append(actual_call)

    result = "namespace {\n"

    result += "\n".join(lambda_function_list)
    result += "\n\n"

    result += "\n".join(all_constructor_params)

    result += "}\n"

    result += "\n".join(all_constructor_calls)
    return result
