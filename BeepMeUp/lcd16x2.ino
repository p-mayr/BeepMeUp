
#include <LiquidCrystal.h>

// Pin assignments for DFRobot LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float sum_vertical_speed = 0.0;
int count = 0;
int refresh_time = 250;
int sum_loop_time = 0;

void setup16x2(){
  
  // Start LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Beep Me Up");

}

void displayValues(){
  if (sum_loop_time > refresh_time){
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(count);
    lcd.setCursor(3, 0);
    lcd.print("Beep Me Up");
    lcd.setCursor(0, 1);
    lcd.print(velocity,1);
    lcd.setCursor(11, 1);
    lcd.print(altitude,1);

    sum_vertical_speed = 0.0;
    sum_loop_time = 0;
    count = 0;
  }
  sum_vertical_speed += vertical_speed;
  sum_loop_time += (int)loop_time;
  count++;
}

