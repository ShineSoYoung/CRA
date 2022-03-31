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

class Employee {
public:
    string employeeNum; //�����ȣ
    string name; //����
    string cl; //��°��ߴܰ�
    string phoneNum; //��ȭ��ȣ
    string birthday; //�������
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

    if (strs.size() != 10) //���� ������ ��
        return -1;

    for (int i = 1; i < strs.size(); i++) {
        if (strs[i] == " ") { //�ɼ� ��ĭ
            continue;
        }
        else if (strs[i] == "") { //null ����
            return -1;
        }
        else {
            employeeInfo[idx] = strs[i];
            idx++;
        }
    }

    for (int i = 0; i < list.size(); i++) {
        if (employeeInfo[0] == list[i]->employeeNum) {//�ߺ��Ǵ� ���
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


void add(char* buf) {
    add_employee(buf);
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
