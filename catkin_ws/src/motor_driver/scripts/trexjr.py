import serial

class TrexJr:
	def __init__(self):
		self.port = serial.Serial('/dev/ttyAMA0', 19200)
	def stop(self):
		self.port.write("\xC5\x00\xCE\x00")
	def move(self, leftspeed, rightspeed):
		""" leftspeed and rightspeed are betwee -127 and 127 """ 
		if (rightspeed < 0):
			self.port.write(chr(0xC6)) #reverse right
		else:
			self.port.write(chr(0xC5)) #forward right
		self.port.write(chr(abs(rightspeed)))

		if (leftspeed < 0):
			self.port.write(chr(0xCE))
		else:
			self.port.write(chr(0xCD))
		self.port.write(chr(abs(leftspeed)))
