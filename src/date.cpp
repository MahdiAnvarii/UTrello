#include "date.h"

Date::Date(int day_, int month_, int year_, bool isHoliday_){
    day = day_;
    month = month_;
    year = year_;
    isHoliday = isHoliday_;
    calculateDayOfWeek();
}

Date::Date(string dateLine){
    istringstream iss(dateLine);
    int year_, month_, day_;
    char sep;
    iss >> year_ >> sep >> month_ >> sep >> day_;
    day = day_;
    month = month_;
    year = year_;
    isHoliday = false;
    calculateDayOfWeek();
}

string Date::createDateLine(){
    ostringstream oss;
    oss << year << '/' << setw(2) << setfill('0') << month << '/' << setw(2) << setfill('0') << day;
    string dateStr = oss.str();
    return dateStr;
}

void Date::calculateDayOfWeek(){
    int daysFromOrigion = ((year - ORIGION_DATE.getYear()) * MONTHS_PER_YEAR + (month - ORIGION_DATE.getMonth())) * DAYS_PER_MONTH + (day - ORIGION_DATE.getDay());
    dayOfWeek = static_cast<DayOfWeek>(daysFromOrigion % DAYS_PER_WEEK);
}

bool Date::isOnAnotherDate(Date theOtherDate){
    return day == theOtherDate.day && month == theOtherDate.month && year == theOtherDate.year;
}

bool Date::isAfterDate(Date theOtherDate){
    return year > theOtherDate.year || 
            year == theOtherDate.year && month > theOtherDate.month ||
            year == theOtherDate.year && month == theOtherDate.month && day > theOtherDate.day;
}

shared_ptr<Date> Date::createTommorow(){
    int year_ = year;
    int month_ = month;
    int day_ = day;

    if (day < DAYS_PER_MONTH) return make_shared<Date>(day_+1, month_, year_, false);
    else if (month_ < MONTHS_PER_YEAR) return make_shared<Date>(1, month_+1, year_, false);
    else return make_shared<Date>(1, 1, year_+1, false);
}

shared_ptr<Date> Date::createTheNextMonth(){
    int year_ = year;
    int month_ = month;
    int day_ = day;
    if (month_ < MONTHS_PER_YEAR) return make_shared<Date>(day_, month_+1, year_, false);
    else return make_shared<Date>(day_, 1, year_+1, false);
}

shared_ptr<Date> Date::createPeriodDay(int day_){
    int year_ = year;
    int month_ = month;
    return make_shared<Date>(day_, month_, year_, false);
}

shared_ptr<Date> Date::createTheNextDayOfWeek(vector<DayOfWeek> daysOfWeek){
    shared_ptr<Date> potentialDate = shared_from_this();
    while (true){
        potentialDate = potentialDate->createTommorow();
        if (find(daysOfWeek.begin(), daysOfWeek.end(), potentialDate->getDayOfWeek()) != daysOfWeek.end()) break;
    }
    return potentialDate;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }
DayOfWeek Date::getDayOfWeek() const { return dayOfWeek; }