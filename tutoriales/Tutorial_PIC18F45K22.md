# Guía introductoria del PIC18F45K22 con PICkit 3 y MPLAB X IDE

## 1. Introducción

El ```PIC18F45K22``` es un microcontrolador de 8 bits de Microchip con una frecuencia de operación de hasta 64 MHz y 35 pines de entrada/salida. Esta guía te guiará a través de la programación del PIC18F45K22 usando MPLAB X IDE, el compilador XC8 y el programador PICkit 3.

## 2. Arquitectura del PIC18F45K22

El PIC18F45K22 utiliza una arquitectura Harvard con memoria de programa y datos separadas. Su estructura interna incluye:

CPU de 8 bits con un conjunto de instrucciones optimizado para control embebido.

Memoria Flash de 32 KB para almacenamiento del programa.

RAM de 1536 Bytes para datos temporales.

EEPROM de 256 Bytes para almacenamiento de datos no volátiles.

Bus de datos de 8 bits y bus de direcciones de 21 bits.

Registros de propósito general y especiales para control y configuración.

Pila de hardware de 31 niveles para control de subrutinas e interrupciones.

Módulo de reloj con opciones de oscilador interno y externo.

3. Características principales del PIC18F45K22

35 pines de E/S configurables.

2 módulos UART, 2 SPI, 2 I2C.

Temporizadores de 8, 16 y 32 bits.

Módulos de PWM y ADC de 10 bits.

Interrupciones anidadas con priorización programable.

4. Herramientas necesarias

4.1. Hardware

Microcontrolador PIC18F45K22

Programador PICkit 3

Placa de desarrollo o protoboard

Cristal de 16 MHz con capacitores de 22pF (opcional)

LEDs, resistencias, cables

4.2. Software

MPLAB X IDE

Compilador XC8

Drivers y software de PICkit 3

5. Configuración de MPLAB X IDE

Descargar e instalar MPLAB X IDE y el compilador XC8 desde Microchip.

Abrir MPLAB X IDE y crear un nuevo proyecto:

Seleccionar PIC18F45K22.

Elegir el compilador XC8.

Configurar la herramienta de programación como PICkit 3.

6. Configuración de PICkit 3

Conectar el PICkit 3 al PC e instalar los drivers.

Conectar el PICkit 3 al PIC18F45K22 usando el siguiente diagrama:

PICkit 3 Pin

PIC18F45K22 Pin

VPP (MCLR)

MCLR (pin 1)

VDD

VDD (pines 11 y 32)

VSS

GND (pines 12 y 31)

PGD

RB7 (pin 40)

PGC

RB6 (pin 39)

Seleccionar PICkit 3 en MPLAB X y verificar la conexión.

7. Primer programa: Parpadeo de LED

7.1. Configuración del código en MPLAB X