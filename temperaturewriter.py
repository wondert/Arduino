"""temperaturewriter listens to serial port and writes contents to file."""
import serial       # requires pySerial package

serial_port = 'COM4'    # '/dev/tty.usbserial' may also work
baud_rate = 9600

ser = serial.Serial(serial_port, baud_rate, timeout=5)
while True:
    line = ser.readline()
    line = line.decode('utf-8')     # ser.readline returns a binary, convert to unicode encoding utf-8 and print string'
    print(line)

'''
write_to_file_path = 'temperaturedata.txt'

output_file = open(write_to_file_path, 'w+')
ser = serial.Serial(serial_port, baud_rate, timeout=5)      # Always include timeout when using readline(). it can block out port without newline.

while True:
    line = ser.readline()
    line = line.decode('utf-8')     # ser.readline returns a binary, convert to string'
    print(line)
    output_file.write(line)
'''
