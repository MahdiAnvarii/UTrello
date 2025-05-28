#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MONTHS_PER_YEAR = 12;
const int DAYS_PER_MONTH = 30;
const int DAYS_PER_WEEK = 7;
const vector<string> ORDERS = {"POST", "DELETE", "PUT", "GET"};
const vector<string> SUBORDERS = {"signup", "login", "logout", "event", "periodic_event", "task", "report"};
const string POST = ORDERS[0];
const string DELETE = ORDERS[1];
const string PUT = ORDERS[2];
const string GET = ORDERS[3];
const vector<string> POST_ORDERS = {"signup", "login", "logout", "event", "periodic_event", "task"};
const vector<string> DELETE_ORDERS = {"task"};
const vector<string> PUT_ORDERS = {"task"};
const vector<string> GET_ORDERS = {"report"};
const string SIGNUP = SUBORDERS[0];
const string LOGIN = SUBORDERS[1];
const string LOGOUT = SUBORDERS[2];
const string EVENT = SUBORDERS[3];
const string PERIODIC_EVENT = SUBORDERS[4];
const string TASK = SUBORDERS[5];
const string REPORT = SUBORDERS[6];
const string USERNAME = "username";
const string PASSWORD = "password";
const string DATE = "date";
const string START_TIME = "start_time";
const string DURATION = "duration";
const string TITLE = "title";
const string DESCRIPTION = "description";
const string TIME = "time";
const string TASK_ID = "task_id";
const int CLOCK_START = 0;
const int CLOCK_END = 23;
const string EMPTY_DESCRIPTION = "";
const string EMPTY_TITLE = "";
const string EMPTY_DATELINE = "";
const string EMPTY_TYPE = "";
const int DEFUALT_INTEGER = -1e9;
const string START_DATE = "start_date";
const string END_DATE = "end_date";
const string TYPE = "type";
const string FROM = "from";
const string TO = "to";
const vector<string> PERIODIC_TYPE = {"Daily", "Weekly", "Monthly"};
const string DAILY = PERIODIC_TYPE[0];
const string WEEKLY = PERIODIC_TYPE[1];
const string MONTHLY = PERIODIC_TYPE[2];
const string DAY = "day";
const string WEEK_DAYS = "week_days";
const vector<string> DAYS_OF_WEEK = {"Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"};
const vector<string> JOB_TYPES = {"event", "periodic_event", "task"};

enum class DayOfWeek {
    Friday,
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday
};

enum class PeriodicType {
    Daily,
    Weekly,
    Monthly
};

PeriodicType stringToPeriodicType(const string& s);
DayOfWeek stringToDayOfWeek(const string& s);
string periodicTypeToString(PeriodicType type);
vector<string> splitTheOrder(string order);
vector<string> splitDaysOFWeek(string daysContainer);

#endif //UTILS_H