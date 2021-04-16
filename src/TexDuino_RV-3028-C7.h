/*
 * TexDuino_RV-3028-C7.h
 *
 * Arduino Library for the TexDuino breakoutboard for the Micro Crystal RV-3028-C7 Real-Time Clock Module
 * 
 *  
 * (c) TexDuino 2020-2021
 * BSD 3-clause "New" or "Revised" License
 *  
 */

#include "Arduino.h"
#include "Wire.h"

#ifndef RV3028C7_h
#define RV3028C7_h


class RV3028C7
{
  public:
    bool begin();
  
    void setSeconds(uint8_t seconds);
    void setMinutes(uint8_t minutes);
    void setHours(uint8_t hours);
    void setAM();
    void setPM();
    
    void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

    void setDay(uint8_t day);

    void setWeekday(uint8_t day);

    void setMonth(uint8_t month);
    void setYear(uint8_t year);
    void setDate(uint8_t day, uint8_t month, uint8_t year);

    void setAlarmSeconds(uint8_t seconds);
    void setAlarmMinutes(uint8_t minutes);
    void setAlarmHours(uint8_t hours);    
    void setAlarmTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

    void setAlarmDay(uint8_t day);
    void setAlarmMonth(uint8_t month);
    void setAlarmYear(uint8_t year);
    void setAlarmDate(uint8_t day, uint8_t month, uint8_t year);

    void enableAlarm();
    void disableAlarm();

    uint8_t getSeconds();
    uint8_t getMinutes();
    uint8_t getHours();
   
    uint8_t getWeekday();
    uint8_t getDate();
    uint8_t getMonth();
    uint8_t getYear();
    
    uint8_t getAlarmSeconds();
    uint8_t getAlarmMinutes();
    uint8_t getAlarmHours();
    char getAlarmTime();

    uint8_t getAlarmDay();
    uint8_t getAlarmMonth();
    uint8_t getAlarmYear();
    char getAlarmDate();

    void clkOUT(int clockFrequency);

    void set24HourClock();
    void set12HourClock();
    
    uint8_t is24Hour();
    uint8_t isAMPM();

    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t weekday;
    uint8_t date;
    uint8_t month;
    int year;
    
   


  private:   
    byte bcdToDec(uint8_t val);
    byte decToBdc(uint8_t val);
    byte readRegister(uint8_t registerAddress);
    bool read12_24bit();

    bool readBit(byte registerAddress, int bitNumber);

    void clearBit(byte registerAddress, int bitNumber);

    void setBit(byte registerAddress, int bitNumber);
  
    void trickleChargerDisable();

    void writeData(byte registerAddress, uint8_t dataToWrite);
    
    void writeRegister(uint8_t registerAddress, uint8_t value);
   // bool readBit(byte registerAddress, int bitNumber);
     
    void readData(byte registerAddress, int numberOfBytes);
 
};

    
#define RV3028C7_Address    (int) 0x52  //The I2C address for the RV-3028-C7
//Registers used for time storage

#define RV3028C7_SecondsRegister      			0x00
#define RV3028C7_MinutesRegister      			0x01
#define RV3028C7_HoursRegister        			0x02
//Registers used for date storage
#define RV3028C7_WeekdayRegister  					0x03
#define RV3028C7_DateRegister         			0x04
#define RV3028C7_MonthRegister        			0x05
#define RV3028C7_YearRegister         			0x06
//Registers used for Alarm
#define RV3028C7_ALARM_MinutesRegister 			0x07
#define RV3028C7_ALARM_HoursRegister   			0x08
#define RV3028C7_ALARM_Date_Register   			0x09
//Registers used for Timers
#define RV3028C7_TimerValue0Register        0x0A
#define RV3028C7_TimerValue1Register        0x0B
#define RV3028C7_TimerStatus1Register       0x0C
#define RV3028C7_TimerStatus2Register       0x0D
//Registers used for Status and Control
#define RV3028C7_StatusRegister             0x0E
#define RV3028C7_Control1Register           0x0F
#define RV3028C7_Control2Register           0x10

//Registers in EEPROM
#define RV3028C7_CLKoutRegister             0x35
#define EEPROM_Backup_Register              0x37

//CLKout options
#define RV3028C7_clkOUT_32768				0b11000000			//32.768 kHz – Default value on delivery 
#define RV3028C7_clkOUT_8192				0b11000001 			//8192 Hz 
#define RV3028C7_clkOUT_1024				0b11000010			//1024 Hz
#define RV3028C7_clkOUT_64					0b11000011 		  //64 Hz 
#define RV3028C7_clkOUT_32					0b11000100			//32 Hz
#define RV3028C7_clkOUT_1           0b11000101
#define RV3028C7_clkOUTpredefined   0b11000101
#define RV3028C7_clkOUT_Disabled    0b01000111


#endif