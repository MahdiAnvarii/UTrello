#include "cli.h"
#include "errors.h"

CliHandler::CliHandler(shared_ptr<UTrello>& app_): app(app_){}

void CliHandler::start(){
    string theOrder;
    while (getline(cin,theOrder)){
        if (theOrder.empty()) continue;
        vector<string> orderToVector = splitTheOrder(theOrder);
        if (orderToVector.empty()) continue;

        try {
            if (find(ORDERS.begin(), ORDERS.end(), orderToVector[0]) == ORDERS.end()) throw BadRequest();
            else if (orderToVector[0] == POST){
                if (find(POST_ORDERS.begin(), POST_ORDERS.end(), orderToVector[1]) == POST_ORDERS.end()) throw NotFound();
                else if (orderToVector[1] == SIGNUP) signup(orderToVector);
                else if (orderToVector[1] == LOGIN) login(orderToVector); 
                else if (orderToVector[1] == LOGOUT) logout(orderToVector); 
                else if (orderToVector[1] == EVENT) createEvent(orderToVector); 
                else if (orderToVector[1] == PERIODIC_EVENT) createPeriodicEvent(orderToVector); 
                else if (orderToVector[1] == TASK) createTask(orderToVector); 
                else if (orderToVector[1] == JOIN_EVENT) createJoinEvent(orderToVector);
                else if (orderToVector[1] == CONFIRM_JOIN_EVENT) confirmJoinEvent(orderToVector);
                else if (orderToVector[1] == REJECT_JOIN_EVENT) rejectJoinEvent(orderToVector);
            }
            else if (orderToVector[0] == DELETE){
                if (find(DELETE_ORDERS.begin(), DELETE_ORDERS.end(), orderToVector[1]) == DELETE_ORDERS.end()) throw NotFound();
                else if (orderToVector[1] == TASK) deleteTask(orderToVector); 
            }
            else if (orderToVector[0] == PUT){
                if (find(PUT_ORDERS.begin(), PUT_ORDERS.end(), orderToVector[1]) == PUT_ORDERS.end()) throw NotFound();
                else if (orderToVector[1] == TASK) editTask(orderToVector);
            }
            else if (orderToVector[0] == GET){
                if (find(GET_ORDERS.begin(), GET_ORDERS.end(), orderToVector[1]) == GET_ORDERS.end()) throw NotFound();
                else if (orderToVector[1] == REPORT) reportJobs(orderToVector);
                else if (orderToVector[1] == JOIN_EVENT) checkInvitationList(orderToVector); 
            }
            
        } catch (const logic_error& e) {
            cout << e.what() << "\n";
        }
    }
}

