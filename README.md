# Diode Curve Tracer

## Overview

This project is a diode curve tracer that uses an Arduino Uno microcontroller to measure and display the I-V characteristics of diodes. The measured curves are displayed on a 128x64 LCD screen using SPI configuration, providing a clear visualization of the diode's performance.

### Features

- *Microcontroller:* Utilizes an Arduino Uno for control and measurement.
- *Display:* 128x64 LCD screen to plot the I-V characteristics in real-time.
- *Measurement Range:* Capable of measuring diodes with a forward voltage up to 4.8V. Diodes with a saturation/breakdown voltage above 4.8V will not be fully drawn.
- *User Interface:* Simple push-button interface to start and stop measurements.
- *Accuracy:* High-precision analog-to-digital conversion to ensure accurate curve plotting.

## Components

- *Arduino Uno*
- *MCP4725 DAC* for voltage sweep across the diode
- *128x64 LCD Screen (SPI Configuration)*
- *100 Ohm Resistor* to measure the current through the diode
- *Diode Under Test (DUT)*
- *Connecting Wires*

## How It Works

1. *Setup:* Connect the diode to the measurement circuit, ensuring proper polarity.
2. *Measurement:* The MCP4725 DAC generates a controlled voltage across the diode, measuring the resulting current through a 100 Ohm resistor.
3. *Plotting:* Data points are collected and plotted on the LCD screen, displaying the I-V curve.
4. *Analysis:* Users can analyze the curve to understand the diode's characteristics, such as forward voltage and reverse breakdown voltage.

## Getting Started

1. *Clone the Repository:*
   bash
   git clone https://github.com/yourusername/diode-curve-tracer.git
   
2. *Upload the Code:* Open the project in the Arduino IDE and upload the code to your Arduino Uno.
3. *Connect Components:* Set up the hardware as per the provided circuit diagram.
4. *Run the Project:* Power up the Arduino and observe the I-V curve on the LCD screen.

## Simulation in Proteus

To run the simulation in Proteus, you must have the following libraries installed:

- *128x64 LCD Library:* [Download here](https://github.com/cdhigh/lcd12864_st7920_proteus)
- *Arduino Library:* [Download here](https://github.com/officialdanielamani/proteus-library-collection)

Ensure these libraries are added to your Proteus installation before running the simulation.

## Future Improvements

- *Data Logging:* Add functionality to log data to an SD card for later analysis.
- *PC Interface:* Develop a software interface to display the curves on a computer.
- *Multiple Diodes:* Implement functionality to switch between multiple diodes for comparative analysis.

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests for any enhancements or bug fixes.

## Acknowledgments

Special thanks to the open-source community and various online resources that inspired this project.

---

Feel free to adjust any details to better match your project's specifics.
