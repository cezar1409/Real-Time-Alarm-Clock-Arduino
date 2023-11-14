#include <LiquidCrystal_I2C.h>
//this library allows you to communicate with I2C devices.
//for ESP32 SDA = GPIO 21; SCL = GPIO 22
#include <Wire.h>
#include <WiFi.h>
#include <NTPClient.h>               
#include <TimeLib.h>  
//We will use NTPClient Library first. This library connects the ESP32 WiFi to a time server, the server sends time information to the module.

//Then we have Time library which converts Unix timestamp (Unix epoch) into seconds, minutes, hours, day of the week, day, month and year.
//initialize the liquid crystal library

LiquidCrystal_I2C lcd(0x27, 16, 2);
//the first parameter is the I2C address
//the second parameter is how many rows are on your screen
//the third parameter is how many columns are on your screen
const char *ssid     = "Dana";
const char *password = "07081994";

WiFiUDP ntpUDP;
 
 
NTPClient timeClient(ntpUDP, "ro.pool.ntp.org", 10800, 60000);
 
char Time[ ] = "TIME:00:00:00";
char Date[ ] = "DATE:00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;
 
 

//the number of the pins connected to the buttons
const int button1 = 15;  
const int button2 = 18;
const int button3 = 5;
const int button4 = 19;
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

const int led = 26;

int BUZZER_PIN = 14; //the number of the pin connected to the buzzer
int BUZZER_CHANNEL = 0;
int sec;
int monthday= 0;
int hours= 10;
int minutes = 10;
int seconds = 25;
int K = 1;
int days= 21;
int months = 5;
int years = 2022;
int asecond;
int aminute;
int ahour;
int aday;
int state=0;



void printLocalTime() 
{
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server
 
  second_ = second(unix_epoch);
  if (last_second != second_) {
 
 
    minute_ = minute(unix_epoch);
    hour_   = hour(unix_epoch);
    day_    = day(unix_epoch);
    month_  = month(unix_epoch);
    year_   = year(unix_epoch);
 
 
 
    Time[12] = second_ % 10 + 48;
    Time[11] = second_ / 10 + 48;
    Time[9]  = minute_ % 10 + 48;
    Time[8]  = minute_ / 10 + 48;
    Time[6]  = hour_   % 10 + 48;
    Time[5]  = hour_   / 10 + 48;
 
 
 
    Date[5]  = day_   / 10 + 48;
    Date[6]  = day_   % 10 + 48;
    Date[8]  = month_  / 10 + 48;
    Date[9]  = month_  % 10 + 48;
    Date[13] = (year_   / 10) % 10 + 48;
    Date[14] = year_   % 10 % 10 + 48;
    //seconds= second_ % 10 + 48 + (second_ / 10 + 48)*10;
    //Serial.println(minute_);
// Serial.println(second_);
 // Serial.println(hour_);
    //Serial.println(day_);
    //Serial.println(Time);
    //Serial.println(Date);
    
 
    lcd.setCursor(0, 0);
    lcd.print(Time);
    lcd.setCursor(0, 1);
    lcd.print(Date);
    lcd.print(" ");
    last_second = second_;
 
  }
  delay(500);
  

 
}

void alarm()
{ 
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Alarm!");
  
  lcd.setCursor(0,1);
  lcd.print("Time:");
  
  if(hours < 10)
  {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  
  if(minutes < 10)
  {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  
  if(seconds < 10)
  {
    lcd.print("0");
  }
  lcd.print(seconds);
  
  
  while (buttonState4 == HIGH)//buzzer ringing
  {
    buttonState4 = digitalRead(button4); 
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_A, 4);
    delay(150);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_B, 5);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_C, 5);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_D, 5);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_E, 5);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_A, 3);
    delay(30);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_C, 5);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_C, 6);
    delay(20);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_F, 5);
    delay(30);
    ledcWriteNote(BUZZER_CHANNEL, (note_t)NOTE_G, 5);
    delay(20);
  }
return;
}



