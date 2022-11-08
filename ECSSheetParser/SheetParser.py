import csv

from model.StateData import StateData
from model.Effector import Effector
from model.Sensor import Sensor

# def parse_csv(csv_file_name):
#     with open(csv_file_name) as csv_file:
#         csv_reader = csv.reader(csv_file, delimiter=',')
#
#         raw_headers = next(csv_reader)  # gets the first row of the reader
#         # trim leftmost cell, unused
#         sensor_headers = raw_headers[1:]
#         print(f'Column names are {sensor_headers}')
#
#         # csv_reader now starts on the second row thanks to our previous next() call
#         return get_ecsstate_dict(sensor_headers, csv_reader)


def iterate_two(obj):
    iterator = iter(obj)

    while True:
        try:
            yield next(iterator), next(iterator)
        except StopIteration:
            return


def parse_csvs(effector_csv_name, sensor_csv_name) -> list[StateData]:
    with open(effector_csv_name) as effector_csv:
        effector_datas = parse_valve_csv(effector_csv)

    with open(sensor_csv_name) as sensor_csv:
        sensor_datas = parse_sensor_csv(sensor_csv)

    return [StateData(states_effectors.name, states_effectors.effectorsList, states_sensors.sensorsList)
            for states_effectors, states_sensors in zip(effector_datas, sensor_datas)]


def parse_valve_csv(effector_csv) -> list[StateData]:
    csv_reader = csv.reader(effector_csv, delimiter=',')

    raw_headers = next(csv_reader)  # gets the first row of the reader
    # trim leftmost cell, unused
    valve_headers = raw_headers[1:]
    print(f'Column names are {valve_headers}')

    # csv_reader now starts on the second row thanks to our previous next() call

    result = []

    for row in csv_reader:
        if state_name := row[0]:  # if there is something in the first column of this row
            print(f"Found this ECSState with valve data: {state_name}")

            effectorsList = []

            for sensor, data in zip(valve_headers, row[1:]):  # skip the first thing in the row, that was the name
                effectorsList.append(Effector(sensor, data))

            result.append(StateData(state_name, effectorsList, []))

    return result


def parse_sensor_csv(sensor_csv) -> list[StateData]:
    csv_reader = csv.reader(sensor_csv, delimiter=',')

    raw_headers = next(csv_reader)  # gets the first row of the reader
    # trim leftmost cell, unused
    sensor_headers = raw_headers[1:]  # additional space after each
    print(f'Column names are {sensor_headers}')

    # csv_reader now starts on the second row thanks to our previous next() call

    result = []

    for row in csv_reader:
        if state_name := row[0]:  # if there is something in the first column of this row
            print(f"Found this ECSState with sensor data: {state_name}")

            sensorsList = []

            for sensor, data in zip(iterate_two(sensor_headers), iterate_two(row[1:])):  # skip the first thing in the row, that was the name
                sensor_name, _ = sensor
                low, high = data
                sensorsList.append(Sensor(sensor_name, low, high))

            result.append(StateData(state_name, [], sensorsList))

    return result


# # sensor_headers should be stripped of any blank cells to the left
# def get_ecsstate_dict(sensor_headers, csv_reader):
#     ecsstate_to_data_dict = {}
#
#     for row in csv_reader:
#         if state_name := row[0]:  # if there is something in the first column of this row
#             print(f"Found this ECSState: {state_name}")
#
#             contents_dict = {}
#             for sensor, data in zip(sensor_headers, row[1:]):  # skip the first thing in the row, that was the name
#                 contents_dict[sensor] = data
#
#             ecsstate_to_data_dict[state_name] = contents_dict
#
#     return ecsstate_to_data_dict

