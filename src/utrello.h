#ifndef UTRELLO_H
#define UTRELLO_H

#include "utils.h"
#include "date.h"
#include "user.h"

class UTrello{
public:
    UTrello(const string& holidayFileAddress_);
    void addNewUser(const string& username, const string& password);
    void logToUser(const string& username, const string& password);
    void logoutFromUser();
    void addNewEvent(string dateLine, int start_time, int duration, string title, const string& description);
    void addNewPeriodicEvent(string startDateLine, string endDateLine, int start_time, int duration, string type, 
                                string title, const string& description, bool& holidayFoundFlag, int day=0, vector<string> week_days={});
    void addNewTask(string dateLine, int time, string title, const string& description);
    void deleteTask(int taskID);
    void editTask(int taskID, string dateLine, int time, string title, const string& description);
    void reportJobs(string fromDateLine, string toDateLine, string type);             
private:
    void processHolidayFile(const string& holidayFileAddress_);
    vector<shared_ptr<Date>> holidays;
    vector<shared_ptr<User>> users;
    vector<string> userUsernames;
};

#endif //UTRELLO_H