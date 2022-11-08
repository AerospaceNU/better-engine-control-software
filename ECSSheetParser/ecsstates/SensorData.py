from model.Sensor import Sensor


class SensorData:
    def __init__(self, sensor_list: list[Sensor]):
        self.sensor_list = sensor_list

    def get_definition(self):
        result = ""
        result += "struct SensorData: public CommandData {\n"

        result += "\n".join(f"int {sensor.name} = 0;"
                            for sensor in self.sensor_list)
        result += "\n}"
        return result