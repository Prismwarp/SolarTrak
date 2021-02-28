
#include <Servo.h> // include Servo library 

// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 65;   // 65;     // stand horizontal servo

int servohLimitHigh = 165;  // set horizontal high limit
int servohLimitLow = 15;    // set horizontal low limit

int horzpin = 9;  //  set horizontal servo output pin to
int vertpin = 10;  // set vertical servo output pin to

// 65 degrees MAX
Servo vertical;   // vertical servo 
int servov = 50;    //   50;     // stand vertical servo

int servovLimitHigh = 130; // set vertical high limit
int servovLimitLow = 45;   // set vertical low limit


// LDR pin connections
//  name  = analogpin;
int ldrlt = 0; //LDR top left - A0
int ldrld = 1; //LDR down left - A1
int ldrrt = 2; //LDR top right - A2 
int ldrrd = 3; //LDR down right - A3

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(horzpin); 
  vertical.attach(vertpin);
  horizontal.write(90);
  vertical.write(45);
  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  // int dtime = analogRead(4)/20; // read potentiometers lets you manual change delay on the fly
  // int tol = analogRead(5)/4;    // read potentiometer for tolerance lets you change tolerance on the fly
  int dtime = 10;   // for now just set delay manually
  int tol = 50;     // for now just set tolerance manually
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt


  // send the outputs to serial monitor for debug if need be
  
 /* Serial.print(avt);
 Serial.print(" ");
 Serial.print(avd);
 Serial.print(" ");
 Serial.print(avl);
 Serial.print(" ");
 Serial.print(avr);
 Serial.print("   ");
 Serial.print(dtime);
 Serial.print("   ");
 Serial.print(tol);
 Serial.println(" "); */
  
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
    delay(dtime);
 

}




