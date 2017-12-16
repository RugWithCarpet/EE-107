--- Auto-Dictator readme.txt ---
Created by: Alex Kucy, Vickram Gidwani, Raymond Reynolds


The following readme contains step-by-step instructions on how to operate the Auto-Dictator.


//Software//

Relevant files: main.c, led.c, led.h, mom_button.c, mom_button.h, uart.c, uart.h, adc.c, adc.h

This project can be compiled and built as is in the TI Code Composer Studio. Along with the files above, this project uses the TI driverlib (folder included in package) and a modified linker file (also included in package).

In order to change the sampling frequency, two parameters in adc.c must be changed. The directions are commented at the top of the file and amongst the code. This file is made to support four different sampling frequencies: (4, 8, 16, 25 kHz). The table below shows how the relevant parameters in this file need to be set to achieve each of these frequencies.

Sampling Frequency (kHz)	| timer_param.timerPeriod	| CCR1_param.compareValue
----------------------------|---------------------------|-------------------------
	4						|			499				|			498
	8						|			249				|			248
	16						|			124				|			123
	25						|			79				|			78


In addition to the code in the project is the UART_RX.py serial recieve code. This code also needs to be adjusted according the sampling frequency chosen. Firstly, the 'freq' parameter needs to be changed to the kHz value of sampling frequency chosen (4, 8, 16, 25). The 'samplingTime' parameter can also be changed to adjust the number of seconds for which samples are collected, but the default value of 5 is good for testing.



//Collecting RAW files//

In order to collect audio samples into raw files on a computer, the board needs to be running the code from the project, it needs to be powered, and it needs to be connected to via its miniUSB output to a computer's USB port. UART_RX.py should then be run on the computer. The button on the board starts the generation of samples. The script will collect 'samplingTime' (defulat = 5) seconds of samples and then generate a file named "audioTest_FREQkHz.raw" where FREQ is the frequency of kHz chosen. For example after changing the appropriate settings in adc.c and UART_RX.py, an audio signal sampled at 8 kHz will have an output file named "audioTest_8kHz.raw". Before starting UART_RX.py, one must make sure that the file that the code should generate does not already exist in the same directory as the python code.

The board also supports starting and stopping recording by use of the momentary button. This functionality does not change the overall length of an output file, but just stops the generation of samples. If the python code has not made an output file, further samples will need to be generated until 'samplingTime' seconds of samples have been collected. In effect, the momentary button serves to pause the recording. Another implication of this is that the audio output file will only have 'samplingTime' seconds of audio samples, even if the LED indicator on the board is still on because the button has not been pressed. In this state, the board is still generating samples, but they are not being received by the computer.



//Cloud Processing//

We use Audacity to convert our .raw audio into .flac audio format. The .flac file is then uploaded to Google Cloud Platform, where we then use the Google Speech API to transcribe the audio into a text printout.


/Audacity/

To open your raw audio samples in Audacity, select File > Import > Raw Data. Then input your audio sample’s bit encoding, byte order, and sampling rate. Your .raw audio will now play in Audacity.

To export your audio into the .flac audio format, you will first need to install the ffmpeg plug-in into Audacity. Please see Audacity’s documentation for further details.Once ffmpeg is installed, go to File > Save Other > Export Audio. Select “Open custom FFmpeg format options” to open the FFmpeg menu, from which you select flac for both the format and codec. Then save your file and Audcaity will export your .flac audio file.


/Google Speech API/

To use Google Speech API, you will first need to create an account with Google Cloud Platform Services. 

Once your account is set up, you will then need to create a project and generate an API key for that project. You will use this API key to allow your applications to call on and then authenticate with any of Google’s cloud APIs. Use this API key to enable Google Speech API. For further details of authenticating with Google Cloud, please visit their documentation.

Within your project, you will then create a storage bucket. Upload your .flac audio file to this storage bucket.

Open up Google cloudshell. You will use this terminal to run your program. Upload the python script (transcribe.py) to the cloudshell. For further details about the scripts operation, please see the comments inside transcribe.py

Run the command $ python transcribe.py gs://BUCKET_NAME/FILE_NAME.flac

When Google Speech API has finished processing your audio, it will return a text output that is the transcription of your audio. Should you desire it, you can also receive a confidence score for the transcription.

You may now handle the returned text however you like, a simple print statement or have it written into a file to be passed to other programs. The text output completes the function of Auto-Dictator.