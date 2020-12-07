#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
int pinCS = 9;
int numberOfHorizontalDisplays = 1; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали
long lt;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays); 
byte x =4;
byte y =4;
void setup() {
  Serial.begin(9600);
    matrix.setIntensity(1); // яркость от 0 до 15

    matrix.fillScreen(LOW); // очистка матрицы
   
}

void loop() {
float mpu=random(-3,3);
  if ( millis()-lt>100)
  {
    if(mpu>=0)
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
     if (x>0)
     {
              matrix.drawPixel(x-1, y, 1);
              --x;
     }
      else
        matrix.drawPixel(x, y, 1); 
    }
    
    matrix.write();
    Serial.print(x);
        Serial.print("   ");
     Serial.println(mpu);
    matrix.fillScreen(LOW);
    lt=millis();
  }
   
}
