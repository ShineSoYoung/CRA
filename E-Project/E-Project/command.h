#ifndef __COMMAND__
#define __COMMAND__

#include <vector>
#include "resultprinter.h"
#include "datamanager.h"

class command
{
public:
    command()
    {
        printer = nullptr;
    }

    virtual string processCommand(datamanager& DB, CmdParam command) = 0;
protected:
    void selectPrinter(vector<Employee*> findArray, bool printoption)
    {
        if (findArray.size() == 0) printer = new noResultPrinter();
        else if (printoption) printer = new detailResultPrinter();
        else printer = new defaultResultPrinter();
    }

    vector<bool> makeOptionList(CmdParam command)
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

    void releasePrinter()
    {
        delete printer;
    }

    resultPrinter* printer;
};

#endif