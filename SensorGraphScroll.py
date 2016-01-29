"""
Program to create a scrolling data plot from data input through serial com4 with a baudrate of 9600
Takes one argument in command line, specifying maximum number of data points to display on the x axis at any given time.0

Usage:      python serialgraphscroll.py [points] [serial-input]


"""
import serial 						
import numpy						
import matplotlib.pyplot as plt
import csv

count = 0
relativeCount = []                              # count used for graphing once scrolling begins
plt.ion()	        		        # interactive mode to plot live data
dataStore = []                                  # empty list of data
graphStore = []                                 # empty list to store data being used by graph
#input = sys.argv[2]
serialData = serial.Serial('com3', 9600) 	# object to read from serial port
                                                # port_no and baudrate
MAX_PLOT_SIZE = 20 ############################## maximum graph size in x direction

#graphRange = []                                 # x range for scrolling graph
#beginning = 0
#ending = 0
dataRange = []                                  # y range for scrolling graph
beginData = 0
endData = 0
temp = 0                                        # variable because I couldn't test if parenthesis-stacking works with arrays

plt.plot(graphStore, 'r,', label='Humidity')
plt.ylim(-5,100)
plt.grid(True)
plt.title("Sensor Data")

def graph():
        global count                                    # allow modification of count
        print ("during graph: ")
        print ("count: ", count)
        print ("data: ", len(graphStore)-1)
        if (count < MAX_PLOT_SIZE):
                plt.scatter(count,graphStore[count])    # old graphing method
                count += 1                              ### count must be incremented in either case
        else:
                
                endData = count+1                          # end of x range
                beginData = (count - MAX_PLOT_SIZE)     # beginning of x range
                dataRange = numpy.arange(beginData,(endData))    # setting x range
                plt.scatter(dataRange,graphStore)       # graphing with specified range
                count += 1
                graphStore.pop(0)                           # removes first item of array, effectively scrolling graph

        plt.show()                              # display
        plt.pause(0.001)                        # because humans are slow


while(True):                                    # change to a way to sense data >>>JUDAH
        y = float(serialData.readline())
        dataStore.append(y)
        graphStore.append(y)
        graph()

with open('sensor_data.csv','w') as data_output:
        datawriter = csv.writer(data_output, delimiter = ',')
        datawriter.writerow(dataStore)
