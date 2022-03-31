#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

enum
{
	EMPLOYEE_NUM,
	NAME,
	CARRER_LEVEL,
	PHONE_NUM,
	BIRTH_DAY,
	CERTI
};

map<string, int> columnMap{
	{"employeeNum", EMPLOYEE_NUM },
	{"name", NAME},
	{"cl", CARRER_LEVEL},
	{"phoneNum", PHONE_NUM},
	{"birthday", BIRTH_DAY},
	{"certi", CERTI},
};

class Employee {
public:
	string employeeNum;
	string name;
	string cl;
	string phoneNum;
	string birthday;
	string certi;

	void printEmployee() {
		cout << "사번:" << employeeNum  << endl;
		cout << "이름:" << name << endl;
		cout << "직급:" << cl << endl;
		cout << "번호:" << phoneNum << endl;
		cout << "생일:" << birthday << endl;
		cout << "등급:" << certi << endl;
		puts("-----------------------\n");
	}
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

void changeColumnValue(Employee* targetRecord,string changeColumn, string changeStr)
{
	int targetColumnNum = columnMap.find(changeColumn)->second;
	switch (targetColumnNum)
	{
	case EMPLOYEE_NUM:
		targetRecord->employeeNum = changeStr;
		break;
	case NAME:
		targetRecord->name = changeStr;
		break;
	case CARRER_LEVEL:
		targetRecord->cl = changeStr;
		break;
	case PHONE_NUM:
		targetRecord->phoneNum = changeStr;
		break;
	case BIRTH_DAY:
		targetRecord->birthday = changeStr;
		break;
	case CERTI:
		targetRecord->certi = changeStr;
		break;
	}
}

string mod(string cmd)
{
	string result;
	int resultCnt = 0;
	string searchColumn, searchStr, changeColumn, changeStr;
	
	vector<string> param = split(cmd, ',');

	searchColumn = param[4];
	searchStr = param[5];
	changeColumn = param[6];
	changeStr = param[7];

	for (int i = 0; i < list.size(); i++)
	{
		switch (columnMap.find(searchColumn)->second)
		{
		case EMPLOYEE_NUM:
			if (list[i]->employeeNum == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		case NAME:
			if (list[i]->name == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		case CARRER_LEVEL:
			if (list[i]->cl == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		case PHONE_NUM:
			if (list[i]->phoneNum == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		case BIRTH_DAY:
			if (list[i]->birthday == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		case CERTI:
			if (list[i]->certi == searchStr)
			{
				changeColumnValue(list[i], changeColumn, changeStr);
				resultCnt++;
			}
			break;
		}
	}

	result += "MOD,";

	if (resultCnt == 0)
	{
		result += "NONE";
	}
	else
	{
		result += to_string(resultCnt);
	}

	result += '\0';
	return result;
}

#if 0
int main()
{
	Employee e0 = { "18050301","KYUMOK KIM","CL2","010-9777-6055","19980906","PRO" };
	Employee e1 = { "18050302","SEUNGWOO HYUN","CL3","010-1111-2233","19900302","PRO" };
	
	list.push_back(&e0);
	list.push_back(&e1);
	
	for (auto& e : list)
	{
		e->printEmployee();
	}

	cout << mod("MOD, , , ,employeeNum,18050301,phoneNum,010-0000-0000") << endl;
	cout << mod("MOD, , , ,name,SEUNGWOO HYUN,certi,EX") << endl;

	puts("\n---변경 후---");
	for (auto& e : list)
	{
		e->printEmployee();
	}

	return 0;
}
#endif