
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

//Text size information
#define BASE_CHAR_HEIGHT 5
#define SIZE_MULT 1
#define CHAR_SIZE (BASE_CHAR_HEIGHT * SIZE_MULT)
#define TITLE_OFFSET 0
#define ARTIST_OFFSET 1
#define ALBUM_OFFSET 2
#define V_BUFF 3

#define STRLEN 400

float p = 3.1415926;
String artist;
String album;
String title;

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
  char str[STRLEN] = {'\0'};
  String data = "";
  //Clear out anything from before
  while(Serial2.available()){
    char c = Serial2.read();
  }
  Serial2.print("AD\r"); //Get metadata
  delay(100); //Let the command be processed switch to a while loop waiting on available in the future
  data = get_metadata(&i);
  artist = get_artist(data);
  album = get_album(data);
  title = get_title(data);

  tft.fillScreen(ST7735_BLACK);

  draw_title(title.toCharArray(), title.length());
  draw_artist(artist.toCharArray(), artist.length());
  draw_album(album.toCharArray(), album.length());
  delay(3000); //Check for new song every 3 seconds
}

String get_metadata(int* i){
  /*Get all the metadata*/
  int complete = 0;
  int timer = 0;
  String data;
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
  return data;
}

String get_artist(String metadata){
    i = metadata.indexOf("Artist=") + 7;
    if (i != 1){
      metadata.remove(0,n); //Removes everything up to the artist
      i = metadata.indexOf('\n'); //Gets end of line after artist
      metadata.remove(i);
    } else {
      metadata = ""; //Don't know what it is
    }
    return metadata
}

String get_title(String metadata){
    i = metadata.indexOf("Title=") + 6;
    if (i != 1){
      metadata.remove(0,n); //Removes everything up to the artist
      i = metadata.indexOf('\n'); //Gets end of line after artist
      metadata.remove(i);
    } else {
      metadata = ""; //Don't know what it is
    }
    return metadata
}

String get_album(String metadata){
    i = metadata.indexOf("Album=") + 6;
    if (i != 1){
      metadata.remove(0,n); //Removes everything up to the artist
      i = metadata.indexOf('\n'); //Gets end of line after artist
      metadata.remove(i);
    } else {
      metadata = ""; //Don't know what it is
    }
    return metadata
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void draw_title(char *text, uint16_t color) {
  tft.setCursor((TITLE_OFFSET * CHAR_SIZE) + V_BUFF, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(SIZE_MULT);
  tft.print("Title: ");
  tft.print(text);
}

void draw_artist(char *text, uint16_t color) {
  tft.setCursor((ARTIST_OFFSET * CHAR_SIZE) + V_BUFF, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(SIZE_MULT);
  tft.print("Artist: ");
  tft.print(text);
}

void draw_album(char *text, uint16_t color) {
  tft.setCursor((ALBUM_OFFSET * CHAR_SIZE) + V_BUFF, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(SIZE_MULT);
  tft.print("Artist: ");
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
