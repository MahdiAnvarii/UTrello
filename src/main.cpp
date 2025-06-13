#include "../server/server.hpp"
#include "handlers.h"
#include "utrello.h"

void mapServerPaths(Server& server, shared_ptr<UTrello> app) {
    server.get("/css/error.css", new ShowFile("css/error.css", "text/css"));
    server.get("/css/style.css", new ShowFile("css/style.css", "text/css"));
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(app));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(app));
    server.get("/logout", new LogoutHandler(app));
    server.get("/main", new MainHandler("template/main.html", app));
    server.get("/create-task", new CreateTaskHandler("template/create_task.html", app));
    server.post("/create-task", new CreateTaskPostHandler(app));
    server.get("/delete-task", new DeleteTaskHandler("template/delete_task.html", app));
    server.post("/delete-task", new DeleteTaskPostHandler(app));
    server.get("/edit-task", new EditTaskHandler("template/edit_task.html", app));
    server.post("/edit-task", new EditTaskPostHandler(app));
    server.get("/create-event", new CreateEventHandler("template/create_event.html", app));
    server.post("/create-event", new CreateEventPostHandler(app));
    server.get("/create-periodic-event", new CreatePeriodicEventHandler("template/create_periodic_event.html", app));
    server.post("/create-periodic-event", new CreatePeriodicEventPostHandler(app));
    server.get("/create-join-event", new CreateJoinEventHandler("template/create_join_event.html", app));
    server.post("/create-join-event", new CreateJoinEventPostHandler(app));
    server.get("/report-jobs", new ReportJobsHandler("template/report_jobs.html", app));
    server.post("/report-jobs", new ReportJobsPostHandler(app));
    server.get("/check-invitations", new CheckInvitationsHandler(app));
    server.post("/check-invitations", new CheckInvitationsPostHandler(app));
}

int main(int argc, char** argv) {
    try {
        int port = argc > 1 ? stoi(argv[1]) : 5000;
        const string holidayFileAddress = argv[2];
        Server server(port);
        shared_ptr<UTrello> app = make_shared<UTrello>(holidayFileAddress);
        mapServerPaths(server, app);
        cout << "Server running on port: " << port << endl;
        server.run();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
    catch (const Server::Exception& e) {
        cerr << e.getMessage() << endl;
    }
    return 0;
}