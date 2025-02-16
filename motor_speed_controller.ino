#include <LiquidCrystal_I2C.h> 


int ledpin =12;// a pin for a led that indicates the door state (open or closed - on:open _ off:closed)
int potenpin=A0;// a pin for a potentiometre
int motorpin=10;// a pin for the DC motor


LiquidCrystal_I2C lcd(0x27, 20, 4);// an lcd displayer object 

int speed1pin=6;// pins for the buttons 
int speed2pin=5;
int speed3pin=4;
int speed4pin=3;

float poten_value=0;// a variable to store the value read from the potentiometre pin 
float poten_prev_value=0; // a variable to avoid displaying the same value in a loop 

int speed1_state=HIGH; // variable for the state of each speed button
int speed2_state=HIGH;
int speed3_state=HIGH;
int speed4_state=HIGH;

void setup(){
  lcd.init(); // initialisation of the displayer
  lcd.clear();
  lcd.backlight(); // active le rétro-éclairage
  lcd.setCursor(0, 0); // se positionner à la première ligne
  

  // in/output configuration 
  pinMode(motorpin, OUTPUT);// PWM

  pinMode(potenpin, INPUT); //analog;

  pinMode(speed1pin,INPUT_PULLUP); // digital inputs 
  pinMode(speed2pin,INPUT_PULLUP);
  pinMode(speed3pin,INPUT_PULLUP);
  pinMode(speed4pin,INPUT_PULLUP);




}

void loop(){
  poten_prev_value=poten_value; 
  poten_value=analogRead(potenpin);
  poten_value=map(poten_value,0,1023,0,255); // changing the scale of the read value to be used to change the motor speed ( [0,1023] => [0,255])

  if (poten_prev_value!=poten_value) // if the value read from the potentiometre changes 
  {
    analogWrite(motorpin, poten_value); // change the motor speed 
    lcd.clear();
    lcd.print("Continuous value:");
    lcd.setCursor(0,1);
    lcd.print("speed :");
    lcd.print(poten_value/255 *100); // displaying the speed percent 
    lcd.print("%");
  }



  
  speed1_state=digitalRead(speed1pin); // reading the state of the button 
  speed2_state=digitalRead(speed2pin);
  speed3_state=digitalRead(speed3pin);
  speed4_state=digitalRead(speed4pin);
  
  if (speed1_state==LOW) // if the button didcated to the first speed is pressed 
  {
    analogWrite(motorpin, 64); 
    lcd.clear();
    lcd.print("Discrete value:");
    lcd.setCursor(0,1);
    lcd.print("speed 1 :25%");

  }
  else if (speed2_state==LOW)
  {
    analogWrite(motorpin, 128);
    lcd.clear();
    lcd.print("Discrete value:");
    lcd.setCursor(0,1);
    lcd.print("speed 2 :50%");
  }
  else if (speed3_state==LOW)
  {
    analogWrite(motorpin, 192);
    lcd.clear();
    lcd.print("Discrete value:");
    lcd.setCursor(0,1);
    lcd.print("speed 3 :75%");
  }
  else if (speed4_state==LOW)
  {
    analogWrite(motorpin, 255);
    lcd.clear();
    lcd.print("Discrete value:");
    lcd.setCursor(0,1);
    lcd.print("speed 4 :100%");
  }
  


}

