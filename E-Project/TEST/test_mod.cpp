#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

class ModTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18050302,SEUNGWOO HYUN,CL3,010-1111-2233,19900302,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,19000000,SAM CHOI,CL1,010-3333-1111,19990506,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18011111,CHOI HYBUSUN,CL4,010-5555-1111,19990508,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18022222,TAXI CHOI,CL3,010-6666-1111,19990408,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18000000,HARBANG KIM,CL2,010-3333-1111,19990208,PRO"));
    }

    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18050301"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18050302"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,19000000"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18011111"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18022222"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18000000"));
    }

    Parser parser;
    datamanager DB;
    addCommand addCmd;
    modifyCommand modCmd;
    deleteCommand delCmd;
};

TEST_F(ModTest, mod_with_name_none_none) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"cl", "CL2", "name", "CHANGE CHANGE"} });
    EXPECT_EQ(result, "MOD,2\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "TAXI CHOI", "certi", "EX"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"certi", "PRO", "phoneNum", "010-0000-0000"} });
    EXPECT_EQ(result, "MOD,5\n");
}
TEST_F(ModTest, mod_with_cl_none_none) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "HARBANG KIM", "cl", "CL4"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"cl", "CL3", "phoneNum", "010-9999-9999"} });
    EXPECT_EQ(result, "MOD,2\n");
}
TEST_F(ModTest, mod_with_phoneNum_none_none) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "HARBANG KIM", "cl", "CL4"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"cl", "CL3", "phoneNum", "010-9999-9999"} });
    EXPECT_EQ(result, "MOD,2\n");

}

TEST_F(ModTest, mod_with_birthday_none_none) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"birthday", "19990506", "cl", "CL2"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "HARBANG KIM", "birthday", "19990208"} });

    EXPECT_EQ(result, "MOD,1\n");
}

TEST_F(ModTest, mod_with_name_none_f) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,true,false,false,false,false,false,false,{"name", "TAXI", "name", "HARBANG HYUN"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,true,false,false,false,false,false,false,{"name", "HARBANG", "birthday", "19990506"} });
    EXPECT_EQ(result, "MOD,2\n");
}

TEST_F(ModTest, mod_with_phoneNum_none_m) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,true,false,false,false,false,{"phoneNum", "3333", "phoneNum", "010-1111-1111"} });
    EXPECT_EQ(result, "MOD,2\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,true,false,false,false,false,{"phoneNum", "1111", "birthday", "19990506"} });
    EXPECT_EQ(result, "MOD,3\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,true,false,false,false,false,{"phoneNum", "3333", "birthday", "19990506"} });
    EXPECT_EQ(result, "MOD,NONE\n");
}

TEST_F(ModTest, mod_with_birthday_none_y) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,true,false,false,{"birthday", "1998", "phoneNum", "010-1111-1111"} });
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,true,false,false,{"birthday", "1999", "birthday", "19940101"} });
    EXPECT_EQ(result, "MOD,4\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,true,false,false,{"birthday", "1999", "birthday", "19940101"} });
    EXPECT_EQ(result, "MOD,NONE\n");
}
TEST_F(ModTest, mod_with_birthday_none_m) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,true,false,{"birthday", "05", "birthday", "19990408"} });
    EXPECT_EQ(result, "MOD,2\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,true,false,{"birthday", "04", "birthday", "19941001"} });
    EXPECT_EQ(result, "MOD,3\n");

    result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,false,false,false,false,false,false,true,false,{"birthday", "04", "name", "ZZ ZZ"} });
    EXPECT_EQ(result, "MOD,NONE\n");
}

// [TBD] -p Option Test
TEST_F(ModTest, mod_with_certi_p_none) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,true,false,false,false,false,false,false,false,{"certi", "PRO", "certi", "EX"} });

    string expectResult = "MOD,18000000,HARBANG KIM,CL2,010-3333-1111,19990208,PRO\n";
    expectResult += "MOD,18011111,CHOI HYBUSUN,CL4,010-5555-1111,19990508,PRO\n";
    expectResult += "MOD,18022222,TAXI CHOI,CL3,010-6666-1111,19990408,PRO\n";
    expectResult += "MOD,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO\n";
    expectResult += "MOD,18050302,SEUNGWOO HYUN,CL3,010-1111-2233,19900302,PRO\n";


    EXPECT_EQ(result, expectResult);
}


TEST_F(ModTest, mod_with_name_p_l) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,true,false,true,false,false,false,false,false,{"name", "CHOI", "certi", "EX"} });
    string expectResult = "MOD,18022222,TAXI CHOI,CL3,010-6666-1111,19990408,PRO\n";
    expectResult += "MOD,19000000,SAM CHOI,CL1,010-3333-1111,19990506,PRO\n";

    EXPECT_EQ(result, expectResult);
}

TEST_F(ModTest, mod_with_phoneNum_p_m) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,true,false,false,true,false,false,false,false,{"phoneNum", "3333", "birthday", "20000101"} });
    string expectResult = "MOD,18000000,HARBANG KIM,CL2,010-3333-1111,19990208,PRO\n";
    expectResult += "MOD,19000000,SAM CHOI,CL1,010-3333-1111,19990506,PRO\n";

    EXPECT_EQ(result, expectResult);
}

class ModTest_with_P : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18050302,SEUNGWOO HYUN,CL3,010-1111-2233,19900302,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,19000000,SAM CHOI,CL1,010-3333-1111,19990506,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18011111,CHOI HYBUSUN,CL4,010-5555-1111,19990508,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18022222,TAXI CHOI,CL3,010-6666-1111,19990408,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18000000,HARBANG KIM,CL2,010-3333-1111,19990208,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,69010101,HARBANG HYUN,CL2,010-1234-2233,19990208,PRO"));
    }

    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18050301"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18050302"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,19000000"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18011111"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18022222"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18000000"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,69010101"));
    }

    datamanager DB;
    Parser parser;
    addCommand addCmd;
    modifyCommand modCmd;
    deleteCommand delCmd;
};

TEST_F(ModTest_with_P, mod_with_phoneNum_p_l) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,true,false,false,false,true,false,false,false,{"phoneNum", "2233", "phoneNum", "010-0000-0000"} });
    string expectResult = "MOD,69010101,HARBANG HYUN,CL2,010-1234-2233,19990208,PRO\n";
    expectResult += "MOD,18050302,SEUNGWOO HYUN,CL3,010-1111-2233,19900302,PRO\n";

    EXPECT_EQ(result, expectResult);
}

TEST_F(ModTest_with_P, mod_with_birthday_p_d) {
    string result = modCmd.processCommand(DB, CmdParam{ CmdType::MOD,true,false,false,false,false,false,false,true,{"birthday", "08", "name", "BALCK PINK"} });

    string expectResult = "MOD,69010101,HARBANG HYUN,CL2,010-1234-2233,19990208,PRO\n";
    expectResult += "MOD,18000000,HARBANG KIM,CL2,010-3333-1111,19990208,PRO\n";
    expectResult += "MOD,18011111,CHOI HYBUSUN,CL4,010-5555-1111,19990508,PRO\n";
    expectResult += "MOD,18022222,TAXI CHOI,CL3,010-6666-1111,19990408,PRO\n";

    EXPECT_EQ(result, expectResult);
}
