#ifndef ERRORS_H
#define ERRORS_H

#include "utils.h"

class NotFound : public logic_error {
public:
    NotFound() : logic_error("Not Found") {}
};

class BadRequest : public logic_error {
public:
    BadRequest() : logic_error("Bad Request") {}
};

class PermissionDenied : public logic_error {
public:
    PermissionDenied() : logic_error("Permission Denied") {}
};

class Overlap : public logic_error {
public:
    Overlap() : logic_error("Overlap") {}
};

class HolidayFound : public logic_error {
public:
    HolidayFound() : logic_error("Holiday Found") {}
};

class Empty : public logic_error {
public:
    Empty() : logic_error("Empty") {}
};

#endif //ERRORS_H