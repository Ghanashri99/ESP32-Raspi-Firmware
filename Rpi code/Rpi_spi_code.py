import spidev
import time

# Create SPI object and open bus 0, device 0 (CE0)
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 500000
spi.mode = 0b00

# 👇 This is the variable you can change easily
message_to_send = "RUN"

def send_and_receive_string(msg):
    buffer_size = 32
    data = list(msg.encode('utf-8'))
    data += [0] * (buffer_size - len(data))  # Pad to 32 bytes

    print(f"Sending: {msg}")
    response = spi.xfer2(data)

    received = bytes(response).decode('utf-8').rstrip('\x00')
    print(f"Received from ESP32: {received}\n")

try:
    while True:
        send_and_receive_string(message_to_send)
        time.sleep(2)

except KeyboardInterrupt:
    print("Stopped by user")
    spi.close()

