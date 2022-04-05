#include "EmployeeManager.h"

int main(int argc, char* argv[])
{
    EmployeeManager* employeeManager = new EmployeeManager();
    employeeManager->setIoFiles(argv[1], argv[2]);
    employeeManager->run();
    delete employeeManager;

    return 0;
}