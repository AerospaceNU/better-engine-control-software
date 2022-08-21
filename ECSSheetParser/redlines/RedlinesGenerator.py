from collections import defaultdict

from redlines.IntWithinRedline import IntWithinRedline
from redlines.ValveStateRedline import ValveStateRedline


def format_vector_definition(ecsstate, redlines_list):
    newline = "\n"  # for some moronic reason f-strings dont allow backslashes, so you have to define a var

    return f"{format_vector_type(ecsstate)} = " \
           f"{{{(',' + newline).join(redline.str_with_new_init() for redline in redlines_list)}}};"


def format_vector_type(ecsstate):
    return f"std::vector<IRedline*> {ecsstate}"


def format_vector_declaration(ecsstate):
    return format_vector_type(ecsstate) + ";"


def field_lambda_definitions(field_list):
    return (f"auto {field}Selector = {format_lambda_selector(field)};" for field in field_list)


def format_lambda_selector(field):
    return f"[](SensorData &data) {{ return data.{field}; }}"


# generates redline vectors with name {ecsstate name}_REDLINES
def generate_ecsstate_redlines(ecsstate_data):
    # # generate field-selecting lambdas
    # for selector_def in field_lambda_definitions(sensor_headers):
    #     print(selector_def)

    ecsstate_to_redlines = defaultdict(list)

    for ecs_state, data in ecsstate_data.items():
        for sensor_name, sensor_data in data.items():
            try:
                lBound, rBound = sensor_data.split("-")
                ecsstate_to_redlines[ecs_state].append(IntWithinRedline(f"{sensor_name} in {ecs_state}",
                                                                 sensor_name,
                                                                 int(lBound),
                                                                 int(rBound)))

            except ValueError:  # thrown on split() or int()
                if (capital_data := sensor_data.upper()) in ("OPEN", "CLOSED", "INVALID"):
                    ecsstate_to_redlines[ecs_state].append(ValveStateRedline(f"{sensor_name} in {ecs_state}",
                                                                      sensor_name,
                                                                      capital_data))
                else:
                    print(f"No match found for '{sensor_data}'")

    for ecs_state in ecsstate_to_redlines:
        print(format_vector_definition(ecs_state + "_REDLINES", ecsstate_to_redlines[ecs_state]))

    print("\nPRINTING DECLARATIONS")

    for ecs_state in ecsstate_to_redlines:
        print(format_vector_declaration(ecs_state + "_REDLINES"))