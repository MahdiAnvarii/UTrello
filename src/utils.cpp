#include "utils.h"

PeriodicType stringToPeriodicType(const string& s) {
    if (s == "Daily")   return PeriodicType::Daily;
    else if (s == "Weekly")  return PeriodicType::Weekly;
    else return PeriodicType::Monthly;
}

DayOfWeek stringToDayOfWeek(const string& s) {
    if (s == "Friday")   return DayOfWeek::Friday;
    else if (s == "Saturday")   return DayOfWeek::Saturday;
    else if (s == "Sunday")   return DayOfWeek::Sunday;
    else if (s == "Monday")   return DayOfWeek::Monday;
    else if (s == "Tuesday")   return DayOfWeek::Tuesday;
    else if (s == "Wednesday")   return DayOfWeek::Wednesday;
    else return DayOfWeek::Thursday;
}

string periodicTypeToString(PeriodicType type) {
    switch (type) {
        case PeriodicType::Daily: return "Daily";
        case PeriodicType::Weekly: return "Weekly";
        case PeriodicType::Monthly: return "Monthly";
        default: return "Unknown";
    }
}

vector<string> splitTheOrder(string order){
    istringstream iss(order);
    vector<string> orderToVector;
    bool insideQuote = false;
    string word;
    string temp;
    while (iss >> word) {
        if (word.front() == '\"' && word.back() == '\"'){
            orderToVector.push_back(word.substr(1, word.length() - 2));
        }
        else if (word.front() == '\"'){
            temp = word.substr(1);
            insideQuote = true;
        } else if (insideQuote && word.back() == '\"'){
            temp += " " + word.substr(0, word.length() - 1);
            orderToVector.push_back(temp);
            insideQuote = false;
        } else if (insideQuote) {
            temp += " " + word;
        } else {
            orderToVector.push_back(word);
        }
    }
    return orderToVector;
}

vector<string> splitDaysOFWeek(string daysContainer){
    istringstream iss(daysContainer);
    vector<string> daysOfWeek;
    string dayOfWeek;

    while (getline(iss, dayOfWeek, ',')) {
        daysOfWeek.push_back(dayOfWeek);
    }
    return daysOfWeek;
}