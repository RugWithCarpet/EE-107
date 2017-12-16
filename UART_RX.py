## Auto-Dictator ##
## Computer-side serial receive python code ##
## Raymond Reynolds ##
## Vickram Gidwani ##
## Alex Kucy ##

import serial #pyserial package
import time

#in kHz (for file naming purposes)
freq = 25 #4, 8, 16, 25
fileName = "audioTest_" + str(freq) + "kHz.raw" #name file
samplingTime = 5 #5 seconds of sampling time
numSamples = freq*1000*samplingTime #number of total bytes to be collected (8 bit depth, so 1 byte per sample)
file = open(fileName,"w")
with serial.Serial("/dev/cu.usbserial-AI05GG94", 230400) as ser: #baud rate of 230400 for support up to 230400/8 = 28.8 kHz sampling
	x = ser.read(numSamples)
file.write(x)
file.close()