
#ifndef __ADD_COMMAND__
#define __ADD_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

const int validStringNum = 6;

class addCommand : public NoneOptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        if ((isValidAddCmd(command) == true) &&
            (isSameEmployeeNum(DB, command.strs[static_cast<int>(EmInfo::EMPLOYEE_NUM)]) == false))
            addData(DB, command);        
        return "";
    }
private:

    bool isValidAddCmd(const ParsedCmd command) {
        if (command.strs.size() != validStringNum)
            return false;
        for (string data : command.strs) {
            if (true == isEmptyData(data)) {
                return false;
            }
        }

        return true;
    }

    bool isEmptyData(string data)
    {
        return data == "";
    }

    bool isSameEmployeeNum(datamanager& DB, string employeeNum)
    {
        vector<bool> dummyOptionList;
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