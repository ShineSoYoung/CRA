
#ifndef __ADD_COMMAND__
#define __ADD_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

const int validStringNum = 6;

class addCommand : public NoneOptionalCommand
{
public:
    virtual bool checkCommandIsValid(datamanager& DB, const ParsedCmd command) override
    {
        return ((isValidAddCmd(command) == true) &&
            (isSameEmployeeNum(DB, command.strs[static_cast<int>(EmInfo::EMPLOYEE_NUM)]) == false));
    }
    virtual vector<Employee*> getTargetEntryVector(datamanager& DB, const ParsedCmd command)
    {
        Employee* em = new Employee();
        vector<Employee*> result;
        em->employeeNum = command.strs[static_cast<int>(EmInfo::EMPLOYEE_NUM)];
        em->name = command.strs[static_cast<int>(EmInfo::NAME)];
        em->cl = command.strs[static_cast<int>(EmInfo::CARRER_LEVEL)];
        em->phoneNum = command.strs[static_cast<int>(EmInfo::PHONE_NUM)];
        em->birthday = command.strs[static_cast<int>(EmInfo::BIRTH_DAY)];
        em->certi = command.strs[static_cast<int>(EmInfo::CERTI)];
        return result;
    }
    virtual string processCommand(datamanager& DB, vector<Employee*> targetVector) override
    {
        addData(DB, targetVector);
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

    void addData(datamanager& DB, vector<Employee*> targetVector)
    {
        Employee e;
        e.employeeNum = targetVector[0]->employeeNum;
        e.name = targetVector[0]->name;
        e.cl = targetVector[0]->cl;
        e.phoneNum = targetVector[0]->phoneNum;
        e.birthday = targetVector[0]->birthday;
        e.certi = targetVector[0]->certi;
        DB.add_data(e);

        delete targetVector[0];
    }

};

#endif