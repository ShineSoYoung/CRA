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


void add(CmdParam cmdParam) {
    //add_employee(buf);
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
    return true;
}

CmdParam getCmdParam(char* buf) {
    CmdParam cmdParam;
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
