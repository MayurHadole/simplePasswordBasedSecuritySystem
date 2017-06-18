/*  FILE          : simplePasswordBasedSecuritySystem.ino
    PROJECT       : PROG8125-16S 
    PROGRAMMER    : Mayur Hadole (5783)
    FIRST VERSION : 2016-06-12
    DESCRIPTION   :
       This program takes input(i.e passcode of 4 digit/character
    or combilnation of both ) from user through serial port and
    if it matches to one of the 10 existing passcodes stored in
    an array, the serial port shows "Access Granted".If not
    serial port will show "Access Denied".
        As a feedback for access granted, green LED will be ON,
    speaker will beep once and LCD will Display "ACCESS GRANTED".
        For feedback of access denied, red LED will be OFF,
    speaker will beep twice and LCD will Display "ACCESS GRANTED".
        if entered passcode is more the 4 digits long, Serial port
    will show "Password is of 4 digits, Plese enter again" and will
    show "access denied" on serial port and LCD


         This code is tested on Teensy 3.1 board
*/


// include the LCD library code:
#include <LiquidCrystal.h>

// Red LED is connected to pin 12
const uint8_t redLedPin = 12;

// Green LED is connected to pin 11
const uint8_t greenLedPin = 11;

//Speaker is connected to pin 10
const uint8_t speakerPin = 10;

/* LCD RS pin to digital pin 14
  LCD Enable pin to digital pin 15
  LCD D4 pin to digital pin 5
  LCD D5 pin to digital pin 4
  LCD D6 pin to digital pin 3
  LCD D7 pin to digital pin 2
  LCD R/W pin to ground
  10K resistor:
  ends to +5V and ground
  wiper to LCD VO pin (pin 3)*/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(14, 15, 5, 4, 3, 2);

//to store 10 passcodes, the size of the array is 10
const uint8_t passCodesArraySize = 10;

//length of passcode
const uint8_t passCodeLength = 4;

//this variable is used to save length of entered passcode which
//is more than 4.
uint8_t LengthOfInvalidPasscode;

//this character array is used to save invalid passcode(which is
//greater than 4 digits).
char garbagePasscode[20];

const uint16_t positiveAuditoryFrequency = 2000;
const uint16_t negativeAuditoryFrequency1 = 5000;
const uint16_t negativeAuditoryFrequency2 = 10000;
const uint16_t delayOf2Seconds = 2000;
const uint16_t delayOf1Second = 1000;
const uint16_t durationOf1Second = 1000;
const uint8_t delayOf100milliSeconds = 100;
const uint16_t delayOf500MilliSeconds = 500;
const uint16_t durationOf500MilliSeconds = 500;
const uint16_t serialBaudRate = 9600;

//prototypes of the functions used in this program.
void accessGranted();
void accessDenied();
void positiveAuditoryFeedback();
void negativeAuditoryFeedback();
void TurnGreenLedON();
void TurnRedLedON();
void LCDfeedback(boolean granted);

//enteredPassCode variable will be used to store entered passcode
//by the user
char enteredPassCode[passCodeLength];

//passCodesArray stores the 10 valid passcodes
char passCodesArray[passCodesArraySize][passCodeLength + 1] =
           { "may1", "abcd", "1a2b", "1234", "flow"
             , "rock", "1s2s", "car3", "pik1", "wolf" };

// FUNCTION     : accessGranted
// DESCRIPTION  :
//    This fuction prints "Access Granted" on serial port and
// also calls two functions to glow green LED and to make a
// single beep sound using speaker.
// PARAMETERS   : void
// RETURNS      : void
void accessGranted()
{
  Serial.println("Access Granted");
  LCDfeedback(true);
  TurnGreenLedON();
  positiveAuditoryFeedback();
}

// FUNCTION     : accessDenied
// DESCRIPTION  :
//    This fuction prints "Access Denied" on serial port and
// also calls two functions to glow red LED and to make a
// two beep sounds using speaker.
// PARAMETERS   : void
// RETURNS      : void
void accessDenied()
{
  Serial.println("Access Denied");
  LCDfeedback(false);
  TurnRedLedON();
  negativeAuditoryFeedback();
}

// FUNCTION     : positiveAuditoryFeedback
// DESCRIPTION  :
//    This fuction makes the single beep sound using speaker.
// PARAMETERS   : void
// RETURNS      : void
void positiveAuditoryFeedback()
{
  //Sends the PWM signal of frequency 2000 Hz for 1 second to
  //speaker pin
  tone(speakerPin, positiveAuditoryFrequency , durationOf1Second);
}

// FUNCTION     : negativeAuditoryFeedback
// DESCRIPTION  :
//    This fuction makes two beep sounds using speaker.
// PARAMETERS   : void
// RETURNS      : void
void negativeAuditoryFeedback()
{
  //Sends the PWM signal of frequency 5000 Hz for 1 second to
  //speaker pin
  tone(speakerPin, negativeAuditoryFrequency1, durationOf500MilliSeconds);
  //wait for two seconds to make two beep sounds.
  delay(delayOf1Second);
  //Sends the PWM signal of frequency 10000 Hz for 1 second to
  //speaker pin
  tone(speakerPin, negativeAuditoryFrequency2, durationOf500MilliSeconds);
}

