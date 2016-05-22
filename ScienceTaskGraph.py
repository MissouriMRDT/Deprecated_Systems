"""
Concerns:
    Need to test graph actually works (!)
    Check to make sure plt attributes can be changed outside subplots
"""

import csv
import matplotlib.pyplot as plt

temp1_data = []
temp2_data = []
temp3_data = []
temp4_data = []

temp1_time = []
temp2_time = []
temp3_time = []
temp4_time = []

humid1_data = []
humid2_data = []
humid3_data = []
humid4_data = []

humid1_time = []
humid2_time = []
humid3_time = []
humid4_time = []

csv_name = input("Enter name of CSV file: ")
with open(csv_name, 'rb') as csvfile:
    for line in csvfile.readlines():
        row = line.split(' ')
        if(row[1] == "Temp1"):        
            temp1_data.append(row[2])
            # Parse date-time stamp 
            temp1_time.append(row[0])
        elif(row[1] == "Temp2"):
            temp2_data.append(row[2])
            temp2_time.append(row[0])
        elif(row[1] == "Temp3"):
            temp3_data.append(row[2])
            temp3_time.append(row[0])
        elif(row[1] == "Temp4"):
            temp4_data.append(row[2])
            temp4_time.append(row[0])
        elif(row[1] == "Humid1"):
            humid1_data.append(row[2])
            humid1_time.append(row[0])
        elif(row[1] == "Humid2"):
            humid2_data.append(row[2])
            humid2_data.append(row[0])
        elif(row[1] == "Humid3"):
            humid3_data.append(row[2])
            humid3_data.append(row[0])
        elif(row[1] == "Humid4"):
            humid4_data.append(row[2])
            humid4_data.append(row[0])
            
# Temperature Figure
plt.figure(1)
plt.subplots_adjust(hspace=0.30)
plt.suptitle("Soil Temperature Readings", fontsize=17)

#T1 Subplot
plt.subplot(2,2,1)
plt.title("Temp1")
plt.xlabel("Time Sample Taken")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.plot(x=temp1_time, y=temp1_data, 'ro')

#T2 Subplot
plt.subplot(2,2,2)
plt.title("Temp2")
plt.xlabel("Time Sample Taken")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.plot(x=temp2_time, y=temp2_data, 'ro')

#T3 Subplot
plt.subplot(2,2,3)
plt.title("Temp3")
plt.xlabel("Time Sample Taken")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.plot(x=temp3_time, y=temp3_data, 'ro')

#T4 Subplot
plt.subplot(2,2,4)
plt.title("Temp4")
plt.xlabel("Time Sample Taken")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.plot(x=temp4_time, y=temp4_data, 'ro')

# Humidity Figure
plt.figure(2)
plt.subplots_adjust(hspace=0.30)
plt.suptitle("Soil Temperature Readings", fontsize=17)

#M1 Subplot
plt.subplot(2,2,1)
plt.title("Humid1")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.plot(x=humid1_time, y=humid1_data, 'ro')

#M2 Subplot
plt.subplot(2,2,1)
plt.title("Humid2")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.plot(x=humid2_time, y=humid2_data, 'ro')

#M3 Subplot
plt.subplot(2,2,1)
plt.title("Humid3")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.plot(x=humid3_time, y=humid3_data, 'ro')

#M4 Subplot
plt.subplot(2,2,1)
plt.title("Humid4")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.plot(x=humid4_time, y=humid4_data, 'ro')
