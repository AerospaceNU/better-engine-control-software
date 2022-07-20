import csv
from collections import defaultdict

from IntWithinRedline import IntWithinRedline
from ValveStateRedline import ValveStateRedline

INPUT_FILE = "input.csv"


def format_vector_definition(ecsstate, redlines_list):
    newline = "\n"  # for some moronic reason f-strings dont allow backslashes, so you have to define a var

    return f"{format_vector_type(ecsstate)} = " \
           f"{{{(',' + newline).join(redline.str_with_new_init() for redline in redlines_list)}}};"


def format_vector_type(ecsstate):
    return f"extern std::vector<IRedline*> {ecsstate}"


def format_vector_declaration(ecsstate):
    return format_vector_type(ecsstate) + ";"


def field_lambda_definitions(field_list):
    return (f"auto {field}Selector = {format_lambda_selector(field)};" for field in field_list)


def format_lambda_selector(field):
    return f"[](SensorData &data) {{ return data.{field}; }}"


if __name__ == "__main__":
    with open(INPUT_FILE) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')

        vector_to_redlines = defaultdict(list)

        raw_headers = next(csv_reader)  # gets the first row of the reader
        # trim leftmost cell, unused
        sensor_headers = raw_headers[1:]

        print(f'Column names are {sensor_headers}')

        # generate field-selecting lambdas
        for selector_def in field_lambda_definitions(sensor_headers):
            print(selector_def)

        print("\n")
        for row in csv_reader:  # csv_reader now starts on the second row thanks to our previous next() call
            if name := row[0]:  # if there is something in the first column of this row
                print(f"Found this ECSState: {name}")

                for sensor, data in zip(sensor_headers, row[1:]):
                    try:
                        lBound, rBound = data.split("-")
                        vector_to_redlines[name].append(IntWithinRedline(f"{sensor} in {name}",
                                                                         sensor,
                                                                         int(lBound),
                                                                         int(rBound)))

                    except ValueError:  # thrown on split() or int()
                        if (capital_data := data.upper()) in ("OPEN", "CLOSED", "INVALID"):
                            vector_to_redlines[name].append(ValveStateRedline(f"{sensor} in {name}",
                                                                              sensor,
                                                                              capital_data))
                        else:
                            print(f"No match found for '{data}'")

                print("\n")

        for ecs_state in vector_to_redlines:
            print(format_vector_definition(ecs_state + "_REDLINES", vector_to_redlines[ecs_state]))

        print("\nPRINTING DECLARATIONS")

        for ecs_state in vector_to_redlines:
            print(format_vector_declaration(ecs_state + "_REDLINES"))
