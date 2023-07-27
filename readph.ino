#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float calibration_value = 21.34;
int phval = 0;
float ph_act = 0;
unsigned long int avgval;
int buffer_arr[10] ,temp;

typedef union {  float number;  
  uint8_t bytes[4];  } FLOATUNION_t;;

void setup()
{
  sensors.begin();
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.begin(16, 2);
  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   Bienvenido a    ");
  lcd.setCursor(0, 1);
  lcd.print(" Medidor pH    ");
  delay(2000);
  lcd.clear();
}
void loop() {  
  
  FLOATUNION_t float1, float2; 
  sensors.requestTemperatures();
  float1.number = ph_act;
  float2.number = sensors.getTempCByIndex(0);
  
  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 4.3;
  ph_act = -5.70 * volt +29.5 ;
  lcd.setCursor(0, 0);
  lcd.print("pH Val:");
  lcd.setCursor(8,0);
  lcd.print(ph_act);
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(6,1);
  lcd.print(float2.number);

  Serial.write(float1.bytes, 4);  
  Serial.write(float2.bytes, 4);
  
  delay(500);
}
