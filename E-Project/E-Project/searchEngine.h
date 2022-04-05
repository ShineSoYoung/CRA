#ifndef __SEARCH_MACHINE__
#define __SEARCH_MACHINE__

#include <vector>
#include <string>

#include "compareMachine.h"

class searchEngine
{
public:
    vector<Employee*> search(vector<Employee*> list, string column, string value, const optionList optionlist)
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
    void selectCompareMachine(string column, const optionList optionlist)
    {
        if ("employeeNum" == column)
        {
            compare = new ComparemachineWithEmployeeNumber();
        }
        else if ("name" == column)
        {
            if (optionlist.searchforFirstName)
            {
                compare = new ComparemachineWithFirstName();
            }
            else if (optionlist.searchforLastName)
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
            if (optionlist.searchforMiddlePhoneNumber)
            {
                compare = new ComparemachineWithPhoneNumberOnlyMiddle();
            }
            else if (optionlist.searchforLastPhoneNumber)
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
            if (optionlist.searchforBirthdayYear)
            {
                compare = new ComparemachineWithBirthdayOnlyYear();
            }
            else if (optionlist.searchforBirthdayMonth)
            {
                compare = new ComparemachineWithBirthdayOnlyMonth();
            }
            else if (optionlist.searchforBirthdayDay)
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