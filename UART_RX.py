import serial
import time
ser = serial.Serial("/dev/cu.usbserial-AI05GG94")
fileNum = 1
while (1):
	fileName = "audioTest" + str(fileNum) + ".raw"
	file = open(fileName,"w")
	while (1):
		with serial.Serial("/dev/cu.usbserial-AI05GG94", 9600) as ser:
			x = ser.read()
		if (x == END_OF_FILE_INDICATOR):
			break
		file.write(x)
	file.close()
	fileNum = fileNum + 1