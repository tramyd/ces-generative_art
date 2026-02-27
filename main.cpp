#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
int temperatureF;

void drawFace(String line1, String line2 = "", String line3 = "") {

  int centerX = tft.width() / 2;
  int startY = tft.height() * 0.65;   

  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(3);

  int lineHeight = 35;
  int totalLines = 1;
  if (line2 != "") totalLines++;
  if (line3 != "") totalLines++;

  int boxWidth = 80;                          
  int boxHeight = (totalLines * lineHeight) + 20; 
  int boxX = centerX - boxWidth / 2;
  int boxY = startY - 25;

  tft.drawRoundRect(boxX, boxY, boxWidth, boxHeight, 10, TFT_WHITE);

  int earHeight = 20;
  int earWidth = 15;

  int leftX1 = boxX + 5;          
  int leftY1 = boxY;                
  int leftX2 = leftX1 + earWidth / 2;   
  int leftY2 = boxY - earHeight;    
  int leftX3 = leftX1 + earWidth;       
  int leftY3 = boxY;                

  tft.fillTriangle(leftX1, leftY1, leftX2, leftY2, leftX3, leftY3, TFT_WHITE);

  int rightX1 = boxX + boxWidth - earWidth - 5;  
  int rightY1 = boxY;                
  int rightX2 = rightX1 + earWidth / 2;         
  int rightY2 = boxY - earHeight;    
  int rightX3 = rightX1 + earWidth;            
  int rightY3 = boxY;                

  tft.fillTriangle(rightX1, rightY1, rightX2, rightY2, rightX3, rightY3, TFT_WHITE);

  tft.drawString(line1, centerX, startY);
  tft.drawString(line2, centerX, startY + lineHeight);

  if (line3 != "") {
    tft.drawString(line3, centerX, startY + (lineHeight * 2));
  }
}

void setup() {
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  randomSeed(analogRead(0));
}

void loop() {
  tft.fillScreen(TFT_BLACK);

  temperatureF = random(0, 110);  

  tft.setTextDatum(MC_DATUM);

  tft.setTextSize(2);
  tft.drawString("Temperature", tft.width()/2, 50);

  tft.setTextSize(3.5);
  tft.drawString(String(temperatureF) + " F",
                 tft.width()/2,
                 80);

  
  if (temperatureF < 20) {                
    drawFace("x_x");
  }
  else if (temperatureF < 32) {           
    drawFace("O_O");
  }
  else if (temperatureF < 50) {           
    drawFace("-_-");
  }
  else if (temperatureF < 65) {           
    drawFace("^_^");
  }
  else if (temperatureF < 85) {           
    drawFace(">_<");
  }
  else {                                   
    drawFace("@_@");
  }

  delay(2000);
}
  
