#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

#define SQRT_2  1.4142
//#define OFFSET 511.0 //2,5V aproximadamente
#define Pi 3.1416

int leitura = -1;
int vmax = -1;
int vmin = 1024;

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  //pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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
  for (int i=0 ; i<999 ; i++){
    leitura = analogRead(A0);
    if (leitura > vmax){
      vmax = leitura;
    };
    if (leitura < vmin){
      vmin = leitura;
    };
    delay(1);
  };
  //O OFFSET faz a onda ter amplitude de 0-2.5V, daí a multiplicação por 2.
  //Isso se dá porque a saída do ZMPT é analógica de 0-5V, que com o OFFSET representa uma onda AC de amplitude máxima de 2.5V
  float OFFSET = (vmax + vmin) / 2; // o OFFSET teórico seria 512, mas na prática não ocorre.
  float ajuste = 512.0 - OFFSET; //fator de ajuste para aproximar o OFFSET de 512
  float Vp = (2.0 * (float(vmax-OFFSET) + ajuste)) * (250.0 / 1023.0);
  float RMS = Vp / SQRT_2;
  float Media = (2.0/Pi) * Vp;
  float Vmin = (2.0 * (float(vmin-OFFSET) - ajuste)) * (250.0 / 1023.0);
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