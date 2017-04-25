from collections import deque
import numpy as np
import argparse
import serial

arduino = serial.Serial('/dev/ttyUSB0', 57600, timeout=5)
arduino.flush()
arduino.write("joss")	