/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL25GU6SnIr"
#define BLYNK_TEMPLATE_NAME         "PH Tripoli"
#define BLYNK_AUTH_TOKEN            "cLolM734TLYcbjBCCh97oDB1SN9e4g1z"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h> // Library for LCD

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = ".......@......";
char pass[] = "ASAS@cxz";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

// or Software Serial on Uno, Nano...
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

BlynkTimer timer;
double ph = 0.0;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  lcd.setCursor(0, 0);
  lcd.print("ph reading:");
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(4800);
lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
