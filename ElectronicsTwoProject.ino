
// Code made by Alan E 
// 9/20/24 - 1/15/25

//ALARM LIBRARIES
#include <Keypad.h> 
#include <virtuabotixRTC.h>
//#include <LiquidCrystal_I2C.h>

//PUSH-UP LIBRARIES
#include <LiquidCrystal.h> 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LIBRARIES ABOVE, INTERGERS BELOW
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ALARM INTERGERS
int i1,i2,i3,i4;
char c1,c2,c3,c4;
char keypressed,keypressedx;
int A_hour=NULL;
int A_minute=NULL;
int AlarmIsActive=NULL;
int buzzer = 25;
uint8_t SCLK;                                                                                        
uint8_t IO;                                                                                          
uint8_t C_E;                                                                                         
uint8_t seconds;                                                                                     
uint8_t minutes;                                                                                     
uint8_t hours;                                                                                       
uint8_t dayofweek;                                                                                   
uint8_t dayofmonth;                                                                                  
uint8_t month;                                                                                       
int year; 

//PUSH-UP INTERGERS
const int trigPin = 26; //set   pins for the ultrasonic sensor, button and buzzer
const int echoPin = 9;
const int buttonPina = A0;
const int buttonPinb = A1;
const int b = 13;
long duration; // set integers
int distance;
int p;
int buttonStatea = 0;
int buttonStateb = 0;
int x = 1;
int y = 1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INTERGERS ABOVE, PRE-VOID SETUP BELOW
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ALARM CLOCK PRE-VOID SETUP
#define LCD_COLUMNS 16
#define LCD_LINES 2
#define I2C_ADDR 0x27 //LCD i2c stuff
#define BACKLIGHT_PIN 3
virtuabotixRTC myRTC(23, 24, 22); //Wiring of the RTC (CLK,DAT,RST)
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
//35-42 is the keypad stuff
byte rowPins[numRows] = {35,36,37,38}; //Rows 0 to 3 //if you modify your pins you should modify this too
byte colPins[numCols]= {39,40,41,42}; //Columns 0 to 3
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
void updateTime(); 

//PUSHUP PRE=VOID SETUP
LiquidCrystal lcd1(6, 7, 2, 3, 4, 5); // set lcd pins
LiquidCrystal lcd2(49, 48, 47, 46, 45, 44); // set lcd pins

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PRE-VOID SETUP ABOVE, VOID SETUP BELOW
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

//PUSHUP CODE
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //set pin modes
  pinMode(echoPin, INPUT);
////////////  pinMode(buttonPina, INPUT);
  pinMode(buttonPinb, INPUT);
  pinMode(b, OUTPUT);
  lcd1.begin(16, 2); //   begin lcd, define scale of lcd (16 places in a row, 2 rows)
  lcd2.begin(16, 2);
  lcd1.print("----Push Ups----");

//ALARM CLOCK CODE
  myRTC.setDS1302Time(0, 0, 0 , 0 , 0 , 0 , 2000);  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VOID SETUP ABOVE, VOID LOOP BELOW
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

