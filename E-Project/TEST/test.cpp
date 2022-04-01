#include "pch.h"
#include "../E-Project/main.cpp"

#if 0
class AddTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {

    }
    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }
};

TEST_F(AddTest, BasicAddCase) {

	EXPECT_EQ(add_employee("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,18115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV"), 0);
}

TEST_F(AddTest, SameAddCase) {

	//같은 사번
	EXPECT_EQ(add_employee("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"), -1);
}

TEST_F(AddTest, NullAddCase) {

	//비어있는 정보가 있는 경우
	EXPECT_EQ(add_employee("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,"), -1);
}

class DeleteTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        list.push_back(new Employee{ "17040889", "YOUNGHYUN JI", "CL2", "010-3550-2670", "19920430", "PRO" });
        list.push_back(new Employee{ "12345678", "JAY JI", "CL3", "010-1234-1234", "19901231", "EX" });
    }

    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }
protected:
};

TEST_F(DeleteTest, delete_with_name) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, , , ,name,BIHONG HWANG");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL, , , ,name,YOUNGHYUN JI");
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_cl) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, , , ,cl,CL4");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL, , , ,name,YOUNGHYUN JI");
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_phonenumber) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, , , ,phoneNum,010-4567-5678");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL, , , ,phoneNum,010-3550-2670");
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_birthday) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, , , ,birthday,20210101");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL, , , ,birthday,19920430");
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_name_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p, , ,name,BIHONG HWANG");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p, , ,name,YOUNGHYUN JI");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_cl_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p, , ,cl,CL4");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p, , ,cl,CL2");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p, , ,phoneNum,010-7894-4567");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p, , ,phoneNum,010-3550-2670");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_birthday_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p, , ,birthday,19951230");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p, , ,birthday,19920430");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_name_option_f) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, ,-f, ,name,BIHONG");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL, ,-f, ,name,YOUNGHYUN");
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_name_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, ,-l, ,name,HWANG");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-l, ,name,JI");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\nDEL,12345678,JAY JI,CL3,010-1234-1234,19901231,EX\n");
    EXPECT_EQ(list.size(), 0);
}

TEST_F(DeleteTest, delete_with_phonenumber_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, ,-m, ,phoneNum,7894");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-m, ,phoneNum,3550");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL, ,-l, ,phoneNum,7894");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-l, ,phoneNum,2670");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_birthday_option_y) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p,-y, ,birthday,2000");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-y, ,birthday,1992");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_birthday_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p,-m, ,birthday,08");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-m, ,birthday,04");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}

TEST_F(DeleteTest, delete_with_birthday_option_d) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "YOUNGHYUN JI");
    EXPECT_EQ(list[1]->name, "JAY JI");

    string result = deleteEmpolyee("DEL,-p,-d, ,birthday,05");
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = deleteEmpolyee("DEL,-p,-d, ,birthday,30");
    EXPECT_EQ(result, "DEL,17040889,YOUNGHYUN JI,CL2,010-3550-2670,19920430,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY JI");
}
#endif

TEST(IO_Test, InputTest_getCmdParam) {
    CmdParam cmd;
    CmdParam fake;
    vector<string> strs;
    cmd = getCmdParam("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    strs.push_back("15123099");
    strs.push_back("VXIHXOTH JHOP");
    strs.push_back("CL3");
    strs.push_back("010-3112-2609");
    strs.push_back("19771211");
    strs.push_back("ADV");
    fake.set(CmdType::ADD, false, false, false, false, false, false, false, false, strs);
    EXPECT_EQ(true, (cmd == fake));
}