# haxyl
This is code for learning to interface with the Haxyls
Date: February 28, 2024
Author: Bryan Duarte

*** The original project used an ESP32 which was running Arduino/hapticFrames/hapticFrames.ino to drive the Haxyls. This could be done with an Arduino also if necessary.

*** The embedded code was running in python on a Raspberry PI. This code is  in Embedded Code/embedded_dynamic_handler.py and Embedded Code/embedded_static_handler.py. If running on another embedded system that is capable of running python the embedded_dynamic_handler.py might be the most helpful for learning how to set up and communicate with the Arduino/ESP32.

*** The Dynamic Haptic Patterns directory is how patterns were constructed to communicate real life scenarios expressed across the body through haptics. The Dynamic Haptic Patterns/dynamic patterns with descriptions.txt file lists out each dynamic haptic interaction along with the corresponding JSON strings to execute the pattern in haptics using the Haxyls. The Dynamic Haptic Patterns/dynamic_pattern_list.json file contains the JSON that is read in by the embedded handler code to execute each dynamic haptic interaction. The Dynamic Haptic Patterns/dynamic_pattern_list_builder.py is just a script I wrote to help generate the JSON file rather than trying to remember and enter numbers manually.

*** The GUI directory contains code to launch a GUI that drove the codefor executing user studies. This is not very helpful unless you are trying to run everything as I did and trying to manually select patterns. I ran this on a laptop. 


*** Work flow:
1. I had a wifi router set up at my desk that was just brodcasting a SSID. It was not internet connected it was only used to create a local network connection. 

2. I assigned this network to the ESP32, the Rasp PI, and connected my laptop to the network. With all devices talking on the same local network I was able to use my laptop to send patterns to the Rasp PI which then sent the JSON pattern over a serial connection to the ESP32. 

If you are asking why there was a laptop talking to a PI, and a PI talking to an ESP32 that is a great question. The answer is because the GUI is not the end use case. It was meant to be a self contained wearable solution so the PI is the main controller and the ESP32 is the chipset handling the haptic frames. Are both necessary? No, they are not both necessary; however, the set up allowed for heavier computations to be executed on the PI such as AI/ML while the ESP32 handled the rest. 

If someone uses this code to get started with the Haxyls and would like to submit code that has a different work flow please feel free to submit a pull request and I will consider adding it to the files I pulled together.
 