#include <stdio.h>
#include <iostream>
#include <fstream>

#define DBG 1

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

void add(char* buf) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void del(char* buf) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void sch(char* buf) {
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