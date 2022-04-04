#ifndef __DATAMANAGER__
#define __DATAMANAGER__

#include <vector>
#include <string>
#include <map>
#include <malloc.h>

#include "searchEngine.h"

const int MINIMUM_ENTRY_COUNT = 100000;
const int EXTRA_ROOM_ENTRY_COUNT = 50000;

enum {
    EMPLOYEE_NUM = 0,
    NAME,
    CARRER_LEVEL,
    PHONE_NUM,
    BIRTH_DAY,
    CERTI
};

union unionEmployee{
    Employee structEmployee;
    string stringArray[6];
};

class datamanager
{
public:
    datamanager()
    {
        employeeList.reserve(MINIMUM_ENTRY_COUNT + EXTRA_ROOM_ENTRY_COUNT);
    }

    void add_data(Employee em)
    {
        Employee* e = new Employee();
        e->employeeNum = em.employeeNum;
        e->name = em.name;
        e->cl = em.cl;
        e->phoneNum = em.phoneNum;
        e->birthday = em.birthday;
        e->certi = em.certi;

        employeeList.push_back(e);
    }
    vector<Employee*> search_data(string column, string value, vector<bool> optionlist)
    {
        return searchengine.search(employeeList, column, value, optionlist);
    }
    void modify_data(vector<Employee*> modifyingdata, string column, string value)
    {
        map<string, int> columnMap{
            {"employeeNum", EMPLOYEE_NUM },
            {"name", NAME},
            {"cl", CARRER_LEVEL},
            {"phoneNum", PHONE_NUM},
            {"birthday", BIRTH_DAY},
            {"certi", CERTI},
        };
        int targetColumnNum = columnMap.find(column)->second;
        for (Employee* em : modifyingdata)
        {
            unionEmployee* unionEm = reinterpret_cast<unionEmployee*>(em);
            unionEm->stringArray[targetColumnNum] = value;
        }
    }
    void delete_data(vector<Employee*> deletingdata)
    {
        for (Employee* em : deletingdata)
        {
            for (vector<Employee*>::iterator it = employeeList.begin(); it != employeeList.end();)
            {
                if ((*it)->employeeNum == em->employeeNum)
                {
                    delete (*it);
                    it = employeeList.erase(it);
                }
                else ++it;
            }
        }
    }
private:
    vector<Employee*> employeeList;
    searchEngine searchengine;
};

#endif