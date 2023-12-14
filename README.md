# PES_Final_project

PES Final Project Report Topic – Weather Monitoring Station
Name: Tharuni Gelli
Objective
Due to numerous instances of fires occurring in and around Boulder, I conceived the notion of
establishing a weather surveillance station. The objective of this initiative is to consistently observe the
climate by employing a temperature/humidity sensor (SHT21) for continuous temperature monitoring and
an MQ7 sensor designed to detect concentrations of CO in the air.
Implementation
1) Before the main function begins, the FRDM-KL25Z initiates PWM and conducts
automated tests with varying values of the RGB LED in Danger, Warning, and Safe
states.
2) Initiate the initialization process for all other modules utilized in the project, followed
by executing automated tests specifically designed for the circular buffer..
3)The FRDM-KL25Z retrieves temperature, humidity, and CO level values from the SHT21
(Temperature/Humidity sensor) and MQ7 (CO Sensor).
4) The SHT21 is interfaced using the I2C communication protocol, with I2C1 being
employed specifically for the SHT21. And the MQ7 is interfaced using the internal ADC.
5) Initiating the command processor, which can receive various inputs and generate
corresponding outputs. The menu is structured as follows:
Enter 'Author' to retrieve the Author's name.
Enter 'Dump' with Arguments: (Start, Len) to obtain a hex dump of the requested
memory.
Enter 'Temperature' to display the surrounding temperature.
Enter 'Humidity' to display the surrounding humidity levels.
Enter 'CO' to display the surrounding CO levels.
Enter 'Weather' to initiate the Weather Monitoring station.
Enter 'Help' to view available weather options.
6) Enter the string ‘‘weather’ to start weather monitoring.
7) UART is employed to showcase the temperature, humidity, and CO level values upon
the initiation of the weather monitoring station. Additionally, warning messages such as
danger, warning, and safe are printed.
8) PWM is employed for controlling RGB LEDs, serving as indicators for various
situations:
● GREEN signifies the safe state.
● YELLOW signifies the warning state.
● RED signifies the danger state.
9) The Systick timer and delay function are utilized to introduce a delay

DEmo video lonk of the project:
https://drive.google.com/file/d/1ECQBSjFKeMyf-O8mTz99O8KQSbWXjLNk/view?usp=drive_link
