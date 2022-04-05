#ifndef __COMMAND__
#define __COMMAND__

#include <vector>
#include "resultprinter.h"
#include "datamanager.h"

const int findColumn = 0;
const int findValue = 1;
const int targetColumn = 2;
const int targetValue = 3;

class Command
{
public:
    Command() {}
    virtual string processCommand(datamanager& DB, const ParsedCmd command) = 0;
protected:

};


class NoneOptionalCommand : public Command {
public:
    NoneOptionalCommand() :Command() {}
};

class OptionalCommand : public Command {

public:
    OptionalCommand() :Command(), printer(nullptr) {}
protected:
    void selectPrinter(vector<Employee*> findArray, bool printoption)
    {
        if (findArray.size() == 0) printer = &noPrinter;
        else if (printoption) printer = &detailPrinter;
        else printer = &defaultPrinter;
    }

    optionList makeOptionList(const ParsedCmd command)
    {
        optionList list;
        list.searchforFirstName = command.firstNameFlag;
        list.searchforLastName = command.lastNameFlag;
        list.searchforMiddlePhoneNumber = command.midNumFlag;
        list.searchforLastPhoneNumber = command.lastNumFlag;
        list.searchforBirthdayYear = command.yearFlag;
        list.searchforBirthdayMonth = command.monthFlag;
        list.searchforBirthdayDay = command.dateFlag;
        return list;
    }

    resultPrinter* printer;

    noResultPrinter noPrinter;
    detailResultPrinter detailPrinter;
    defaultResultPrinter defaultPrinter;
};

#endif