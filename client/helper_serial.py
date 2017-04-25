import sys
import serial

arduino = serial.Serial(sys.argv[1], 57600, timeout=5)
arduino.flush()
arduino.write("\n")
print "[PYTHON] helper_serial done!!!"
