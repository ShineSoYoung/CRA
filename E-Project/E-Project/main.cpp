#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "commandClassType.h"
#include "searchEngine.h"

#define DBG 1

using namespace std;

ifstream readFile;
ofstream printFile;

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