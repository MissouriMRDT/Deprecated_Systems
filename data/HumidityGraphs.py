import numpy as np
import matplotlib.pyplot as plt

data = []
csv_name = input("Enter name of CSV file: ")
data = np.loadtxt(csv_name, delimiter=',')

plt.ion()           # enable interactivity
plt.ylim(-3,53)
plt.xlim(xmin = 0, xmax = len(data))
plt.title("Soil Temperature")
plt.ylabel("Temperature (Celsius)")
plt.xlabel("Sample Number (2 samples per second)")
plt.grid(True)
plt.scatter(np.arange(len(data)), data)
