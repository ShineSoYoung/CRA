#include "EmployeeManager.h"

const int ARGC_LIMIT_CNT = 3;

int main(int argc, char* argv[])
{
    if (argc > ARGC_LIMIT_CNT) {
        exit(EXIT_FAILURE);
    }

    EmployeeManager* employeeManager = new EmployeeManager();
    employeeManager->setIoFiles(argv[1], argv[2]);
    employeeManager->run();
    delete employeeManager;

    return 0;
}