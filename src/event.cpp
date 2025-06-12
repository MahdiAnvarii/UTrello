#include "event.h"

Event::Event(shared_ptr<Date> eventDate_, int eventCounter_, int start_time_, int duration_, string title_, string description_):
                    eventDate(eventDate_) {
    eventID = eventCounter_;
    start_time = start_time_;
    duration = duration_; 
    title = title_;
    description = description_;
}

shared_ptr<Date> Event::getEventDate() const { return eventDate; }
int Event::getEventStartTime() const { return start_time; }
int Event::getEventDuration() const { return duration; }
int Event::getEventID() const { return eventID; }

void Event::reportEvent(){
    cout << "event \"" << title << "\" on " << eventDate->createDateLine() << " from " << start_time 
    << " for " << duration << " hours:";
    if (description != EMPTY_DESCRIPTION) cout << " \""<< description << "\"" << endl;
    else cout << endl;
}

void sortEvents(vector<shared_ptr<Event>>& events){
    sort(events.begin(), events.end(), [](const shared_ptr<Event> a, const shared_ptr<Event> b) {
        if (a->getEventDate()->getYear() != b->getEventDate()->getYear()) {
            return a->getEventDate()->getYear() < b->getEventDate()->getYear();
        }
        if (a->getEventDate()->getMonth() != b->getEventDate()->getMonth()) {
            return a->getEventDate()->getMonth() < b->getEventDate()->getMonth();
        }
        if (a->getEventDate()->getDay() != b->getEventDate()->getDay()) {
            return a->getEventDate()->getDay() < b->getEventDate()->getDay();
        }
        if (a->getEventStartTime() != b->getEventStartTime()) {
            return a->getEventStartTime() < b->getEventStartTime();
        }
        return a->getEventID() < b->getEventID();
    });
}


PeriodicEvent::PeriodicEvent(vector<shared_ptr<Date>> periodicEventDates_, int periodicEventCounter_, int start_time_, int duration_, 
                                PeriodicType periodicType_, string title_, string description_) :
                                periodicEventDates(periodicEventDates_), periodicType(periodicType_) {
    periodicEventID = periodicEventCounter_;
    start_time = start_time_; 
    duration = duration_; 
    title = title_;
    description = description_;
}

vector<shared_ptr<Date>> PeriodicEvent::getPeriodicEventDates() const { return periodicEventDates; }
int PeriodicEvent::getPeriodicEventStartTime() const { return start_time; }
int PeriodicEvent::getPeriodicEventDuration() const { return duration; }
int PeriodicEvent::getPeriodicEventID() const { return periodicEventID; }

void PeriodicEvent::reportPeriodicEvent(shared_ptr<Date> periodicEventDate){
    cout << "periodic_event \"" << title << "\" on " << periodicEventDate->createDateLine() << " from " << start_time 
    << " for " << duration << " hours " << periodicTypeToString(periodicType) << ":";
    if (description != EMPTY_DESCRIPTION) cout << " \""<< description << "\"" << endl;
    else cout << endl;
}

void sortPeriodicEvents(vector<shared_ptr<PeriodicEvent>>& periodicEvents){
    sort(periodicEvents.begin(), periodicEvents.end(), [](const shared_ptr<PeriodicEvent> a, const shared_ptr<PeriodicEvent> b) {
        if (a->getPeriodicEventStartTime() != b->getPeriodicEventStartTime()) {
            return a->getPeriodicEventStartTime() < b->getPeriodicEventStartTime();
        }
        return a->getPeriodicEventID() < b->getPeriodicEventID();
    });
}


Task::Task(shared_ptr<Date> taskDate_, int taskCounter_, int time_, string title_, string description_):
                    taskDate(taskDate_) {
    taskID = taskCounter_;
    time = time_;
    title = title_;
    description = description_;
}

void Task::editTask(string dateLine_, int time_, string title_, string description_){
    if (time_ != DEFUALT_INTEGER) time = time_;
    if (title_ != EMPTY_TITLE) title = title_;
    if (description_ != EMPTY_DESCRIPTION) description = description_;
    if (dateLine_ != EMPTY_DATELINE) {
        shared_ptr<Date> taskDate_ = make_shared<Date>(dateLine_);
        taskDate = taskDate_;
    }
}

