#include <lpc21xx.h>

#include "LCD.h"
#include "lcd_defines.h"
#include "rtclock.h"
#include "kpm.h"
#include "schedule.h"
#include "delay.h"


//EINT0 ISR
void EINT0_ISR(void) __irq;


//menu request flag
volatile u32 menu_request = 0;


//global variables
s32 hour;
s32 min;
s32 sec;

s32 date;
s32 month;
s32 year;

s32 day;

u32 on_hour;
u32 on_min;

u32 off_hour;
u32 off_min;


//temporary schedule variables
u32 temp_on_hour;
u32 temp_on_min;

u32 temp_off_hour;
u32 temp_off_min;


//week table
u8 week[][4] =
{
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"
};


//leap year
u32 IsLeapYear(u32 year)
{
    if((year % 400) == 0)
        return 1;

    if((year % 100) == 0)
        return 0;

    if((year % 4) == 0)
        return 1;

    return 0;
}


//get days in month
u32 GetDaysInMonth(u32 month, u32 year)
{
    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            if(IsLeapYear(year))
                return 29;

            return 28;

        default:
            return 0;
    }
}


//display RTC
void DisplayRTC(void)
{
    static u32 count = 0;
    static u32 mode = 0;


    //get time
    GetRTCTimeInfo(&hour,
                   &min,
                   &sec);


    //display time
    WRITE_LCD_CMD(GOTO_LINE1_POS0);

    WRITE_LCD_DATA((hour / 10) + '0');
    WRITE_LCD_DATA((hour % 10) + '0');

    WRITE_LCD_DATA(':');

    WRITE_LCD_DATA((min / 10) + '0');
    WRITE_LCD_DATA((min % 10) + '0');

    WRITE_LCD_DATA(':');

    WRITE_LCD_DATA((sec / 10) + '0');
    WRITE_LCD_DATA((sec % 10) + '0');


    //get day
    GetRTCDay(&day);


    //display day
    WRITE_LCD_CMD(GOTO_LINE1_POS0 + 10);

    if(day <= 6)
    {
        StrLCD(week[day]);
    }


    //get date
    GetRTCDateInfo(&date,
                   &month,
                   &year);


    //display second line
    if(count == 0)
    {
        WRITE_LCD_CMD(GOTO_LINE2_POS0);

        //clear second line
        StrLCD("                ");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);


        if(mode == 0)
        {
            //display date
            WRITE_LCD_DATA((date / 10) + '0');
            WRITE_LCD_DATA((date % 10) + '0');

            WRITE_LCD_DATA('/');

            WRITE_LCD_DATA((month / 10) + '0');
            WRITE_LCD_DATA((month % 10) + '0');

            WRITE_LCD_DATA('/');

            U32LCD(year);
        }
        else
        {
            //display on off time
            StrLCD("ON:");

            WRITE_LCD_DATA((on_hour / 10) + '0');
            WRITE_LCD_DATA((on_hour % 10) + '0');

            WRITE_LCD_DATA(':');

            WRITE_LCD_DATA((on_min / 10) + '0');
            WRITE_LCD_DATA((on_min % 10) + '0');

            StrLCD("OF:");

            WRITE_LCD_DATA((off_hour / 10) + '0');
            WRITE_LCD_DATA((off_hour % 10) + '0');

            WRITE_LCD_DATA(':');

            WRITE_LCD_DATA((off_min / 10) + '0');
            WRITE_LCD_DATA((off_min % 10) + '0');
        }
    }


    //delay is 200ms
    count++;


    //2 seconds
    if(count >= 10)
    {
        count = 0;

        if(mode == 0)
        {
            mode = 1;
        }
        else
        {
            mode = 0;
        }
    }
}


//set hour
void SetHour(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER HOUR:");

        hour = ReadNum();

        if(hour > 23)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID HOUR");

            delay_ms(1000);
        }

    }while(hour > 23);


    //set RTC time
    SetRTCTimeInfo(hour,
                   min,
                   sec);
}


//set minute
void SetMinute(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER MIN:");

        min = ReadNum();

        if(min > 59)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID MIN");

            delay_ms(1000);
        }

    }while(min > 59);


    //set RTC time
    SetRTCTimeInfo(hour,
                   min,
                   sec);
}


//set second
void SetSecond(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER SEC:");

        sec = ReadNum();

        if(sec > 59)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID SEC");

            delay_ms(1000);
        }

    }while(sec > 59);


    //set RTC time
    SetRTCTimeInfo(hour,
                   min,
                   sec);
}


