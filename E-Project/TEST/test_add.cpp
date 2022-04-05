#include "gtest/gtest.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/ioManager.h"
#include "../E-Project/EmployeeManager.h"

class AddTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
    }
    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,cl,CL1"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,cl,CL2"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,cl,CL3"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,cl,CL4"));
    }

    Parser parser;
    datamanager DB;
    addCommand addCmd;
    searchCommand schCmd;
    deleteCommand delCmd;
};

TEST_F(AddTest, BasicAddCase) {

    EXPECT_EQ(addCmd.processCommand(DB, parser.parse("ADD, , , ,15120999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV")), "");
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH,-p, , ,employeeNum,15120999")), "SCH,15120999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV\n");
    EXPECT_EQ(addCmd.processCommand(DB, parser.parse("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO")), "");
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH,-p, , ,employeeNum,17112609")), "SCH,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO\n");
    EXPECT_EQ(addCmd.processCommand(DB, parser.parse("ADD, , , ,18115050,TTETHU HBO,CL3,010-4581-2050,20080718,ADV")), "");
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH,-p, , ,employeeNum,18115050")), "SCH,18115050,TTETHU HBO,CL3,010-4581-2050,20080718,ADV\n");
}

TEST_F(AddTest, SameAddCase) {

    //같은 사번
    EXPECT_EQ(addCmd.processCommand(DB, parser.parse("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-0959,19911021,PRO")), "");
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH,-p, , ,employeeNum,88114052")), "SCH,88114052,NQ LVARW,CL4,010-4528-0959,19911021,PRO\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-0991-9521,19640910,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,88114052")), "SCH,1\n");
}

TEST_F(AddTest, NullAddCase) {

    //비어있는 정보가 있는 경우
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,name,VSID TVO")), "SCH,NONE\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,17111236,,010-3669-1077,20120718,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,17111236")), "SCH,NONE\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,17111236")), "SCH,NONE\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,17111236")), "SCH,NONE\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,17111236")), "SCH,NONE\n");
    EXPECT_EQ(addCmd.checkCommandIsValid(DB, parser.parse("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,")), false);
    EXPECT_EQ(schCmd.processCommand(DB, parser.parse("SCH, , , ,employeeNum,17111236")), "SCH,NONE\n");
}

class AddSampleSizeTest : public ::testing::Test
{
public:
protected:
    
    virtual void SetUp() override
    {
        DB = new datamanager();
    }
    virtual void TearDown() override
    {
        inputFile.close();
        delete DB;
    }

    void openInputFile(string inputFileName)
    {
        inputFile.open(inputFileName);
        if (!inputFile.is_open()) {
            cout << "file open fail" << endl;
        }
    }

    int addDataInDB(void) 
    {
        int cnt = 0;

        while (!inputFile.eof()) {
            char buf[256] = { 0, };
            inputFile.getline(buf, 256);
            if (vlid.isValid(buf) == false) break;

            ParsedCmd = parser.parse(buf);
            string result = addCmd.processCommand(*DB, ParsedCmd);

            if (result == "FAIL")
                return -1;

            cnt++;
        }
        return cnt;
    }

    ifstream inputFile;
    Validator vlid;
    Parser parser;
    datamanager *DB;
    addCommand addCmd;
    searchCommand schCmd;
    deleteCommand delCmd;
    ParsedCmd ParsedCmd;
};

TEST_F(AddSampleSizeTest, SampleSize100) {

    openInputFile("SampleSize100_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 100);
}

TEST_F(AddSampleSizeTest, SampleSize150) {

    openInputFile("SampleSize150_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 150);
}

TEST_F(AddSampleSizeTest, SampleSize200) {

    openInputFile("SampleSize200_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 200);
}

#if 0
TEST_F(AddSampleSizeTest, SampleSize1000) {
    openInputFile("SampleSize1000_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 1000);
}
#endif

#if 0
TEST_F(AddSampleSizeTest, SampleSize10000) {
    openInputFile("SampleSize10000_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 10000);
}
#endif

#if 0
TEST_F(AddSampleSizeTest, SampleSize100000) {
    openInputFile("SampleSize100000_input.txt");
    int result = addDataInDB();
    EXPECT_EQ(result, 100000);
}
#endif
