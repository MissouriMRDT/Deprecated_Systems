"""
Concerns:
    TimeStamp usage.                    
    -> Giant gaps between drills?       
    -> Ignore gets graphs out of sync
    -> Parsing is odd
    Need to test graph actually works (!)
    Check to make sure plt attributes can be changed outside subplots
"""

import csv
import matplotlib.pyplot as plt

temp1_data = []
temp2_data = []
temp3_data = []
temp4_data = []

humid1_data = []
humid2_data = []
humid3_data = []
humid4_data = []

csv_name = input("Enter name of CSV file: ")
with open(csv_name, 'rb') as csvfile:
    for line in csvfile.readlines():
        row = line.split(' ')
        if(row[1] == "Temp1"):        
            temp1_data.append(row[2]);
            #temp1_time.append(row[0]);
        elif(row[1] == "Temp2"):
            temp2_data.append(row[2]);
            #temp2_time.append(row[0]);
        elif(row[1] == "Temp3"):
            temp3_data.append(row[2]);
            #temp3_time.append(row[0]);
        elif(row[1] == "Temp4"):
            temp4_data.append(row[2]);
            #temp4_time.append(row[0]);
        elif(row[1] == "Humid1"):
            humid1_data.append(row[2]);
            #humid1_time.append(row[0]);
        elif(row[1] == "Humid2"):
            humid2_data.append(row[2]);
            #humid2_data.append(row[0]);
        elif(row[1] == "Humid3"):
            humid3_data.append(row[2]);
            #humid3_data.append(row[0]);
        elif(row[1] == "Humid4"):
            humid4_data.append(row[2]);
            #humid4_data.append(row[0]);

plt.ion()
xlim(xmin = 0)

# Temperature Figure
plt.figure(1)
plt.ylim(0,50)
plt.title("Soil Temperature")
plt.ylabel("Temperature (Celsius)")
#plt.xlabel("Time Sample Taken")
plt.grid(True)
#T1 Subplot
plt.subplot(2,2,1)
plt.title("Temp1")
plt.plot(y=temp1_data, 'ro')
#T2 Subplot
plt.subplot(2,2,2)
plt.title("Temp2")
plt.plot(y=temp2_data, 'ro')
#T3 Subplot
plt.subplot(2,2,3)
plt.title("Temp3")
plt.plot(y=temp3_data, 'ro')
#T4 Subplot
plt.subplot(2,2,4)
plt.title("Temp4")
plt.plot(y=temp4_data, 'ro')

# Humidity Figure
plt.figure(2)
plt.ylim(0,100)
plt.title("Soil Moisture")
plt.ylabel("Water Content (%)")
#plt.xlabel("Time Sample Taken")
plt.grid(True)
#M1 Subplot
plt.subplot(2,2,1)
plt.title("Humid1")
plt.plot(y=humid1_data, 'ro')
#M2 Subplot
plt.subplot(2,2,1)
plt.title("Humid2")
plt.plot(y=humid2_data, 'ro')
#M3 Subplot
plt.subplot(2,2,1)
plt.title("Humid3")
plt.plot(y=humid3_data, 'ro')
#M4 Subplot
plt.subplot(2,2,1)
plt.title("Humid4")
plt.plot(y=humid4_data, 'ro')

plt.show()
