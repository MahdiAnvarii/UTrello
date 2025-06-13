#include "handlers.h"
#include "errors.h"

SignupHandler::SignupHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* SignupHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");   
    try {
        app->addNewUser(username, password); 
        Response* res = Response::redirect("/login");
        return res;  
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

LoginHandler::LoginHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* LoginHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try {
        app->logToUser(username, password);
        Response* res = Response::redirect("/main?username=" + username);
        res->setSessionId("SID");
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const NotFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/404.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

LogoutHandler::LogoutHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* LogoutHandler::callback(Request* req) {
    try {
        app->logoutFromUser();
        Response* res = Response::redirect("/login");
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

MainHandler::MainHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> MainHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

CreateTaskHandler::CreateTaskHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> CreateTaskHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

CreateTaskPostHandler::CreateTaskPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CreateTaskPostHandler::callback(Request* req) {
    string title = req->getBodyParam("title");
    string date = req->getBodyParam("date");
    string time = req->getBodyParam("time");
    string description = req->getBodyParam("description");
    try {
        app->addNewTask(date, stoi(time), title, description);
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

DeleteTaskHandler::DeleteTaskHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> DeleteTaskHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

DeleteTaskPostHandler::DeleteTaskPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* DeleteTaskPostHandler::callback(Request* req) {
    string task_id = req->getBodyParam("task_id");
    try {
        app->deleteTask(stoi(task_id));
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const NotFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/404.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

EditTaskHandler::EditTaskHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> EditTaskHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

EditTaskPostHandler::EditTaskPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* EditTaskPostHandler::callback(Request* req) {
    string task_id = req->getBodyParam("task_id");
    string title = req->getBodyParam("title");
    string date = req->getBodyParam("date");
    string timeStr = req->getBodyParam("time");
    string description = req->getBodyParam("description");
    int time = DEFUALT_INTEGER;
    if (!timeStr.empty()) time = stoi(timeStr);
    try {
        app->editTask(stoi(task_id), date, time, title, description);
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const NotFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/404.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    }
}

CreateEventHandler::CreateEventHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> CreateEventHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

CreateEventPostHandler::CreateEventPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CreateEventPostHandler::callback(Request* req) {
    string title = req->getBodyParam("title");
    string date = req->getBodyParam("date");
    string start_time = req->getBodyParam("starttime");
    string duration = req->getBodyParam("duration");
    string description = req->getBodyParam("description");
    try {
        app->addNewEvent(date, stoi(start_time), stoi(duration), title, description);
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Overlap& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/409.html"));
        return res;
    } catch (const HolidayFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/451.html"));
        return res;
    }
}

CreatePeriodicEventHandler::CreatePeriodicEventHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> CreatePeriodicEventHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

CreatePeriodicEventPostHandler::CreatePeriodicEventPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CreatePeriodicEventPostHandler::callback(Request* req) {
    bool holidayFound = false;
    string title = req->getBodyParam("title");
    string start_date = req->getBodyParam("startdate");
    string end_date = req->getBodyParam("enddate");
    string start_time = req->getBodyParam("starttime");
    string duration = req->getBodyParam("duration");
    string selected_days = req->getBodyParam("week_days");
    string description = req->getBodyParam("description");
    vector<string> daysOfWeekForEvent = splitByCommas(selected_days);
    try {
        app->addNewPeriodicEvent(start_date, end_date, stoi(start_time), stoi(duration), WEEKLY, title, description, 
                                    holidayFound, 0, daysOfWeekForEvent);
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        try {
            if (holidayFound) throw HolidayFound();
            return res;
        } catch (const HolidayFound& e) {
            Response* res = new Response;
            res->setHeader("Content-Type", "text/html");
            res->setBody(utils::readFile("static/451.html"));
            return res;
        }     
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Overlap& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/409.html"));
        return res;
    }
}

CreateJoinEventHandler::CreateJoinEventHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> CreateJoinEventHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

CreateJoinEventPostHandler::CreateJoinEventPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CreateJoinEventPostHandler::callback(Request* req) {
    string guests = req->getBodyParam("guests");
    string title = req->getBodyParam("title");
    string date = req->getBodyParam("date");
    string start_time = req->getBodyParam("starttime");
    string end_time = req->getBodyParam("endtime");
    string description = req->getBodyParam("description");
    try {
        app->addNewJoinEvent(guests, date, stoi(start_time), stoi(end_time), title, description);
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/main?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const NotFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/404.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Overlap& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/409.html"));
        return res;
    } catch (const HolidayFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/451.html"));
        return res;
    }
}

ReportJobsHandler::ReportJobsHandler(const string& filePath, shared_ptr<UTrello> _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> ReportJobsHandler::handle(Request* req) {
    string newUsername = req->getQueryParam("username");
    map<string, string> context;
    context["username"] = newUsername;
    return context;
}

ReportJobsPostHandler::ReportJobsPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* ReportJobsPostHandler::callback(Request* req) {
    string from_date = req->getBodyParam("fromdate");
    string to_date = req->getBodyParam("todate");
    string type = req->getBodyParam("jobtype");
    try {
        vector<string> reportResultsVector = app->reportJobs(from_date, to_date, type);
        Response* res = new Response();
        string username = req->getBodyParam("username");
        res->setHeader("Content-Type", "text/html");
        res->setBody(generatePageForReport(reportResultsVector, username));
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Empty& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/460.html"));
        return res;
    }
}

CheckInvitationsHandler::CheckInvitationsHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CheckInvitationsHandler::callback(Request* req) {
    try {
        vector<string> reportResultsVector = app->checkInvitationList();
        Response* res = new Response();
        string username = req->getQueryParam("username");
        res->setHeader("Content-Type", "text/html");
        res->setBody(generatePageForInvitations(reportResultsVector, username));
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Empty& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/460.html"));
        return res;
    }
}

CheckInvitationsPostHandler::CheckInvitationsPostHandler(shared_ptr<UTrello> _app) : app(_app) {}
Response* CheckInvitationsPostHandler::callback(Request* req) {
    try {
        string invitation_id = req->getBodyParam("invitation_id");
        string action = req->getBodyParam("action");
        if (action == "accept") {
            app->confirmJoinEvent(stoi(invitation_id));
        } else if (action == "reject") {
            app->rejectJoinEvent(stoi(invitation_id));
        }
        string username = req->getBodyParam("username");
        Response* res = Response::redirect("/check-invitations?username=" + username);
        return res;
    } catch (const BadRequest& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/400.html"));
        return res;
    } catch (const NotFound& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/404.html"));
        return res;
    } catch (const PermissionDenied& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/403.html"));
        return res;
    } catch (const Overlap& e) {
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(utils::readFile("static/409.html"));
        return res;
    }
}

string generatePageForReport(const vector<string>& reportResultsVector, string username) {
    string html;
    html += "<!DOCTYPE html>\n";
    html += "<html lang='en'>\n";
    html += "<head>\n";
    html += "  <meta charset='UTF-8'>\n";
    html += "  <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    html += "  <title>Job Reports</title>\n";
    html += "  <link rel='stylesheet' href='../css/style.css' />\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "  <h1>" + username + "'s Job Reports</h1>\n";

    for (size_t i = 0; i < reportResultsVector.size(); ++i) {
        html += "  <div class='report'>\n";
        html += "    <div class='index'>Report #" + to_string(i+1) + "</div>\n";
        html += "    <pre>" + reportResultsVector[i] + "</pre>\n";
        html += "  </div>\n";
    }

    html += "</body>\n";
    html += "</html>\n";
    return html;
}

string generatePageForInvitations(const vector<string>& invitationsVector, string username) {
    string html;
    html += "<!DOCTYPE html>\n";
    html += "<html lang='en'>\n";
    html += "<head>\n";
    html += "  <meta charset='UTF-8'>\n";
    html += "  <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    html += "  <title>Invitations List</title>\n";
    html += "  <link rel='stylesheet' href='../css/style.css' />\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "  <h1>" + username + "'s Invitations List</h1>\n";
    html += "  <a href='/main?username=" + username + "' class='back-arrow'>⬅</a>\n";

    for (size_t i = 0; i < invitationsVector.size(); ++i) {
        string theInvitationID = extractInvitationID(invitationsVector[i]);
        html += "  <div class='report'>\n";
        html += "    <div class='index'>Invitation #" + to_string(i+1) + "</div>\n";
        html += "    <pre>" + invitationsVector[i] + "</pre>\n";
        html += "    <form class='action-form' method='POST' action='/check-invitations'>\n";
        html += "      <input type='hidden' name='invitation_id' value='" + theInvitationID + "' />\n";
        html += "      <input type='hidden' name='username' value='" + username + "' />\n";
        html += "      <button name='action' value='accept' class='accept-btn'>✔ Accept</button>\n";
        html += "      <button name='action' value='reject' class='reject-btn'>✖ Reject</button>\n";
        html += "    </form>\n";
        html += "  </div>\n";
    }

    html += "</body>\n";
    html += "</html>\n";
    return html;
}