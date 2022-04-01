#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <sstream>
#include <string>

#define DBG 1

using namespace std;

ifstream readFile;
ofstream printFile;


string columnName[6] = { "employeeNum", "name", "cl", "phoneNum", "birthday", "certi" };

enum class CmdType {
    ADD,
    DEL,
    SCH,
    MOD,
};

class CmdParam {
public:
    CmdType cmd;
    bool printFlag; // -p
    bool firstNameFlag; // -f
    bool lastNameFlag; // -l
    bool midNumFlag; // -m
    bool lastNumFlag; // -l
    bool yearFlag; // -y
    bool monthFlag; // -m
    bool dateFlag; // -d
    vector<string> strs;
};


class Employee {
public:
    string employeeNum; //사원번호
    string name; //성명
    string cl; //경력개발단계
    string phoneNum; //전화번호
    string birthday; //생년월일
    string certi; //CERTI
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

int add_employee(string s) {

    string employeeInfo[10];
    int idx = 0;

    vector<string> strs = split(s, ',');

    if (strs.size() != 10) //정상 데이터 수
        return -1;

    for (int i = 1; i < strs.size(); i++) {
        if (strs[i] == " ") { //옵션 빈칸
            continue;
        }
        else if (strs[i] == "") { //null 정보
            return -1;
        }
        else {
            employeeInfo[idx] = strs[i];
            idx++;
        }
    }

    for (int i = 0; i < list.size(); i++) {
        if (employeeInfo[0] == list[i]->employeeNum) {//중복되는 사번
            //cout << "ERROR::same employee number!!" << endl;
            return -1;
        }
    }

    Employee* e = new Employee();
    e->employeeNum = employeeInfo[0];
    e->name = employeeInfo[1];
    e->cl = employeeInfo[2];
    e->phoneNum = employeeInfo[3];
    e->birthday = employeeInfo[4];
    e->certi = employeeInfo[5];

    list.push_back(e);

    return 0;
}

string sch_employee(string s)
{
    Employee employee;
    string result;
    string searchColumn, searchStr;
    int resultCnt = 0;
    int idx = 0;
    int found = 0;
    int foundColumnNum;

    vector<string> strs = split(s, ',');

    searchColumn = strs[4];
    searchStr = strs[5];

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
    result += '\0';
    cout << result;
    return result;
}

const int COMMAND_TYPE = 0;
const int COMMAND_OPTION_1 = 1;
const int COMMAND_OPTION_2 = 2;
const int COMMAND_OPTION_3 = 3;
const int COMMAND_COLUMN = 4;
const int COMMAND_VALUE = 5;

void deleteFoundEntry(vector<Employee*> findArray)
{
    for (Employee* em : findArray)
    {
        for (vector<Employee*>::iterator it = list.begin(); it != list.end();)
        {
            if ((*it)->employeeNum == em->employeeNum)
            {
                it = list.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

string deleteEmpolyee(string command)
{
    string result = "";
    bool printoption = false;
    vector<Employee*> findArray;
    vector<string> parsedCommand = split(command, ',');
    if (parsedCommand[COMMAND_TYPE] != "DEL")
    {
        result += "FAIL :: command error";
    }
    if (parsedCommand[COMMAND_OPTION_1] == "-p")
    {
        printoption = true;
    }

    if ("name" == parsedCommand[COMMAND_COLUMN])
    {
        if ("-f" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                vector<string> splitedName = split(em->name, ' ');
                if (splitedName[0] == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if ("-l" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                vector<string> splitedName = split(em->name, ' ');
                if (splitedName[1] == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (" " == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->name == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
    }
    else if ("cl" == parsedCommand[COMMAND_COLUMN])
    {
        for (Employee* em : list)
        {
            if (em->cl == parsedCommand[COMMAND_VALUE])
            {
                findArray.push_back(em);
            }
        }
    }
    else if ("phoneNum" == parsedCommand[COMMAND_COLUMN])
    {
        if ("-m" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                vector<string> splitedPhoneNum = split(em->phoneNum, '-');
                if (splitedPhoneNum[1] == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if ("-l" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                vector<string> splitedPhoneNum = split(em->phoneNum, '-');
                if (splitedPhoneNum[2] == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (" " == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->phoneNum == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
    }
    else if ("birthday" == parsedCommand[COMMAND_COLUMN])
    {
        if ("-y" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(0, 4) == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if ("-m" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(4, 2) == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if ("-d" == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->birthday.substr(6, 2) == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
        else if (" " == parsedCommand[COMMAND_OPTION_2])
        {
            for (Employee* em : list)
            {
                if (em->birthday == parsedCommand[COMMAND_VALUE])
                {
                    findArray.push_back(em);
                }
            }
        }
    }
  
    if (findArray.size() == 0)
    {
        result = "DEL,NONE\n";
    }
    else
    {
        if (printoption)
        {
            for (Employee* em : findArray)
            {
                result += ("DEL," + em->employeeNum + "," + em->name + "," +
                    em->cl + "," + em->phoneNum + "," + em->birthday + "," +
                    em->certi + "\n");
            }
            deleteFoundEntry(findArray);
        }
        else
        {
            deleteFoundEntry(findArray);
            result += ("DEL," + to_string(findArray.size()) + "\n");
        }
    }

    return result;
}

void add(CmdParam cmdParam) {
    //add_employee(buf);
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void del(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}


void sch(char* buf) {
    printf("%s\n", sch_employee(buf));
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