import csv
import matplotlib.pyplot as plt
import numpy as np

plt.ion()
plt.figure()
plt.grid(True)
plt.ylim(0,1023)

ccd_data = []
csv_name = input("Enter name of CSV file: ")
with open(csv_name, 'r') as csvfile:
    csvreader = csv.reader(csvfile, delimiter=',')
    for row in csvfile.readlines():
        ccd_data = row.split(',')
        ccd_data = [int(i) for i in ccd_data]
        data_len = len(ccd_data)
        plt.xlim(xmax=data_len)
        plt.plot(np.arange(start=0, stop=data_len, step=1), ccd_data)
