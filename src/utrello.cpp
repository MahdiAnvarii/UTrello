#include "utrello.h"
#include "errors.h"

UTrello::UTrello(const string& holidayFileAddress_){
    processHolidayFile(holidayFileAddress_);
}

void UTrello::processHolidayFile(const string& holidayFileAddress_){
    ifstream holidayFile(holidayFileAddress_);
    string holidayFileLine;
    getline(holidayFile, holidayFileLine);
    while(getline(holidayFile, holidayFileLine)){
        istringstream iss(holidayFileLine);
        string day, month, year;
        getline(iss, day, ',');
        getline(iss, month, ',');
        getline(iss, year, ',');

        shared_ptr<Date> holiday = make_shared<Date>(stoi(day), stoi(month), stoi(year), true);
        holidays.push_back(holiday);
    }
}

void UTrello::addNewUser(const string& username, const string& password){
    for (auto user: users){
        if (user->getUsername() == username) throw BadRequest();
    }
    for (auto user: users){
        if (user->logged()) throw PermissionDenied();
    }
    shared_ptr<User> newUser = make_shared<User>(username, password);
    users.push_back(newUser);
    userUsernames.push_back(username);
}

void UTrello::logToUser(const string& username, const string& password){
    if (find(userUsernames.begin(), userUsernames.end(), username) == userUsernames.end()) throw NotFound();
    for (auto user: users){
        if (user->getUsername() == username && user->getPassword() != password) throw PermissionDenied();
    }
    for (auto user: users){
        if (user->logged()) throw PermissionDenied();
    }
    for (auto user: users){
        if (user->getUsername() == username && user->getPassword() == password) user->login();
    }
}

void UTrello::logoutFromUser(){
    bool isSomeOneLogged = false;
    for (auto user: users){
        if (user->logged()){
            isSomeOneLogged = true;
            user->logout();
        }
    }
    if (!isSomeOneLogged) throw PermissionDenied();
}

shared_ptr<User> UTrello::ifSomeOneLoggedIn(){
    shared_ptr<User> theUser = nullptr;
    for (auto user: users){
        if (user->logged()) theUser = user;
    }
    if (theUser == nullptr) throw PermissionDenied();
    return theUser;
}

void UTrello::checkConflictsWithOthers(shared_ptr<Date> eventDate, shared_ptr<User> theUser, int start_time, int duration){
    for (auto userEvent : theUser->getEvents()){
        if (eventDate->isOnAnotherDate(*(userEvent->getEventDate())) && 
            start_time+duration > userEvent->getEventStartTime() && 
            start_time < userEvent->getEventStartTime()+userEvent->getEventDuration()) throw Overlap();
    }
    for (auto userPeriodicEvent : theUser->getPeriodicEvents()){
        for (auto periodicEventDate : userPeriodicEvent->getPeriodicEventDates()){
            if (eventDate->isOnAnotherDate(*(periodicEventDate)) && 
                start_time+duration > userPeriodicEvent->getPeriodicEventStartTime() && 
                start_time < userPeriodicEvent->getPeriodicEventStartTime()+userPeriodicEvent->getPeriodicEventDuration()) throw Overlap();
        }
    }
}

void UTrello::addNewEvent(string dateLine, int start_time, int duration, string title, const string& description){
    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    if (start_time > CLOCK_END || start_time < CLOCK_START || duration <= CLOCK_START) throw BadRequest();
    shared_ptr<Date> eventDate = make_shared<Date>(dateLine);
    checkConflictsWithOthers(eventDate, theUser, start_time, duration);

    for (auto holiday : holidays){
        if (eventDate->isOnAnotherDate(*holiday)) throw HolidayFound();
    }

    theUser->addNewEvent(eventDate, start_time, duration, title, description);
}

