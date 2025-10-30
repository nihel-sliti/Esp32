
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define FRAME_WIDTH 128
#define FRAME_HEIGHT 64
#define FRAME_DELAY 70 // Bisa diubah sesuai kebutuhan


const byte PROGMEM frames[][FRAME_WIDTH * FRAME_HEIGHT / 8] = {
  //chercher un frame ou plusieur sur la dimension 128*64 
  //code le sur bitmap et copier le code ici 
};


#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))


void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED gagal ditemukan"));
    while (true);
  }
  display.clearDisplay();
}


int frame = 0;


void loop() {
  display.clearDisplay();
 
  int x = (SCREEN_WIDTH - FRAME_WIDTH) / 2;  // Pusat X
  int y = (SCREEN_HEIGHT - FRAME_HEIGHT) / 2; // Pusat Y
 
  display.drawBitmap(x, y, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();


  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}