//time menu
void SetTimeMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.HR 2.MIN");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.SEC 4.BACK");


        key = KeyScan();


        //hour
        if(key == '1')
        {
            SetHour();
        }


        //minute
        else if(key == '2')
        {
            SetMinute();
        }


        //second
        else if(key == '3')
        {
            SetSecond();
        }


        //back to RTC menu
        else if(key == '4')
        {
            return;
        }
    }
}


//set date
void SetDate(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER DATE:");

        date = ReadNum();


        if((date < 1) ||
           (date > GetDaysInMonth(month, year)))
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID DATE");

            delay_ms(1000);
        }

    }while((date < 1) ||
           (date > GetDaysInMonth(month, year)));


    //set RTC date
    SetRTCDateInfo(date,
                   month,
                   year);
}


//set month
void SetMonth(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER MONTH:");

        month = ReadNum();


        if((month < 1) ||
           (month > 12))
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID MONTH");

            delay_ms(1000);
        }

    }while((month < 1) ||
           (month > 12));


    //check current date
    if(date > GetDaysInMonth(month, year))
    {
        date = 1;
    }


    //set RTC date
    SetRTCDateInfo(date,
                   month,
                   year);
}


//set year
void SetYear(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ENTER YEAR:");

        year = ReadNum();


        if((year < 2000) ||
           (year > 2099))
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID YEAR");

            delay_ms(1000);
        }

    }while((year < 2000) ||
           (year > 2099));


    //check current date
    if(date > GetDaysInMonth(month, year))
    {
        date = 1;
    }


    //set RTC date
    SetRTCDateInfo(date,
                   month,
                   year);
}


//date menu
void SetDateMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.DATE 2.MONTH");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.YEAR 4.BACK");


        key = KeyScan();


        //date
        if(key == '1')
        {
            SetDate();
        }


        //month
        else if(key == '2')
        {
            SetMonth();
        }


        //year
        else if(key == '3')
        {
            SetYear();
        }


        //back to RTC menu
        else if(key == '4')
        {
            return;
        }
    }
}


//set day
void SetDayMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("0S 1M 2T 3W");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("4T 5F 6S 7B");


        //get day
        key = KeyScan();


        if((key >= '0') &&
           (key <= '6'))
        {
            day = key - '0';

            //set RTC day
            SetRTCDay(day);

            return;
        }


        //back to RTC menu
        else if(key == '7')
        {
            return;
        }
    }
}


//set ON hour
void SetOnHour(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ON HOUR:");

        temp_on_hour = ReadNum();


        if(temp_on_hour > 23)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID HOUR");

            delay_ms(1000);
        }

    }while(temp_on_hour > 23);
}


//set ON minute
void SetOnMinute(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("ON MIN:");

        temp_on_min = ReadNum();


        if(temp_on_min > 59)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID MIN");

            delay_ms(1000);
        }

    }while(temp_on_min > 59);
}


//set OFF hour
void SetOffHour(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("OFF HOUR:");

        temp_off_hour = ReadNum();


        if(temp_off_hour > 23)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID HOUR");

            delay_ms(1000);
        }

    }while(temp_off_hour > 23);
}


//set OFF minute
void SetOffMinute(void)
{
    do
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("OFF MIN:");

        temp_off_min = ReadNum();


        if(temp_off_min > 59)
        {
            WRITE_LCD_CMD(0x01);

            StrLCD("INVALID MIN");

            delay_ms(1000);
        }

    }while(temp_off_min > 59);
}


//ON menu
void OnMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.HR 2.MIN");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.BACK");


        key = KeyScan();


        //ON hour
        if(key == '1')
        {
            SetOnHour();
        }


        //ON minute
        else if(key == '2')
        {
            SetOnMinute();
        }


        //back to schedule menu
        else if(key == '3')
        {
            return;
        }
    }
}


//OFF menu
void OffMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.HR 2.MIN");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.BACK");


        key = KeyScan();


        //OFF hour
        if(key == '1')
        {
            SetOffHour();
        }


        //OFF minute
        else if(key == '2')
        {
            SetOffMinute();
        }


        //back to schedule menu
        else if(key == '3')
        {
            return;
        }
    }
}


