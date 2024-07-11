import numpy as np

class ControlSystem:
    def __init__(self):
        self.target_temp = 25.0
        self.target_ph = 7.0
        self.target_light = 500.0

    def control_temperature(self, current_temp):
        if current_temp < self.target_temp:
            return "Heating"
        elif current_temp > self.target_temp:
            return "Cooling"
        return "Stable"

    def control_ph(self, current_ph):
        if current_ph < self.target_ph:
            return "Increase pH"
        elif current_ph > self.target_ph:
            return "Decrease pH"
        return "Stable"

    def control_light(self, current_light):
        if current_light < self.target_light:
            return "Increase Light"
        elif current_light > self.target_light:
            return "Decrease Light"
        return "Stable"

    def adjust_controls(self, sensor_data):
        temp_action = self.control_temperature(sensor_data['temperature'])
        ph_action = self.control_ph(sensor_data['ph'])
        light_action = self.control_light(sensor_data['light'])
        return temp_action, ph_action, light_action

control_system = ControlSystem()
sensor_data = {'temperature': 24, 'ph': 7.2, 'light': 450}
actions = control_system.adjust_controls(sensor_data)
print(f"Control Actions: {actions}")
