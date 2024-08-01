import serial
from pynput.keyboard import Key, Controller

# Inicialize a comunicação serial
ser = serial.Serial('COM7', 115200)  # Substitua 'COM3' pela porta serial correta

# Inicialize o controlador do teclado
keyboard = Controller()

# Dicionário para mapear as mensagens do Arduino para as teclas correspondentes
key_map = {
    "H": 'h',  # RED piezo
    "I": 'i',  # YELLOW piezo
    "J": 'j',  # BLUE piezo
    "K": 'k',  # GREEN piezo
    "A": 'a',  # dpad U
    "B": 'b',  # dpad R
    "C": 'c',  # dpad D
    "D": 'd',  # dpad L
    "G": 'g',  # kick
    "E": 'e',  # select
    "F": 'f'   # start
}

try:

    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print(f"Received: {data}")
            if data in key_map:
                key = key_map[data]
                keyboard.press(key)
                keyboard.release(key)
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()