#include "user.h"
#include "errors.h"

User::User(string username_, string password_){
    username = username_;
    password = password_;
}

void User::login() { isLoggedIn = true; }
void User::logout() { isLoggedIn = false; }

void User::checkConflictsWithOthers(shared_ptr<Date> eventDate, int start_time, int duration){
    for (auto userEvent : events){
        if (eventDate->isOnAnotherDate(*(userEvent->getEventDate())) && 
            start_time+duration > userEvent->getEventStartTime() && 
            start_time < userEvent->getEventStartTime()+userEvent->getEventDuration()) throw Overlap();
    }
    for (auto userPeriodicEvent : periodicEvents){
        for (auto periodicEventDate : userPeriodicEvent->getPeriodicEventDates()){
            if (eventDate->isOnAnotherDate(*(periodicEventDate)) && 
                start_time+duration > userPeriodicEvent->getPeriodicEventStartTime() && 
                start_time < userPeriodicEvent->getPeriodicEventStartTime()+userPeriodicEvent->getPeriodicEventDuration()) throw Overlap();
        }
    }
    for (auto joinEvent : joinEvents){
        if (eventDate->isOnAnotherDate(*(joinEvent->getJoinEventDate())) && 
            start_time+duration > joinEvent->getJoinEventStartTime() && 
            start_time < joinEvent->getJoinEventStartTime()+joinEvent->getJoinEventDuration()) throw Overlap();
    }
}

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

void User::reportTasksHelper(shared_ptr<Date>& fromDate, shared_ptr<Date>& toDate, bool& isReportEmpty){
    for (auto task : tasks){
        if (fromDate->isOnAnotherDate(*(task->getTaskDate()))) {
            task->reportTask();
            isReportEmpty = false;
        }
    }
}

void User::reportEventsHelper(shared_ptr<Date>& fromDate, shared_ptr<Date>& toDate, bool& isReportEmpty){
    for (auto event : events){
        if (fromDate->isOnAnotherDate(*(event->getEventDate()))) {
            event->reportEvent();
            isReportEmpty = false;
        }
    }
}

void User::reportPeriodicEventsHelper(shared_ptr<Date>& fromDate, shared_ptr<Date>& toDate, bool& isReportEmpty){
    for (auto periodicEvent : periodicEvents){
        for (auto periodicEventDate : periodicEvent->getPeriodicEventDates()){
            if (fromDate->isOnAnotherDate(*periodicEventDate)) {
                periodicEvent->reportPeriodicEvent(periodicEventDate);
                isReportEmpty = false;
            }
        }
    }
}

void User::reportJoinEventsHelper(shared_ptr<Date>& fromDate, shared_ptr<Date>& toDate, bool& isReportEmpty){
    for (auto joinEvent : joinEvents){
        if (fromDate->isOnAnotherDate(*(joinEvent->getJoinEventDate()))) {
            joinEvent->reportJoinEvent();
            isReportEmpty = false;
        }
    }
}

void User::reportJobs(shared_ptr<Date> fromDate, shared_ptr<Date> toDate, string type){
    bool isReportEmpty = true;
    sortEvents(events);
    sortPeriodicEvents(periodicEvents);
    sortTasks(tasks);
    sortJoinEvents(joinEvents);

    if (type == EMPTY_TITLE){
        while (true){
            reportJoinEventsHelper(fromDate, toDate, isReportEmpty);
            reportPeriodicEventsHelper(fromDate, toDate, isReportEmpty);
            reportEventsHelper(fromDate, toDate, isReportEmpty);
            reportTasksHelper(fromDate, toDate, isReportEmpty);
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == EVENT){
        while (true){
            reportEventsHelper(fromDate, toDate, isReportEmpty);
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == PERIODIC_EVENT){
        while (true){
            reportPeriodicEventsHelper(fromDate, toDate, isReportEmpty);
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == TASK){
        while (true){
            reportTasksHelper(fromDate, toDate, isReportEmpty);
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    } else if (type == JOIN_EVENT){
        while (true){
            reportJoinEventsHelper(fromDate, toDate, isReportEmpty);
            if (fromDate->isOnAnotherDate(*toDate)) break;
            fromDate = fromDate->createTommorow();
        }
    }

    if (isReportEmpty) throw Empty();
}

void User::createNewJoinEvent(vector<shared_ptr<User>> guestUsers, shared_ptr<Date> joinEventDate, int joinEventCounter, 
                            int start_time, int duration, string title, const string& description){

    shared_ptr<JoinEvent> newJoinEvent = make_shared<JoinEvent>(joinEventDate, joinEventCounter, start_time, duration, title, 
                                                        description, username, shared_from_this());
    for (auto guestUser : guestUsers) guestUser->sendJoinEventInvitation(newJoinEvent);
}

void User::addHostToTheEvent(shared_ptr<JoinEvent> newJoinEvent){
    joinEvents.push_back(newJoinEvent);
}

void User::sendJoinEventInvitation(shared_ptr<JoinEvent> newJoinEvent){
    invitedJoinEvents.push_back(newJoinEvent);
}

void User::checkInvitationList(){
    if (invitedJoinEvents.empty()) throw Empty();
    for (auto invitedJoinEvent : invitedJoinEvents) invitedJoinEvent->printInvitation();
}

void User::confirmJoinEvent(int invitationID){
    auto invitedIt = find_if(invitedJoinEvents.begin(), invitedJoinEvents.end(), [invitationID](const shared_ptr<JoinEvent>& invitedJoinEvent){
            return invitedJoinEvent->getJoinEventID() == invitationID;
        });

    if (invitedIt == invitedJoinEvents.end()) throw NotFound();
    else {
        invitedJoinEvents.erase(invitedIt);
        checkConflictsWithOthers((*invitedIt)->getJoinEventDate(), (*invitedIt)->getJoinEventStartTime(), (*invitedIt)->getJoinEventDuration());
        joinEvents.push_back(*invitedIt);
        (*invitedIt)->increaseAcceptedGuests();
        if ((*invitedIt)->getAcceptedGuests() == 1){
            auto theHost = (*invitedIt)->getHostWeakPointer();
            if (auto hostPtr = theHost.lock()) hostPtr->addHostToTheEvent((*invitedIt));
        }
    }
}

void User::rejectJoinEvent(int invitationID){
    auto invitedIt = find_if(invitedJoinEvents.begin(), invitedJoinEvents.end(), [invitationID](const shared_ptr<JoinEvent>& invitedJoinEvent){
            return invitedJoinEvent->getJoinEventID() == invitationID;
        });

    if (invitedIt == invitedJoinEvents.end()) throw NotFound();
    else {
        invitedJoinEvents.erase(invitedIt);
    }
}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
bool User::logged() const { return isLoggedIn; }
vector<shared_ptr<Event>> User::getEvents() const { return events; }
vector<shared_ptr<PeriodicEvent>> User::getPeriodicEvents() const { return periodicEvents; }