void UTrello::addNewPeriodicEvent(string startDateLine, string endDateLine, int start_time, int duration, string type, 
                                    string title, const string& description, bool& holidayFoundFlag, int day, vector<string> week_days) {

    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    if (start_time > CLOCK_END || start_time < CLOCK_START || duration <= CLOCK_START ||
        find(PERIODIC_TYPE.begin(), PERIODIC_TYPE.end(), type) == PERIODIC_TYPE.end()) throw BadRequest();
    
    PeriodicType periodicType = stringToPeriodicType(type);
    vector<DayOfWeek> daysOfWeek(week_days.size());
    transform(week_days.begin(), week_days.end(), daysOfWeek.begin(), stringToDayOfWeek);
    shared_ptr<Date> eventStartDate = make_shared<Date>(startDateLine);
    shared_ptr<Date> eventEndDate = make_shared<Date>(endDateLine);
    vector<shared_ptr<Date>> potentialPeriodicEventDates;

    if (periodicType == PeriodicType::Daily){
        shared_ptr<Date> potentialDate = eventStartDate;
        while (true) {
            checkConflictsWithOthers(potentialDate, theUser, start_time, duration);
            potentialPeriodicEventDates.push_back(potentialDate);
            if (potentialDate->isOnAnotherDate(*eventEndDate)) break;
            potentialDate = potentialDate->createTommorow();
        }
    } 
    else if (periodicType == PeriodicType::Monthly){
        shared_ptr<Date> potentialDate = eventStartDate->createPeriodDay(day);
        while (true) {
            checkConflictsWithOthers(potentialDate, theUser, start_time, duration);
            potentialPeriodicEventDates.push_back(potentialDate);
            potentialDate = potentialDate->createTheNextMonth();
            if (potentialDate->isAfterDate(*eventEndDate)) break;
        }
    }
    else if (periodicType == PeriodicType::Weekly){
        shared_ptr<Date> potentialDate = eventStartDate;
        while (true) {
            checkConflictsWithOthers(potentialDate, theUser, start_time, duration);
            potentialPeriodicEventDates.push_back(potentialDate);
            if (potentialDate->isOnAnotherDate(*eventEndDate)) break;
            potentialDate = potentialDate->createTheNextDayOfWeek(daysOfWeek);
        }
    }

    vector<shared_ptr<Date>> periodicEventDates;
    for (auto potentialDate : potentialPeriodicEventDates){
        try {
            for (auto holiday : holidays){
                if (potentialDate->isOnAnotherDate(*holiday)) throw HolidayFound();
            }
            periodicEventDates.push_back(potentialDate);
        } catch (const logic_error& e) {
            holidayFoundFlag = true;
        }
    }

    theUser->addNewPeriodicEvent(periodicEventDates, start_time, duration, periodicType, title, description);
}

void UTrello::addNewTask(string dateLine, int time, string title, const string& description){
    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    if (time > CLOCK_END || time < CLOCK_START) throw BadRequest();

    shared_ptr<Date> taskDate = make_shared<Date>(dateLine);
    theUser->addNewTask(taskDate, time, title, description);
}

void UTrello::deleteTask(int taskID){
    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    theUser->deleteTask(taskID);
}

void UTrello::editTask(int taskID, string dateLine, int time, string title, const string& description){
    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    if (time != DEFUALT_INTEGER && (time > CLOCK_END || time < CLOCK_START)) throw BadRequest();
    theUser->editTask(taskID, dateLine, time, title, description);
}

void UTrello::reportJobs(string fromDateLine, string toDateLine, string type){
    shared_ptr<User> theUser = ifSomeOneLoggedIn();
    if (type != EMPTY_TYPE && find(JOB_TYPES.begin(), JOB_TYPES.end(), type) == JOB_TYPES.end()) throw BadRequest();
    shared_ptr<Date> toDate = make_shared<Date>(toDateLine);
    shared_ptr<Date> fromDate = nullptr;
    if (fromDateLine != EMPTY_DATELINE) fromDate = make_shared<Date>(fromDateLine);
    else fromDate = make_shared<Date>(1, 1, 1404, true);
    theUser->reportJobs(fromDate, toDate, type);
}