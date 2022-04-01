
#ifndef __ADD_COMMAND__
#define __ADD_COMMAND__

#include "commandClassType.h"

class addCommand
{
public:
    int add_employee(vector<Employee*>& list, CmdParam command)
    {
        if (isValidAddCmd(command) == false)
            return -1;

        if (isSameEmployeeNum(list, command.strs[0]) == true)
            return -1;

        addData(list, command);

        return 0;
    }

private:

    bool isValidAddCmd(CmdParam command) {
        int idx = 0;
        for (int i = 0; i < command.strs.size(); i++) {

            if (command.strs[i] == "") { //null 정보
                return false;
            }
            else {
                idx++;
            }
        }

        if (idx != 6) {
            return false;
        }

        return true;
    }

    bool isSameEmployeeNum(vector<Employee*>& list, string employeeNum)
    {
        for (int i = 0; i < list.size(); i++) {
            if (employeeNum == list[i]->employeeNum) {//중복되는 사번
                return true;
            }
        }
        return false;
    }

    void addData(vector<Employee*>& list, CmdParam command)
    {
        Employee* e = new Employee();
        e->employeeNum = command.strs[0];
        e->name = command.strs[1];
        e->cl = command.strs[2];
        e->phoneNum = command.strs[3];
        e->birthday = command.strs[4];
        e->certi = command.strs[5];

        list.push_back(e);
    }

};

#endif