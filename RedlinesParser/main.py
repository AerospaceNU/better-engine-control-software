import csv
from collections import defaultdict

from IntWithinRedline import IntWithinRedline
from ValveStateRedline import ValveStateRedline

INPUT_FILE = "input.csv"


def format_vector(ecsstate, redlines_list):
    newline = "\n"

    return f"{format_vector_type(ecsstate)} = {{" \
           f"{(',' + newline).join(redline.str_with_new_init() for redline in redlines_list)}}};"


def format_vector_type(ecsstate):
    return f"extern const std::vector<const IRedline*> {ecsstate}"


def format_vector_declaration(ecsstate):
    return format_vector_type(ecsstate) + ";"


if __name__ == "__main__":
    with open(INPUT_FILE) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0

        vector_to_redlines = defaultdict(list)

        for row in csv_reader:
            if line_count == 0:

                print(f'Column names are {row}')
                sensor_headers = row
                line_count += 1

            else:
                if row[0]:
                    name = row[0]
                    print(f"Found this ECSState: {name}")

                    for sensor, data in zip(sensor_headers[1:], row[1:]):
                        try:
                            lBound, rBound = data.split("-")
                            vector_to_redlines[name].append(IntWithinRedline(f"{sensor} in {name}", sensor, int(lBound), int(rBound)))

                        except ValueError:
                            if (capital_data := data.upper()) in ("OPEN", "CLOSED", "INVALID"):
                                vector_to_redlines[name].append((ValveStateRedline(f"{sensor} in {name}", sensor, capital_data)))
                            else:
                                print(f"No match found for '{data}'")

                    print("\n")

                line_count += 1

        for thing in vector_to_redlines:
            print(format_vector(thing, vector_to_redlines[thing]))

        print("\n")

        for thing in vector_to_redlines:
            print(format_vector_declaration(thing))

        # print(f'Processed {line_count} lines.')
