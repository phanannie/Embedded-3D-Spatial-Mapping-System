# Student name: Annie Phan
# Student number: 400380760
# Python version: 3.8.10

import serial
import math

# Setup serial port. Adjust 'COM4' to your device's port.
ser = serial.Serial('COM4', 115200)

# Open a file to append distance data. Rename "distance_data.xyz" as needed.
f = open("distance_data.xyz", "a")

# Initialize variables for scanning.
i = 0  # Step counter for angle calculation.
x = 0  # Initial x-displacement in millimeters.
increment = 100  # Set increment in mm for each full scan. Adjust as needed.

# Continuous read and write loop.
while True:  
    s = ser.readline()
    a = s.decode("utf-8").strip()  # Clean up input string.
    
    if a.isdigit():  # Check for numeric data.
        angle = (i / 32) * 2 * math.pi  # Calculate angle for current step.
        dist = int(a)  # Convert distance string to integer.
        y = dist * math.cos(angle)  # Calculate y-coordinate.
        z = dist * math.sin(angle)  # Calculate z-coordinate.
        f.write(f'{x} {y} {z}\n')  # Save x, y, z to file.
        i += 1
        
        # Reset and increment x after a full rotation.
        if i == 32:
            i = 0
            x += increment

    # Handle non-numeric data or end of data set.
    elif i > 0:  
        f.close()  # Save and close file to ensure data integrity.
        f = open("distance_data.xyz", "a")  # Reopen for next data set.
        i = 0  # Reset step counter.

    # Debug output: current data string and x-displacement.
    print(a, x)