void print_time_and_date()
{
  // tell the screen to write the Alarm numbers
  //everytime any variable is less than 10 instead of 9, on the lcd is shown 09
  lcd.setCursor(0,0);
  lcd.print("Set:");
  if(hours < 10)
  {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if(minutes < 10)
  {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if(seconds < 10)
  {
    lcd.print("0");
  }
  lcd.print(seconds);
  lcd.setCursor(0,1);
  lcd.print("Alarm:");
  if(days < 10)
  {
    lcd.print("0");
  }
  lcd.print(days);
  lcd.print("/");
  if(months < 10)
  {
    lcd.print("0");
  }
  lcd.print(months);
  lcd.print("/");
  lcd.print(years);
  lcd.print(" ");
  //changes the cursor for every state
  blink();
}

void setup(){

  pinMode(button1, INPUT_PULLUP); //or INPUT and add resistor
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
 

  // initialize LCD
  lcd.begin();
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(115200);
 
  lcd.setCursor(0, 0);
  lcd.print(Time);
  lcd.setCursor(0, 1);
  lcd.print(Date);
 
  WiFi.begin(ssid, password);
  Serial.print("Connecting.");
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  timeClient.begin();


  
  
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void blink()
{//cursor blink moving
    if (state == 0)
      lcd.setCursor(3, 0);
    if (state == 1)
      lcd.setCursor(6, 0);
    if (state == 2)
      lcd.setCursor(9, 0);
    if (state == 3)
      lcd.setCursor(5, 1);
    if (state == 4)
      lcd.setCursor(8, 1);
    if (state == 5)
      lcd.setCursor(11, 1);
}

void setalarm()
{//alarm setting
  delay(2000);
  lcd.clear();
  print_time_and_date();
  delay(2000);
  while( K == 1)
  {
    lcd.blink();
    //1st button increment
    //2nd button decrement
    //3rd button move through date and time
    //4th button - set date and time for alarm
    if(months == 1 || months == 3 || months == 5 || months == 7 || months == 8 || months == 10 || months == 12 )
      monthday = 31;
    else if(months == 4 || months == 6 || months == 9 || months == 11 )
      monthday = 30;
    else if(years %4 == 0)
      monthday = 29;
    else
      monthday = 28;

    buttonState = digitalRead(button1);
    if (buttonState == LOW)
    {
      if (state == 0)
      {
        hours += 1;
        if(hours == 24)
           hours = 0; 
      }
      else if (state == 1)
      {
        minutes += 1;
        if(minutes == 60)
           minutes = 0; 
      }
      else if (state == 2)
      {
        seconds += 1;
        if(seconds == 60)
           seconds = 0; 
      }
      else if (state == 3)
      {
        days += 1;
        if(days == monthday+1)
           days = 1; 
      }
      else if (state == 4)
      { 
        months += 1;
        if(months == 12)
          months = 1; 
      }
      else if (state == 5)
        years += 1;
       
      print_time_and_date();
      delay(500);
  } 

  buttonState2 = digitalRead(button2);
  if (buttonState2 == LOW)
  {
      if (state == 0)
        {hours -= 1;
        if(hours == -1)
           hours = 23; }
      else if (state == 1)
        {minutes -= 1;
         if(minutes == -1)
           minutes = 59; }
      else if (state == 2)
        {seconds -= 1;
      if(seconds == -1)
           seconds = 59; }
      else if (state == 3)
        {days -= 1;
        if(days == 0)
           days = monthday; }
      else if (state == 4)
        {months -= 1;
        if(months == 0)
           months = 12; }
      else if (state == 5)
        years -= 1;
        
      print_time_and_date();
      delay(500);
  } 

  buttonState3 = digitalRead(button3);
  if (buttonState3 == LOW)
  {
      state += 1;
        blink();
      if (state == 6)
      {   state = 0;
          blink();
                    }
      delay(500);
  } 
   buttonState4 = digitalRead(button4);
  if (buttonState4 == LOW)
  K = 0;
}
}

void loop()
{ 
  printLocalTime();//prints actual time
  lcd.noBlink();
  buttonState4 = digitalRead(button4);
  if (buttonState4 == LOW) //if button is placed change to alarm set up screen
  {
    K = 1;//constant
    setalarm();
    delay(250);
  }
     
  //real time variables

  //comparison between the alarm set and the rt variables
  if(day_==days)
    if(hour_==hours)
      if(minute_==minutes)
        if(second_==seconds)
        { alarm();//alarm ringing
          ledcWrite(0, 0);
          delay(10);
        }
        
 
}
