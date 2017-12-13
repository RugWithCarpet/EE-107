import serial
import time
ser = serial.Serial("/dev/cu.usbserial-AI05GG94")
fileNum = 1
while (1):
	fileName = "audioTest" + str(fileNum) + ".txt"
	file = open(fileName,"w")
	while (1):
		with serial.Serial("/dev/cu.usbserial-AI05GG94", 9600) as ser:
			x = ser.read()
		if (str(x, 'utf-8') == '\n'):
			break
		file.write(str(x,'utf-8'))
	file.close()
	fileNum = fileNum + 1