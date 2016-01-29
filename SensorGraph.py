import serial 						
import numpy						
import matplotlib.pyplot as plt 	

count = 0
plt.ion()	  ##########READ THIS############        # interactive mode to plot live data
dataStore = []  			        # empty list of data
serialData = serial.Serial('com4', 9600) 	# object to read from serial port
						# port_no and baudrate

plt.plot(dataStore, 'ro-', label='Temperature')	
plt.ylim(-5,100)
plt.grid(True)
plt.title("Sensor Data")


while (True):
        y = float(serialData.readline())
        dataStore.append(y)
        plt.scatter(count,dataStore[count])
        count += 1
        plt.show()
        plt.pause(0.001)
