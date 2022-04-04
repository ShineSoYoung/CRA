#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

class SchTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, parser.parse("ADD, , , ,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,17000001,홍 길훈,CL3,010-1111-2233,19900302,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,17000054,APKEWER JAG,CL1,010-3333-2243,19670504,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,90020002,FDJKA GJKD,CL1,010-3333-2243,19780401,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,17000002,ZXKWI QKW,CL1,010-3333-2243,19870426,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,01000002,DSKFDSK FDS,CL1,010-3333-2243,19890416,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,90000342,AGBDSFSD DS,CL1,010-3333-2243,19950416,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12000023,AS FDSFC,CL1,010-3333-2243,19970716,ADV"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12000012,AXCXZV DSFQW,CL1,010-3333-2243,19960116,ADV"));
    }
    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17000000"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17000001"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17000002"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17000054"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,90020002"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17000002"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,01000002"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,90000342"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,12000023"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,12000012"));
    }

    datamanager DB;
    Parser parser;
    addCommand addCmd;
    searchCommand schCmd;
    deleteCommand delCmd;
};

TEST_F(SchTest, sch_none) {
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"employeeNum","1700333"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name","이 순신"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum","013-2222-3333"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl","CL6"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"certi","GOLD"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","15930303"} }), "SCH,NONE\n");
}


TEST_F(SchTest, sch_with_name) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name", "홍 길동"} });
    EXPECT_EQ(result, "SCH,1\n");
}

TEST_F(SchTest, sch_with_cl) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "SCH,2\n");
}

TEST_F(SchTest, sch_with_birthday) {
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900302"} }), "SCH,2\n");
    EXPECT_EQ(schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900306"} }), "SCH,1\n");
}

TEST_F(SchTest, sch_with_phonenumber) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum", "010-1111-2222"} });
    EXPECT_EQ(result, "SCH,1\n");
}

TEST_F(SchTest, sch_with_name_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"name", "홍 길동"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\n");
}

TEST_F(SchTest, sch_with_cl_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"phoneNum", "010-1111-2244"} });
    EXPECT_EQ(result, "SCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"birthday", "19900306"} });
    EXPECT_EQ(result, "SCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_name_option_f) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,true,false,false,false,false,false,false,{"name", "홍"} });
    EXPECT_EQ(result, "SCH,3\n");
}

TEST_F(SchTest, sch_with_name_option_l) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,true,false,false,false,false,false,{"name", "길동"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_m) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,true,false,false,false,false,{"phoneNum","1111"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,17000001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_l) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,true,false,false,false,{"phoneNum","2244"} });
    EXPECT_EQ(result, "SCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_y) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,true,false,false,{"birthday","1990"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,17000001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_m) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,true,false,{"birthday","03"} });
    EXPECT_EQ(result, "SCH,17000000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,17000001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_d) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,true,{"birthday","06"} });
    EXPECT_EQ(result, "SCH,17000002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_same_cl_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"cl","CL1"} });
    EXPECT_EQ(result, "SCH,90000342,AGBDSFSD DS,CL1,010-3333-2243,19950416,ADV\nSCH,90020002,FDJKA GJKD,CL1,010-3333-2243,19780401,ADV\nSCH,01000002,DSKFDSK FDS,CL1,010-3333-2243,19890416,ADV\nSCH,12000012,AXCXZV DSFQW,CL1,010-3333-2243,19960116,ADV\nSCH,12000023,AS FDSFC,CL1,010-3333-2243,19970716,ADV\n");
}

TEST_F(SchTest, sch_with_same_certi_option_p) {
    string result = schCmd.processCommand(DB, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"certi","ADV"} });
    EXPECT_EQ(result, "SCH,90000342,AGBDSFSD DS,CL1,010-3333-2243,19950416,ADV\nSCH,90020002,FDJKA GJKD,CL1,010-3333-2243,19780401,ADV\nSCH,01000002,DSKFDSK FDS,CL1,010-3333-2243,19890416,ADV\nSCH,12000012,AXCXZV DSFQW,CL1,010-3333-2243,19960116,ADV\nSCH,12000023,AS FDSFC,CL1,010-3333-2243,19970716,ADV\n");
}
