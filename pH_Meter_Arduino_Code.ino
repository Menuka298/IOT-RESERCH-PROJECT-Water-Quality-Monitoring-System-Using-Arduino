#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleTimer.h>
 
SimpleTimer timer;
 
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
 
float ph_act;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
 
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup() 
{
  Wire.begin();
 Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE); 
 
 
timer.setInterval(500L, display_pHValue);
}
void loop() {
  timer.run();
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;
 
 Serial.println("pH Val: ");
 Serial.print(ph_act);
 delay(1000);
}
 
void display_pHValue()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("pH:");
 
  display.setTextSize(2);
  display.setCursor(55, 0);
  display.print(ph_act);
 
 display.display();
}
