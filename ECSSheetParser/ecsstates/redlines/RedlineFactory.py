def constructRedline(name: str, sensorSelector: str, *additonal_args):
    stringed_args = (str(arg) for arg in additonal_args)
    return f'RedlineFactory("{name}", {sensorSelector}, {", ".join(stringed_args)})'
