##############Missouri University of Science and Technology#############
#                        Mars Rover Design Team                        #
#        Author: Matthew Healy    mhrh3@mst.edu                        #
#                                                                      #
#        serial input in real time.                                    #
#                                                                      #
#        Usage: python3.4 sciplot.py [-h] [-p] [-b] [-f] [-m] [-s]     #
#                                                                      #
#   Note: This script should be run from within the directory          #
#           That you wish to use to store the .csv file on exit, as    #
#           saves to the current directory                             #
########################################################################



import serial                   # used for .readline()					
import numpy			# used for arange()			
import matplotlib.pyplot as plt # used for all of plotting
import csv                      # used for csv.writer() and writerow()
import argparse                 # used for argparse.ArgumentParser()

# used for auto-selection of serial ports
import glob
import sys

global count                    # data count
global MAX_PLOT_SIZE
global beginData                # beginning of x range
global endData                  # ending of x range
global filename
global port
global sensorType

count = 0
relativeCount = []
plt.ion()
dataStore = []
graphStore = []


dataRange = []
beginData = 0
endData = 0

port = 0
baudrate = 9600


def identify_serial():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
        
    """
    # parses name of operating system and assigns corrolating prefix for serial port
    # then checks which serial port is recieving data, and returns that
    
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        return 0

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass

    valid_ports = []
    for port in result:
        testinput = serial.Serial(port, 9600, timeout=.001)
        print("Testing serial input: ",port)
        testdata = testinput.readline()
        try:
            print(float(testdata))
        except (NameError, ValueError):
            print("Serial input invalid: ",port)
            
            pass
        else:
            print("Valid port: ", port)
            valid_ports.append(port)
    if (len(valid_ports) == 1):
        return port
    else:
        print("There is more than one valid serial input, you must specify which to use by using th -p tag.")
        print("These are the valid inputs: ",valid_ports)


def graph():
    global count
    if sensorType=="humidity":
        upperY = 900
        lowerY = -5
    elif sensorType=="temp":
        upperY =  100
        lowerY = -15
    if (count < MAX_PLOT_SIZE): # holding still
        plt.clf()               # clear current plot
        plt.scatter(count,graphStore[count])
        plt.ylim(lowerY,upperY)
        plt.grid(True)
        plt.title(sensorType)
        plt.plot(graphStore)
        plt.show()
        count += 1
    else:                       # start scrolling
        plt.clf()               # clear current plot
        endData = count+1
        beginData = (count - MAX_PLOT_SIZE)
        dataRange = numpy.arange(beginData,(endData))
        plt.ylim(lowerY,upperY)
        plt.grid(True)
        plt.title(sensorType)
        plt.scatter(dataRange,graphStore)
        plt.plot(dataRange,graphStore)
        plt.show
        count += 1
        graphStore.pop(0)
    plt.pause(0.0001)

def main():
        serialport = identify_serial()
        
        
        parser = argparse.ArgumentParser(description='plot scientific data in real time')
        parser.add_argument('-p', default='/dev/tty.usbmodem1411', action="store", dest="port",help="name of serial input")
        parser.add_argument('-b', default=9600, action="store", dest="baudrate", help="baudrate for data transfer")
        parser.add_argument('-f', default="sensor_data", action="store", dest="filename", help="name of file for data to be stored in")
        parser.add_argument('-m', default=7, action="store", dest="MAX_PLOT_SIZE", help="maximum size for x axis (recommended < 10)")
        parser.add_argument('-s', default="humidity", action="store", dest="sensor", help="sensor being used, in order to correctly title plot")

        args = parser.parse_args()
                                # reed to specify global variables for modification
        global MAX_PLOT_SIZE
        global filename
        global port
        global sensorType
        MAX_PLOT_SIZE = args.MAX_PLOT_SIZE
        port = args.port
        filename = args.filename + '.csv'
        serialData = serial.Serial(port, baudrate)
        sensorType = args.sensor
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
