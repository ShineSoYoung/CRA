#ifndef __COMMAND_CLASS_TYPE__
#define __COMMAND_CLASS_TYPE__

#include <vector>
#include <string>

using namespace std;

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

#endif