//set schedule
void SetScheduleMenu(void)
{
    u32 key;


    //copy existing schedule
    temp_on_hour = on_hour;
    temp_on_min = on_min;

    temp_off_hour = off_hour;
    temp_off_min = off_min;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.ON 2.OFF");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.BACK");


        key = KeyScan();


        //ON menu
        if(key == '1')
        {
            OnMenu();
        }


        //OFF menu
        else if(key == '2')
        {
            OffMenu();
        }


        //back / save schedule
        else if(key == '3')
        {
            //same ON and OFF time is invalid
            if((temp_on_hour == temp_off_hour) &&
               (temp_on_min == temp_off_min))
            {
                WRITE_LCD_CMD(0x01);

                StrLCD("SAME TIME");

                delay_ms(1000);
            }
            else
            {
                //save schedule
                on_hour = temp_on_hour;
                on_min = temp_on_min;

                off_hour = temp_off_hour;
                off_min = temp_off_min;


                Schedule_SetTime(on_hour,
                                 on_min,
                                 off_hour,
                                 off_min);


                WRITE_LCD_CMD(0x01);

                StrLCD("SCHEDULE SAVED");

                delay_ms(1000);

                return;
            }
        }
    }
}


//RTC menu
void RTC_SubMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.TIME 2.DATE");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.DAY 4.BACK");


        //wait for key
        key = KeyScan();


        //time
        if(key == '1')
        {
            SetTimeMenu();
        }


        //date
        else if(key == '2')
        {
            SetDateMenu();
        }


        //day
        else if(key == '3')
        {
            SetDayMenu();
        }


        //back to MAIN menu
        else if(key == '4')
        {
            return;
        }
    }
}


//main menu
void MainMenu(void)
{
    u32 key;


    while(1)
    {
        WRITE_LCD_CMD(0x01);

        WRITE_LCD_CMD(GOTO_LINE1_POS0);
        StrLCD("1.RTC  2.SCH");

        WRITE_LCD_CMD(GOTO_LINE2_POS0);
        StrLCD("3.EXIT");


        //wait for key
        key = KeyScan();


        //RTC
        if(key == '1')
        {
            RTC_SubMenu();
        }


        //schedule
        else if(key == '2')
        {
            SetScheduleMenu();
        }


        //exit menu
        else if(key == '3')
        {
            return;
        }
    }
}


//EINT0 initialization
void EINT0_Init(void)
{
    //P0.1 as EINT0
    PINSEL0 &= ~(3 << 2);
    PINSEL0 |= (3 << 2);


    //edge triggered
    EXTMODE |= (1 << 0);


    //falling edge
    EXTPOLAR &= ~(1 << 0);


    //IRQ
    VICIntSelect &= ~(1 << 14);


    //clear interrupt
    EXTINT = (1 << 0);


    //VIC slot 0
    VICVectAddr0 = (u32)EINT0_ISR;
    VICVectCntl0 = (1 << 5) | 14;


    //enable EINT0
    VICIntEnable |= (1 << 14);
}


//EINT0 ISR
void EINT0_ISR(void) __irq
{
    //set menu request
    menu_request = 1;


    //clear interrupt
    EXTINT = (1 << 0);


    //end of interrupt
    VICVectAddr = 0;
}


//main
int main()
{
    u32 device_status;


    //initialize peripherals
    INIT_LCD();

    RTC_Init();

    INIT_KPM();

    LED_Init();

    EINT0_Init();


    //initial time
   // SetRTCTimeInfo(9,
          //         0,
             //      0);


    //initial date
    SetRTCDateInfo(22,
                   9,
                   2026);


    //initial day
    SetRTCDay(1);


    //initial schedule
    on_hour = 9;
    on_min = 1;

    off_hour = 9;
    off_min = 2;


    Schedule_SetTime(on_hour,
                     on_min,
                     off_hour,
                     off_min);


    while(1)
    {
        //display RTC
        DisplayRTC();


        //delay for LCD refresh
        delay_ms(200);


        //get current time
        GetRTCTimeInfo(&hour,
                       &min,
                       &sec);


        //control LED
        device_status = Schedule_IsActive(hour,
                                          min,
                                          sec);


        if(device_status)
        {
            LED_Control(1);
        }
        else
        {
            LED_Control(0);
        }


        //check menu request
        if(menu_request == 1)
        {
            menu_request = 0;


            //display main menu
            MainMenu();


            WRITE_LCD_CMD(0x01);
            delay_ms(2);
        }
    }
}