void CliHandler::signup(vector<string> orderToVector){
    try {
        auto usernameIt = find(orderToVector.begin(), orderToVector.end(), USERNAME);
        int usernameIndex = distance(orderToVector.begin(), usernameIt);
        auto passwordIt = find(orderToVector.begin(), orderToVector.end(), PASSWORD);
        int passwordIndex = distance(orderToVector.begin(), passwordIt);
        if (usernameIt == orderToVector.end() || passwordIt == orderToVector.end() || abs(usernameIndex-passwordIndex) == 1 ||
            usernameIndex+1 >= orderToVector.size() || passwordIndex+1 >= orderToVector.size()) throw BadRequest();

        app->addNewUser(orderToVector[usernameIndex+1], orderToVector[passwordIndex+1]);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::login(vector<string> orderToVector){
    try {
        auto usernameIt = find(orderToVector.begin(), orderToVector.end(), USERNAME);
        int usernameIndex = distance(orderToVector.begin(), usernameIt);
        auto passwordIt = find(orderToVector.begin(), orderToVector.end(), PASSWORD);
        int passwordIndex = distance(orderToVector.begin(), passwordIt);
        if (usernameIt == orderToVector.end() || passwordIt == orderToVector.end() || abs(usernameIndex-passwordIndex) == 1 ||
            usernameIndex+1 >= orderToVector.size() || passwordIndex+1 >= orderToVector.size()) throw BadRequest();

        app->logToUser(orderToVector[usernameIndex+1], orderToVector[passwordIndex+1]);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::logout(vector<string> orderToVector){
    try {
        app->logoutFromUser();
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::createEvent(vector<string> orderToVector){
    try {
        auto dateIt = find(orderToVector.begin(), orderToVector.end(), DATE);
        int dateIndex = distance(orderToVector.begin(), dateIt);
        auto startTimeIt = find(orderToVector.begin(), orderToVector.end(), START_TIME);
        int startTimeIndex = distance(orderToVector.begin(), startTimeIt);
        auto durationIt = find(orderToVector.begin(), orderToVector.end(), DURATION);
        int durationIndex = distance(orderToVector.begin(), durationIt);
        auto titleIt = find(orderToVector.begin(), orderToVector.end(), TITLE);
        int titleIndex = distance(orderToVector.begin(), titleIt);
        auto descriptionIt = find(orderToVector.begin(), orderToVector.end(), DESCRIPTION);
        int descriptionIndex = distance(orderToVector.begin(), descriptionIt);
        if (dateIt == orderToVector.end() || startTimeIt == orderToVector.end() || 
            durationIt == orderToVector.end() || titleIt == orderToVector.end() ||
            abs(dateIndex-startTimeIndex) == 1 || abs(dateIndex-durationIndex) == 1 || abs(dateIndex-titleIndex) == 1 ||
            abs(startTimeIndex-durationIndex) == 1 || abs(startTimeIndex-titleIndex) == 1 || abs(durationIndex-titleIndex) == 1 ||
            dateIndex+1 >= orderToVector.size() || startTimeIndex+1 >= orderToVector.size() ||
            durationIndex+1 >= orderToVector.size() || titleIndex+1 >= orderToVector.size()) throw BadRequest();

        string description = EMPTY_DESCRIPTION;
        if (descriptionIt != orderToVector.end() && descriptionIndex+1 < orderToVector.size()) description = orderToVector[descriptionIndex+1];
        app->addNewEvent(orderToVector[dateIndex+1], stoi(orderToVector[startTimeIndex+1]), 
                            stoi(orderToVector[durationIndex+1]), orderToVector[titleIndex+1], description);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::createPeriodicEvent(vector<string> orderToVector){
    bool holidayFound = false;
    try {
        auto startDateIt = find(orderToVector.begin(), orderToVector.end(), START_DATE);
        int startDateIndex = distance(orderToVector.begin(), startDateIt);
        auto endDateIt = find(orderToVector.begin(), orderToVector.end(), END_DATE);
        int endDateIndex = distance(orderToVector.begin(), endDateIt);
        auto startTimeIt = find(orderToVector.begin(), orderToVector.end(), START_TIME);
        int startTimeIndex = distance(orderToVector.begin(), startTimeIt);
        auto durationIt = find(orderToVector.begin(), orderToVector.end(), DURATION);
        int durationIndex = distance(orderToVector.begin(), durationIt);
        auto typeIt = find(orderToVector.begin(), orderToVector.end(), TYPE);
        int typeIndex = distance(orderToVector.begin(), typeIt);
        auto titleIt = find(orderToVector.begin(), orderToVector.end(), TITLE);
        int titleIndex = distance(orderToVector.begin(), titleIt);
        auto descriptionIt = find(orderToVector.begin(), orderToVector.end(), DESCRIPTION);
        int descriptionIndex = distance(orderToVector.begin(), descriptionIt);

        if (startDateIt == orderToVector.end() || endDateIt == orderToVector.end() || startTimeIt == orderToVector.end() || 
            durationIt == orderToVector.end() || typeIt == orderToVector.end() || titleIt == orderToVector.end() ||
            abs(startDateIndex-endDateIndex) == 1 || abs(startDateIndex-startTimeIndex) == 1 || abs(startDateIndex-durationIndex) == 1 ||
            abs(startDateIndex-typeIndex) == 1 || abs(startDateIndex-titleIndex) == 1 || abs(endDateIndex-startTimeIndex) == 1 ||
            abs(endDateIndex-durationIndex) == 1 || abs(endDateIndex-typeIndex) == 1 || abs(endDateIndex-titleIndex) == 1 ||
            abs(startTimeIndex-durationIndex) == 1 || abs(startTimeIndex-typeIndex) == 1 || abs(startTimeIndex-titleIndex) == 1 ||
            abs(durationIndex-typeIndex) == 1 || abs(durationIndex-titleIndex) == 1 || abs(typeIndex-titleIndex) == 1 ||
            startDateIndex+1 >= orderToVector.size() || endDateIndex+1 >= orderToVector.size() || 
            startTimeIndex+1 >= orderToVector.size() || durationIndex+1 >= orderToVector.size() || 
            typeIndex+1 >= orderToVector.size() || titleIndex+1 >= orderToVector.size()) throw BadRequest();

        string description = EMPTY_DESCRIPTION;
        if (descriptionIt != orderToVector.end() && descriptionIndex+1 < orderToVector.size()) description = orderToVector[descriptionIndex+1];

        if (orderToVector[typeIndex+1] == DAILY){
            app->addNewPeriodicEvent(orderToVector[startDateIndex+1], orderToVector[endDateIndex+1], 
                                                stoi(orderToVector[startTimeIndex+1]), stoi(orderToVector[durationIndex+1]), 
                                                orderToVector[typeIndex+1], orderToVector[titleIndex+1], description, holidayFound);

        } 
        else if (orderToVector[typeIndex+1] == MONTHLY){
            auto dayIt = find(orderToVector.begin(), orderToVector.end(), DAY);
            int dayIndex = distance(orderToVector.begin(), dayIt);
            if (dayIt == orderToVector.end() || abs(startDateIndex-dayIndex) == 1 || abs(endDateIndex-dayIndex) == 1 ||
                abs(startTimeIndex-dayIndex) == 1 || abs(durationIndex-dayIndex) == 1 || abs(typeIndex-dayIndex) == 1 || 
                abs(titleIndex-dayIndex) == 1 || dayIndex+1 >= orderToVector.size()) throw BadRequest();

            app->addNewPeriodicEvent(orderToVector[startDateIndex+1], orderToVector[endDateIndex+1], stoi(orderToVector[startTimeIndex+1]), 
                                    stoi(orderToVector[durationIndex+1]), orderToVector[typeIndex+1], orderToVector[titleIndex+1], 
                                    description, holidayFound, stoi(orderToVector[dayIndex+1]));
        } 
        else if (orderToVector[typeIndex+1] == WEEKLY){
            auto weekDaysIt = find(orderToVector.begin(), orderToVector.end(), WEEK_DAYS);
            int weekDaysIndex = distance(orderToVector.begin(), weekDaysIt);
            if (weekDaysIt == orderToVector.end() || abs(startDateIndex-weekDaysIndex) == 1 || abs(endDateIndex-weekDaysIndex) == 1 ||
                abs(startTimeIndex-weekDaysIndex) == 1 || abs(durationIndex-weekDaysIndex) == 1 || abs(typeIndex-weekDaysIndex) == 1 || 
                abs(titleIndex-weekDaysIndex) == 1 || weekDaysIndex+1 >= orderToVector.size()) throw BadRequest();

            if (orderToVector[weekDaysIndex+1] == "") throw BadRequest();
            vector<string> daysOfWeekForEvent = splitByCommas(orderToVector[weekDaysIndex+1]);
            for (auto dayOfWeekForEvent : daysOfWeekForEvent){
                if (find(DAYS_OF_WEEK.begin(), DAYS_OF_WEEK.end(), dayOfWeekForEvent) == DAYS_OF_WEEK.end()) throw BadRequest();
            }
            app->addNewPeriodicEvent(orderToVector[startDateIndex+1], orderToVector[endDateIndex+1], stoi(orderToVector[startTimeIndex+1]), 
                                    stoi(orderToVector[durationIndex+1]), orderToVector[typeIndex+1], orderToVector[titleIndex+1], 
                                    description, holidayFound, 0, daysOfWeekForEvent);
        }

        try {
            if (holidayFound) throw HolidayFound();
            cout << "OK" << "\n";
        } catch (const logic_error& e) {
            cout << e.what() << "\n";
        }
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::createTask(vector<string> orderToVector){
    try {
        auto dateIt = find(orderToVector.begin(), orderToVector.end(), DATE);
        int dateIndex = distance(orderToVector.begin(), dateIt);
        auto timeIt = find(orderToVector.begin(), orderToVector.end(), TIME);
        int timeIndex = distance(orderToVector.begin(), timeIt);
        auto titleIt = find(orderToVector.begin(), orderToVector.end(), TITLE);
        int titleIndex = distance(orderToVector.begin(), titleIt);
        auto descriptionIt = find(orderToVector.begin(), orderToVector.end(), DESCRIPTION);
        int descriptionIndex = distance(orderToVector.begin(), descriptionIt);

        if (dateIt == orderToVector.end() || timeIt == orderToVector.end() || titleIt == orderToVector.end() ||
            abs(dateIndex-timeIndex) == 1 || abs(dateIndex-titleIndex) == 1 || abs(timeIndex-titleIndex) == 1 ||
            dateIndex+1 >= orderToVector.size() || timeIndex+1 >= orderToVector.size() || titleIndex+1 >= orderToVector.size()) throw BadRequest();

        string description = EMPTY_DESCRIPTION;
        if (descriptionIt != orderToVector.end() && descriptionIndex+1 < orderToVector.size()) description = orderToVector[descriptionIndex+1];
        app->addNewTask(orderToVector[dateIndex+1], stoi(orderToVector[timeIndex+1]), orderToVector[titleIndex+1], description);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::deleteTask(vector<string> orderToVector){
    try {
        auto taskIdIt = find(orderToVector.begin(), orderToVector.end(), TASK_ID);
        int taskIdIndex = distance(orderToVector.begin(), taskIdIt);

        if (taskIdIt == orderToVector.end() || taskIdIndex+1 >= orderToVector.size()) throw BadRequest();
        app->deleteTask(stoi(orderToVector[taskIdIndex+1]));
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::editTask(vector<string> orderToVector){
    try {
        auto dateIt = find(orderToVector.begin(), orderToVector.end(), DATE);
        int dateIndex = distance(orderToVector.begin(), dateIt);
        auto timeIt = find(orderToVector.begin(), orderToVector.end(), TIME);
        int timeIndex = distance(orderToVector.begin(), timeIt);
        auto titleIt = find(orderToVector.begin(), orderToVector.end(), TITLE);
        int titleIndex = distance(orderToVector.begin(), titleIt);
        auto descriptionIt = find(orderToVector.begin(), orderToVector.end(), DESCRIPTION);
        int descriptionIndex = distance(orderToVector.begin(), descriptionIt);
        auto taskIdIt = find(orderToVector.begin(), orderToVector.end(), TASK_ID);
        int taskIdIndex = distance(orderToVector.begin(), taskIdIt);

        if (taskIdIt == orderToVector.end() || (dateIt == orderToVector.end() && timeIt == orderToVector.end() && 
            titleIt == orderToVector.end() && descriptionIt == orderToVector.end()) || abs(dateIndex-timeIndex) == 1 || 
            abs(dateIndex-titleIndex) == 1 || abs(dateIndex-descriptionIndex) == 1 || abs(dateIndex-taskIdIndex) == 1 || 
            abs(timeIndex-titleIndex) == 1 || abs(timeIndex-descriptionIndex) == 1 || abs(timeIndex-taskIdIndex) == 1 || 
            abs(titleIndex-descriptionIndex) == 1 || abs(titleIndex-taskIdIndex) == 1 || abs(descriptionIndex-taskIdIndex) == 1 ||
            dateIndex+1 == orderToVector.size() || timeIndex+1 == orderToVector.size() || titleIndex+1 == orderToVector.size() ||
            descriptionIndex+1 == orderToVector.size() || taskIdIndex+1 == orderToVector.size()) throw BadRequest();

        int taskID = DEFUALT_INTEGER;
        int time = DEFUALT_INTEGER;
        string dateLine, title, description;
        if (dateIt != orderToVector.end()) dateLine = orderToVector[dateIndex+1];
        if (timeIt != orderToVector.end()) time = stoi(orderToVector[timeIndex+1]);
        if (titleIt != orderToVector.end()) title = orderToVector[titleIndex+1];
        if (descriptionIt != orderToVector.end()) description = orderToVector[descriptionIndex+1];
        if (taskIdIt != orderToVector.end()) taskID = stoi(orderToVector[taskIdIndex+1]);

        app->editTask(taskID, dateLine, time, title, description);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::reportJobs(vector<string> orderToVector){
    try{
        auto fromDateIt = find(orderToVector.begin(), orderToVector.end(), FROM);
        int fromDateIndex = distance(orderToVector.begin(), fromDateIt);
        auto toDateIt = find(orderToVector.begin(), orderToVector.end(), TO);
        int toDateIndex = distance(orderToVector.begin(), toDateIt);
        auto typeIt = find(orderToVector.begin(), orderToVector.end(), TYPE);
        int typeIndex = distance(orderToVector.begin(), typeIt);

        if (toDateIt == orderToVector.end() || abs(fromDateIndex-toDateIndex) == 1 || abs(fromDateIndex-typeIndex) == 1 || 
            abs(toDateIndex-typeIndex) == 1 || fromDateIndex+1 == orderToVector.size() || toDateIndex == orderToVector.size() || 
            typeIndex+1 == orderToVector.size()) throw BadRequest();

        string fromDateLine, toDateLine, type;
        toDateLine = orderToVector[toDateIndex+1];
        if (fromDateIt != orderToVector.end()) fromDateLine = orderToVector[fromDateIndex+1];
        if (typeIt != orderToVector.end()) type = orderToVector[typeIndex+1];

        app->reportJobs(fromDateLine, toDateLine, type);

    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::createJoinEvent(vector<string> orderToVector){
    try {
        auto guestsIt = find(orderToVector.begin(), orderToVector.end(), GUESTS);
        int guestsIndex = distance(orderToVector.begin(), guestsIt);
        auto dateIt = find(orderToVector.begin(), orderToVector.end(), DATE);
        int dateIndex = distance(orderToVector.begin(), dateIt);
        auto startTimeIt = find(orderToVector.begin(), orderToVector.end(), START_TIME);
        int startTimeIndex = distance(orderToVector.begin(), startTimeIt);
        auto endTimeIt = find(orderToVector.begin(), orderToVector.end(), END_TIME);
        int endTimeIndex = distance(orderToVector.begin(), endTimeIt);
        auto titleIt = find(orderToVector.begin(), orderToVector.end(), TITLE);
        int titleIndex = distance(orderToVector.begin(), titleIt);
        auto descriptionIt = find(orderToVector.begin(), orderToVector.end(), DESCRIPTION);
        int descriptionIndex = distance(orderToVector.begin(), descriptionIt);
        if (guestsIt == orderToVector.end() || dateIt == orderToVector.end() || startTimeIt == orderToVector.end() || 
            endTimeIt == orderToVector.end() || titleIt == orderToVector.end() || abs(guestsIndex-dateIndex) == 1 ||
            abs(guestsIndex-startTimeIndex) == 1 || abs(guestsIndex-endTimeIndex) == 1 || abs(guestsIndex-titleIndex) == 1 ||
            abs(dateIndex-startTimeIndex) == 1 || abs(dateIndex-endTimeIndex) == 1 || abs(dateIndex-titleIndex) == 1 ||
            abs(startTimeIndex-endTimeIndex) == 1 || abs(startTimeIndex-titleIndex) == 1 || abs(endTimeIndex-titleIndex) == 1 ||
            guestsIndex+1 >= orderToVector.size() || dateIndex+1 >= orderToVector.size() || startTimeIndex+1 >= orderToVector.size() ||
            endTimeIndex+1 >= orderToVector.size() || titleIndex+1 >= orderToVector.size()) throw BadRequest();

        if (orderToVector[guestsIndex+1] == "") throw BadRequest();
        string description = EMPTY_DESCRIPTION;
        if (descriptionIt != orderToVector.end() && descriptionIndex+1 < orderToVector.size()) description = orderToVector[descriptionIndex+1];
        app->addNewJoinEvent(orderToVector[guestsIndex+1], orderToVector[dateIndex+1], stoi(orderToVector[startTimeIndex+1]), 
                            stoi(orderToVector[endTimeIndex+1]), orderToVector[titleIndex+1], description);
        cout << "OK" << "\n";
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::checkInvitationList(vector<string> orderToVector){
    try {
        app->checkInvitationList();
            
    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::confirmJoinEvent(vector<string> orderToVector){
    try {
        auto invitationIdIt = find(orderToVector.begin(), orderToVector.end(), INVITATION_ID);
        int invitationIdIndex = distance(orderToVector.begin(), invitationIdIt);
        if (invitationIdIt == orderToVector.end() || invitationIdIndex+1 == orderToVector.size()) throw BadRequest();

        app->confirmJoinEvent(stoi(orderToVector[invitationIdIndex+1]));
        cout << "OK" << "\n";

    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}

void CliHandler::rejectJoinEvent(vector<string> orderToVector){
    try {
        auto invitationIdIt = find(orderToVector.begin(), orderToVector.end(), INVITATION_ID);
        int invitationIdIndex = distance(orderToVector.begin(), invitationIdIt);
        if (invitationIdIt == orderToVector.end() || invitationIdIndex+1 == orderToVector.size()) throw BadRequest();

        app->rejectJoinEvent(stoi(orderToVector[invitationIdIndex+1]));
        cout << "OK" << "\n";

    } catch (const logic_error& e) {
        cout << e.what() << "\n";
    }
}