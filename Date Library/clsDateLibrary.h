#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>

#include "clsString.h"


using namespace std;


class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;


public:


    clsDate() {
         clsDate Date = GetSystemDate();
        _Day = Date.Day;
        _Month = Date.Month;
        _Year = Date.Year;
    }


    clsDate(string Date) {
       vector<string> newDate = clsString::Split(Date , "/");
        _Day = stoi(newDate[0]);
        _Month = stoi(newDate[1]);
        _Year = stoi(newDate[2]);
    }

    clsDate(short Day ,short Month ,short Year) {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short Days, short Year) {
        clsDate Date1 = GetDateFromDayOrderInYear(Days, Year);

        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }
  

     static clsDate GetSystemDate() {
     
        time_t t = time(0);
        tm* now = localtime(&t);
        short Day, Month, Year;
       Year = now->tm_year + 1900;
       Month = now->tm_mon + 1;
       Day = now->tm_mday;
        return clsDate(Day,Month,Year);
    }

    static bool IsLeapYear(short year) {
 

        return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
    }

    bool IsLeapYear() {
        return  IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return  IsLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return  NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return  NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return  NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return  NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return  NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return  NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return  NumberOfSecondsInAYear();
    }

     static short NumbersOfDaysInMonth(short year, short month) {
        short days = 0;
        (month == 2) ? (IsLeapYear(year) ? days = 29 : days = 28) :
            ((month == 4 || month == 6 || month == 9 || month == 11) ? days = 30 : days = 31);
        return days;





    }

     short NumbersOfDaysInMonth() {
      return   NumbersOfDaysInMonth(_Year, _Month);
     }

     static short NumberOfHoursInAMonth(short Month, short Year)
     {
         return  NumbersOfDaysInMonth(Month, Year) * 24;
     }

     short NumberOfHoursInAMonth()
     {
         return  NumbersOfDaysInMonth(_Month, _Year) * 24;
     }

     static int NumberOfMinutesInAMonth(short Month, short Year)
     {
         return  NumberOfHoursInAMonth(Month, Year) * 60;
     }

     int NumberOfMinutesInAMonth()
     {
         return  NumberOfHoursInAMonth(_Month, _Year) * 60;
     }

     static int NumberOfSecondsInAMonth(short Month, short Year)
     {
         return  NumberOfMinutesInAMonth(Month, Year) * 60;
     }

     int NumberOfSecondsInAMonth()
     {
         return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
     }


    clsDate GetDateFromDayOrderInYear(short Days, short Year) {
        clsDate Date1;
        // short DaysInMonth = NumbersOfDaysInMonth(Year,)
        short totalDays = Days;
        short month;
        for (int i = 1; i <= 12; i++) {
            short DaysInMonth = NumbersOfDaysInMonth(Year, i);
            if (totalDays > DaysInMonth) {
                totalDays-= DaysInMonth;
                month = i;

            }
            else {
                Date1.Day = totalDays;
                Date1.Month = i;
                Date1.Year = Year;
                return  Date1;
            }
        }
    }


    static short DayOfWeekOrder(short year, short month, short day) {
        short a = (14 - month) / 12;
        short y = year - a;
        short m = month + 12 * a - 2;
        // Gregorian calendar:
        //0:sun, 1:Mon, 2:Tue...etc
        short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
        return d;


    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayShortName(short DayOfWeekOrder){
        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
        return arrDayNames[DayOfWeekOrder -1];
    }

    static string DayShortName(short Day, short Month, short Year)
    {

        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];

    }

    string DayShortName()
    {

        string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];

    }


    static string MonthShortName(short MonthNumber)
    {
        string arrMonthNames[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul" ,"Aug" ,"Sep" ,"Oct" ,"Nov" ,"Dec" };
        return arrMonthNames[MonthNumber-1];

    }

    static void printMonthCalendar(short year, short month) {
        short count = 1;
        cout << "\n______________________" << MonthShortName(month - 1) << "______________________\n";
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
        do {
            for (int i = 0; i < 7; i++) {
                if (i == DayOfWeekOrder(year, month, count) && count <= NumbersOfDaysInMonth(year, month)) {

                    printf("%5d", count);
                    count = count + 1;

                }
                else {
                    printf("     ");
                }

            }
            cout << "\n";
        } while (count < NumbersOfDaysInMonth(year, month));

        cout << "________________________________________";
    }

    void printMonthCalendar() {
       printMonthCalendar(_Year, _Month);
   }

   static void printYearCalendar(short year) {

       cout << "\n________________________________________\n";
       cout << "\t\t Calendar - " << year;

       for (int i = 1; i <= 12; i++) {
           printMonthCalendar(year, i);
       }

   }

   void printYearCalendar() {
       printYearCalendar(_Year);
   }

   static short DaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
   {


       short TotalDays = 0;

       for (int i = 1; i <= Month - 1; i++)
       {
           TotalDays += NumbersOfDaysInMonth(i, Year);
       }

       TotalDays += Day;

       return TotalDays;
   }

   short DaysFromTheBeginningOfTheYear()
   {


       short TotalDays = 0;

       for (int i = 1; i <= _Month - 1; i++)
       {
           TotalDays += NumbersOfDaysInMonth(i, _Year);
       }

       TotalDays += _Day;

       return TotalDays;
   }

   void AddDays(short Days)
   {


       short RemainingDays = Days + DaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
       short MonthDays = 0;

       _Month = 1;

       while (true)
       {
           MonthDays = NumbersOfDaysInMonth(_Month, _Year);

           if (RemainingDays > MonthDays)
           {
               RemainingDays -= MonthDays;
               _Month++;

               if (_Month > 12)
               {
                   _Month = 1;
                   _Year++;

               }
           }
           else
           {
               _Day = RemainingDays;
               break;
           }

       }


   }



   static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
   {
       return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
   }

   bool IsDateBeforeDate2(clsDate Date2)
   {
       //note: *this sends the current object :-) 
       return  IsDate1BeforeDate2(*this, Date2);

   }

   static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
   {
       return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
   }

   bool IsDateEqualDate2(clsDate Date2)
   {
       return  IsDate1EqualDate2(*this, Date2);
   }

   static bool IsLastDayInMonth(clsDate Date)
   {

       return (Date.Day == NumbersOfDaysInMonth(Date.Month, Date.Year));

   }

   bool IsLastDayInMonth()
   {

       return IsLastDayInMonth(*this);

   }

   static bool IsLastMonthInYear(short Month)
   {
       return (Month == 12);
   }


    static bool IsValidDate(clsDate Date) {
      return  (Date.Month > 0 && Date.Month <=12) ?
           (Date.Day <= NumbersOfDaysInMonth(Date.Year, Date.Month)) ?
           true : false : false;

       
       
       
   }


    bool IsValidDate() {
       return IsValidDate(*this);
    }




  static short GetDifferenceInDays(clsDate Date1,clsDate Date2, bool IncludeEndDay = false) {

       short Days = 0;
       bool neg = true;
       // if (isDate1BeforeDate2(Date1, Date2))? 
       if (IsDate1BeforeDate2(Date1, Date2)) {
           while (IsDate1BeforeDate2(Date1, Date2)) {
               Date1 = AddOneDay(Date1);
               Days++;
           }
           return IncludeEndDay ? Days = ++Days : Days;;
       }
       else {
           while (IsDate1BeforeDate2(Date2, Date1)) {
               Date2 = AddOneDay(Date2);
               Days++;
           }
           return IncludeEndDay ? Days = -++Days : -Days;;
       }





   }

  short GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
      return GetDifferenceInDays(*this,Date2,IncludeEndDay);
  }


    static clsDate AddOneDay(clsDate Date) {
       short Day = NumbersOfDaysInMonth(Date.Year, Date.Month);
       if (IsLastDayInMonth(Date)) {
           if (IsLastMonthInYear(Date.Month))
           {
               Date.Day = 1;
               Date.Month = 1;
               Date.Year++;
           }
           else {
               Date.Day = 1;
               Date.Month++;
           }

       }
       else {
           Date.Day++;
       }

       return Date;

   }

    void AddOneDay()

    {
        *this = AddOneDay(*this);
    }

    static void  SwapDates(clsDate& Date1, clsDate& Date2)
    {

        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;

    }


   static short CalculateMyAgeInDays(clsDate DateOfBirth) {
       clsDate  Date2;
       Date2 = GetSystemDate();

        return GetDifferenceInDays(DateOfBirth,Date2);
   }

   static clsDate IncreaseDateByOneWeek(clsDate& Date)
   {

	   for (int i = 1; i <= 7; i++)
	   {
		   Date = AddOneDay(Date);
	   }

	   return Date;
   }

   void IncreaseDateByOneWeek()
   {
	   IncreaseDateByOneWeek(*this);
   }

   clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
   {

	   for (short i = 1; i <= Weeks; i++)
	   {
		   Date = IncreaseDateByOneWeek(Date);
	   }
	   return Date;
   }

   void IncreaseDateByXWeeks(short Weeks)
   {
	   IncreaseDateByXWeeks(Weeks, *this);
   }

   clsDate IncreaseDateByOneMonth(clsDate& Date)
   {

	   if (Date.Month == 12)
	   {
		   Date.Month = 1;
		   Date.Year++;
	   }
	   else
	   {
		   Date.Month++;
	   }

	   //last check day in date should not exceed max days in the current month
	   // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
	   // be 28/2/2022
	   short NumberOfDaysInCurrentMonth = NumbersOfDaysInMonth(Date.Month, Date.Year);
	   if (Date.Day > NumberOfDaysInCurrentMonth)
	   {
		   Date.Day = NumberOfDaysInCurrentMonth;
	   }

	   return Date;
   }

   void IncreaseDateByOneMonth()
   {

	   IncreaseDateByOneMonth(*this);

   }

   clsDate IncreaseDateByXDays(short Days, clsDate& Date)
   {

	   for (short i = 1; i <= Days; i++)
	   {
		   Date = AddOneDay(Date);
	   }
	   return Date;
   }

   void IncreaseDateByXDays(short Days)
   {

	   IncreaseDateByXDays(Days, *this);
   }

   clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
   {

	   for (short i = 1; i <= Months; i++)
	   {
		   Date = IncreaseDateByOneMonth(Date);
	   }
	   return Date;
   }

   void IncreaseDateByXMonths(short Months)
   {
	   IncreaseDateByXMonths(Months, *this);
   }

   static clsDate IncreaseDateByOneYear(clsDate& Date)
   {
	   Date.Year++;
	   return Date;
   }

   void IncreaseDateByOneYear()
   {
	   IncreaseDateByOneYear(*this);
   }

   clsDate IncreaseDateByXYears(short Years, clsDate& Date)
   {
	   Date.Year += Years;
	   return Date;

   }

   void IncreaseDateByXYears(short Years)
   {
	   IncreaseDateByXYears(Years);
   }

   clsDate IncreaseDateByOneDecade(clsDate& Date)
   {
	   //Period of 10 years
	   Date.Year += 10;
	   return Date;
   }

   void IncreaseDateByOneDecade()
   {
	   IncreaseDateByOneDecade(*this);
   }

   clsDate IncreaseDateByXDecades(short Decade, clsDate& Date)
   {
	   Date.Year += Decade * 10;
	   return Date;
   }

   void IncreaseDateByXDecades(short Decade)
   {
	   IncreaseDateByXDecades(Decade, *this);
   }

   clsDate IncreaseDateByOneCentury(clsDate& Date)
   {
	   //Period of 100 years
	   Date.Year += 100;
	   return Date;
   }

   void IncreaseDateByOneCentury()
   {
	   IncreaseDateByOneCentury(*this);
   }

   clsDate IncreaseDateByOneMillennium(clsDate& Date)
   {
	   //Period of 1000 years
	   Date.Year += 1000;
	   return Date;
   }

   clsDate IncreaseDateByOneMillennium()
   {
	   IncreaseDateByOneMillennium(*this);
   }

   static clsDate DecreaseDateByOneDay(clsDate Date)
   {
	   if (Date.Day == 1)
	   {
		   if (Date.Month == 1)
		   {
			   Date.Month = 12;
			   Date.Day = 31;
			   Date.Year--;
		   }
		   else
		   {

			   Date.Month--;
			   Date.Day = NumbersOfDaysInMonth(Date.Month, Date.Year);
		   }
	   }
	   else
	   {
		   Date.Day--;
	   }

	   return Date;
   }

   void DecreaseDateByOneDay()
   {
	   DecreaseDateByOneDay(*this);
   }

   static clsDate DecreaseDateByOneWeek(clsDate& Date)
   {

	   for (int i = 1; i <= 7; i++)
	   {
		   Date = DecreaseDateByOneDay(Date);
	   }

	   return Date;
   }

   void DecreaseDateByOneWeek()
   {
	   DecreaseDateByOneWeek(*this);
   }

   static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
   {

	   for (short i = 1; i <= Weeks; i++)
	   {
		   Date = DecreaseDateByOneWeek(Date);
	   }
	   return Date;
   }

   void DecreaseDateByXWeeks(short Weeks)
   {
	   DecreaseDateByXWeeks(Weeks, *this);
   }

   static clsDate DecreaseDateByOneMonth(clsDate& Date)
   {

	   if (Date.Month == 1)
	   {
		   Date.Month = 12;
		   Date.Year--;
	   }
	   else
		   Date.Month--;


	   //last check day in date should not exceed max days in the current month
	  // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
	  // be 28/2/2022
	   short NumberOfDaysInCurrentMonth = NumbersOfDaysInMonth(Date.Month, Date.Year);
	   if (Date.Day > NumberOfDaysInCurrentMonth)
	   {
		   Date.Day = NumberOfDaysInCurrentMonth;
	   }


	   return Date;
   }

   void DecreaseDateByOneMonth()
   {
	   DecreaseDateByOneMonth(*this);
   }

   static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
   {

	   for (short i = 1; i <= Days; i++)
	   {
		   Date = DecreaseDateByOneDay(Date);
	   }
	   return Date;
   }

   void DecreaseDateByXDays(short Days)
   {
	   DecreaseDateByXDays(Days, *this);
   }

   static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
   {

	   for (short i = 1; i <= Months; i++)
	   {
		   Date = DecreaseDateByOneMonth(Date);
	   }
	   return Date;
   }

   void DecreaseDateByXMonths(short Months)
   {
	   DecreaseDateByXMonths(Months, *this);
   }

   static clsDate DecreaseDateByOneYear(clsDate& Date)
   {

	   Date.Year--;
	   return Date;
   }

   void DecreaseDateByOneYear()
   {
	   DecreaseDateByOneYear(*this);
   }

   static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
   {

	   Date.Year -= Years;
	   return Date;
   }

   void DecreaseDateByXYears(short Years)
   {
	   DecreaseDateByXYears(Years, *this);
   }

   static clsDate DecreaseDateByOneDecade(clsDate& Date)
   {
	   //Period of 10 years
	   Date.Year -= 10;
	   return Date;
   }

   void DecreaseDateByOneDecade()
   {
	   DecreaseDateByOneDecade(*this);
   }

   static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
   {

	   Date.Year -= Decades * 10;
	   return Date;
   }

   void DecreaseDateByXDecades(short Decades)
   {
	   DecreaseDateByXDecades(Decades, *this);
   }

   static clsDate DecreaseDateByOneCentury(clsDate& Date)
   {
	   //Period of 100 years
	   Date.Year -= 100;
	   return Date;
   }

   void DecreaseDateByOneCentury()
   {
	   DecreaseDateByOneCentury(*this);
   }

   static clsDate DecreaseDateByOneMillennium(clsDate& Date)
   {
	   //Period of 1000 years
	   Date.Year -= 1000;
	   return Date;
   }

   void DecreaseDateByOneMillennium()
   {
	   DecreaseDateByOneMillennium(*this);
   }


   static short IsEndOfWeek(clsDate Date)
   {
	   return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
   }

   short IsEndOfWeek()
   {
	   return IsEndOfWeek(*this);
   }

   static bool IsWeekEnd(clsDate Date)
   {
	   //Weekends are Fri and Sat
	   short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	   return  (DayIndex == 5 || DayIndex == 6);
   }

   bool IsWeekEnd()
   {
	   return  IsWeekEnd(*this);
   }

   static bool IsBusinessDay(clsDate Date)
   {
	   //Weekends are Sun,Mon,Tue,Wed and Thur

	  /*
	   short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	   return  (DayIndex >= 5 && DayIndex <= 4);
	  */

	  //shorter method is to invert the IsWeekEnd: this will save updating code.
	   return !IsWeekEnd(Date);

   }

   bool IsBusinessDay()
   {
	   return  IsBusinessDay(*this);
   }

   static short DaysUntilTheEndOfWeek(clsDate Date)
   {
	   return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
   }

   short DaysUntilTheEndOfWeek()
   {
	   return  DaysUntilTheEndOfWeek(*this);
   }

   static short DaysUntilTheEndOfMonth(clsDate Date1)
   {

	   clsDate EndOfMontDate;
	   EndOfMontDate.Day = NumbersOfDaysInMonth(Date1.Month, Date1.Year);
	   EndOfMontDate.Month = Date1.Month;
	   EndOfMontDate.Year = Date1.Year;

	   return GetDifferenceInDays(Date1, EndOfMontDate, true);

   }

   short DaysUntilTheEndOfMonth()
   {
	   return DaysUntilTheEndOfMonth(*this);
   }

   static short DaysUntilTheEndOfYear(clsDate Date1)
   {

	   clsDate EndOfYearDate;
	   EndOfYearDate.Day = 31;
	   EndOfYearDate.Month = 12;
	   EndOfYearDate.Year = Date1.Year;

	   return GetDifferenceInDays(Date1, EndOfYearDate, true);

   }

   short DaysUntilTheEndOfYear()
   {
	   return  DaysUntilTheEndOfYear(*this);
   }

   //i added this method to calculate business days between 2 days
   static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
   {

	   short Days = 0;
	   while (IsDate1BeforeDate2(DateFrom, DateTo))
	   {
		   if (IsBusinessDay(DateFrom))
			   Days++;

		   DateFrom = AddOneDay(DateFrom);
	   }

	   return Days;

   }

   static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
   {
	   /*short Days = 0;
	   while (IsDate1BeforeDate2(DateFrom, DateTo))
	   {
		   if (IsBusinessDay(DateFrom))
			   Days++;

		   DateFrom = AddOneDay(DateFrom);
	   }*/

	   return CalculateBusinessDays(DateFrom, DateTo);

   }
   //above method is eough , no need to have method for the object

   static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
   {

	   short WeekEndCounter = 0;

	   for (short i = 1; i <= VacationDays; i++)
	   {

		   if (IsWeekEnd(DateFrom))
			   WeekEndCounter++;

		   DateFrom = AddOneDay(DateFrom);
	   }
	   //to add weekends 
	   for (short i = 1; i <= WeekEndCounter; i++)
		   DateFrom = AddOneDay(DateFrom);

	   return DateFrom;
   }

   static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
   {
	   return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));

   }

   bool IsDateAfterDate2(clsDate Date2)
   {
	   return IsDate1AfterDate2(*this, Date2);
   }

   enum enDateCompare { Before = -1, Equal = 0, After = 1 };

   static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
   {
	   if (IsDate1BeforeDate2(Date1, Date2))
		   return enDateCompare::Before;

	   if (IsDate1EqualDate2(Date1, Date2))
		   return enDateCompare::Equal;

	   /* if (IsDate1AfterDate2(Date1,Date2))
			return enDateCompare::After;*/

			//this is faster
	   return enDateCompare::After;

   }

   enDateCompare CompareDates(clsDate Date2)
   {
	   return CompareDates(*this, Date2);
   }
    void SetDay(short Day) {
        _Day = Day;
    }

    short GetDay() {
        return _Day;
    }


    void SetMonth(short Month) {
        _Month = Month;
    }

    short GetMonth() {
        return _Month;
    }

    void SetYear(short Year) {
        _Year = Year;
    }

    short GetYear() {
        return _Year;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    static string DateToString(clsDate Date) {
        return to_string(Date.Day) + "/" + to_string(Date.Month) +"/" + to_string(Date.Year);
    }

    string DateToString() {
        return DateToString(*this);
    }

    void Print() {
        cout<<DateToString()<<endl;
    }

};
