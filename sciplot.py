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
import glob
import sys

sensor_type = "humidity"
count = 0
relative_count = []
plt.ion()
data_store = []
graph_store = []

MAX_PLOT_SIZE = 7

data_range = []
begin_data = 0
end_data = 0

port = 0
baud_rate = 9600


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
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
    return result


def serial_check(list_of_ports):
    valid_ports = []
    for port in list_of_ports:
        test_input = serial.Serial(port, 9600, timeout=.001)
        print("Testing serial input: ",port)
        test_data = test_input.readline()
        try:
            print(float(test_data))
        except (NameError, ValueError):
            print("Serial input invalid: ",port)
            pass
        else:
            print("made it to else clause")
            valid_ports.append(port)
    if (len(valid_ports) == 1):
        return port
    else:
        print("There is more than one valid serial input, you must specify which to use by using th -p tag.")
        print("These are the valid inputs: ",valid_ports)


def graph():
    global count
    global sensor_type
    if sensor_type=="humidity":
        upperY = 900
        lowerY = -5
    elif sensor_type=="temp":
        upperY =  100
        lowerY = -15
    if (count < MAX_PLOT_SIZE): # holding still
        plt.clf()               # clear current plot
        plt.scatter(count,graph_store[count])
        plt.ylim(-5,100)
        plt.grid(True)
        plt.title(sensor_type)
        plt.plot(graph_store)
        plt.show()
        count += 1
    else:                                       # start scrolling graph
        plt.clf()
        end_data = count+1
        begin_data = (count - MAX_PLOT_SIZE)
        data_range = numpy.arange(begin_data,(end_data))
        plt.ylim(-5,100)
        plt.grid(True)
        plt.title(sensor_type)
        plt.scatter(data_range,graph_store)
        plt.plot(data_range,graph_store)
        plt.show()
        count += 1
        graph_store.pop(0)
    plt.pause(0.0001)

def main():
        ports_list = serial_ports()
        print("Found list of availible serial inputs: ", ports_list)
        serial_port = serial_check(ports_list)
        
        parser = argparse.ArgumentParser(description='plot scientific data in real time')
        parser.add_argument('-p', default="COM4", action="store", dest="port",help="name of serial input")
        parser.add_argument('-b', default=9600, action="store", dest="baudrate", help="baudrate for data transfer")
        parser.add_argument('-f', default="sensor_data", action="store", dest="file_name", help="name of file for data to be stored in")
        parser.add_argument('-m', default=7, action="store", dest="MAX_PLOT_SIZE", help="maximum size for x axis (recommended < 10)")
        parser.add_argument('-s', default="Sensor Data", action="store", dest="sensor_type", help="sensor being used, in order to correctly title plot")

        args = parser.parse_args()
        MAX_PLOT_SIZE = args.MAX_PLOT_SIZE
        port = args.port
        file_name = args.file_name + '.csv'
        serial_data = serial.Serial(port, baud_rate)
        sensor_type = args.sensor_type
        while(True):
            try:
                y = float(serial_data.readline())
                data_store.append(y)
                graph_store.append(y)
                graph()
            except(KeyboardInterrupt,SystemExit):
                with open(file_name,'w') as data_output:
                    datawriter = csv.writer(data_output, delimiter = ',')
                    datawriter.writerow(data_store)
                raise
                    
if __name__=="__main__":
        main()
