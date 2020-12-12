#include "MPU9250.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>


#define time_period 2000
MPU9250 IMU(Wire,0x68);

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int status;
long int timer;
float angle_x, angle_y, angle_z;
float gyro_x_zero, gyro_y_zero, gyro_z_zero, accel_x_zero, accel_y_zero, accel_z_zero;
byte x = 4;
byte y = 4;
void setup()
{
  Serial.begin(115200);
  Serial.println("angle_x, angle_y, angle_z");
  status = IMU.begin();
  matrix.setIntensity(1); // яркость от 0 до 15
  matrix.fillScreen(LOW); // очистка матрицы
  calibrate;
  if (status < 0) 
  {   
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  
}

void loop()
{
  if (timer < micros())
  {
    timer = micros() + time_period;
    IMU.readSensor();
    getAngle();
    if (angle_x < -40)
    {
      if (x<7)
      {
        matrix.drawPixel(x+1, y, 1); 
        ++x;
      }
      else
        matrix.drawPixel(x, y, 1);
    }
    else
    {
      if (angle_x > 40)
      {
        if (x > 0)
        {
          matrix.drawPixel(x - 1, y, 1); 
          --x;
        }
        else
          matrix.drawPixel(x, y, 1);        
      }
      else
      {
        matrix.drawPixel(x, y, 1);
      }
    }
    matrix.write();
    matrix.fillScreen(LOW);
    Serial.print(angle_x);
    Serial.print(" , "); 
    Serial.print(angle_y);
    Serial.print(" ,  ");
    Serial.print(angle_z);
    Serial.print(" ,  ");
    Serial.println(x);
    
  }
}
