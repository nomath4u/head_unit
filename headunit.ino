
#include <Adafruit_GFX.h>

#include <Adafruit_ST7735.h>
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     6
#define TFT_RST    1  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     12

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define STRLEN 400

float p = 3.1415926;
//char str[STRLEN] = {'\0'};
void setup(void) {
  Serial.begin(9600);
  Serial2.begin(115200);
  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);
  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST7735_BLACK);
  /*Once this is working try what is in the print test*/
  testdrawtext("No song available yet ", ST7735_WHITE);
  delay(1000);

}

void loop() {
  int act = 0;
  int i =0;
  int complete = 0;
  int timer = 0;
  char str[STRLEN] = {'\0'};
  String data = "";
  clearbuff();
  //Clear out anything from before
  while(Serial2.available()){
    char c = Serial2.read();
  }
  Serial2.print("AD\r"); //Get metadata
  delay(100); //Let the command be processed switch to a while loop waiting on available in the future
  //while( Serial2.available()){
    /*Get all the metadata*/
    while( complete < 7){
      if(Serial2.available()){
        //str[i] = Serial2.read();
        char c = Serial2.read();
        data += c;
        timer = millis();

        i++;
        //complete = 0;
        if(c == '\n'){
          complete++;
        }
      }
      if ((millis() - timer) > 500){ //
        complete++;
      }

  }
  //Serial.println(str);
  //str[i] = '\0';
  //if(act){
    tft.fillScreen(ST7735_BLACK);
    data.toCharArray(str,i);
    testdrawtext(str,ST7735_WHITE);
  //}
  //tft.fillScreen(ST7735_BLACK);
  //testdrawtext("Testing", ST7735_WHITE);
  delay(1000);
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void clearbuff(){
  //str[0] = '\0';
  int i = 0;
  for (i = 0; i < STRLEN; i++){
    //str[i] = '\0';
  }
}


    
