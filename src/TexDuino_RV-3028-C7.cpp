/*
 * TexDuino_RV-3028-C7.h
 *
 * Arduino Library for the TexDuino breakoutboard for the Micro Crystal RV-3028-C7 Real-Time Clock Module
 * 
 * (c) TexDuino 2020-2021
 * BSD 3-clause "New" or "Revised" License
 *  
 */


#include "TexDuino_RV-3028-C7.h"

bool RV3028C7::begin(){
  Wire.begin();
  trickleChargerDisable();
  return true;

}

void RV3028C7::setSeconds(uint8_t seconds){

  writeData(RV3028C7_SecondsRegister, seconds);
  
}

void RV3028C7::setMinutes(uint8_t minutes){

  writeData(RV3028C7_MinutesRegister, minutes);

}

void RV3028C7::setHours(uint8_t hours){

  writeData(RV3028C7_HoursRegister, hours);

}

void RV3028C7::setAM(){

  clearBit(RV3028C7_HoursRegister,5);    

}

void RV3028C7::setPM(){

    setBit(RV3028C7_HoursRegister,5);    

}

void RV3028C7::setWeekday(uint8_t day){

  writeData(RV3028C7_WeekdayRegister, day);

}

void RV3028C7::setDay(uint8_t month){

  writeData(RV3028C7_DateRegister, month);

}
void RV3028C7::setMonth(uint8_t month){

  writeData(RV3028C7_MonthRegister, month);

}

void RV3028C7::setYear(uint8_t year){

  writeData(RV3028C7_YearRegister, year);

}

void RV3028C7::setTime(uint8_t hours, uint8_t minutes, uint8_t seconds){
  
  setSeconds(seconds);
  setMinutes(minutes);
  setHours(hours);

}

void RV3028C7::setDate(uint8_t day, uint8_t month, uint8_t year){

  setDay(day);
  setMonth(month);
  setYear(year);

}


uint8_t RV3028C7::getSeconds(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_SecondsRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);
  if (Wire.available()){
    seconds = Wire.read();    //
  }

  return(bcdToDec(seconds));

}


uint8_t RV3028C7::getMinutes(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_MinutesRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);
  
  if (Wire.available()){
    minutes = Wire.read();    //
  }

    return(bcdToDec(minutes));

}

uint8_t RV3028C7::getHours(){
  
  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_HoursRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);

  if (Wire.available()){
    hours = Wire.read();    //
  }

  uint8_t tHours = bcdToDec(hours);
  
  if (is24Hour()==0){
    //nothing to change
  }
   else{
    //substract 20 from the hours register to get the correct 12 hour(AM/PM) time
    if (tHours >12){
      tHours = tHours-20;
    } 
  }

   return (tHours);
   //return (bcdToDec(hours));
}



uint8_t RV3028C7::getWeekday(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_WeekdayRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);
  
  if (Wire.available()){
    weekday = Wire.read();    //
  }

  return(bcdToDec(weekday));

}


uint8_t RV3028C7::getDate(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_DateRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);
  
  if (Wire.available()){
    date = Wire.read();    //
  }

  return(bcdToDec(date));

}


uint8_t RV3028C7::getMonth(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_MonthRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);
  
  if (Wire.available()){
    month = Wire.read();    //
  }

  return(bcdToDec(month));

}



uint8_t RV3028C7::getYear(){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(RV3028C7_YearRegister);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);

  if (Wire.available()){
    year = Wire.read();   
  }

  year = bcdToDec(year);
 
  return(year);

}


void RV3028C7::clkOUT(int clockFrequency){

  writeRegister(RV3028C7_CLKoutRegister, clockFrequency);

}



uint8_t RV3028C7::is24Hour(){
    
    //read 12_24 bit. 0 if using 24 hour clock and 1 if using 12 hour clock
return readBit(RV3028C7_Control2Register, 1);

}


void RV3028C7::set24HourClock(){

    //clear 12_24 bit to use 24 hour clock
    clearBit(RV3028C7_Control2Register,1);    
  
}


void RV3028C7::set12HourClock(){

    //set 12_24 bit to use 12 hour clock (AM/PM)
    setBit(RV3028C7_Control2Register,1);

}


uint8_t RV3028C7::isAMPM() {

return readBit(RV3028C7_HoursRegister, 5);
  
}


void RV3028C7::enableAlarm(){

}


void RV3028C7::disableAlarm(){
  
}


void RV3028C7::readData(byte registerAddress, int numberOfBytes){
  
  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, numberOfBytes);

}


void RV3028C7::writeData(byte registerAddress, uint8_t dataToWrite){
  
  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(registerAddress);
  Wire.write(decToBdc(dataToWrite));
  Wire.endTransmission();

}

byte RV3028C7::bcdToDec(uint8_t val){

    return( (val/16*10) + (val%16) );
}


byte RV3028C7::decToBdc(byte val){

  return( (val/10*16) + (val%10) );

}


bool RV3028C7::readBit(byte registerAddress, int bitNumber)
{
	uint8_t value = readRegister(registerAddress);
	value &= (1 << bitNumber);
  return value;
  
	
}

void RV3028C7::setBit(byte registerAddress, int bitNumber){

  uint8_t tValue = readRegister(registerAddress);

  bitSet(tValue, bitNumber);
	writeRegister(registerAddress, tValue);

}

void RV3028C7::clearBit(byte registerAddress, int bitNumber){

  uint8_t tValue = readRegister(registerAddress);
	bitClear(tValue, bitNumber);
 	writeRegister(registerAddress, tValue);

}

bool RV3028C7::read12_24bit(){
    return(readBit(RV3028C7_Control2Register,1));
}


byte RV3028C7::readRegister(uint8_t registerAddress){
  
  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(RV3028C7_Address, 1);

  byte returnValue = 0x00;

	if (Wire.available()) {
 	  returnValue = Wire.read();
  }
   else{
	  returnValue = 0xFF; //error
  }

  return returnValue;
  
}


void RV3028C7::writeRegister(uint8_t registerAddress, byte dataToWrite){

  Wire.begin();
  Wire.beginTransmission(RV3028C7_Address);
  Wire.write(registerAddress);
  Wire.write(dataToWrite);
  Wire.endTransmission();

}


void RV3028C7::trickleChargerDisable(){
  /*
  *
  * the TexDuino RV-3028-C7 is delivered with an onbord NON rechargeable primary battery; 
  * therefore it is critical that the trickle charger function stays disabled.
  * 
  */

  clearBit(EEPROM_Backup_Register,5);

}
