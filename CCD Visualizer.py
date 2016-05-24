import csv
import matplotlib.pyplot as plt
import numpy as np

plt.ion()

csv_name = input("Enter name of CSV file: ")
file = open(csv_name)
numline = len(file.readlines())
file.close()

ccd_data = [[] for y in range(numline)]
data_len = []
max_len = 0
row_count = 0

with open(csv_name, 'r') as csvfile:
    csvreader = csv.reader(csvfile, delimiter=',')
    for row in csvfile.readlines():
        ccd_data[row_count] = row.split(',')
        ccd_data[row_count] = [int(i) for i in ccd_data[row_count]]
        data_len.append(len(ccd_data[row_count]))
        if len(ccd_data[row_count]) > max_len:
            max_len = len(ccd_data[row_count])
        row_count = row_count + 1

for row in range(numline):
    plt.delaxes()
    plt.grid(True)
    plt.xlim(xmin=0, xmax=max_len)
    plt.ylim(ymin=0, ymax=1023)
    plt.plot(np.arange(start=0, stop=data_len[row], step=1), ccd_data[row])
    plt.show()
    plt.pause(0.0001)
    input("Press Enter to continue")

        

            
