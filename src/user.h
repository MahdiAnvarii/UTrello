#ifndef USER_H
#define USER_H

#include "utils.h"
#include "event.h"
#include "date.h"

class User : public enable_shared_from_this<User> {
public:
    User(string username_, string password_);
    string getUsername() const;
    string getPassword() const;
    bool logged() const;
    void login();
    void logout();
    vector<shared_ptr<Event>> getEvents() const;
    vector<shared_ptr<PeriodicEvent>> getPeriodicEvents() const;
    void checkConflictsWithOthers(shared_ptr<Date> eventDate, int start_time, int duration);
    void addNewEvent(shared_ptr<Date> eventDate, int start_time, int duration, string title, const string& description);
    void addNewPeriodicEvent(vector<shared_ptr<Date>> periodicEventDates, int start_time, int duration, 
                                PeriodicType periodicType, string title, const string& description);
    void addNewTask(shared_ptr<Date> taskDate, int time, string title, const string& description);
    void deleteTask(int taskID);
    void editTask(int taskID, string dateLine, int time, string title, const string& description);
    void reportTasksHelper(shared_ptr<Date>& fromDate, vector<string>& reportResultsVector, bool& isReportEmpty);
    void reportEventsHelper(shared_ptr<Date>& fromDate, vector<string>& reportResultsVector, bool& isReportEmpty);
    void reportPeriodicEventsHelper(shared_ptr<Date>& fromDate, vector<string>& reportResultsVector, bool& isReportEmpty);
    void reportJoinEventsHelper(shared_ptr<Date>& fromDate, vector<string>& reportResultsVector, bool& isReportEmpty);
    vector<string> reportJobs(shared_ptr<Date> fromDate, shared_ptr<Date> toDate, string type);
    void createNewJoinEvent(vector<shared_ptr<User>> guestUsers, shared_ptr<Date> joinEventDate, int joinEventCounter, 
                                int start_time, int duration, string title, const string& description);
    void sendJoinEventInvitation(shared_ptr<JoinEvent> newJoinEvent);
    vector<string> checkInvitationList();
    void confirmJoinEvent(int invitationID);
    void rejectJoinEvent(int invitationID);
    void addHostToTheEvent(shared_ptr<JoinEvent> newJoinEvent);
private:
    string username;
    string password;
    bool isLoggedIn = false;
    vector<shared_ptr<Event>> events;
    vector<shared_ptr<PeriodicEvent>> periodicEvents;
    vector<shared_ptr<Task>> tasks;
    vector<shared_ptr<JoinEvent>> joinEvents;
    vector<shared_ptr<JoinEvent>> invitedJoinEvents;
    int eventCounter = 1;
    int periodicEventCounter = 1;
    int taskCounter = 1;
};

#endif //USER_H