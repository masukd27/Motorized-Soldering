import serial
import numpy as np
import matplotlib.pyplot as plt

rp = serial.Serial('COM5', 115200, timeout=1)  # RP2040
uno = serial.Serial('COM6', 9600, timeout=1)   # UNO

threshold = 120.0

plt.ion()
fig, ax = plt.subplots()
img = ax.imshow(np.zeros((24, 32)), cmap='inferno', vmin=20, vmax=100)
plt.colorbar(img)

while True:
    line = rp.readline().decode('utf-8').strip()

    if line.startswith("Max Temp:"):
        try:
            temp = float(line.split(":")[1].strip())
            print("🔥", temp)
            if temp > threshold:
                uno.write(b'ON\n')
        except:
            continue
        continue

    if line == "ON" or line == "getFrame failed":
        print(line)
        continue

    try:
        values = [float(x) for x in line.split(",")]
        if len(values) == 768:
            matrix = np.array(values).reshape((24, 32))
            img.set_data(matrix)
            plt.pause(0.01)
    except:
        continue
