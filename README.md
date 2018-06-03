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
