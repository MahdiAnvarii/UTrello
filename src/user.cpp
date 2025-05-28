#include "user.h"
#include "errors.h"

User::User(string username_, string password_){
    username = username_;
    password = password_;
}

void User::login() { isLoggedIn = true; }
void User::logout() { isLoggedIn = false; }

void User::addNewEvent(shared_ptr<Date> eventDate, int start_time, int duration, string title, const string& description){
    shared_ptr<Event> newEvent = make_shared<Event>(eventDate, eventCounter, start_time, duration, title, description);
    eventCounter+=1;
    events.push_back(newEvent);
}

void User::addNewPeriodicEvent(vector<shared_ptr<Date>> periodicEventDates, int start_time, int duration, 
                                PeriodicType periodicType, string title, const string& description){

    shared_ptr<PeriodicEvent> newPeriodicEvent = make_shared<PeriodicEvent>(periodicEventDates, periodicEventCounter, 
                                                                            start_time, duration, periodicType, title, description);
    periodicEventCounter+=1;
    periodicEvents.push_back(newPeriodicEvent);
}

void User::addNewTask(shared_ptr<Date> taskDate, int time, string title, const string& description){
    shared_ptr<Task> newTask = make_shared<Task>(taskDate, taskCounter, time, title, description);
    taskCounter+=1;
    tasks.push_back(newTask);
}

void User::deleteTask(int taskID){
    auto deletedIt = find_if(tasks.begin(), tasks.end(), [taskID](const shared_ptr<Task>& task) {
            return task->getTaskID() == taskID;
        });

    if (deletedIt == tasks.end()) throw NotFound();
    else tasks.erase(deletedIt);
}

void User::editTask(int taskID, string dateLine, int time, string title, const string& description){
    auto editedIt = find_if(tasks.begin(), tasks.end(), [taskID](const shared_ptr<Task>& task) {
        return task->getTaskID() == taskID;
        });

    if (editedIt == tasks.end()) throw NotFound();
    else (*editedIt)->editTask(dateLine, time, title, description);
}

void User::reportJobs(shared_ptr<Date> fromDate, shared_ptr<Date> toDate, string type){
    bool isReportEmpty = true;
    sortEvents(events);
    sortPeriodicEvents(periodicEvents);
    sortTasks(tasks);

    if (type == EMPTY_TITLE){
        while (true){
            for (auto periodicEvent : periodicEvents){
                for (auto periodicEventDate : periodicEvent->getPeriodicEventDates()){
                    if (fromDate->isOnAnotherDate(*periodicEventDate)) {
                        periodicEvent->reportPeriodicEvent(periodicEventDate);
                        isReportEmpty = false;
                    }
                }
            }
            for (auto event : events){
                if (fromDate->isOnAnotherDate(*(event->getEventDate()))) {
                    event->reportEvent();
                    isReportEmpty = false;
                }
            }
            for (auto task : tasks){
                if (fromDate->isOnAnotherDate(*(task->getTaskDate()))) {
                    task->reportTask();
                    isReportEmpty = false;
                }
            }
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == EVENT){
        while (true){
            for (auto event : events){
                if (fromDate->isOnAnotherDate(*(event->getEventDate()))) {
                    event->reportEvent();
                    isReportEmpty = false;
                }
            }
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == PERIODIC_EVENT){
        while (true){
            for (auto periodicEvent : periodicEvents){
                for (auto periodicEventDate : periodicEvent->getPeriodicEventDates()){
                    if (fromDate->isOnAnotherDate(*periodicEventDate)) {
                        periodicEvent->reportPeriodicEvent(periodicEventDate);
                        isReportEmpty = false;
                    }
                }
            }
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == TASK){
        while (true){
            for (auto task : tasks){
                if (fromDate->isOnAnotherDate(*(task->getTaskDate()))) {
                    task->reportTask();
                    isReportEmpty = false;
                }
            }
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    }

    if (isReportEmpty) throw Empty();
}


string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
bool User::logged() const { return isLoggedIn; }
vector<shared_ptr<Event>> User::getEvents() const { return events; }
vector<shared_ptr<PeriodicEvent>> User::getPeriodicEvents() const { return periodicEvents; }