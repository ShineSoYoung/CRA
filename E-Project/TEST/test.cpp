#include "pch.h"
#include "../E-Project/main.cpp"

TEST(BasicAddCase, AddTest) {

	EXPECT_EQ(add_employee("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,18115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV"), 0);
}

TEST(SameAddCase, AddTest) {

	//같은 사번
	EXPECT_EQ(add_employee("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"), -1);
}

TEST(NullAddCase, AddTest) {

	//비어있는 정보가 있는 경우
	EXPECT_EQ(add_employee("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,"), -1);

}

TEST(SearchSuccess, SearchCntTest)
{
	EXPECT_EQ(sch_employee("SCH, , , ,employeeNum,17111236"), "SCH,5");
}