#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

ifstream readFile;
ofstream printFile;

class Employee {
public:
    string employeeNum; //�����ȣ
    string name; //����
    string cl; //��°��ߴܰ�
    string phoneNum; //��ȭ��ȣ
    string birthday; //�������
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