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
    shared_ptr<User> ifSomeOneLoggedIn();
    void addNewEvent(string dateLine, int start_time, int duration, string title, const string& description);
    void addNewPeriodicEvent(string startDateLine, string endDateLine, int start_time, int duration, string type, 
                                string title, const string& description, bool& holidayFoundFlag, int day=0, vector<string> week_days={});
    void addNewTask(string dateLine, int time, string title, const string& description);
    void deleteTask(int taskID);
    void editTask(int taskID, string dateLine, int time, string title, const string& description);
    vector<string> reportJobs(string fromDateLine, string toDateLine, string type);
    void addNewJoinEvent(string guestsLine, string dateLine, int start_time, int end_time, string title, const string& description);
    vector<string> checkInvitationList();
    void confirmJoinEvent(int invitationID);
    void rejectJoinEvent(int invitationID);    
private:
    void processHolidayFile(const string& holidayFileAddress_);
    vector<shared_ptr<Date>> holidays;
    vector<shared_ptr<User>> users;
    vector<string> usersUsernames;
    int joinEventCounter = 1;
};

#endif //UTRELLO_H