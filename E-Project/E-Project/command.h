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

    vector<bool> makeOptionList(const ParsedCmd command)
    {
        vector<bool> optionlist;
        optionlist.push_back(command.firstNameFlag);
        optionlist.push_back(command.lastNameFlag);
        optionlist.push_back(command.midNumFlag);
        optionlist.push_back(command.lastNumFlag);
        optionlist.push_back(command.yearFlag);
        optionlist.push_back(command.monthFlag);
        optionlist.push_back(command.dateFlag);
        return optionlist;
    }

    resultPrinter* printer;

    noResultPrinter noPrinter;
    detailResultPrinter detailPrinter;
    defaultResultPrinter defaultPrinter;
};

#endif