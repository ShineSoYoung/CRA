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

void add(char* buf) {
    add_employee(buf);
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void del(char* buf) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void sch(char* buf) {
    printf("%s\n", sch_employee(buf));
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void mod(char* buf) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void manager(char* buf) {
    if (buf[0] == 'A' && buf[1] == 'D' && buf[2] == 'D') {
        /* ADD */
        add(buf);
    }
    else if (buf[0] == 'D' && buf[1] == 'E' && buf[2] == 'L') {
        /* DEL */
        del(buf);
    }
    else if (buf[0] == 'S' && buf[1] == 'C' && buf[2] == 'H') {
        /* SCH */
        sch(buf);
    }
    else if (buf[0] == 'M' && buf[1] == 'O' && buf[2] == 'D') {
        /* MOD */
        mod(buf);
    }
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
    readFile.open(inputFileName);
    printFile.open(outputFileName);
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            char buf[256] = { 0, };
            readFile.getline(buf, 256);
            manager(buf);

            printFile << buf << endl;
        }
    }

    return 0;
}
