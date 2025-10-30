// Include
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Screen Info
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C


// Dino Info
#define DINO_WIDTH 25
#define DINO_HEIGHT 26
#define DINO_INIT_X 10
#define DINO_INIT_Y 29


// Line info
#define BASE_LINE_X 0
#define BASE_LINE_Y 54
#define BASE_LINE_X1 127
#define BASE_LINE_Y1 54


// Trees info
#define TREE1_WIDTH 11
#define TREE1_HEIGHT 23
#define TREE2_WIDTH 22
#define TREE2_HEIGHT 23
#define TREE_Y 35


#define JUMP_PIXEL 22 // Max jump in pixel
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static const unsigned char PROGMEM dino1[]={
  // 'dino', 25x26px
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00,
0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00,
0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00,
0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00,
0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00,
0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00,
0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00
};


static const unsigned char PROGMEM tree1[]={
  // 'tree1', 11x23px
0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0,
0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00,
0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00
};


static const unsigned char PROGMEM tree2[]={
  // 'tree2', 22x23px
0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf,
0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff,
0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0,
0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f,
0x03, 0xe0, 0x1f, 0x03, 0xe0
};
void setup(){
Serial.begin(9600);
// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}
// Clear the buffer
display.clearDisplay();
introMessage();
// Run game in loop
while(1){
    if (Serial.available()){
        if(Serial.parseInt()==1){
            play();
        }
    }
}
}
void loop(){


}
void rederScene(){
  display.drawBitmap(10,29,dino1, 25, 26, SSD1306_WHITE);
  display.drawBitmap(50, TREE_Y, tree1, 11, 23, SSD1306_WHITE);
  display.drawBitmap(100, TREE_Y, tree2, 22, 23, SSD1306_WHITE);
  display.drawLine(0, 54, 127,54, SSD1306_WHITE);
  display.display();
}
// Move tree function
void moveTree(int16_t *x, int type=0){
  if(type==0){
    display.drawBitmap(*x, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, SSD1306_WHITE);
  }
  else if(type==1){
    display.drawBitmap(*x, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, SSD1306_WHITE);
  }
}
// Move dino function
void moveDino(int16_t *y, int type=0){
    display.drawBitmap(DINO_INIT_X, *y, dino1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
}


// Game over display with score
void gameOver(int score=0){
  display.clearDisplay();
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,5);
  display.println("Game Over");
  display.setTextSize(1);
  display.setCursor(10,30);
  display.print("Score: ");
  display.print(score);
  display.setCursor(1,45);
  display.println("Enter 1 To Play Again");
  display.display();
}
void displayScore(int score){
display.setTextSize(1);
display.setCursor(64,10);
display.print("Score: ");
display.print(score);


}


void play(){


int16_t tree_x=127; // End of the screen
int16_t tree1_x=195; // So that second type of tree comes after some time
int tree_type = random(0,2); // Select random type of tree
int tree_type1 = random(0,2);
int16_t dino_y = DINO_INIT_Y;
int input_command;
int jump=0; // init jump state is 0 i.e on base
int score=0;
for(;;){
display.clearDisplay();


if (Serial.available()){ // Check for serial Data
  input_command = Serial.parseInt();
  if(input_command==5){ // Jump
    Serial.println("Jump");
    if(jump==0) jump=1;
  }
}
if(jump==1){ // Going UP
  dino_y--;
  if(dino_y== (DINO_INIT_Y-JUMP_PIXEL)){
    jump=2;
    score++;
  }
}
else if(jump==2){ // Coming down
  dino_y++;
  if(dino_y== DINO_INIT_Y){
   jump=0;
  }
}
if(tree_x<= (DINO_INIT_X+DINO_WIDTH) && tree_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
//      Serial.println("Might be Collision Happened");
  if(dino_y>=(DINO_INIT_Y-3)){
    // Collision Happened
    Serial.println("Collision Happened");
    break;
  }
}
if(tree1_x<= (DINO_INIT_X+DINO_WIDTH) && tree1_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
//      Serial.println("Might be Collision Happened");
  if(dino_y>=(DINO_INIT_Y-3)){
    // Collision Happened
    Serial.println("Collision Happened");
    break;
  }
}
displayScore(score); // Live Score
moveTree(&tree_x,tree_type);// Move tree 1
moveTree(&tree1_x,tree_type1); // Move tree 2
moveDino(&dino_y); // Move dino
display.drawLine(0,54,127,54, SSD1306_WHITE); // Base line
tree_x--;
tree1_x--;
if(tree_x==0) {
  tree_x = 127;
  tree_type = random(0,1);
}
if(tree1_x==0) {
  tree1_x = 195;
  tree_type1 = random(0,1);
}
display.display();
}
Serial.println("Game Over");
gameOver(score);
}        
void introMessage(){
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,5);
  display.println("Dino Game");
  display.setTextSize(1);
  display.setCursor(5,45);
  display.println("Enter 1 To Play ");
  display.display();
}





