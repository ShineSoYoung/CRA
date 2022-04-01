#ifndef __SEARCH_MACHINE__
#define __SEARCH_MACHINE__

#include <vector>
#include <string>

#include "commandClassType.h"
#include "compareMachine.h"

class searchEngine
{
public:
    vector<Employee*> search(vector<Employee*> list, string column, string value, vector<bool> optionlist)
    {
        selectCompareMachine(column, optionlist);
        vector<Employee*> findArray;
        for (Employee* em : list)
        {
            if (compare->isSatifiedEntry(em, value)) findArray.push_back(em);
        }
        releaseCompareMachine();
        return findArray;
    }
private:
    void selectCompareMachine(string column, vector<bool>  optionlist)
    {
        if ("employeeNum" == column)
        {
            compare = new ComparemachineWithEmployeeNumber();
        }
        else if ("name" == column)
        {
            if (optionlist[0])
            {
                compare = new ComparemachineWithFirstName();
            }
            else if (optionlist[1])
            {
                compare = new ComparemachineWithLastName();
            }
            else
            {
                compare = new ComparemachineWithName();
            }
        }
        else if ("cl" == column)
        {
            compare = new ComparemachineWithCL();
        }
        else if ("phoneNum" == column)
        {
            if (optionlist[2])
            {
                compare = new ComparemachineWithPhoneNumberOnlyMiddle();
            }
            else if (optionlist[3])
            {
                compare = new ComparemachineWithPhoneNumberOnlyLast();
            }
            else
            {
                compare = new ComparemachineWithPhoneNumber();
            }
        }
        else if ("birthday" == column)
        {
            if (optionlist[4])
            {
                compare = new ComparemachineWithBirthdayOnlyYear();
            }
            else if (optionlist[5])
            {
                compare = new ComparemachineWithBirthdayOnlyMonth();
            }
            else if (optionlist[6])
            {
                compare = new ComparemachineWithBirthdayOnlyDay();
            }
            else
            {
                compare = new ComparemachineWithBirthday();
            }
        }
        else if ("certi" == column)
        {
            compare = new ComparemachineWithCerti();
        }
    }

    void releaseCompareMachine()
    {
        delete compare;
    }

    Comparemachine* compare;
};

#endif