#ifndef DATE_H
#define DATE_H

#include "utils.h"

class Date : public enable_shared_from_this<Date> {
public:
    Date(int day_, int month_, int year_, bool isHoliday_);
    Date(string dateLine);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    DayOfWeek getDayOfWeek() const;
    bool isOnAnotherDate(Date theOtherDate);
    bool isAfterDate(Date theOtherDate);
    shared_ptr<Date> createTommorow();
    shared_ptr<Date> createTheNextMonth();
    shared_ptr<Date> createPeriodDay(int day_);
    shared_ptr<Date> createTheNextDayOfWeek(vector<DayOfWeek> daysOfWeek);
    string createDateLine();
private:
    void calculateDayOfWeek();
    int day;
    int month;
    int year;
    int isHoliday;
    DayOfWeek dayOfWeek;
};

const Date ORIGION_DATE = Date(1, 1, 1404, true);

#endif //DATE_H