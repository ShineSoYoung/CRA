#include "pch.h"
#include "../E-Project/main.cpp"
#include "../E-Project/ioManager.h"
#include "../E-Project/commandClassType.h"

TEST(IO_Test, InputTest) {
    char* tmp[20] = { "15123099", "VXIHXOTH JHOP", "CL3", "010-3112-2609", "19771211", "ADV" };
    vector<string> strs;
    for (int i = 0; tmp[i]; i++) {
        strs.push_back(tmp[i]);
    }

    CmdParam fake(CmdType::ADD, false, false, false, false, false, false, false, false, strs);
    Parcer* parcer = new Parcer();
    CmdParam cmd = parcer->parce("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    
    EXPECT_EQ(true, (cmd == fake));
}