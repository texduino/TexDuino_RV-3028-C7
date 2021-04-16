/*
 * TexDuino_RV-3028-C7.h
 *
 * Arduino Example for the TexDuino RV-3028-C7 API
 * 
 * (c) TexDuino 2020-2021
 * BSD 3-clause "New" or "Revised" License
 *  
 */

#include <TexDuino_RV-3028-C7.h>

RV3028C7 rtc;


void setup() {

Serial.begin(9600);

  delay(1000);
    
  Wire.begin();
  if (rtc.begin() == false) {
    Serial.print("Oops, can't talk to RV-3028-C7 RTC. Check your wiring first!");
    Serial.print("check www.TexDuino.com for help");
    while (1);
  }
  else{
    Serial.println("Connected to TexDuino RV-3028-C7 Real Time Clock");
  }



//once you set the date and time, be sure to comment out these lines    


//if you want to use a 24 hour clock, uncomment the following two lines and comment out the 12 hour section
//rtc.set24HourClock();   //set the clock to 24 hour clock
//rtc.setTime(13,47,0);   //set time to 13:47:00

//if you want to use a 12 hour clock, uncomment the following three lines and comment out the 24 hour line section above
rtc.set12HourClock();   //set the clock to 12 hour clock (AM/PM)
rtc.setTime(1,47,0);   //set time to 1:47:00 PM
rtc.setPM();   // set it to PM. Alternativeley you can use rtc.setAM to set AM

rtc.setDate(10,1,21);   // set the date to January 10, 2021
rtc.setWeekday(0);    // we have to tell it what day of the week it is, in this example it is Sunday, the first day of the week in USA, so will set it to 0
}



void loop() {

  // this will print the stored date and time every second
  
  Serial.print(rWeekday());
  Serial.print(" ");

  Serial.print(rMonth());
  
 Serial.print(" ");
  Serial.print(rtc.getDate());  

  Serial.print(" ");
  Serial.print(rtc.getYear());  
  //Serial.print(2000 + rtc.getYear());  //the RV-3028-C7 only stores the last 2 digits of the year (21) if you want to display 2021 add 2000 to the year
  
  Serial.print(" ");
  Serial.print(rtc.getHours());
  Serial.print(":");
  printLeadingZero(rtc.getMinutes());
  Serial.print(":");
  printLeadingZero(rtc.getSeconds());

   
  if(rtc.is24Hour() == 0) {
    //the 12_24 bit not is set, using 24 hour clock
    Serial.println("");
  }
   else {
      //the 12_24 bit is set, using 12 hour clock
      if(rtc.isAMPM() == 0){
        Serial.println(" AM");
      }
      else {
       Serial.println(" PM");
      }
  }

  Serial.println("");
  delay(1000);
  
}


String rWeekday(){
  //the day of the week is stored as a number, 0 through 7. set the proper name according to your locale
  switch(rtc.getWeekday()){
    case 0:
      return "Sunday";
      break;
    
    case 1:
      return "Monday";
      break;

    case 2:
      return "Tuesday";
      break;

    case 3:
      return "Wednesday";
      break;

    case 4:
      return "Thursday";
      break;

    case 5:
      return "Friday";
      break;

    case 6:
      return "Saturday";
      break;

  }
  
}



String rMonth(){
  //the month is stored as a number, 1 through 12. set the proper name according to your locale

  switch(rtc.getMonth()){
    
    case 1:
      return "January";
      break;

    case 2:
      return "February";
      break;

    case 3:
      return "March";
      break;

    case 4:
      return "April";
      break;

    case 5:
      return "May";
      break;

    case 6:
      return "June";
      break;

    case 7:
      return "July";
      break;

    case 8:
      return "August";
      break;

    case 9:
      return "September";
      break;

    case 10:
      return "October";
      break;

    case 11:
      return "November";
      break;

    case 12:
      return "December";
      break;

  }
  
}

void printLeadingZero(uint8_t info){
  //use this if you want to print a leading 0 on numbers that are less then 10
  if (info < 10) {
    Serial.print("0"); // print a 0 before if the number is < than 10
  }
  Serial.print(info);
  
}