// LOOP CODE BELOW
  myRTC.updateTime();
  keypressed=NO_KEY;
  while(keypressed == NO_KEY){ //As long as no key is pressed we keep showing the date and time, I'm obliged to clear the screen everytime so the numbers don't get confused
                               //And I should add that little delay so the screen shows correctly otherwise it didn't work for me
  keypressed = myKeypad.getKey();
  lcd2.clear(); //Here after clearing the LCD we take the time from the module and print it on the screen with usual LCD functions
  myRTC.updateTime();
  if(myRTC.hours==A_hour && myRTC.minutes==A_minute && AlarmIsActive==1 && myRTC.seconds >= 0 && myRTC.seconds <= 2){
    while(p <= 10){
     tone(buzzer, 500); //You can modify the tone or make your own sound
     delay(100);
     tone(buzzer, 600);
     delay(100);
     lcd2.clear();
     lcd2.print("----WAKE  UP----"); //Message to show when the alarm is ringing
     keypressedx = myKeypad.getKey();
//////////////////////////////////////////////////////////////////////////////////////////
    digitalWrite(trigPin, HIGH);   // send out an ultra sonic sound for 10 microseconds and measure the time it took   for the sound to go from the trigpin to the echo pin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance   = duration * 0.034/2; //convert the time the signal took to travel to distance in   cm
  Serial.println(distance);

  if (p == (10 * y) && x == (1 * y)) { //this   if statement plays a sound every ten pushups
                 tone(b, 146.8);
                  delay(50);
                 noTone(b);
                 delay(100);
                  tone(b, 146.8);
                 delay(50);
                 noTone(b);
                  delay(50);
                 tone(b, 293.7);
                 delay(100);
                  noTone(b);
                  delay(125);
                  tone(b, 20.7);
                  noTone(b);
                  delay(150);
                  noTone(b);
                  tone(b, 63.7);
                  delay(175);
                  noTone(b);
                  delay(200);
                  noTone(b);
                 x ++;
                 y ++;
                 keypressedx = NO_KEY;
   noTone(buzzer);
   }
  else if (distance <= 10) {delay(350); //this if else statement makes sure   that the time between pushup-readings always stay the same
     } 
  
  buttonStatea   = digitalRead(buttonPina); //these lines of code resets every integer and the lcd   to the original state by the press of a button
   if (buttonStatea == LOW) {
    p = 0;
    x = 1;
    y = 1;
    lcd1.setCursor(0,1);
    lcd1.print("0       "); } 

  lcd1.setCursor(0, 1); // set cursor on the second row
  buttonStateb   = digitalRead(buttonPinb); //these lines of code resets every integer and the lcd   to the original state by the press of a button
   if (buttonStateb == LOW) {
    p = 0;
    x = 1;
    y = 1;
    lcd1.setCursor(0,1);
    lcd1.print("0       "); } 

  lcd1.setCursor(0, 1); // set cursor on the second row
   
  if (distance <= 10 ) {p ++;} //print a point if a pushup has been done
     lcd1.print(p,DEC);                 
       keypressedx = NO_KEY;
   noTone(buzzer);
  delay(100);  
  if (distance <= 10)   { //if the distance stays smaller then ten for a while, this piece of code makes   sure that only one point is given for one pushup
      digitalWrite(trigPin,   HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
       duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034/2;
      keypressedx = NO_KEY;
   noTone(buzzer);
   delay(100);
   delay(100);}

    }
  
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// START OF PUSHUP CODE
  digitalWrite(trigPin, HIGH);   // send out an ultra sonic sound for 10 microseconds and measure the time it took   for the sound to go from the trigpin to the echo pin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance   = duration * 0.034/2; //convert the time the signal took to travel to distance in   cm
  Serial.println(distance);

  if (p == (10 * y) && x == (1 * y)) { //this   if statement plays a sound every ten pushups
                 tone(b, 146.8);
                  delay(50);
                 noTone(b);
                 delay(100);
                  tone(b, 146.8);
                 delay(50);
                 noTone(b);
                  delay(50);
                 tone(b, 293.7);
                 delay(100);
                  noTone(b);
                 AlarmIsActive=0;
                 x ++;
                 y ++;
                 keypressedx = NO_KEY;
   noTone(buzzer);
   lcd2.setCursor(0,0);
   lcd2.print(myRTC.dayofmonth);
   lcd2.print("/");
   lcd2.print(myRTC.month);
   lcd2.print("/");
   lcd2.print(myRTC.year);
   lcd2.setCursor(0,1);
   lcd2.print(myRTC.hours);
   lcd2.print(":");
   lcd2.print(myRTC.minutes);
   lcd2.print(":");
   lcd2.print(myRTC.seconds);
   delay(100);
   }
  else if (distance <= 10) {delay(350);} //this if else statement makes sure   that the time between pushup-readings always stay the same
  
  buttonStatea   = digitalRead(buttonPina); //these lines of code resets every integer and the lcd   to the original state by the press of a button
   if (buttonStatea == LOW) {
    p = 0;
    x = 1;
    y = 1;
    lcd1.setCursor(0,1);
    lcd1.print("0       "); } 

  lcd1.setCursor(0, 1); // set cursor on the second row
  buttonStateb   = digitalRead(buttonPinb); //these lines of code resets every integer and the lcd   to the original state by the press of a button
   if (buttonStateb == LOW) {
    p = 0;
    x = 1;
    y = 1;
    lcd1.setCursor(0,1);
    lcd1.print("0       "); } 

  lcd1.setCursor(0, 1); // set cursor on the second row
   
  if (distance <= 10 ) {p ++;} //print a point if a pushup has been done
     lcd1.print(p,DEC);                 
       keypressedx = NO_KEY;
   noTone(buzzer);
   lcd2.setCursor(0,0);
   lcd2.print(myRTC.dayofmonth);
   lcd2.print("/");
   lcd2.print(myRTC.month);
   lcd2.print("/");
   lcd2.print(myRTC.year);
   lcd2.setCursor(0,1);
   lcd2.print(myRTC.hours);
   lcd2.print(":");
   lcd2.print(myRTC.minutes);
   lcd2.print(":");
   lcd2.print(myRTC.seconds);
  delay(100);  
  while (distance <= 10)   { //if the distance stays smaller then ten for a while, this piece of code makes   sure that only one point is given for one pushup
      digitalWrite(trigPin,   HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
       duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034/2;
      keypressedx = NO_KEY;
   noTone(buzzer);
   lcd2.setCursor(0,0);
   lcd2.print(myRTC.dayofmonth);
   lcd2.print("/");
   lcd2.print(myRTC.month);
   lcd2.print("/");
   lcd2.print(myRTC.year);
   lcd2.setCursor(0,1);
   lcd2.print(myRTC.hours);
   lcd2.print(":");
   lcd2.print(myRTC.minutes);
   lcd2.print(":");
   lcd2.print(myRTC.seconds);
   delay(100);
   delay(100);}
//END OF PUSHUP CODE
  keypressedx = NO_KEY;
  noTone(buzzer);
  lcd2.setCursor(0,0);
  lcd2.print(myRTC.dayofmonth);
  lcd2.print("/");
  lcd2.print(myRTC.month);
  lcd2.print("/");
  lcd2.print(myRTC.year);
  lcd2.setCursor(0,1);
  lcd2.print(myRTC.hours);
  lcd2.print(":");
  lcd2.print(myRTC.minutes);
  lcd2.print(":");
  lcd2.print(myRTC.seconds);
  delay(100);
  }
 

         if (keypressed == '*') //As we everytime check the key pressed we only proceed to setup if we press "*"
             {
              lcd2.clear();
              lcd2.print("---SETUP TIME---");
             delay(1000);
              lcd2.clear();
              lcd2.print("---SETUP YEAR---");
              //It automatically passes to setting up the month...until it's finished
              //The keys from keypad are all considered chars (c) so we should convert them to int that's what I did then we store them (i)
              //We do some math and we get the year, month... as int so we can inject them to the RTC otherwise it will not be compiled
              //Months like April you should write 04, 03 for March... otherwise it will not pass to the next parameter
              //The RTC virtuabotix library is already set to not accept strange time and dates (45/17/1990) (58:90:70), and yes old dates are considered as errors
             char keypressed2 = myKeypad.waitForKey();  
                    if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' && keypressed2 !='A' && keypressed2 !='B' && keypressed2 !='C' && keypressed2 !='D' )
                      {
                       c1 = keypressed2;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                 char      keypressed3 = myKeypad.waitForKey();
                    if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' && keypressed3 !='A' && keypressed3 !='B' && keypressed3 !='C' && keypressed3 !='D' )
                      {
                       c2 = keypressed3;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }
                   char  keypressed4 = myKeypad.waitForKey();
                   if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' && keypressed4 !='A' && keypressed4 !='B' && keypressed4 !='C' && keypressed4 !='D' )
                      {
                       c3 = keypressed4;
                       lcd2.setCursor(2, 1);
                       lcd2.print(c3);
                       }
                   char   keypressed5 = myKeypad.waitForKey();
                   if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#' && keypressed5 !='A' && keypressed5 !='B' && keypressed5 !='C' && keypressed5 !='D' )
                      {
                       c4 = keypressed5;
                       lcd2.setCursor(3, 1);
                       lcd2.print(c4);
                       }

                     i1=(c1-48)*1000;        //the keys pressed are stored into chars I convert them to int then i did some multiplication to get the code as an int of xxxx
                     i2=(c2-48)*100;
                     i3=(c3-48)*10;
                     i4=c4-48;
                     int N_year=i1+i2+i3+i4;
                   delay(500);
                     lcd2.clear();
                     lcd2.print("--SETUP MONTH--");

////////////////////////////////////////////////////////////////
                     char keypressed6 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' && keypressed6 !='A' && keypressed6 !='B' && keypressed6 !='C' && keypressed6 !='D' )
                      {
                       c1 = keypressed6;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                    char   keypressed7 = myKeypad.waitForKey();
                    if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#' && keypressed7 !='A' && keypressed7 !='B' && keypressed7 !='C' && keypressed7 !='D' )
                      {
                       c2 = keypressed7;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_month=i1+i2;
                     delay(500);

                     lcd2.clear();
                     lcd2.print("---SETUP  DAY---");
                     
 ////////////////////////////////////////////////////////////////                    
                      char keypressed8 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed8 != NO_KEY && keypressed8 !='*' && keypressed8 !='#' && keypressed8 !='A' && keypressed8 !='B' && keypressed8 !='C' && keypressed8 !='D' )
                      {
                        c1 = keypressed8;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                      char keypressed9 = myKeypad.waitForKey();
                    if (keypressed9 != NO_KEY && keypressed9 !='*' && keypressed9 !='#' && keypressed9 !='A' && keypressed9 !='B' && keypressed9 !='C' && keypressed9 !='D' )
                      {
                        c2 = keypressed9;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_day=i1+i2;
                    delay(500);
                     lcd2.clear();
                     lcd2.print("---SETUP HOUR---");
////////////////////////////////////////////////////////////////////////////////////:                     
                     char keypressed10 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed10 != NO_KEY && keypressed10 !='*' && keypressed10 !='#' && keypressed10 !='A' && keypressed10 !='B' && keypressed10 !='C' && keypressed10 !='D' )
                      {
                       c1 = keypressed10;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                    char   keypressed11 = myKeypad.waitForKey();
                    if (keypressed11 != NO_KEY && keypressed11 !='*' && keypressed11 !='#' && keypressed11 !='A' && keypressed11 !='B' && keypressed11 !='C' && keypressed11 !='D' )
                      {
                        c2 = keypressed11;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_hour=i1+i2;
                    delay(500);
                     lcd2.clear();
                     lcd2.print("--SETUP MINUTES--");
////////////////////////////////////////////////////////////////////////////////////:
                    char keypressed12 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed12 != NO_KEY && keypressed12 !='*' && keypressed12 !='#' && keypressed12 !='A' && keypressed12 !='B' && keypressed12 !='C' && keypressed12 !='D' )
                      {
                        c1 = keypressed12;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                   char    keypressed13 = myKeypad.waitForKey();
                    if (keypressed13 != NO_KEY && keypressed13 !='*' && keypressed13 !='#' && keypressed13 !='A' && keypressed13 !='B' && keypressed13 !='C' && keypressed13 !='D' )
                      {
                        c2 = keypressed13;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_minutes=i1+i2;
                    delay(500);
                     lcd2.clear();

                    myRTC.setDS1302Time(22, N_minutes, N_hour, 1, N_day, N_month, N_year); //once we're done setting the date and time we transfer to values to the RTC module
                    myRTC.updateTime();
                                                                                           //the 22 stands for seconds you can add a setup for it too if you want
                                                                                           //the 1 stands for day of the week, as long I don't show it on the screen I don't change it
                    keypressed=NO_KEY; //the "*" key is stored in "keypressed" so I remove that value from it otherwise it will get me in the setup again
              }
/////////////////////////////////////////Alarm setup/////////////////////////////////
              
             if (keypressed == 'A'){
              lcd2.clear();
              lcd2.print("--ALARM  SETUP--");
              delay(1000);
              lcd2.clear();
              lcd2.print("---ALARM HOUR---");
               
               char keypressed14 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
                      {
                       c1 = keypressed14;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                    char   keypressed15 = myKeypad.waitForKey();
                    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
                      {
                        c2 = keypressed15;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_hour=i1+i2;
                    delay(500);
                     lcd2.clear();
                     lcd2.print("-ALARM  MINUTES-");
                      char keypressed16 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
                      {
                       c1 = keypressed16;
                       lcd2.setCursor(0, 1);
                       lcd2.print(c1);
                       }
                    char   keypressed17 = myKeypad.waitForKey();
                    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
                      {
                        c2 = keypressed17;
                       lcd2.setCursor(1, 1);
                       lcd2.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_minute=i1+i2;
                    delay(500);
                     lcd2.clear();
                      AlarmIsActive=1;
                      keypressed=NO_KEY;
             }
             // this button breaks the code if it's removed.
             if (keypressed == 'B')
             {
              lcd2.clear();
              lcd2.print("hamburger");
             }
             else {
              myRTC.updateTime();
              keypressed=NO_KEY;
             }
  }