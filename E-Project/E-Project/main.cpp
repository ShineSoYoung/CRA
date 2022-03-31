#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

ifstream readFile;
ofstream printFile;

class Employee {
public:
    string employeeNum; //사원번호
    string name; //성명
    string cl; //경력개발단계
    string phoneNum; //전화번호
    string birthday; //생년월일
    string certi; //CERTI
};

int main(int argc, char* argv[])
{
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    readFile.open(inputFileName);
    printFile.open(outputFileName);
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            char buf[256] = { 0, };
            readFile.getline(buf, 256);
            printFile << buf << endl;
        }
    }

    return 0;
}