﻿#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>

#include "EmployeeManager.h"
#include "commandClassType.h"
#include "ioManager.h"

using namespace std;

#if 0
int main(int argc, char* argv[])
{
    EmployeeManager* employeeManager = new EmployeeManager();
    employeeManager->setInputData(argv[1], argv[2]);
    employeeManager->run();

    return 0;
}
#endif