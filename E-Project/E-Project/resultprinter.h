#ifndef __RESULT_PRINTER__
#define __RESULT_PRINTER__

#include <vector>
#include <string>

#include "commandClassType.h"

class resultPrinter
{
public:
    virtual string printFinalResult(string cmd, vector<Employee*> findArray) = 0;
private:

};

class defaultResultPrinter : public resultPrinter
{
public:
    virtual string printFinalResult(string cmd, vector<Employee*> findArray) override
    {
        return (cmd + to_string(findArray.size()) + "\n");
    }
private:
};

class detailResultPrinter : public resultPrinter
{
public:
    virtual string printFinalResult(string cmd, vector<Employee*> findArray) override
    {
        string result = "";
        for (Employee* em : findArray)
        {
            result += (cmd + em->employeeNum + "," + em->name + "," +
                em->cl + "," + em->phoneNum + "," + em->birthday + "," +
                em->certi + "\n");
        }
        return result;
    }
private:
};

class noResultPrinter : public resultPrinter
{
public:
    virtual string printFinalResult(string cmd, vector<Employee*> findArray) override
    {
        return cmd + "NONE\n";
    }
private:

};

#endif