#ifndef EVENT_H
#define EVENT_H

#include "utils.h"
#include "date.h"

class User; 

class Event{
public:
    Event(shared_ptr<Date> eventDate_, int eventCounter_, int start_time_, int duration_, string title_, string description_);
    shared_ptr<Date> getEventDate() const;
    int getEventStartTime() const;
    int getEventDuration() const;
    int getEventID() const;
    string reportEvent();
private:
    shared_ptr<Date> eventDate;
    int eventID;
    int start_time;
    int duration; 
    string title;
    string description;
};

class PeriodicEvent{
public:
    PeriodicEvent(vector<shared_ptr<Date>> periodicEventDates_, int periodicEventCounter_, int start_time_, int duration_, 
                    PeriodicType periodicType_, string title_, string description_);
    vector<shared_ptr<Date>> getPeriodicEventDates() const;
    int getPeriodicEventStartTime() const;
    int getPeriodicEventDuration() const;
    int getPeriodicEventID() const;
    string reportPeriodicEvent(shared_ptr<Date> periodicEventDate);
private:
    vector<shared_ptr<Date>> periodicEventDates;
    int periodicEventID;
    int start_time; 
    int duration;
    PeriodicType periodicType; 
    string title;
    string description;
};

class Task{
public:
    Task(shared_ptr<Date> taskDate_, int taskCounter_, int time_, string title_, string description_);
    void editTask(string dateLine_, int time_, string title_, string description_);
    shared_ptr<Date> getTaskDate() const;
    int getTaskID() const;
    int getTaskTime() const;
    string reportTask();
private:
    shared_ptr<Date> taskDate;
    int taskID;
    int time;
    string title;
    string description;
};

class JoinEvent{
public:
    JoinEvent(shared_ptr<Date> JoinEventDate_, int JoinEventCounter_, int start_time_, int duration_, string title_, 
                string description_, string hostUserName_, shared_ptr<User> host_);
    shared_ptr<Date> getJoinEventDate() const;
    weak_ptr<User> getHostWeakPointer() const;
    int getJoinEventStartTime() const;
    int getJoinEventDuration() const;
    int getJoinEventID() const;
    string printInvitation();
    string reportJoinEvent();
    int getAcceptedGuests() const;
    void increaseAcceptedGuests();
private:
    weak_ptr<User> host;
    shared_ptr<Date> joinEventDate;
    int joinEventID;
    int start_time; 
    int duration;
    string title;
    string description;
    string hostUserName;
    int acceptedGuests = 0;
};

void sortEvents(vector<shared_ptr<Event>>& events);
void sortPeriodicEvents(vector<shared_ptr<PeriodicEvent>>& periodicEvents);
void sortTasks(vector<shared_ptr<Task>>& tasks);
void sortJoinEvents(vector<shared_ptr<JoinEvent>>& joinEvents);

#endif //EVENT_H