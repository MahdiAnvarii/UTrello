#ifndef USER_H
#define USER_H

#include "utils.h"
#include "event.h"
#include "date.h"

class User{
public:
    User(string username_, string password_);
    string getUsername() const;
    string getPassword() const;
    bool logged() const;
    void login();
    void logout();
    vector<shared_ptr<Event>> getEvents() const;
    vector<shared_ptr<PeriodicEvent>> getPeriodicEvents() const;
    void addNewEvent(shared_ptr<Date> eventDate, int start_time, int duration, string title, const string& description);
    void addNewPeriodicEvent(vector<shared_ptr<Date>> periodicEventDates, int start_time, int duration, 
                                PeriodicType periodicType, string title, const string& description);
    void addNewTask(shared_ptr<Date> taskDate, int time, string title, const string& description);
    void deleteTask(int taskID);
    void editTask(int taskID, string dateLine, int time, string title, const string& description);
    void reportJobs(shared_ptr<Date> fromDate, shared_ptr<Date> toDate, string type);
private:
    string username;
    string password;
    bool isLoggedIn = false;
    vector<shared_ptr<Event>> events;
    vector<shared_ptr<PeriodicEvent>> periodicEvents;
    vector<shared_ptr<Task>> tasks;
    int eventCounter = 1;
    int periodicEventCounter = 1;
    int taskCounter = 1;
};

#endif //USER_H