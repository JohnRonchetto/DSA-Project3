#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "CampusCompass.h"
#include "parseCommand.h"

using namespace std;

// You must write 5 unique, meaningful tests for credit on the testing section
// of this project!



// UNIT TESTS REQUIRED

// 1. Test at least five incorrect commands.
TEST_CASE("Incorrect command", "[invalid commands]") {

    CampusCompass cc("data/edges.csv", "data/classes.csv");

    // insert some valid students for comparison in invalid commands
    bool val1 = verifyCommand(R"(insert "Brandon" 45679999 20 2 COP3530 MAC2311)", cc);
    REQUIRE(val1);
    REQUIRE(cc.getStudentCount() == 1);
    REQUIRE(cc.hasStudent(45679999));

    bool val2 = verifyCommand(R"(insert "Brian" 35459999 21 3 COP3530 CDA3101 MAC2311)", cc);
    REQUIRE(val2);
    REQUIRE(cc.getStudentCount() == 2);
    REQUIRE(cc.hasStudent(35459999));

    bool val3 = verifyCommand(R"(insert "Briana" 87879999 22 3 CDA3101 MAC2311 EEL3701)", cc);
    REQUIRE(val3);
    REQUIRE(cc.getStudentCount() == 3);
    REQUIRE(cc.hasStudent(87879999));


    SECTION("1) insert - invalid name") {

        int sCountBefore = cc.getStudentCount();

        // name contains $
        bool invalidCommand = verifyCommand(R"(insert "$John$" 12345678 20 2 COP3530 MAC2311)", cc);

        REQUIRE_FALSE(invalidCommand);
        REQUIRE(cc.getStudentCount() == sCountBefore);
        REQUIRE_FALSE(cc.hasStudent(12345678));

    }

    SECTION("2) remove - invalid ufid") {
        int sCountBefore = cc.getStudentCount();

        // ufid not 8 digits
        bool invalidCommand = verifyCommand(R"(remove 1234567)", cc);

        REQUIRE_FALSE(invalidCommand);
        REQUIRE(cc.getStudentCount() == sCountBefore);
        REQUIRE_FALSE(cc.hasStudent(1234567));
    }

    SECTION("3) dropClass - drop invalid class") {

        const Student* Brandon = cc.getStudent(45679999);
        vector<string> bClassCodes = {"COP3530", "MAC2311"};

        // class doesn't respect the format
        bool invalidCommand = verifyCommand(R"(dropClass 45679999 COOP3502)", cc);

        REQUIRE_FALSE(invalidCommand);
        REQUIRE(Brandon->classCodes == bClassCodes);
    }

    SECTION("4) toggleEdgeClosure - wrong number edges") {
        bool invalidCommand = verifyCommand("toggleEdgesClosure 2 1 2", cc);
        REQUIRE_FALSE(invalidCommand);

        const GraphEdge* ge = cc.getGraphEdge(1, 2);
        // first edge status should still be the same (open)
        REQUIRE(ge->open == true);
    }

    SECTION("5) CheckEdgeStatus - invalid location IDs") {
        bool invalidCommand = verifyCommand("CheckEdgeStatus 22.3 45.7", cc);

        REQUIRE_FALSE(invalidCommand);
    }

}



// TEST_CASE("Test 2", "[tag]") {
//   // you can also use "sections" to share setup code between tests, for example:
//   int one = 1;
//
//   SECTION("num is 2") {
//     int num = one + 1;
//     REQUIRE(num == 2);
//   };
//
//   SECTION("num is 3") {
//     int num = one + 2;
//     REQUIRE(num == 3);
//   };
//
//   // each section runs the setup code independently to ensure that they don't
//   // affect each other
// }



