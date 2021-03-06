#include "gtest/gtest.h"
#include "../E-Project/ioManager.h"
#include "../E-Project/parsedCommandType.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/deleteCommand.h"

class IOTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
    }
    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,15120999"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,17112609"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18115050"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,88114052"));
    }

    Parser parser;
    datamanager DB;
    addCommand addCmd;
    searchCommand schCmd;
    deleteCommand delCmd;
};

TEST_F(IOTest, parseADD) {
    char* buf[20] = { "15123099", "VXIHXOTH JHOP", "CL3", "010-3112-2609", "19771211", "ADV" };
    vector<string> strs;
    for (int i = 0; buf[i]; i++) {
        strs.push_back(buf[i]);
    }
    ParsedCmd fake(CmdType::ADD, false, false, false, false, false, false, false, false, strs);
    ParsedCmd subject = parser.parse("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseDel) {
    char* buf[20] = { "employeeNum", "18115040"};
    vector<string> strs;
    for (int i = 0; buf[i]; i++) {
        strs.push_back(buf[i]);
    }
    ParsedCmd fake(CmdType::DEL, false, false, false, false, false, false, false, false, strs);
    ParsedCmd subject = parser.parse("DEL, , , ,employeeNum,18115040");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseDelWithSingleOpt) {
    vector<string> strs;
    ParsedCmd fake;
    ParsedCmd subject;

    /* printFlag */
    char* bufPrint[20] = { "employeeNum", "18115040" };
    for (int i = 0; bufPrint[i]; i++) {
        strs.push_back(bufPrint[i]);
    }
    fake.set(CmdType::DEL, true, false, false, false, false, false, false, false, strs);
    subject = parser.parse("DEL,-p, , ,employeeNum,18115040");
    bool result = (subject == fake);
    EXPECT_EQ(true, result);

    /* Name */
    strs.clear();
    char* bufName[20] = { "name", "LDEXRI" };
    for (int i = 0; bufName[i]; i++) {
        strs.push_back(bufName[i]);
    }
    /* firstNameFlag */
    fake.set(CmdType::DEL, false, true, false, false, false, false, false, false, strs);
    subject = parser.parse("DEL, ,-f, ,name,LDEXRI");
    result = (subject == fake);
    EXPECT_EQ(true, result);

    /* lastNameFlag */
    fake.set(CmdType::DEL, false, false, true, false, false, false, false, false, strs);
    subject = parser.parse("DEL, ,-l, ,name,LDEXRI");
    EXPECT_EQ(true, (subject == fake));

    /* Number */
    strs.clear();
    char* bufNumber[20] = { "phoneNum", "1234" };
    for (int i = 0; bufNumber[i]; i++) {
        strs.push_back(bufNumber[i]);
    }
    /* midNumFlag */
    fake.set(CmdType::DEL, false, false, false, true, false, false, false, false, strs);
    subject = parser.parse("DEL, ,-m, ,phoneNum,1234");
    EXPECT_EQ(true, (subject == fake));

    /* lastNumFlag */
    fake.set(CmdType::DEL, false, false, false, false, true, false, false, false, strs);
    subject = parser.parse("DEL, ,-l, ,phoneNum,1234");
    EXPECT_EQ(true, (subject == fake));

    /* Date */
    /* yearFlag */
    strs.clear();
    char* bufYear[20] = { "birthday", "2003" };
    for (int i = 0; bufYear[i]; i++) {
        strs.push_back(bufYear[i]);
    }
    fake.set(CmdType::DEL, false, false, false, false, false, true, false, false, strs);
    subject = parser.parse("DEL, ,-y, ,birthday,2003");
    EXPECT_EQ(true, (subject == fake));

    /* monthFlag */
    strs.clear();
    char* bufMonthDay[20] = { "birthday", "12" };
    for (int i = 0; bufMonthDay[i]; i++) {
        strs.push_back(bufMonthDay[i]);
    }
    fake.set(CmdType::DEL, false, false, false, false, false, false, true, false, strs);
    subject = parser.parse("DEL, ,-m, ,birthday,12");
    EXPECT_EQ(true, (subject == fake));

    /* dateFlag */
    fake.set(CmdType::DEL, false, false, false, false, false, false, false, true, strs);
    subject = parser.parse("DEL, ,-d, ,birthday,12");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseDelWithMultiOpts) {
    vector<string> strs;
    ParsedCmd fake;
    ParsedCmd subject;

    /* Name */
    strs.clear();
    char* bufName[20] = { "name", "LDEXRI" };
    for (int i = 0; bufName[i]; i++) {
        strs.push_back(bufName[i]);
    }
    /* printFlag & firstNameFlag */
    fake.set(CmdType::DEL, true, true, false, false, false, false, false, false, strs);
    subject = parser.parse("DEL,-p,-f, ,name,LDEXRI");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & lastNameFlag */
    fake.set(CmdType::DEL, true, false, true, false, false, false, false, false, strs);
    subject = parser.parse("DEL,-p,-l, ,name,LDEXRI");
    EXPECT_EQ(true, (subject == fake));

    /* Number */
    strs.clear();
    char* bufNumber[20] = { "phoneNum", "1234" };
    for (int i = 0; bufNumber[i]; i++) {
        strs.push_back(bufNumber[i]);
    }
    /* printFlag & midNumFlag */
    fake.set(CmdType::DEL, true, false, false, true, false, false, false, false, strs);
    subject = parser.parse("DEL,-p,-m, ,phoneNum,1234");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & lastNumFlag */
    fake.set(CmdType::DEL, true, false, false, false, true, false, false, false, strs);
    subject = parser.parse("DEL,-p,-l, ,phoneNum,1234");
    EXPECT_EQ(true, (subject == fake));

    /* Date */
    /* printFlag & yearFlag */
    strs.clear();
    char* bufYear[20] = { "birthday", "2003" };
    for (int i = 0; bufYear[i]; i++) {
        strs.push_back(bufYear[i]);
    }
    fake.set(CmdType::DEL, true, false, false, false, false, true, false, false, strs);
    subject = parser.parse("DEL,-p,-y, ,birthday,2003");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & monthFlag */
    strs.clear();
    char* bufMonthDay[20] = { "birthday", "12" };
    for (int i = 0; bufMonthDay[i]; i++) {
        strs.push_back(bufMonthDay[i]);
    }
    fake.set(CmdType::DEL, true, false, false, false, false, false, true, false, strs);
    subject = parser.parse("DEL,-p,-m, ,birthday,12");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & dateFlag */
    fake.set(CmdType::DEL, true, false, false, false, false, false, false, true, strs);
    subject = parser.parse("DEL,-p,-d, ,birthday,12");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseMod) {
    char* buf[20] = { "employeeNum", "08123556", "birthday", "20110706" };
    vector<string> strs;
    for (int i = 0; buf[i]; i++) {
        strs.push_back(buf[i]);
    }
    ParsedCmd fake(CmdType::MOD, false, false, false, false, false, false, false, false, strs);
    ParsedCmd subject = parser.parse("MOD, , , ,employeeNum,08123556,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseModWithSingleOpt) {
    vector<string> strs;
    ParsedCmd fake;
    ParsedCmd subject;

    /* printFlag */
    char* bufPrint[20] = { "employeeNum", "08123556", "birthday", "20110706" };
    for (int i = 0; bufPrint[i]; i++) {
        strs.push_back(bufPrint[i]);
    }
    fake.set(CmdType::MOD, true, false, false, false, false, false, false, false, strs);
    subject = parser.parse("MOD,-p, , ,employeeNum,08123556,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* Name */
    strs.clear();
    char* bufName[20] = { "name", "LDEXRI", "birthday", "20110706" };
    for (int i = 0; bufName[i]; i++) {
        strs.push_back(bufName[i]);
    }
    /* firstNameFlag */
    fake.set(CmdType::MOD, false, true, false, false, false, false, false, false, strs);
    subject = parser.parse("MOD, ,-f, ,name,LDEXRI,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* lastNameFlag */
    fake.set(CmdType::MOD, false, false, true, false, false, false, false, false, strs);
    subject = parser.parse("MOD, ,-l, ,name,LDEXRI,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* Number */
    strs.clear();
    char* bufNumber[20] = { "phoneNum", "1234", "birthday", "20110706" };
    for (int i = 0; bufNumber[i]; i++) {
        strs.push_back(bufNumber[i]);
    }
    /* midNumFlag */
    fake.set(CmdType::MOD, false, false, false, true, false, false, false, false, strs);
    subject = parser.parse("MOD, ,-m, ,phoneNum,1234,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* lastNumFlag */
    fake.set(CmdType::MOD, false, false, false, false, true, false, false, false, strs);
    subject = parser.parse("MOD, ,-l, ,phoneNum,1234,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* Date */
    /* yearFlag */
    strs.clear();
    char* bufYear[20] = { "birthday", "2003", "certi", "PRO"};
    for (int i = 0; bufYear[i]; i++) {
        strs.push_back(bufYear[i]);
    }
    fake.set(CmdType::MOD, false, false, false, false, false, true, false, false, strs);
    subject = parser.parse("MOD, ,-y, ,birthday,2003,certi,PRO");
    EXPECT_EQ(true, (subject == fake));

    /* monthFlag */
    strs.clear();
    char* bufMonthDay[20] = { "birthday", "12", "certi", "PRO" };
    for (int i = 0; bufMonthDay[i]; i++) {
        strs.push_back(bufMonthDay[i]);
    }
    fake.set(CmdType::MOD, false, false, false, false, false, false, true, false, strs);
    subject = parser.parse("MOD, ,-m, ,birthday,12,certi,PRO");
    EXPECT_EQ(true, (subject == fake));

    /* dateFlag */
    fake.set(CmdType::MOD, false, false, false, false, false, false, false, true, strs);
    subject = parser.parse("MOD, ,-d, ,birthday,12,certi,PRO");
    EXPECT_EQ(true, (subject == fake));
}

TEST_F(IOTest, parseModWithMultiOpts) {
    vector<string> strs;
    ParsedCmd fake;
    ParsedCmd subject;

    /* Name */
    strs.clear();
    char* bufName[20] = { "name", "LDEXRI", "birthday", "20110706" };
    for (int i = 0; bufName[i]; i++) {
        strs.push_back(bufName[i]);
    }
    /* printFlag & firstNameFlag */
    fake.set(CmdType::MOD, true, true, false, false, false, false, false, false, strs);
    subject = parser.parse("MOD,-p,-f, ,name,LDEXRI,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & lastNameFlag */
    fake.set(CmdType::MOD, true, false, true, false, false, false, false, false, strs);
    subject = parser.parse("MOD,-p,-l, ,name,LDEXRI,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* Number */
    strs.clear();
    char* bufNumber[20] = { "phoneNum", "1234", "birthday", "20110706" };
    for (int i = 0; bufNumber[i]; i++) {
        strs.push_back(bufNumber[i]);
    }
    /* printFlag & midNumFlag */
    fake.set(CmdType::MOD, true, false, false, true, false, false, false, false, strs);
    subject = parser.parse("MOD,-p,-m, ,phoneNum,1234,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & lastNumFlag */
    fake.set(CmdType::MOD, true, false, false, false, true, false, false, false, strs);
    subject = parser.parse("MOD,-p,-l, ,phoneNum,1234,birthday,20110706");
    EXPECT_EQ(true, (subject == fake));

    /* Date */
    /* printFlag & yearFlag */
    strs.clear();
    char* bufYear[20] = { "birthday", "2003", "certi", "PRO" };
    for (int i = 0; bufYear[i]; i++) {
        strs.push_back(bufYear[i]);
    }
    fake.set(CmdType::MOD, true, false, false, false, false, true, false, false, strs);
    subject = parser.parse("MOD,-p,-y, ,birthday,2003,certi,PRO");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & monthFlag */
    strs.clear();
    char* bufMonthDay[20] = { "birthday", "12", "certi", "PRO" };
    for (int i = 0; bufMonthDay[i]; i++) {
        strs.push_back(bufMonthDay[i]);
    }
    fake.set(CmdType::MOD, true, false, false, false, false, false, true, false, strs);
    subject = parser.parse("MOD,-p,-m, ,birthday,12,certi,PRO");
    EXPECT_EQ(true, (subject == fake));

    /* printFlag & dateFlag */
    fake.set(CmdType::MOD, true, false, false, false, false, false, false, true, strs);
    subject = parser.parse("MOD,-p,-d, ,birthday,12,certi,PRO");
    EXPECT_EQ(true, (subject == fake));
}