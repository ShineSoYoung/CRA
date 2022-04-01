#ifndef __SEARCH_COMMAND__
#define __SEARCH_COMMAND__

#include "commandClassType.h"
#include "resultprinter.h"
#include "searchEngine.h"


class searchCommand
{
public:
    string search_employee(vector<Employee*>& list, CmdParam command)
    {
        searchEngine engine;
        vector<Employee*> findArray = engine.search(list, command.strs[0], command.strs[1], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("SCH,", findArray);
        releasePrinter();
        return result;
    }

private:
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