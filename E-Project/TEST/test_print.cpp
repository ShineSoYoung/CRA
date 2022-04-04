
#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

TEST(IO_Test, InputTest_getCmdParam) {
    CmdParam cmd;
    CmdParam fake;
    Parser parser;
    vector<string> strs;
    cmd = parser.parse("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    strs.push_back("15123099");
    strs.push_back("VXIHXOTH JHOP");
    strs.push_back("CL3");
    strs.push_back("010-3112-2609");
    strs.push_back("19771211");
    strs.push_back("ADV");
    fake = { CmdType::ADD, false, false, false, false, false, false, false, false, strs };
    EXPECT_EQ(true, (cmd == fake));
}


class PrintTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "15123099","VXIHXOTH" "JHOP","CL3","010-3112-2609","19771211","ADV" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "17112609", "FB NTAWR", "CL4", "010-5645-6122", "19861203", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "18115040", "TTETHU HBO","CL3","010-4581-2050","20080718", "ADV" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "88114052", "NQ LVARW","CL4","010-4528-3059","19911021", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "19129568", "SRERLALH HMEF", "CL2","010-3091-9521","19640910", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "17111236", "VSID TVO", "CL1","010-3669-1077","20120718", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "18117906", "TWU QSOLT", "CL4","010-6672-7186","20030413", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "08123556", "WN XV", "CL1","010-7986-5047","20100614", "PRO" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "02117175", "SBILHUT LDEXRI", "CL4","010-2814-1699", "19950704","ADV" } });
        addCmd.processCommand(DB, CmdParam{ CmdType::ADD,false,false,false,false,true,false,false,false,{  "03113260", "HH LTUPF","CL2", "010-5798-5383", "19791018", "PRO" } });
    }
    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,15123099"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17112609"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18115040"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,88114052"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,19129568"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17111236"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18117906"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,08123556"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,02117175"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,03113260"));
        delete default_print;
        delete detail_print;
        delete no_print;
    }

    datamanager DB;
    Parser parser;
    addCommand addCmd;
    deleteCommand delCmd;
    resultPrinter* default_print = new defaultResultPrinter();
    resultPrinter* detail_print = new detailResultPrinter();
    resultPrinter* no_print = new noResultPrinter();

};

// list 접근 불가에 따른 변경 필요
/*
TEST_F(PrintTest, DefaultPrintCase) {

    EXPECT_EQ(default_print->printFinalResult("MOD,", list), "MOD,10\n");
    EXPECT_EQ(default_print->printFinalResult("SCH,", list), "SCH,10\n");
    EXPECT_EQ(default_print->printFinalResult("DEL,", list), "DEL,10\n");
}

TEST_F(PrintTest, DetailPrintCase) {

    string str = "";
    str += "MOD,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO\n";
    str += "MOD,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV\n";
    str += "MOD,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO\n";
    str += "MOD,08123556,WN XV,CL1,010-7986-5047,20100614,PRO\n";
    str += "MOD,15123099,VXIHXOTHJHOP,CL3,010-3112-2609,19771211,ADV\n";

    EXPECT_EQ(detail_print->printFinalResult("MOD,", list), str);
}

TEST_F(PrintTest, NonePrintCase) {

    EXPECT_EQ(no_print->printFinalResult("MOD,", list), "MOD,NONE\n");
    EXPECT_EQ(no_print->printFinalResult("SCH,", list), "SCH,NONE\n");
    EXPECT_EQ(no_print->printFinalResult("DEL,", list), "DEL,NONE\n");
}
*/