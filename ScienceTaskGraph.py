##################################################################
#          Missouri University of Science and Technology         #
#                    Mars Rover Design Team                      #
#       John Maruska                        jwmbq6@mst.edu       #
#   2016 Spring Semester - Intended for use with Zenith rover    #
##################################################################

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
with open(csv_name, 'r') as csvfile:
    csvreader = csv.reader(csvfile, delimiter=' ')
    for row in csvfile.readlines():
        datestamp, sensor, raw_data = row.split(' ')
        if(sensor == "Temp1"):       
            temp1_time.append(dateutil.parser.parse(datestamp))
            temp1_data.append(raw_data)
        elif(sensor == "Temp2"):
            temp2_time.append(dateutil.parser.parse(datestamp))
            temp2_data.append(raw_data)
        elif(sensor == "Temp3"):
            temp3_time.append(dateutil.parser.parse(datestamp))
            temp3_data.append(raw_data)
        elif(sensor == "Temp4"):
            temp4_time.append(dateutil.parser.parse(datestamp))
            temp4_data.append(raw_data)
        elif(sensor == "Humid1"):
            humid1_time.append(dateutil.parser.parse(datestamp))
            humid1_data.append(raw_data)
        elif(sensor == "Humid2"):
            humid2_time.append(dateutil.parser.parse(datestamp))
            humid2_data.append(raw_data)
        elif(sensor == "Humid3"):
            humid3_time.append(dateutil.parser.parse(datestamp))
            humid3_data.append(raw_data)
        elif(sensor == "Humid4"):
            humid4_time.append(dateutil.parser.parse(datestamp))
            humid4_data.append(raw_data)
            
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
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid1_time, y=humid1_data)

#M2 Subplot
plt.subplot(2,2,2)
plt.title("Humid2")
plt.ylabel("Water Content (%)")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid2_time, y=humid2_data)

#M3 Subplot
plt.subplot(2,2,3)
plt.title("Humid3")
plt.ylabel("Water Content (%)")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid3_time, y=humid3_data)

#M4 Subplot
plt.subplot(2,2,4)
plt.title("Humid4")
plt.ylabel("Water Content (%)")
plt.grid(True)
plt.ylim(0,100)
plt.xticks(ha='right', rotation=15)
plt.plot_date(x=humid4_time, y=humid4_data)

plt.show()
