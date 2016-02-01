import serial 						
import numpy						
import matplotlib.pyplot as plt
import csv
import argparse

global count
global MAX_PLOT_SIZE
global beginData
global endData
count = 0
relativeCount = []                              # count used for graphing once scrolling begins
plt.ion()	        		        # interactive mode to plot live data
dataStore = []                                  # empty list of data
graphStore = []                                 # empty list to store data being used by graph
serialData = serial.Serial('/dev/tty.usbmodem0F005721', 9600) 	# object to read from serial port
                                                # port_no and baudrate
MAX_PLOT_SIZE = 7                              # maximum graph size in x direction

dataRange = []                                  # y range for scrolling graph
beginData = 0
endData = 0

plt.plot(graphStore, 'r,', label='Humidity')


def graph():
        global count                                    # allow modification of count
        if (count < MAX_PLOT_SIZE):
                plt.clf()
                plt.scatter(count,graphStore[count])    # old graphing method
                plt.ylim(-5,100)
                plt.grid(True)
                plt.title("Sensor Data")
                plt.plot(graphStore)
                plt.show()
                count += 1                              ### count must be incremented in either case
        else:
                plt.clf()
                endData = count+1                          # end of x range
                beginData = (count - MAX_PLOT_SIZE)     # beginning of x range
                dataRange = numpy.arange(beginData,(endData))    # setting x range
                plt.ylim(-5,100)
                plt.grid(True)
                plt.title("Sensor Data")
                plt.scatter(dataRange,graphStore)       # graphing with specified range
                plt.plot(dataRange,graphStore)
                plt.show
        
                count += 1
                graphStore.pop(0)                           # removes first item of array, effectively scrolling graph

        plt.pause(0.001)                                # because humans are slow

def main():
        while(True):
                
                try:
                        y = float(serialData.readline())
                        dataStore.append(y)
                        graphStore.append(y)
                        graph()
                except(KeyboardInterrupt,SystemExit):
                        with open(filename,'w') as data_output:
                                datawriter = csv.writer(data_output, delimiter = ',')
                                datawriter.writerow(dataStore)

if __name__=="__main__":
        main()
