#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>

#include "EmployeeManager.h"
#include "parcedCommandType.h"
#include "ioManager.h"

using namespace std;

int main(int argc, char* argv[])
{
    EmployeeManager* employeeManager = new EmployeeManager();
    employeeManager->setIoFiles(argv[1], argv[2]);
    employeeManager->run();
    delete employeeManager;

    return 0;
}