from model.Sensor import Sensor
from model.Effector import Effector


class StateData:
    def __init__(self, name: str, effectorsList: list[Effector], sensorsList: list[Sensor]):
        self.name: str = name
        self.effectorsList: list[Effector] = effectorsList
        self.sensorsList: list[Sensor] = sensorsList
