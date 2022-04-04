#ifndef __MODIFY_COMMAND__
#define __MODIFY_COMMAND__

#include "commandClassType.h"
#include "command.h"

class modifyCommand : public command
{
public:
    virtual string processCommand(datamanager& DB, CmdParam command) override
    {
        vector<Employee*> findArray = DB.search_data(command.strs[0], command.strs[1], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("MOD,", findArray);
        DB.modify_data(findArray, command.strs[2], command.strs[3]);
        releasePrinter();
        return result;
    }

private:
};

#endif