// FUNCTION     : TurnGreenLedON
// DESCRIPTION  :
//    This fuction turns the green LED ON.

// PARAMETERS   : void
// RETURNS      : void
void TurnGreenLedON()
{
  digitalWrite(greenLedPin , HIGH);  //turns ON the green LED
  digitalWrite(redLedPin , LOW);  //turns OFF the red LED
}

// FUNCTION     : TurnRedLedON
// DESCRIPTION  :
//    This fuction turns the red LED ON.

// PARAMETERS   : void
// RETURNS      : void
void TurnRedLedON()
{
  digitalWrite(redLedPin , HIGH);  //turns ON the red LED
  digitalWrite(greenLedPin , LOW);  //turns Off the green LED
}


// FUNCTION     : LCDfeedback
// DESCRIPTION  :
//    This fuction prints "Access Granted" on LCD if passed 
// argument is true else it prints "Access Denied" on LCD.
//
// PARAMETERS   : boolean granted
// RETURNS      : void

void LCDfeedback(boolean granted)
{
  //Clears the LCD screen
  lcd.clear();
  // set cursor position to start of first line on the LCD
  lcd.setCursor(0,0);
  //text to print
  lcd.print("     ACCESS");
  // set cursor position to start of next line
  lcd.setCursor(0,1);
  //if this function is called with "true" argument bottom line
  //of lcd will print "GRANTED" else it will print "DENIED" 
  if (granted == true)
  {
    
    lcd.print("     GRANTED");
  }
  else
  {
    lcd.print("     DENIED");
  }
}


void setup()
{
  // put your setup code here, to run once:
  //Initializes serial port and Sets the data rate in bits per
  //second (baud)for serial data transmission.
  Serial.begin( serialBaudRate );

  //wait for 2 seconds to let serial port initialized.
  delay( delayOf2Seconds );

  // sets the digital pin redLedPin as output.
  pinMode( redLedPin, OUTPUT );

  // sets the digital pin greenLedPin as output.
  pinMode( greenLedPin, OUTPUT );

  // sets the digital pin speakerPin as output.
  pinMode( speakerPin, OUTPUT );

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //prints "Enter Passcode" on the serial port.This line of code
  //is added in Setup() because it needs to be printed only once
  //at the start of the program.
  Serial.println("Enter Passcode");
  //prints "Enter Passcode" on LCD
  lcd.print("Enter Passcode"); 

}

void loop()
{
  // put your main code here, to run repeatedly:
  //if bytes available in serial port buffer are more than zero then.

  
  //if entered passcode length is between o and 4
  if ( Serial.available() > 0 && Serial.available() <= passCodeLength )
  {
    //This for loop is used to get string serialy in entered
    //passcode variable.
    for (uint8_t i = 0; i < passCodeLength ; i++)
    {
      //get data from serial port to the variable
      enteredPassCode[i] = Serial.read();
      //this line of code will print the Entered passcode on
      //serial port.
      Serial.write( enteredPassCode[i] );
      //wait for 100 milliseconds
      delay( delayOf100milliSeconds );
    }
    //this newline backslash character is outside loop because
    //newline is needed only when whole passcode or string is
    //printed.
    Serial.write("\n");

    //"denied" is a flag,which will make sure that accessDenied()
    // function will only be called once in all for loop 
    // executions.
    boolean denied = false;

    //this loop compares the entered passcode with every valid
    //passcode stored in the array.
    //this loop will execute 10 times equal to the size of
    //passcodes array.
    for (uint8_t i = 0; i < passCodesArraySize ; i++)
    {
      //0,1,2,3 in following "if" statement are used to compare
      // each and every letter/digit with passcodes array.
      //if entered passcode is equal to i'th valid passcode of
      //array then
      if (enteredPassCode[0] == passCodesArray[i][0] &&
          enteredPassCode[1] == passCodesArray[i][1] &&
          enteredPassCode[2] == passCodesArray[i][2] &&
          enteredPassCode[3] == passCodesArray[i][3]    )
      {
        accessGranted();
        //if valid passcode is entered so,no need to call
        //accessDenied(). so, flag is set to true.
        denied = true;
      }
      //if entered passcode is not equal to valid passcode
      else
      {
        // (!denied) condition excludes the calling 
        //accesdenied() if passcodes matches.
        //(i==(passCodesArraySize - 1)) makes sure that 
        //accesDenied() function is called only when all 
        //passcodes are compared with entered passcode 
        if (!denied && i == (passCodesArraySize - 1))
        {
          accessDenied();
          denied = true;
        }
      }
    }
  }
  //if length of entered passcode is not 4 digits/characters then
  else if(Serial.available() > passCodeLength)
  {
    //gets the length of long passcode in variable
    LengthOfInvalidPasscode = Serial.available();
    //this for loop is used to transfer long invalid passcode
    //into garbage character array. 
    for(uint8_t i=0 ; i <= LengthOfInvalidPasscode ; i++)
    {
      garbagePasscode[i]= Serial.read();
    }
    Serial.write("Passcode is of 4 digits, please enter again \n");
    //as entered passcode is too long and is obviously wrong so calling
    // accessdDenied() function 
    accessDenied();
  }
}
