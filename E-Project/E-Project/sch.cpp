#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


string columnName[6] = { "employeeNum", "name", "cl", "phoneNum", "birthday", "certi" };

class Employee {
public:
	string employeeNum;
	string name;
	string cl;
	string phoneNum;
	string birthday;
	string certi;
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

string sch(string s)
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
	return result;
}

int main()
{
	//add ºÎºÐ ´ëÃ¼
	Employee classEmployee0 = { "1700000","È« ±æµ¿","CL2","010-1111-2222","19900302","ADV" };
	Employee classEmployee1 = { "1700001","È« ±æÈÆ","CL3","010-1111-2233","19900302","PRO" };
	Employee classEmployee2 = { "1700002","È« ±æ¼ø","CL2","010-1111-2244","19900306","ADV" };

	list.push_back(&classEmployee0);
	list.push_back(&classEmployee1);
	list.push_back(&classEmployee2);

	cout << "testing...\n";
	cout << sch("SCH,,,,birthday,19900302") << endl;

	return 0;
}