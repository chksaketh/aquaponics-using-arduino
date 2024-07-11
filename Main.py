import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from adafruit_io.adafruit_io import Client, Feed, RequestError

# Initialize Adafruit IO Client
aio = Client('your_aio_username', 'your_aio_key')

# Sensor data simulation (replace with actual sensor integration)
def get_sensor_data():
    return {
        'temperature': np.random.uniform(20, 30),
        'humidity': np.random.uniform(40, 60),
        'ph': np.random.uniform(6.5, 7.5),
        'light': np.random.uniform(200, 800)
    }

# Fetch or create feed
try:
    temperature_feed = aio.feeds('temperature')
except RequestError:
    temperature_feed = aio.create_feed(Feed(name='temperature'))

# Send data to Adafruit IO
def send_data_to_aio(sensor_data):
    aio.send_data(temperature_feed.key, sensor_data['temperature'])
    # Similarly, send other sensor data

# Main loop
while True:
    sensor_data = get_sensor_data()
    send_data_to_aio(sensor_data)
    print(f"Data sent: {sensor_data}")
    time.sleep(60)  # Delay for demonstration
