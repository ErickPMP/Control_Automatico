import sys, serial, argparse
import numpy as np
import csv
from time import time, sleep
from collections import deque
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# 🛠️ Define la cantidad de sensores (cámbialo según necesites)
NUM_SENSORS = 4  # Cambia este valor para agregar o quitar sensores
TIEMPO_MOSTRADO = 20
PUERTO = 'COM20'

class AnalogPlot:
    def __init__(self, strPort, maxLen):
        self.ser = serial.Serial(strPort, 9600, timeout=1)

        # Esperar a que Arduino envíe "READY"
        while True:
            line = self.ser.readline().decode().strip()
            if line == "READY":
                break

        # Enviar 'S' para indicar que puede empezar a enviar datos
        self.ser.write(b'S')

        # Inicializar listas dinámicas para sensores y tiempo
        self.sensors = [deque([0.0] * maxLen, maxlen=maxLen) for _ in range(NUM_SENSORS)]
        self.time_stamps = deque([0.0] * maxLen, maxlen=maxLen)
        self.start_time = time() #ADICIONAL MODIF

        # Crear archivo CSV con encabezado dinámico
        self.csv_file = open("C:/Yo/datos2.csv", "w", newline="")
        self.csv_writer = csv.writer(self.csv_file)
        headers = ["Tiempo"] + [f"Sensor {i+1}" for i in range(NUM_SENSORS-1)]
        self.csv_writer.writerow(headers)

    def add(self, data):
        assert len(data) == NUM_SENSORS, f"Esperando {NUM_SENSORS} sensores, pero recibidos {len(data)}"
        
        for i in range(NUM_SENSORS):
            self.sensors[i].append(data[i])
        
        self.time_stamps.append(data[0])
        # Guardar datos en CSV
        self.csv_writer.writerow(data)

    def update(self, frameNum, lines, ax):
        try:
            line = self.ser.readline().decode().strip()
            data = [float(val) for val in line.split()]

            if len(data) == NUM_SENSORS:
                self.add(data)
                
                # Actualizar gráficos dinámicamente
                for i in range(NUM_SENSORS-1): #MODIF
                    lines[i].set_data(self.time_stamps, self.sensors[i+1]) #MODIF

                ax.set_xlim(self.time_stamps[0], self.time_stamps[-1])

        except ValueError:
            print("Error al convertir datos, posible ruido en la comunicación.")
        except Exception as e:
            print(f"Error inesperado: {e}")
        
        return lines

    def close(self):
        self.ser.close()
        self.csv_file.close()

def main():
    parser = argparse.ArgumentParser(description="LDR serial")
    parser.add_argument('--port', dest='port', required=False, default=PUERTO)
    args = parser.parse_args()
    strPort = args.port

    print(f'Reading from serial port {strPort}...')

    analogPlot = AnalogPlot(strPort, TIEMPO_MOSTRADO*10)

    print('Plotting data...')

    fig, ax = plt.subplots()
    ax.set_xlim(0, TIEMPO_MOSTRADO)
    ax.set_ylim(-800, 600)
    ax.set_xlabel("Tiempo (s)")
    ax.set_ylabel("Lectura del sensor")
    ax.grid()

    # Crear líneas de ploteo dinámicamente
    lines = [ax.plot([], [], label=f"Sensor {i+1}")[0] for i in range(NUM_SENSORS-1)] # MODIF
    ax.legend(loc="upper right")

    anim = animation.FuncAnimation(fig, analogPlot.update, 
                                   fargs=(lines, ax), 
                                   interval=100,
                                   cache_frame_data=False)

    plt.show()
    analogPlot.close()
    print('Exiting.')

if __name__ == '__main__':
    main()
