#include "MPU9250.h"  //библиотека для работы с mpu9250
#include <SPI.h>  //библиотека для работы с матрицей
#include <Adafruit_GFX.h>  //библиотека для работы с матрицей
#include <Max72xxPanel.h>  //библиотека для работы с матрицей


#define time_period 1000
MPU9250 IMU(Wire,0x68);

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int status;
long int timer, timer2;
float angle_x, angle_y, angle_z;
float s_x, s_y;
float gyro_x_zero, gyro_y_zero, gyro_z_zero, accel_x_zero, accel_y_zero, accel_z_zero;
int pos_x = 0, pos_y = 0;
void setup()
{
  Serial.begin(115200);
  Serial.println("angle_x, s_x");
  status = IMU.begin();
  status = IMU.calibrateGyro ();
  status = IMU.calibrateAccel ();
  matrix.setIntensity(1); // яркость от 0 до 15
  matrix.fillScreen(LOW); // очистка матрицы
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
    getPos();
      matrix.drawPixel(7 - pos_x, pos_y, 1); 
      matrix.write();
      matrix.fillScreen(LOW);
      Serial.print(angle_x);
      Serial.print(" , ");
      Serial.print(s_x, 6) ;
      Serial.print(" , ");
      Serial.print(angle_y);
      Serial.print(" , ");
      Serial.println(s_y, 6);
  }
}
