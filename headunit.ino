
#include <Adafruit_GFX.h>

#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <SD.h> //This needs to be the Adafruit one if not using arduino v23


/*Defines for the 1.8" TFT from adafruit working on a Teensy 3.1 
with hardware SPI in normal configuration*/
#define TFT_CS     6
#define TFT_RST    1  
#define TFT_DC     12
#define SD_CS      2 //Make this whatever works
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


#define STRLEN 400

float p = 3.1415926;
void setup(void) {
  Serial.begin(9600);
  Serial2.begin(115200);
  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);

  Serial.println("Initialized");
  if(sd_init()){
    draw_background("background.bmp");
  } else {
    tft.fillScreen(ST7735_BLACK);
  }
  delay(500);

  /*Once this is working try what is in the print test*/
  testdrawtext("No song available yet ", ST7735_WHITE);
  delay(1000);

}

void loop() {
  int i =0;
  int complete = 0;
  int timer = 0;
  char str[STRLEN] = {'\0'};
  String data = "";
  //Clear out anything from before
  while(Serial2.available()){
    char c = Serial2.read();
  }
  Serial2.print("AD\r"); //Get metadata
  delay(100); //Let the command be processed switch to a while loop waiting on available in the future
  /*Get all the metadata*/
  while( complete < 7){
    if(Serial2.available()){
      char c = Serial2.read();
      data += c;
      timer = millis();
      i++;
      if(c == '\n'){
        complete++;
      }
    }
    if ((millis() - timer) > 500){ //Could take up to 500 ms for the BT part
                                   //To have new data on serial
      complete++;
    }
  }
  tft.fillScreen(ST7735_BLACK);
  data.toCharArray(str,i);
  testdrawtext(str,ST7735_WHITE);
  delay(1000); //Check for new song every second
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

int sd_init(){
  Serial.print("initializing SD card");
  if(!SD.begin(SD_CS)){
    Serial.println("Failed!");
    return 0;
  }
  Serial.println("Done");
  return 1;
}

void draw_background(char* file_name){
  bmpDraw(file_name, 0,0);
  delay(5000); //Wait 5 seconds for it to render
  }
