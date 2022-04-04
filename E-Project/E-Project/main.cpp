#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>

#include "commandClassType.h"
#include "searchEngine.h"
#include "ioManager.h"

using namespace std;

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


void add(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void del(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void sch(CmdParam cmdParam) {
    
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void mod(CmdParam cmdParam) {
    printf("%s(line:%d)\n", __func__, __LINE__);
}

void manager(CmdParam cmdParam) {
    if (cmdParam.cmd == CmdType::ADD) {
        /* ADD */
        add(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::DEL) {
        /* DEL */
        del(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::SCH) {
        /* SCH */
        sch(cmdParam);
    }
    else if (cmdParam.cmd == CmdType::MOD) {
        /* MOD */
        mod(cmdParam);
    }
}

#if 1
int main(int argc, char* argv[])
{
    IoManager* io = new IoManager();
    io->openIoFile(argv[1], argv[2]);
    
    if (io->isInputFileOpen()) {
        while (!io->isInputFileEnd()) {
            CmdParam cmdParam = io->getInput();
            manager(cmdParam);
        }
    }

    return 0;
}
#endif