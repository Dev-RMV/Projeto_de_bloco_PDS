#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEEN_WIDTH 128
#define SCREEEN_HEIGHT 64
#define OLED_ADDR 0x3c
Adafruit_SSD1306 display(SCREEEN_WIDTH,SCREEEN_HEIGHT,&Wire,-1);

#define SQRT_2  1.4142
#define OFFSET 512.0 //2,5V aproximadamente
#define Pi 3.1416

int leitura = -1;
int max = -1;
int min = 1024;

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  pinMode(A0,INPUT);
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

  leitura = -1;
  max = -1;
  min = 1024;
  for (int i=0 ; i<999 ; i++){
    leitura = analogRead(A0);
    if (leitura > max){
      max = leitura;
    };
    if (leitura < min){
      min = leitura;
    };
    delay(1);
  };
  //O OFFSET faz a onda ter amplitude de 0-2.5V, daí a multiplicação por 2.
  //Isso se dá porque a saída do ZMPT é analógica de 0-5V, que com o OFFSET representa uma onda AC de amplitude máxima de 2.5V
  float Vp = (2.0 * float(max-OFFSET)) * (250.0 / 1023.0);
  float RMS = Vp / SQRT_2;
  float Media = (2.0/Pi) * Vp;
  float Vmin = (2.0 * float(min-OFFSET)) * (250.0 / 1023.0);
  float Vpp = Vp - Vmin;

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,25);
  display.print("Vp: ");
  display.print(Vp);
  display.println("V");
  display.print("Vpp: ");
  display.print(Vpp);
  display.println("V");
  display.print("RMS: ");
  display.print(RMS);
  display.println("V");
  display.print("Media: ");
  display.print(Media);
  display.println("V");
  display.print("Vmin: ");
  display.print(Vmin);
  display.println("V");



  display.display();
  
}