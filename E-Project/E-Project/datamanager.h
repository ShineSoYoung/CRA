#ifndef __DATAMANAGER__
#define __DATAMANAGER__

#include <vector>
#include <string>
#include <map>
#include <malloc.h>

#include "searchEngine.h"

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

        employeeList.push_back(e);
    }
    vector<Employee*> search_data(const string column, const string value, const optionList optionlist)
    {
        return searchengine.search(employeeList, column, value, optionlist);
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