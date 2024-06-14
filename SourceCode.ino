#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <U8g2lib.h>  // Include U8g2 library for graphical functions

Adafruit_MCP4725 dac;
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

const int highSidePin = A0; // Analog pin setup for current measurement
const int lowSidePin = A1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dac.begin(0x60);
  pinMode(highSidePin, INPUT);
  pinMode(lowSidePin, INPUT);
  u8g2.begin();  
}

void loop() {
  displayProgressText("Sweep in Progress.....");
  performSweep();
  displayGraph();
  delay(8000);
}

void drawStaticDisplay() {
    // Define axis properties
    int xAxisStart = 5;
    int xAxisEnd = 95;
    int yAxisStart = 63;
    int yAxisEnd = 10;
    int xDivisions = 5; // 5 divisions for 5 Volts
    int yDivisions = 4; // Adjust the number for current divisions, if needed

    // Drawing the axes
    u8g2.drawLine(xAxisStart, yAxisStart, xAxisEnd, yAxisStart); // X-axis
    u8g2.drawLine(xAxisStart, yAxisStart, xAxisStart, yAxisEnd);  // Y-axis

    // Setting font for axis labels
    u8g2.setFont(u8g2_font_u8glib_4_hr); // Smaller font for axis labels

    // Axis labels
    u8g2.drawStr(xAxisStart - 3, yAxisEnd - 3, "I (mA)"); // Label for Y-axis
    u8g2.drawStr(xAxisEnd, yAxisStart -2, "V (V)"); // Label for X-axis

    // Calculate length of axes
    int xAxisLength = xAxisEnd - xAxisStart;
    int yAxisLength = yAxisStart - yAxisEnd;

    // X-axis divisions: each division represents 1 Volt
    for (int i = 0; i <= xDivisions; i++) {
        int x = xAxisStart + (i * xAxisLength / xDivisions);
        u8g2.drawLine(x, yAxisStart + 1, x, yAxisStart - 1); // Draw tick mark for X-axis
    }
    // Y-axis divisions
    for (int i = 0; i <= yDivisions; i++) {
        int y = yAxisStart - (i * yAxisLength / yDivisions);
        u8g2.drawLine(xAxisStart + 1, y, xAxisStart - 1, y); // Draw tick mark for Y-axis
    }
}

void displayProgressText(const char* text) 
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_cu12_tr);
  u8g2.drawStr(0, 32, text);
  u8g2.sendBuffer();
}

void performSweep() {
  u8g2.clearBuffer();
  drawStaticDisplay();

  float saturationVoltage = 0;
  bool saturationVoltageFound = false;

  for (uint16_t output = 0; output < 4096; output += 5) { // Increment the DAC output in steps to reduce the number of points
    dac.setVoltage(output, false);
    delay(10); // Delay to allow the output to stabilize

    int vHigh = analogRead(highSidePin);
    int vLow = analogRead(lowSidePin);

    float highVoltage = vHigh * (5.0 / 1023.0);
    float lowVoltage = vLow * (5.0 / 1023.0);
    float current = (highVoltage - lowVoltage) / 100; //  100 ohm resistor

    int currentX = map(lowVoltage * 1000, 0, 5000, 5, 95);
    int currentY = map(current * 1000000, 0, 17500, 63, 10);

    u8g2.drawPixel(currentX, currentY); // Plot each point on the display
    if (current > 0.0015 && !saturationVoltageFound) {
      saturationVoltage = lowVoltage;
      saturationVoltageFound = true; }
      
    if (saturationVoltageFound) {
      u8g2.setFont(u8g2_font_5x7_tf);
      u8g2.setCursor(72, 20);
      u8g2.print("Vsat: ");
      u8g2.print(saturationVoltage);
      u8g2.print("V");

    }

    Serial.print("Voltage: ");
    Serial.print(lowVoltage, 3);
    Serial.print(" V, Current: ");
    Serial.print(current, 6);
    Serial.println(" A");
  }
}
void displayGraph() {u8g2.sendBuffer();}