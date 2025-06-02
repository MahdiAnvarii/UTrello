#ifndef CLI_H
#define CLI_H

#include "utils.h"
#include "utrello.h"

class CliHandler{
public:
    CliHandler(shared_ptr<UTrello>& app_);
    void start();
private:
    void signup(vector<string> orderToVector);
    void login(vector<string> orderToVector);
    void logout(vector<string> orderToVector);
    void createEvent(vector<string> orderToVector);
    void createPeriodicEvent(vector<string> orderToVector);
    void createTask(vector<string> orderToVector);
    void deleteTask(vector<string> orderToVector);
    void editTask(vector<string> orderToVector);
    void reportJobs(vector<string> orderToVector);
    void createJoinEvent(vector<string> orderToVector);
    void checkInvitationList(vector<string> orderToVector);
    void confirmJoinEvent(vector<string> orderToVector);
    void rejectJoinEvent(vector<string> orderToVector);
    shared_ptr<UTrello>& app;
};

#endif //CLI_H