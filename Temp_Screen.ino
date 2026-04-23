
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16
  #define TFT_DC         5

#else

  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;
float v =0;

int current = 0;
int tempArray[120];

char currentString[3];

void getTemp(){
  float voltage = 0;
  float celsius = 0;
  float sensor = 0;
  float sum = 0;

  sensor = analogRead(0); //read temp sensor and conver to degrees celsuis
  v = (sensor * 5000)/ 1024; //convert sensor value to mV 
  voltage = v - 500; //remove voltage offset
  celsius = voltage / 10; //convert mV to celsius   
  current = int(celsius);

   for (int a = 119 ; a >= 0 ; --a )
  {
    tempArray[a] = tempArray[a - 1];
  }
  tempArray[0] = current;
}

void drawScreen(){
  int q;
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println("Current: ");
  String tempString = String(current);
  tempString.toCharArray(currentString, 3);
  tft.println(currentString);
  //Drawing scale 
  tft.setCursor(0, 40);
  tft.print("50");
  tft.setCursor(0, 60);
  tft.print("45");
  tft.setCursor(0, 80);
  tft.print("40");
  tft.setCursor(0, 100);
  tft.print("35");
  tft.setCursor(0, 120);
  tft.print("30");
  tft.setCursor(0, 140);
  tft.print("25");
  tft.setCursor(0, 160);
  tft.print("20");
  tft.setCursor(0, 180);
  tft.print("15");
  tft.setCursor(0, 200);
  tft.print("10");
  tft.setCursor(0, 220);
  tft.print("5");
  tft.setCursor(0, 240);
  tft.print("0");

   for (int a = 25 ; a < 145 ; a = a + 10)
  {
    // convert the temperature value to a suitable y-axis position on the LCD
    q = (165 - (tempArray[a - 25]));//CHAMGE THIS VALUE SO STRAIGN LINE DISSAPEARS
    tft.drawPixel(a, q, ST77XX_WHITE);
  }
}


void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.init(240, 320);  
  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(5);
  tft.println("Begin Temp senseor");
  delay(1000);
  Serial.println("Begin");
  delay(1000);


}

void loop() {
  getTemp();
  drawScreen();
  for (int a = 0 ; a < 20 ; a++) // wait 20 minutes until the next reading
  {
    delay(100);                // wait 1 minute
  }
}


