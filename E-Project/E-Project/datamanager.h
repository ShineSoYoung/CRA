#ifndef __DATAMANAGER__
#define __DATAMANAGER__

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#include "searchEngine.h"

using namespace stdext;

typedef unordered_multimap<string, Employee*> EmployeeHashMap;
typedef pair<EmployeeHashMap::iterator, EmployeeHashMap::iterator> EmployeeRange;

const int MINIMUM_ENTRY_COUNT = 100000;
const int EXTRA_ROOM_ENTRY_COUNT = 50000;

class datamanager
{
public:
    datamanager()
    {
        employeeList.reserve(MINIMUM_ENTRY_COUNT + EXTRA_ROOM_ENTRY_COUNT);
        searchengine = searchEngine();
    }

    void add_data(const Employee em)
    {
        Employee* e = new Employee();
        e->employeeNum = em.employeeNum;
        e->name = em.name;
        e->cl = em.cl;
        e->phoneNum = em.phoneNum;
        e->birthday = em.birthday;
        e->certi = em.certi;
        addAllHashMap(e);
        employeeList.push_back(e);
    }
    vector<Employee*> search_data(const string column, const string value, const optionList optionlist)
    {
        vector<Employee*> result;
        EmployeeHashMap hashmap = selectHashMap(column, value, optionlist);
        EmployeeRange range = hashmap.equal_range(value);
        while (range.first != range.second)
        {
            if (!((*range.first).second->deleted)) result.push_back((*range.first).second);
            ++range.first;
        }
        return result;
    }
    void modify_data(vector<Employee*> modifyingdata, const string column, const string value)
    {
        map<string, EmInfo> columnMap{
            {"employeeNum", EmInfo::EMPLOYEE_NUM },
            {"name", EmInfo::NAME},
            {"cl", EmInfo::CARRER_LEVEL},
            {"phoneNum", EmInfo::PHONE_NUM},
            {"birthday", EmInfo::BIRTH_DAY},
            {"certi", EmInfo::CERTI},
        };
        int targetColumnNum = (int)columnMap.find(column)->second;
        for (Employee* em : modifyingdata)
        {
            string* emStringArray = reinterpret_cast<string*>(em);
            emStringArray[targetColumnNum] = value;
            add_data(*em);
            em->deleted = true;
        }
    }
    void delete_data(vector<Employee*> deletingdata)
    {
        for (Employee* em : deletingdata)
        {
            em->deleted = true;
        }
    }
private:
    void addAllHashMap(Employee* em)
    {
        employeeNumberHashMap.insert(EmployeeHashMap::value_type(em->employeeNum, em));
        NameHashMap.insert(EmployeeHashMap::value_type(em->name, em));
        FirstNameHashMap.insert(EmployeeHashMap::value_type(em->name.substr(0, em->name.find(' ')), em));
        LastNameHashMap.insert(EmployeeHashMap::value_type(em->name.substr(em->name.find(' ') + 1, em->name.length() - em->name.find(' ')), em));
        CareerLevelHashMap.insert(EmployeeHashMap::value_type(em->cl, em));
        PhoneNumberHashMap.insert(EmployeeHashMap::value_type(em->phoneNum, em));
        MiddlePhoneNumberHashMap.insert(EmployeeHashMap::value_type(em->phoneNum.substr(4, 4), em));
        LastPhoneNumberHashMap.insert(EmployeeHashMap::value_type(em->phoneNum.substr(9, 4), em));
        BirthdayHashMap.insert(EmployeeHashMap::value_type(em->birthday, em));
        BirthdayYearHashMap.insert(EmployeeHashMap::value_type(em->birthday.substr(0, 4), em));
        BirthdayMonthHashMap.insert(EmployeeHashMap::value_type(em->birthday.substr(4, 2), em));
        BirthdayDayHashMap.insert(EmployeeHashMap::value_type(em->birthday.substr(6, 2), em));
        CertiHashMap.insert(EmployeeHashMap::value_type(em->certi, em));
    }

    EmployeeHashMap& selectHashMap(const string column, const string value, const optionList optionlist)
    {
        if ("employeeNum" == column)
        {
            return employeeNumberHashMap;
        }
        else if ("name" == column)
        {
            if (optionlist.searchforFirstName)
            {
                return FirstNameHashMap;
            }
            else if (optionlist.searchforLastName)
            {
                return LastNameHashMap;
            }
            else
            {
                return NameHashMap;
            }
        }
        else if ("cl" == column)
        {
            return CareerLevelHashMap;
        }
        else if ("phoneNum" == column)
        {
            if (optionlist.searchforMiddlePhoneNumber)
            {
                return MiddlePhoneNumberHashMap;
            }
            else if (optionlist.searchforLastPhoneNumber)
            {
                return LastPhoneNumberHashMap;
            }
            else
            {
                return PhoneNumberHashMap;
            }
        }
        else if ("birthday" == column)
        {
            if (optionlist.searchforBirthdayYear)
            {
                return BirthdayYearHashMap;
            }
            else if (optionlist.searchforBirthdayMonth)
            {
                return BirthdayMonthHashMap;
            }
            else if (optionlist.searchforBirthdayDay)
            {
                return BirthdayDayHashMap;
            }
            else
            {
                return BirthdayHashMap;
            }
        }
        else if ("certi" == column)
        {
            return CertiHashMap;
        }
    }

    vector<Employee*> employeeList;
    searchEngine searchengine;

    EmployeeHashMap employeeNumberHashMap;
    EmployeeHashMap NameHashMap;
    EmployeeHashMap FirstNameHashMap;
    EmployeeHashMap LastNameHashMap;
    EmployeeHashMap CareerLevelHashMap;
    EmployeeHashMap PhoneNumberHashMap;
    EmployeeHashMap MiddlePhoneNumberHashMap;
    EmployeeHashMap LastPhoneNumberHashMap;
    EmployeeHashMap BirthdayHashMap;
    EmployeeHashMap BirthdayYearHashMap;
    EmployeeHashMap BirthdayMonthHashMap;
    EmployeeHashMap BirthdayDayHashMap;
    EmployeeHashMap CertiHashMap;
};

#endif