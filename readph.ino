#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
float calibration_value = 21.34;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;

typedef union
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;
FLOATUNION_t phreading_to_send;
FLOATUNION_t tempreading_to_send;
void setup()
{
  pinMode(A2,INPUT);
  Serial.begin(115200);
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
  float ph_act = -5.70 * volt +29.5 ;
  lcd.setCursor(0, 0);
  lcd.print("pH Val:");
  lcd.setCursor(6,1);
  lcd.print(ph_act);
  phreading_to_send.number = ph_act;
  tempreading_to_send.number = analogRead(A2);
  Serial.write(phreading_to_send.bytes , 4);
  Serial.write(tempreading_to_send.bytes, 4);
  delay(500);
}
