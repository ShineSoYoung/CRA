#ifndef __RESULT_PRINTER__
#define __RESULT_PRINTER__

#include <vector>
#include <string>
#include <algorithm>

const int MAX_NUM_OF_PRINT_ENTRY = 5;
const int ENUM_OFFSET = 31;
const int ENUM_CYCLE = 100;
#define ENUM_ORDER(x) ((x + ENUM_OFFSET) % ENUM_CYCLE)

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
        sortResult(findArray);

        for (int index = 0; index < MAX_NUM_OF_PRINT_ENTRY && index < findArray.size(); index++)
        {
            Employee* em = findArray[index];
            result += (cmd + em->employeeNum + "," + em->name + "," +
                em->cl + "," + em->phoneNum + "," + em->birthday + "," +
                em->certi + "\n");
        }

        return result;
    }
private:

    void sortResult(vector<Employee*>& findArray)
    {
        auto compareEmployeeNum = [](const Employee* e1, const Employee* e2)
        {
            int num1 = stoi(e1->employeeNum.substr(0, 2));
            int num2 = stoi(e2->employeeNum.substr(0, 2));

            if (num1 == num2)
                return e1->employeeNum < e2->employeeNum;

            return ENUM_ORDER(num1) < ENUM_ORDER(num2);
        };

        std::sort(findArray.begin(), findArray.end(), compareEmployeeNum);
    }

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