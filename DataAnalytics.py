import pandas as pd
import matplotlib.pyplot as plt

# Load sensor data from CSV
data = pd.read_csv('sensor_data.csv')

# Plot temperature over time
plt.figure(figsize=(10, 5))
plt.plot(data['timestamp'], data['temperature'], label='Temperature')
plt.xlabel('Time')
plt.ylabel('Temperature (C)')
plt.title('Temperature Over Time')
plt.legend()
plt.show()
