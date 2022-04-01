#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <string>

#include "commandClassType.h"
#include "searchEngine.h"

#define DBG 1

using namespace std;

string columnName[6] = { "employeeNum", "name", "cl", "phoneNum", "birthday", "certi" };

ifstream readFile;
ofstream printFile;

enum {
    EMPLOYEE_NUM,
    NAME,
    CARRER_LEVEL,
    PHONE_NUM,
    BIRTH_DAY,
    CERTI
};

map<string, int> columnMap{
    {"employeeNum", EMPLOYEE_NUM },
    {"name", NAME},
    {"cl", CARRER_LEVEL},
    {"phoneNum", PHONE_NUM},
    {"birthday", BIRTH_DAY},
    {"certi", CERTI},
};

vector<Employee*> list;

vector<string> split(string str, char Delimiter) {
    istringstream iss(str);
    string buffer;
    vector<string> result;

    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);
    }
    return result;
}


string sch_employee(CmdParam command)
{
    Employee employee;
    string result;
    string searchColumn, searchStr;
    int resultCnt = 0;
    int found = 0;
    int foundColumnNum;

    searchColumn = command.strs[0];
    searchStr = command.strs[1];

    for (int i = 0; i < list.size(); i++)
    {
        found = 0;
        for (int j = 0; j < 6; j++)
        {
            if (searchColumn == columnName[j])
            {
                found = 1;
                foundColumnNum = j;
                break;
            }
        }
        if (found == 1)
        {
            switch (foundColumnNum)
            {
            case 0:	// employeeNum
                if (list[i]->employeeNum == searchStr)
                {
                    resultCnt++;
                }
                break;
            case 1:	// name
                if (list[i]->name == searchStr)
                {
                    resultCnt++;
                }
                break;
            case 2:	// cl
                if (list[i]->cl == searchStr)
                {
                    resultCnt++;
                }
                break;
            case 3:	// phoneNum
                if (list[i]->phoneNum == searchStr)
                {
                    resultCnt++;
                }
                break;
            case 4:	// birthday
                if (list[i]->birthday == searchStr)
                {
                    resultCnt++;
                }
                break;
            case 5:	// certi
                if (list[i]->certi == searchStr)
                {
                    resultCnt++;
                }
                break;
            }
        }
    }

    result += "SCH,";

    if (resultCnt == 0)
    {
        result += "NONE";
    }
    else
    {
        result += to_string(resultCnt);
    }
    return result;
}

void modFoundEntry(vector<Employee*> findArray, string changeColumn, string changeValue)
{
    int targetColumnNum = columnMap.find(changeColumn)->second;
    for (Employee* em : findArray)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i]->employeeNum == em->employeeNum)
            {
                switch (targetColumnNum)
                {
                case NAME:
                    list[i]->name = changeValue;
                    break;
                case CARRER_LEVEL:
                    list[i]->cl = changeValue;
                    break;
                case PHONE_NUM:
                    list[i]->phoneNum = changeValue;
                    break;
                case BIRTH_DAY:
                    list[i]->birthday = changeValue;
                    break;
                case CERTI:
                    list[i]->certi = changeValue;
                    break;
                }
            }
        }
    }
}

