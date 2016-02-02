######## Missouri University of Science and Technology########
#        Mars Rover Design Team                              #
#        Author: Matthew Healy    mhrh3@mst.edu              #
#                                                            #
#    SciPlot is a graphing module that plots data from a     #
#    serial input in real time.                              #
#                                                            #
#  Usage: python3.4 sciplot.py [-h] [-p] [-b] [-f] [-m] [-s] #
##############################################################



import serial 						
import numpy						
import matplotlib.pyplot as plt
import csv
import argparse

global count
global MAX_PLOT_SIZE
global beginData
global endData
global filename
global port
global sensor

count = 0
relativeCount = []
plt.ion()
dataStore = []
graphStore = []

MAX_PLOT_SIZE = 7

dataRange = []
beginData = 0
endData = 0

plt.plot(graphStore, 'r,', label='Humidity')
port = 0
baudrate = 9600



def graph():
        global count
        if (count < MAX_PLOT_SIZE):
                plt.clf()
                plt.scatter(count,graphStore[count])
                plt.ylim(-5,100)
                plt.grid(True)
                plt.title(sensor)
                plt.plot(graphStore)
                plt.show()
                count += 1
        else:
                plt.clf()
                endData = count+1
                beginData = (count - MAX_PLOT_SIZE)
                dataRange = numpy.arange(beginData,(endData))
                plt.ylim(-5,100)
                plt.grid(True)
                plt.title(sensor)
                plt.scatter(dataRange,graphStore)
                plt.plot(dataRange,graphStore)
                plt.show
                count += 1
                graphStore.pop(0)
        plt.pause(0.0001)

def main():
        parser = argparse.ArgumentParser(description='plot scientific data in real time')
        parser.add_argument('-p', default="/dev/tty.usbmodem0F005721", action="store", dest="port",help="name of serial input")
        parser.add_argument('-b', default=9600, action="store", dest="baudrate", help="baudrate for data transfer")
        parser.add_argument('-f', default="sensor_data", action="store", dest="filename", help="name of file for data to be stored in")
        parser.add_argument('-m', default=7, action="store", dest="MAX_PLOT_SIZE", help="maximum size for x axis (recommended < 10)")
        parser.add_argument('-s', default="Sensor Data", action="store", dest="sensor", help="sensor being used, in order to correctly title plot")

        args = parser.parse_args()
        global MAX_PLOT_SIZE
        MAX_PLOT_SIZE = args.MAX_PLOT_SIZE
        global port
        port = args.port
        global filename
        filename = args.filename + '.csv'
        serialData = serial.Serial(port, baudrate)
        sensor = args.sensor
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
