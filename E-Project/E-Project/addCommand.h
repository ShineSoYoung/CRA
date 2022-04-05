
#ifndef __ADD_COMMAND__
#define __ADD_COMMAND__

#include "parcedCommandType.h"
#include "command.h"

const int validStringNum = 6;

class addCommand : public NoneOptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, ParcedCmd command) override
    {
        if (isValidAddCmd(command) == false)
            return "FAIL";

        if (isSameEmployeeNum(DB, command.strs[0]) == true)
            return "FAIL";

        addData(DB, command);
        return "";
    }
private:

    bool isValidAddCmd(ParcedCmd command) {
        int idx = 0;
        for (int i = 0; i < command.strs.size(); i++) {

            if (command.strs[i] == "") { //null 정보
                return false;
            }
            else {
                idx++;
            }
        }

        if (idx != validStringNum) {
            return false;
        }

        return true;
    }

    bool isSameEmployeeNum(datamanager& DB, string employeeNum)
    {
        vector<bool> dummyOptionList;
        vector<Employee*> findArray = DB.search_data("employeeNum", employeeNum, dummyOptionList);
        return (0 < findArray.size());
    }

    void addData(datamanager& DB, ParcedCmd command)
    {
        Employee e;
        e.employeeNum = command.strs[0];
        e.name = command.strs[1];
        e.cl = command.strs[2];
        e.phoneNum = command.strs[3];
        e.birthday = command.strs[4];
        e.certi = command.strs[5];

        DB.add_data(e);
    }

};

#endif