string mod_empolyee(CmdParam command)
{
    string result = "";
    vector<Employee*> findArray;

    if ("employeeNum" == command.strs[0])
    {
        for (Employee* em : list)
        {
            if (em->employeeNum == command.strs[1])
            {
                findArray.push_back(em);
            }
        }
    }
    else if ("name" == command.strs[0])
    {
        if (command.firstNameFlag)
        {
            for (Employee* em : list)
            {
                vector<string> splitedName = split(em->name, ' ');
                if (splitedName[0] == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (command.lastNameFlag)
        {
            for (Employee* em : list)
            {
                vector<string> splitedName = split(em->name, ' ');
                if (splitedName[1] == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else
        {
            for (Employee* em : list)
            {
                if (em->name == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
    }

    else if ("cl" == command.strs[0])
    {
        for (Employee* em : list)
        {
            if (em->cl == command.strs[1])
            {
                findArray.push_back(em);
            }
        }
    }
    else if ("phoneNum" == command.strs[0])
    {
        if (command.midNumFlag)
        {
            for (Employee* em : list)
            {
                vector<string> splitedPhoneNum = split(em->phoneNum, '-');
                if (splitedPhoneNum[1] == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (command.lastNumFlag)
        {
            for (Employee* em : list)
            {
                vector<string> splitedPhoneNum = split(em->phoneNum, '-');
                if (splitedPhoneNum[2] == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else
        {
            for (Employee* em : list)
            {
                if (em->phoneNum == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
    }
    else if ("birthday" == command.strs[0])
    {
        if (command.yearFlag)
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(0, 4) == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (command.monthFlag)
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(4, 2) == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (command.dateFlag)
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(6, 2) == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
        else
        {
            for (Employee* em : list)
            {
                if (em->birthday == command.strs[1])
                {
                    findArray.push_back(em);
                }
            }
        }
    }
    else if ("certi" == command.strs[0])
    {
        for (Employee* em : list)
        {
            if (em->certi == command.strs[1])
            {
                findArray.push_back(em);
            }
        }
    }

    if (findArray.size() == 0)
    {
        result = "MOD,NONE\n";
    }
    else
    {
        if (command.printFlag)
        {
            for (Employee* em : findArray)
            {
                result += ("MOD," + em->employeeNum + "," + em->name + "," +
                    em->cl + "," + em->phoneNum + "," + em->birthday + "," +
                    em->certi + "\n");
            }
            modFoundEntry(findArray, command.strs[2], command.strs[3]);
        }
        else
        {
            modFoundEntry(findArray, command.strs[2], command.strs[3]);
            result += ("MOD," + to_string(findArray.size()) + "\n");
        }
    }

    return result;
}

void add(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void del(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void sch(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void mod(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

bool isValid(char* buf) {
    for (int i = 0; buf[i]; i++) {
        if (buf[i] == '/') return false;
    }
    return true;
}

void setFlag(string word, CmdParam& cmdParam) {
    if (word == "ADD") cmdParam.cmd = CmdType::ADD;
    else if (word == "DEL") cmdParam.cmd = CmdType::DEL;
    else if (word == "MOD") cmdParam.cmd = CmdType::MOD;
    else if (word == "SCH") cmdParam.cmd = CmdType::SCH;
    else if (word == "-p") cmdParam.printFlag = true;
    else if (word == "-f") cmdParam.firstNameFlag = true;
    else if (word == "-l") {
        cmdParam.lastNameFlag = true;
        cmdParam.lastNumFlag = true;
    } 
    else if (word == "-m") cmdParam.midNumFlag = true;
    else if (word == "-y") cmdParam.yearFlag = true;
    else if (word == "-m") cmdParam.monthFlag = true;
    else if (word == "-d") cmdParam.dateFlag = true;
    else if (word == " ") {
        ;
    } 
    else {
        cmdParam.strs.push_back(word);
        if (word == "name") cmdParam.lastNumFlag = false;
        else if (word == "phoneNum") cmdParam.lastNameFlag = false;
    }
}

CmdParam getCmdParam(char* buf) {
    CmdParam cmdParam;
    string tmp;
    for (int i = 0; buf[i]; i++) {
        if (buf[i] == ',') {
            setFlag(tmp, cmdParam);
            tmp.clear();
        }
        else tmp.push_back(buf[i]);
    }
    if (tmp.empty() == false) setFlag(tmp, cmdParam);

    return cmdParam;
}

void manager(char* buf) {
    if (isValid(buf) == false) {
        return;
    }

    CmdParam cmdParam = getCmdParam(buf);
    if (cmdParam.cmd == CmdType::ADD) {
        /* ADD */
        add(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::DEL) {
        /* DEL */
        del(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::SCH) {
        /* SCH */
        sch(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::MOD) {
        /* MOD */
        mod(cmdParam);
    }
}

void printFlie(string str) {
    printFile << str << endl;
}
#if 0
int main(int argc, char* argv[])
{
    string inputFileName;
    string outputFileName;
    if (DBG) {
        inputFileName = "input.txt";
        outputFileName = "output.txt";
    }
    else {
        inputFileName = argv[1];
        outputFileName = argv[2];
    }
    readFile.open(inputFileName, ios::in);
    printFile.open(outputFileName, ios::out);
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            char buf[256] = { 0, };
            readFile.getline(buf, 256);
            manager(buf);
        }
    }

    return 0;
}
#endif