
#ifndef __ADD_COMMAND__
#define __ADD_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

const int validParametersCount = 6;

class addCommand : public NoneOptionalCommand
{
public:
    virtual bool checkCommandIsValid(datamanager& DB, const ParsedCmd command) override
    {
        if (isParameterCountIsValid(command.strs) == false) return false;
        if (isParameterHasEmptyEntry(command.strs) == true) return false;
        if (isEmployeeNumAlreayExist(DB, command.strs[static_cast<int>(EmInfo::EMPLOYEE_NUM)]) == true) return false;
        return true;
    }
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        if (!checkCommandIsValid(DB, command))
            return "FAIL";

        addData(DB, command);
        return "";
    }
private:
    bool isParameterCountIsValid(vector<string> parameters)
    {
        return (parameters.size() == validParametersCount);
    }

    bool isParameterHasEmptyEntry(vector<string> parameters) {
        for (string data : parameters) {
            if (true == isEmptyData(data)) {
                return true;
            }
        }
        return false;
    }
    bool isEmptyData(string data)
    {
        return data == "_";
    }

    bool isEmployeeNumAlreayExist(datamanager& DB, string employeeNum)
    {
        optionList dummyOptionList = {false, false, false, false, false, false, false};
        vector<Employee*> findArray = DB.search_data("employeeNum", employeeNum, dummyOptionList);
        return (0 < findArray.size());
    }

    void addData(datamanager& DB, const ParsedCmd command)
    {
        Employee e;
        e.employeeNum = command.strs[static_cast<int>(EmInfo::EMPLOYEE_NUM)];
        e.name = command.strs[static_cast<int>(EmInfo::NAME)];
        e.cl = command.strs[static_cast<int>(EmInfo::CARRER_LEVEL)];
        e.phoneNum = command.strs[static_cast<int>(EmInfo::PHONE_NUM)];
        e.birthday = command.strs[static_cast<int>(EmInfo::BIRTH_DAY)];
        e.certi = command.strs[static_cast<int>(EmInfo::CERTI)];

        DB.add_data(e);
    }

};

#endif