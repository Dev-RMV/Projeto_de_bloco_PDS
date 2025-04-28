#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

#define SQRT_2  1.41
#define Pi 3.14

int leitura = -1;
int vmax = -1;
int vmin = 1024;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(!display.begin(SSD1306_SWITCHCAPVCC,OLED_ADDR)){
    Serial.println(analogRead(A0));
    while(1){
      Serial.println("Nao foi possivel inicializar p display");
      delay(500);
    };  
  };

  leitura = -1;
  vmax = -1;
  vmin = 1024;
  for (int i=0 ; i<4999 ; i++){
    leitura = analogRead(A0);
    if (leitura > vmax){
      vmax = leitura;
    };
    if (leitura < vmin){
      vmin = leitura;
    };
    delay(1);
  };
  
  float OFFSET = float(vmax + vmin) / 2; // o OFFSET teórico seria 511.5, mas na prática não ocorre.
  float ajuste = 511.5 - OFFSET; //fator de ajuste para compensar o OFFSET nao ser 511,5
  float Vp = float(vmax + ajuste) * (250.0 / 1023);
  float Vrms = Vp / SQRT_2;
  float Vavg = (2.0/Pi) * Vp;
  float Vmin = -Vp;
  float Vpp = Vp - Vmin;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  display.print("Vp: ");
  display.print(Vp);
  display.print("V");
  display.setCursor(0,10);
  display.print("Vpp:");
  display.print(Vpp);
  display.print("V");
  display.setCursor(0,20);
  display.print("Vrms: ");
  display.print(RMS);
  display.print("V");
  display.setCursor(0,30);
  display.print("Vavg: ");
  display.print(Media);
  display.print("V");
  display.setCursor(0,40);
  display.print("Vmin: ");
  display.print(Vmin);
  display.print("V");
  Serial.print("Leitura maxima: ");
  Serial.println(vmax);
  Serial.print("Leitura minima: ");
  Serial.println(vmin);
  Serial.print("OFFSET calculado: ");
  Serial.println(OFFSET);
  Serial.print("Ajuste fino: ");
  Serial.println(ajuste);

  





  display.display();
  
}