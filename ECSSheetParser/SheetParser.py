import csv


def get_sensor_headers():
    pass


def parse_csv(csv_file_name):
    with open(csv_file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')

        raw_headers = next(csv_reader)  # gets the first row of the reader
        # trim leftmost cell, unused
        sensor_headers = raw_headers[1:]
        print(f'Column names are {sensor_headers}')

        # csv_reader now starts on the second row thanks to our previous next() call
        return get_ecsstate_dict(sensor_headers, csv_reader)


# sensor_headers should be stripped of any blank cells to the left
def get_ecsstate_dict(sensor_headers, csv_reader):
    ecsstate_to_data_dict = {}

    for row in csv_reader:
        if state_name := row[0]: # if there is something in the first column of this row
            print(f"Found this ECSState: {state_name}")

            contents_dict = {}
            for sensor, data in zip(sensor_headers, row[1:]): # skip the first thing in the row, that was the name
                contents_dict[sensor] = data

            ecsstate_to_data_dict[state_name] = contents_dict

    return ecsstate_to_data_dict
