"""
Concerns:
    Need to test graph actually works (!)
    Check to make sure plt attributes can be changed outside subplots
"""

import csv
import dateutil.parser
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
    csvreader = csv.reader(csvfile, delimiter=' ')
    for row in csvfile.readlines():
        if(row[1] == "Temp1"):       
            temp1_time.append(dateutil.parser.parse(row[0]))
            temp1_data.append(row[2])
        elif(row[1] == "Temp2"):
            temp2_time.append(dateutil.parser.parse(row[0]))
            temp2_data.append(row[2])
        elif(row[1] == "Temp3"):
            temp3_time.append(dateutil.parser.parse(row[0]))
            temp3_data.append(row[2])
        elif(row[1] == "Temp4"):
            temp4_time.append(dateutil.parser.parse(row[0]))
            temp4_data.append(row[2])
        elif(row[1] == "Humid1"):
            humid1_time.append(dateutil.parser.parse(row[0]))
            humid1_data.append(row[2])
        elif(row[1] == "Humid2"):
            humid2_data.append(dateutil.parser.parse(row[0]))
            humid2_data.append(row[2])
        elif(row[1] == "Humid3"):
            humid3_data.append(dateutil.parser.parse(row[0]))
            humid3_data.append(row[2])
        elif(row[1] == "Humid4"):
            humid4_data.append(dateutil.parser.parse(row[0]))
            humid4_data.append(row[2])
            
# Temperature Figure
plt.figure(1)
plt.subplots_adjust(hspace=0.30)
plt.suptitle("Soil Temperature Readings", fontsize=17)

#T1 Subplot
plt.subplot(2,2,1)
plt.title("Temp1")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=temp1_time, y=temp1_data)

#T2 Subplot
plt.subplot(2,2,2)
plt.title("Temp2")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=temp2_time, y=temp2_data)

#T3 Subplot
plt.subplot(2,2,3)
plt.title("Temp3")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=temp3_time, y=temp3_data)

#T4 Subplot
plt.subplot(2,2,4)
plt.title("Temp4")
plt.ylabel("Temperature (Celsius)")
plt.grid(True)
plt.ylim(0,50)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=temp4_time, y=temp4_data)

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
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid1_time, y=humid1_data)

#M2 Subplot
plt.subplot(2,2,2)
plt.title("Humid2")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid2_time, y=humid2_data)

#M3 Subplot
plt.subplot(2,2,3)
plt.title("Humid3")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid3_time, y=humid3_data)

#M4 Subplot
plt.subplot(2,2,4)
plt.title("Humid4")
plt.ylabel("Water Content (%)")
plt.xlabel("Time Sample Taken")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid4_time, y=humid4_data)

plt.show()