shared_ptr<Date> Task::getTaskDate() const { return taskDate; }
int Task::getTaskID() const { return taskID; }

void Task::reportTask(){
    cout << "task \"" << title << "\" on " << taskDate->createDateLine() << " at " << time << ":";
        if (description != EMPTY_DESCRIPTION) cout << " \""<< description << "\"" << endl;
    else cout << endl;
}

void sortTasks(vector<shared_ptr<Task>>& tasks){
    sort(tasks.begin(), tasks.end(), [](const shared_ptr<Task> a, const shared_ptr<Task> b) {
        if (a->getTaskDate()->getYear() != b->getTaskDate()->getYear()) {
            return a->getTaskDate()->getYear() < b->getTaskDate()->getYear();
        }
        if (a->getTaskDate()->getMonth() != b->getTaskDate()->getMonth()) {
            return a->getTaskDate()->getMonth() < b->getTaskDate()->getMonth();
        }
        if (a->getTaskDate()->getDay() != b->getTaskDate()->getDay()) {
            return a->getTaskDate()->getDay() < b->getTaskDate()->getDay();
        }
         if (a->getTaskTime() != b->getTaskTime()) {
            return a->getTaskTime() < b->getTaskTime();
        }
        return a->getTaskID() < b->getTaskID();
    });
}


JoinEvent::JoinEvent(shared_ptr<Date> joinEventDate_, int joinEventCounter_, int start_time_, int duration_, string title_, 
                    string description_, string hostUserName_, shared_ptr<User> host_): joinEventDate(joinEventDate_), host(host_){
    joinEventID = joinEventCounter_;
    start_time = start_time_;
    duration = duration_; 
    title = title_;
    description = description_;
    hostUserName = hostUserName_;
}

void JoinEvent::printInvitation(){
    cout << joinEventID << ". \"" << title << "\" - " << joinEventDate->createDateLine() << " - " 
    << start_time << " - " << start_time+duration << endl;
}

void JoinEvent::reportJoinEvent(){
    cout << "join_event \"" << title << "\" on " << joinEventDate->createDateLine() << " from " << start_time 
    << " to " << start_time+duration << " hosted by " << "\"" << hostUserName << "\" :";
    if (description != EMPTY_DESCRIPTION) cout << " \""<< description << "\"" << endl;
    else cout << endl;
}

void sortJoinEvents(vector<shared_ptr<JoinEvent>>& joinEvents){
    sort(joinEvents.begin(), joinEvents.end(), [](const shared_ptr<JoinEvent> a, const shared_ptr<JoinEvent> b) {
        if (a->getJoinEventDate()->getYear() != b->getJoinEventDate()->getYear()) {
            return a->getJoinEventDate()->getYear() < b->getJoinEventDate()->getYear();
        }
        if (a->getJoinEventDate()->getMonth() != b->getJoinEventDate()->getMonth()) {
            return a->getJoinEventDate()->getMonth() < b->getJoinEventDate()->getMonth();
        }
        if (a->getJoinEventDate()->getDay() != b->getJoinEventDate()->getDay()) {
            return a->getJoinEventDate()->getDay() < b->getJoinEventDate()->getDay();
        }
        if (a->getJoinEventStartTime() != b->getJoinEventStartTime()) {
            return a->getJoinEventStartTime() < b->getJoinEventStartTime();
        }
        return a->getJoinEventID() < b->getJoinEventID();
    });
}

shared_ptr<Date> JoinEvent::getJoinEventDate() const { return joinEventDate; }
weak_ptr<User> JoinEvent::getHostWeakPointer() const { return host; }
int JoinEvent::getJoinEventStartTime() const { return start_time; }
int JoinEvent::getJoinEventDuration() const { return duration; }
int JoinEvent::getJoinEventID() const { return joinEventID; }
int JoinEvent::getAcceptedGuests() const { return acceptedGuests; }
void JoinEvent::increaseAcceptedGuests() { acceptedGuests+=1; }