# dewomslrb
Repository for the DEWO MSLRB project and related.

## Directory Structure
* base - Base Station, linux based (Ubuntu 16.04 LTS Recommended)
* client - Client / Robo which connect to base station, Linux Raspi based (Debian Wheezy)

## HOW TO BUILD

### base (Running at Ubuntu machine)
* using terminal:
user@linux $ cd base/
user@linux $ make

* the executable ones can be found with name Dewo, just type this command to run:
user@linux $ ./Dewo

* if using another config file just place the .cfg file in the directory, type filename after ./Dewo:
user@linux $ ./Dewo config_sip.cfg

* to cleaning the build, just type this command:
user@linux $ make clean

### client (Running at Raspberry machine with Debian Wheezy)
* using terminal:
user@linux $ cd client/
user@linux $ make

* the executable ones can be found with name Dewo, just type this command to run:
user@linux $ ./Dewo

* if using another config file just place the .cfg file in the directory, type filename after ./Dewo:
user@linux $ ./Dewo config_sip.cfg

* to cleaning the build, just type this command:
user@linux $ make clean


## REQUIREMENTS
### for client (Raspberry machine)
* install opencv on raspberry, you can refer with this site:
https://robertcastle.com/2014/02/installing-opencv-on-a-raspberry-pi/

Or you can Googling and find one that works based on your own case.
* install python(if not installed yet, minimum python 2.0)

* install and plug USB-Camera and USB-TTL

## TROUBLESHOOT
if you have any problem, you can check this :
1. Check connection between usb to ttl and your arduino
2. Make sure your camera's cable plugged correctly. if you have an error, unplug and plug again the usb camera on usb port of raspberry pi, and you can rerun your program.
