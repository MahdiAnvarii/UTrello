#ifndef HANDLERS_H
#define HANDLERS_H

#include "utils.h"
#include "utrello.h"
#include "../server/server.hpp"

class SignupHandler : public RequestHandler {
public:
    SignupHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class MainHandler : public TemplateHandler {
public:
    MainHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class CreateTaskHandler : public TemplateHandler {
public:
    CreateTaskHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class CreateTaskPostHandler : public RequestHandler {
public:
    CreateTaskPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class DeleteTaskHandler : public TemplateHandler {
public:
    DeleteTaskHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class DeleteTaskPostHandler : public RequestHandler {
public:
    DeleteTaskPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class EditTaskHandler : public TemplateHandler {
public:
    EditTaskHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class EditTaskPostHandler : public RequestHandler {
public:
    EditTaskPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class CreateEventHandler : public TemplateHandler {
public:
    CreateEventHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class CreateEventPostHandler : public RequestHandler {
public:
    CreateEventPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class CreatePeriodicEventHandler : public TemplateHandler {
public:
    CreatePeriodicEventHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class CreatePeriodicEventPostHandler : public RequestHandler {
public:
    CreatePeriodicEventPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class CreateJoinEventHandler : public TemplateHandler {
public:
    CreateJoinEventHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class CreateJoinEventPostHandler : public RequestHandler {
public:
    CreateJoinEventPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class ReportJobsHandler : public TemplateHandler {
public:
    ReportJobsHandler(const string& filePath, shared_ptr<UTrello> _app);
    map<string, string> handle(Request* req) override;
private:
    shared_ptr<UTrello> app;
};

class ReportJobsPostHandler : public RequestHandler {
public:
    ReportJobsPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class CheckInvitationsHandler : public RequestHandler {
public:
    CheckInvitationsHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

class CheckInvitationsPostHandler : public RequestHandler {
public:
    CheckInvitationsPostHandler(shared_ptr<UTrello> _app);
    Response* callback(Request*) override;
private:
    shared_ptr<UTrello> app;
};

string generatePageForReport(const vector<string>& reportResultsVector, string username);
string generatePageForInvitations(const vector<string>& invitationsVector, string username);

#endif //HANDLERS_H