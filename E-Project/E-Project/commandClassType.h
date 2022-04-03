#ifndef __COMMAND_CLASS_TYPE__
#define __COMMAND_CLASS_TYPE__

#include <vector>
#include <string>

using namespace std;

enum class CmdType {
    UNKHOWN,
    ADD,
    DEL,
    SCH,
    MOD,
};

class CmdParam {
public:

    CmdParam(CmdType cmd, bool printFlag, bool firstNameFlag, bool lastNameFlag, 
        bool midNumFlag, bool lastNumFlag, bool yearFlag, bool monthFlag, bool dateFlag, vector<string> strs) {
        this->cmd = cmd;
        this->printFlag = printFlag;
        this->firstNameFlag = firstNameFlag;
        this->lastNameFlag = lastNameFlag;
        this->midNumFlag = midNumFlag;
        this->lastNumFlag = lastNumFlag;
        this->yearFlag = yearFlag;
        this->monthFlag = monthFlag;
        this->dateFlag = dateFlag;
        this->strs = strs;
    }

    CmdParam() {
        cmd = CmdType::UNKHOWN;
        printFlag = false;
        firstNameFlag = false;
        lastNameFlag = false;
        midNumFlag = false;
        lastNumFlag = false;
        yearFlag = false;
        monthFlag = false;
        dateFlag = false;
        strs.clear();
    }
    void set(CmdType _cmd, bool pf, bool fstName, bool lastName,
        bool midNum, bool lastNum, bool y, bool m, bool d,
        vector<string> _strs) {
        cmd = _cmd, printFlag = pf, firstNameFlag = fstName, lastName = lastName,
            midNumFlag = midNum, lastNumFlag = lastName,
            yearFlag = y, monthFlag = m, dateFlag = d,
            strs = _strs;
    }

    bool operator == (const CmdParam& comp) {
        if (cmd != comp.cmd) return false;
        else if (printFlag != comp.printFlag) return false;
        else if (firstNameFlag != comp.firstNameFlag) return false;
        else if (lastNameFlag != comp.lastNameFlag) return false;
        else if (midNumFlag != comp.midNumFlag) return false;
        else if (lastNumFlag != comp.lastNumFlag) return false;
        else if (yearFlag != comp.yearFlag) return false;
        else if (monthFlag != comp.monthFlag) return false;
        else if (dateFlag != comp.dateFlag) return false;
        else if (strs.size() != comp.strs.size()) return false;
        for (int i = 0; i < strs.size(); i++) {
            if (strs.at(i) != comp.strs.at(i)) return false;
        }
        return true;
    }

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