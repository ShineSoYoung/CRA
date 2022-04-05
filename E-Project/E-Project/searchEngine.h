#ifndef __SEARCH_MACHINE__
#define __SEARCH_MACHINE__

#include <vector>
#include <string>

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
        return findArray;
    }
private:
    void selectCompareMachine(string column, vector<bool>  optionlist)
    {
        if ("employeeNum" == column)
        {
            compare = &employeeCompareMachine;
        }
        else if ("name" == column)
        {
            if (optionlist[0])
            {
                compare = &firstNameComparemachine;
            }
            else if (optionlist[1])
            {
                compare = &lastNameComparemachine;
            }
            else
            {
                compare = &nameComparemachine;
            }
        }
        else if ("cl" == column)
        {
            compare = &careerLevelComparemachine;
        }
        else if ("phoneNum" == column)
        {
            if (optionlist[2])
            {
                compare = &middlePhoneNumberComparemachine;
            }
            else if (optionlist[3])
            {
                compare = &lastPhoneNumberComparemachine;
            }
            else
            {
                compare = &phoneNumberComparemachine;
            }
        }
        else if ("birthday" == column)
        {
            if (optionlist[4])
            {
                compare = &birthdayYearComparemachine;
            }
            else if (optionlist[5])
            {
                compare = &birthdayMonthComparemachine;
            }
            else if (optionlist[6])
            {
                compare = &birthdayDayComparemachine;
            }
            else
            {
                compare = &birthdayComparemachine;
            }
        }
        else if ("certi" == column)
        {
            compare = &certiComparemachine;
        }
    }

    Comparemachine* compare;

    EmployeeNumberComparemachine employeeCompareMachine;

    NameComparemachine nameComparemachine;
    FirstNameComparemachine firstNameComparemachine;
    LastNameComparemachine lastNameComparemachine;

    CareerLevelComparemachine careerLevelComparemachine;

    PhoneNumberComparemachine phoneNumberComparemachine;
    MiddlePhoneNumberComparemachine middlePhoneNumberComparemachine;
    LastPhoneNumberComparemachine lastPhoneNumberComparemachine;

    BirthdayComparemachine birthdayComparemachine;
    BirthdayYearComparemachine birthdayYearComparemachine;
    BirthdayMonthComparemachine birthdayMonthComparemachine;
    BirthdayDayComparemachine birthdayDayComparemachine;

    CertiComparemachine certiComparemachine;
};

#endif