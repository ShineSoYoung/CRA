#ifndef __RESULT_PRINTER__
#define __RESULT_PRINTER__

#include <vector>
#include <string>
#include <algorithm>

const int MAX_NUM_OF_PRINT_ENTRY = 5;

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
        auto compareEmployeeNum = [](const Employee * e1, const Employee * e2)
        {
            string s1 = e1->employeeNum;
            string s2 = e2->employeeNum;

            int num1 = stoi(s1.substr(0, 2));
            int num2 = stoi(s2.substr(0, 2));

            if (num1 == num2)
                return s1 < s2;
            else
                return ((num1 + 100 - 69) % 100) < ((num2 + 100 - 69) % 100);
        };

        std::sort(findArray.begin(), findArray.end(), compareEmployeeNum);

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