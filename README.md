# PES_Final_project

## Climate Data Logger

**Project Report by Tharuni Gelli**

### Objective

Due to numerous instances of fires occurring in and around Boulder, I conceived the notion of establishing a weather surveillance station. The objective of this initiative is to consistently observe the climate by employing a temperature/humidity sensor (SHT21) for continuous temperature monitoring and an MQ7 sensor designed to detect concentrations of CO in the air.

### Implementation

1. Before the main function begins, the FRDM-KL25Z initiates PWM and conducts automated tests with varying values of the RGB LED in Danger, Warning, and Safe states.
2. Initiate the initialization process for all other modules utilized in the project, followed by executing automated tests specifically designed for the circular buffer.
3. The FRDM-KL25Z retrieves temperature, humidity, and CO level values from the SHT21 (Temperature/Humidity sensor) and MQ7 (CO Sensor).
4. The SHT21 is interfaced using the I2C communication protocol, with I2C1 being employed specifically for the SHT21. And the MQ7 is interfaced using the internal ADC.
5. Initiating the command processor, which can receive various inputs and generate corresponding outputs.
   - Enter 'Author' to retrieve the Author's name.
   - Enter 'Dump' with Arguments: (Start, Len) to obtain a hex dump of the requested memory.
   - Enter 'Temperature' to display the surrounding temperature.
   - Enter 'Humidity' to display the surrounding humidity levels.
   - Enter 'CO' to display the surrounding CO levels.
   - Enter 'Weather' to initiate the Weather Monitoring station.
   - Enter 'Help' to view available weather options.
6. Enter the string ‘‘weather’ to start weather monitoring.
7. UART is employed to showcase the temperature, humidity, and CO level values upon the initiation of the weather monitoring station. Additionally, warning messages such as danger, warning, and safe are printed.
8. PWM is employed for controlling RGB LEDs, serving as indicators for various situations:
   - GREEN signifies the safe state.
   - YELLOW signifies the warning state.
   - RED signifies the danger state.
9. The Systick timer and delay function are utilized to introduce a delay

## UART Configuration

1. Baud Rate - 38400
2. Data bits - 8
3. Stop bit - 2
4. Parity - None

## Technology Used

- I2C (Inter-Integrated Circuit): Utilized to interface with the SHT21 temperature and humidity sensor, expanding knowledge beyond the classroom setting.
- ADC (Analog-to-Digital Converter): Applied for interfacing with the MQ7 CO sensor, extending the understanding gained in Assignment 7 to extract data from an external sensor.
- UART (Universal Asynchronous Receiver-Transmitter): Employed for displaying sensor data on the terminal, building on previous assignments.
- PWM (Pulse Width Modulation): Used to control an RGB LED, providing visual indicators for various weather conditions.

## Learning Objectives

- I2C Communication Protocol: Understanding the intricacies of the I2C protocol, necessary for interfacing with the SHT21 sensor and extracting temperature and humidity data.
- ADC for External Sensor: Expanding ADC knowledge to extract data from an external sensor (MQ7 CO sensor) and displaying it through UART.
- Strengthening UART and PWM Concepts: Reinforcing the foundation of UART and PWM through practical implementation in the project.
- Command Processor Implementation: Adding a command processor to enhance the project's functionality and user interaction.

## Hardware Used

- SHT21 Sensor: Provides temperature and humidity data for weather monitoring.
- MQ7 CO Sensor: Measures carbon monoxide levels, contributing to comprehensive environmental monitoring.

## Bonus Implementation

In addition to the core functionalities, the project includes a bonus feature:

- Humidity Sensing: Extracting humidity data from the SHT21 sensor along with temperature values, offering a more complete weather monitoring solution.

## Demo Video

[Watch the demo video](https://drive.google.com/file/d/1ECQBSjFKeMyf-O8mTz99O8KQSbWXjLNk/view?usp=drive_link)

Demo video lonk of the project:
https://drive.google.com/file/d/1ECQBSjFKeMyf-O8mTz99O8KQSbWXjLNk/view?usp=drive_link
