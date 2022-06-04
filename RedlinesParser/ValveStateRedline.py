class ValveStateRedline:
    def __init__(self, name, sensor, expected_state):
        self.name = name
        self.sensor = sensor
        self.expected_state = expected_state

    def __repr__(self):
        return str(self)

    def str_with_new_init(self):
        return "new " + str(self)

    def __str__(self):
        return f'ValveRedline("{self.name}", {self.generate_lambda()}, {self.expected_state})'

    def generate_lambda(self):
        return f"[](const SensorData *data) {{ return data->{self.sensor};}}"

