import serial
import time

#in kHz (for file naming purposes)
freq = 25 #4, 8, 16, 25
fileName = "audioTest_" + str(freq) + "kHz.raw"
file = open(fileName,"w")
with serial.Serial("/dev/cu.usbserial-AI05GG94", 230400) as ser: #baud rate of 230400 for support up to 230400/8 = 28.8 kHz sampling
	x = ser.read(125000) #5*sampling frequency for 5 seconds of audio (8 bit depth, so 1 byte per sample)
file.write(x)
file.close()