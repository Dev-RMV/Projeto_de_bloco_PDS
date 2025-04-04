#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEEN_WIDTH 128
#define SCREEEN_HEIGHT 64
#define OLED_ADDR 0x3c
Adafruit_SSD1306 display(SCREEEN_WIDTH,SCREEEN_HEIGHT,&Wire,-1);
void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  if(!display.begin(SSD1306_SWITCHCAPVCC,OLED_ADDR)){
    while(1){
      Serial.println("Nao foi possivel inicializar p display");
      delay(500);
    }
  
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHIE);
  display.setCursor(10,25);
  display.print("Funcionou?");
  display.display();
  
}