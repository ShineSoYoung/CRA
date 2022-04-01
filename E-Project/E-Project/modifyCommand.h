#ifndef __MODIFY_COMMAND__
#define __MODIFY_COMMAND__

#include "commandClassType.h"
#include "resultprinter.h"
#include "searchEngine.h"
#include <map>

enum {
    EMPLOYEE_NUM,
    NAME,
    CARRER_LEVEL,
    PHONE_NUM,
    BIRTH_DAY,
    CERTI
};

map<string, int> columnMap{
    {"employeeNum", EMPLOYEE_NUM },
    {"name", NAME},
    {"cl", CARRER_LEVEL},
    {"phoneNum", PHONE_NUM},
    {"birthday", BIRTH_DAY},
    {"certi", CERTI},
};

class modifyCommand
{
public:
    string modify_employee(vector<Employee*>& list, CmdParam command)
    {
        searchEngine engine;
        vector<Employee*> findArray = engine.search(list, command.strs[0], command.strs[1], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("MOD,", findArray);
        modFoundEntry(list, findArray, command.strs[2], command.strs[3]);
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

    void modFoundEntry(vector<Employee*>& list, vector<Employee*> findArray, string changeColumn, string changeValue)
    {
        int targetColumnNum = columnMap.find(changeColumn)->second;
        for (Employee* em : findArray)
        {
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i]->employeeNum == em->employeeNum)
                {
                    switch (targetColumnNum)
                    {
                    case NAME:
                        list[i]->name = changeValue;
                        break;
                    case CARRER_LEVEL:
                        list[i]->cl = changeValue;
                        break;
                    case PHONE_NUM:
                        list[i]->phoneNum = changeValue;
                        break;
                    case BIRTH_DAY:
                        list[i]->birthday = changeValue;
                        break;
                    case CERTI:
                        list[i]->certi = changeValue;
                        break;
                    }
                }
            }
        }
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