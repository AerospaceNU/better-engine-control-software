class IntWithinRedline:
    def __init__(self, name: str, sensor: str, lower_bound: int, upper_bound: int):
        self.name = name
        self.sensor = sensor
        self.lower_bound = lower_bound
        self.upper_bound = upper_bound

    def __repr__(self):
        return str(self)

    def str_with_new_init(self):
        return "new " + str(self)

    def __str__(self):
        return f'IntWithinRedline("{self.name}", {self.generate_lambda()}, {self.lower_bound}, {self.upper_bound})'

    def generate_lambda(self):
        return f"[](const SensorData *data) {{ return data->{self.sensor};}}"
