// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include <algorithm>
//
// #include "CampusCompass.h"
// #include "parseCommand.h"
//
//
// using namespace std;
//
// // John Ronchetto
// // UFID: 52490540
//
// // UNIT TESTS REQUIRED
//
// // 1. Test at least five incorrect commands.
// TEST_CASE("Incorrect command", "[invalid commands]") {
//
//     CampusCompass cc("data/edges.csv", "data/classes.csv");
//
//     string expectedOutput = "successful";
//
//     // insert some valid students for comparison in invalid commands
//
//     string actualOutput1 = cc.insertT("Brandon", "11111111", 20, {"COP3530", "MAC2311"});
//     REQUIRE(cc.getStudentCount() == 1);
//     REQUIRE(cc.hasStudent("11111111"));
//     REQUIRE(expectedOutput == actualOutput1);
//
//
//     string actualOutput2 = cc.insertT("Brian", "22222222", 21, {"COP3530", "CDA3101", "MAC2311"});
//     REQUIRE(cc.getStudentCount() == 2);
//     REQUIRE(cc.hasStudent("22222222"));
//     REQUIRE(expectedOutput == actualOutput2);
//
//     string actualOutput3 = cc.insertT("Briana", "33333333", 22, {"CDA3101", "MAC2311", "EEL3701"});
//     REQUIRE(cc.getStudentCount() == 3);
//     REQUIRE(cc.hasStudent("33333333"));
//     REQUIRE(expectedOutput == actualOutput3);
//
//
//     SECTION("1) insert - invalid name") {
//
//         int sCountBefore = cc.getStudentCount();
//
//         // name contains $
//         bool invalidCommand = verifyCommand(R"(insert "$John$" 12345678 20 2 COP3530 MAC2311)", cc);
//
//         REQUIRE_FALSE(invalidCommand);
//         REQUIRE(cc.getStudentCount() == sCountBefore);
//         REQUIRE_FALSE(cc.hasStudent("12345678"));
//
//     }
//
//     SECTION("2) remove - invalid ufid") {
//         int sCountBefore = cc.getStudentCount();
//
//         // ufid not 8 digits
//         bool invalidCommand = verifyCommand(R"(remove 1234567)", cc);
//
//         REQUIRE_FALSE(invalidCommand);
//         REQUIRE(cc.getStudentCount() == sCountBefore);
//         REQUIRE_FALSE(cc.hasStudent("1234567"));
//     }
//
//     SECTION("3) dropClass - drop invalid class") {
//
//         const Student* Brandon = cc.getStudent("11111111");
//         vector<string> bClassCodes = {"COP3530", "MAC2311"};
//
//         // class doesn't respect the format
//         bool invalidCommand = verifyCommand(R"(dropClass 11111111 COOP3502)", cc);
//
//         REQUIRE_FALSE(invalidCommand);
//         REQUIRE(Brandon->classCodes == bClassCodes);
//     }
//
//     SECTION("4) toggleEdgeClosure - wrong number edges") {
//         bool invalidCommand = verifyCommand("toggleEdgesClosure 2 1 2", cc);
//         REQUIRE_FALSE(invalidCommand);
//
//         const GraphEdge* ge = cc.getGraphEdge(1, 2);
//         // first edge status should still be the same (open)
//         REQUIRE(ge->open == true);
//     }
//
//     SECTION("5) CheckEdgeStatus - invalid location IDs") {
//         // should not accept non integers as edges
//         bool invalidCommand = verifyCommand("CheckEdgeStatus 22.3 45.7", cc);
//
//         REQUIRE_FALSE(invalidCommand);
//     }
//
// }
//
// // 2. Test at least three edge cases for various functions
// TEST_CASE("Edge cases for various functions", "[edge cases]") {
//     CampusCompass cc("data/edges.csv", "data/classes.csv");
//
//     string expectedOutputV = "successful";
//
//     // insert some valid students for comparison in invalid commands
//
//     string actualOutput1 = cc.insertT("Brandon", "11111111", 20, {"COP3530", "MAC2311"});
//     REQUIRE(cc.getStudentCount() == 1);
//     REQUIRE(cc.hasStudent("11111111"));
//     REQUIRE(expectedOutputV == actualOutput1);
//
//
//     string actualOutput2 = cc.insertT("Brian", "22222222", 21, {"COP3530", "CDA3101", "MAC2311"});
//     REQUIRE(cc.getStudentCount() == 2);
//     REQUIRE(cc.hasStudent("22222222"));
//     REQUIRE(expectedOutputV == actualOutput2);
//
//     string actualOutput3 = cc.insertT("Briana", "33333333", 22, {"CDA3101"});
//     REQUIRE(cc.getStudentCount() == 3);
//     REQUIRE(cc.hasStudent("33333333"));
//     REQUIRE(expectedOutputV == actualOutput3);
//
//     SECTION("1) insert student with ufid not unique") {
//         int studentCount = cc.getStudentCount();
//
//         // this is Brandon's ID --> should not insert John
//         string actualOutput = cc.insertT("John", "11111111", 19, {"COP3530", "MAC2311"});
//         string expectedOutput = "unsuccessful";
//
//         // john should not have been inserted instead of Brandon
//         const Student* notJohn = cc.getStudent("11111111");
//         REQUIRE("Brandon" == notJohn->name);
//         REQUIRE(cc.getStudentCount() == studentCount);
//
//         REQUIRE(expectedOutput == actualOutput);
//     }
//
//     SECTION("2) drop a class for student, fail if student not enrolled in that class") {
//
//         string expectedOut = "unsuccessful";
//         // brandon is not in this class!
//         string actualOutput = cc.dropClassT("11111111", "EEL3701");
//
//         REQUIRE(expectedOut == actualOutput);
//
//     }
//
//     SECTION("3) remove class code and if student has 0 classes then drop") {
//
//         // removed from Briana and Brian
//         string expectedOut = "2";
//         // Briana only has this class
//         string actualOutput = cc.removeClassT("CDA3101");
//
//         REQUIRE(expectedOut == actualOutput);
//
//         // Briana should not be in student data structure anymore
//         REQUIRE_FALSE(cc.hasStudent("333333333"));  // Briana's UFID
//
//         // Student count should decrease by 1
//         REQUIRE(cc.getStudentCount() == 2);
//     }
// }
//
// // 3. Test your dropClass, removeClass, remove, and replaceClass commands
// TEST_CASE("General command tests", "[general commands]") {
//
//     CampusCompass cc("data/edges.csv", "data/classes.csv");
//
//     // insert some students in data structure as before
//     REQUIRE(verifyCommand(R"(insert "Brandon" 11111111 20 2 COP3530 MAC2311)",cc));
//     REQUIRE(verifyCommand(R"(insert "Brian" 22222222 21 2 CDA3101 MAC2311)",cc));
//     REQUIRE(verifyCommand(R"(insert "Briana" 33333333 22 1 CDA3101)",cc));
//
//     REQUIRE(cc.getStudentCount() == 3);
//
//     SECTION("dropClass") {
//         int beforeCount = cc.getStudentCount();
//
//         // drop class for brandon
//         REQUIRE(verifyCommand(R"(dropClass 11111111 MAC2311)", cc));
//
//         // brandon has still classes
//         REQUIRE(cc.getStudentCount() == beforeCount);
//
//         const Student* s = cc.getStudent("11111111");
//         REQUIRE(s != nullptr);
//
//         const auto& codes = s->classCodes;
//         // should not have mac2311 anymore
//         REQUIRE(std::find(codes.begin(), codes.end(), "MAC2311") == codes.end());
//     }
//
//     SECTION("removeClass") {
//         // remove CDA3101 from everyone
//         REQUIRE( verifyCommand(R"(removeClass CDA3101)", cc) );
//
//         // Briana had only CDA3101 so should not be in data structure anymore
//         REQUIRE_FALSE(cc.hasStudent("33333333"));
//
//         // Brian should still exist, but without CDA3101
//         REQUIRE(cc.hasStudent("22222222"));
//         const Student* brian = cc.getStudent("22222222");
//         REQUIRE(brian != nullptr);
//         const auto& codes = brian->classCodes;
//         REQUIRE(std::find(codes.begin(), codes.end(), "CDA3101") == codes.end());
//
//         // Brandon never had CDA3101, so should still be in student data structure
//         REQUIRE(cc.hasStudent("11111111"));
//
//         // should only have a total of 2 students
//         REQUIRE(cc.getStudentCount() == 2);
//     }
//
//     SECTION("remove") {
//         int beforeCount = cc.getStudentCount();
//
//         // remove Brian
//         REQUIRE( verifyCommand(R"(remove 22222222)", cc) );
//         REQUIRE(cc.getStudentCount() == beforeCount - 1);
//         REQUIRE_FALSE(cc.hasStudent("22222222"));
//
//         // remove Briana
//         REQUIRE( verifyCommand(R"(remove 33333333)", cc) );
//         REQUIRE(cc.getStudentCount() == beforeCount - 2);
//         REQUIRE_FALSE(cc.hasStudent("33333333"));
//
//     }
//
//     SECTION("replaceClass") {
//
//         // make sure Brandon doesn't already have eel3701 and has cop3530
//         const Student* before = cc.getStudent("11111111");
//         REQUIRE(before != nullptr);
//         const auto& codes = before->classCodes;
//         REQUIRE(std::find(codes.begin(), codes.end(), "EEL3701") == codes.end());
//         REQUIRE(std::find(codes.begin(), codes.end(), "COP3530") != codes.end());
//
//
//         // replace COP3530 with EEL3701
//         REQUIRE( verifyCommand(R"(replaceClass 11111111 COP3530 EEL3701)", cc) );
//
//         const Student* after = cc.getStudent("11111111");
//         REQUIRE(after != nullptr);
//         const auto& codesAfter = after->classCodes;
//
//         // now shouldn't have cop, but should have eel
//         REQUIRE(std::find(codesAfter.begin(), codesAfter.end(), "COP3530") == codesAfter.end());
//         REQUIRE(std::find(codesAfter.begin(), codesAfter.end(), "EEL3701") != codesAfter.end());
//
//     }
// }
//
// // 4. Test your printShortestEdges command in a case where a student can reach a class,
// // then one or more edges turn off, and then they cannot reach that class.
// TEST_CASE("PrintShortEdges test with edge closure", "[PrintShortEdges]") {
//     CampusCompass cc("data/edges.csv", "data/classes.csv");
//
//     // From visualizer:
//     // residence ID = 7
//     // class code = 49 (STA3032)
//     // class code = 56 (COP4020)
//     // 7-49 --> 6
//     // 49-56 --> 1
//     // if 49 - 56 closed, 56 should not be reachable (only path)
//
//
//     REQUIRE(verifyCommand(R"(insert "John" 11111111 7 2 STA3032 COP4020)", cc));
//
//     std::string before = cc.printShortestEdgesString("11111111");
//
//
//     std::string expectedBefore =
//         "Name: John\n"
//         "COP4020 | Total Time: 7\n"
//         "STA3032 | Total Time: 6\n";
//
//     REQUIRE(before == expectedBefore);
//
//     std::vector<int> close{49, 56};
//     // Toggle edge 49-56
//     cc.toggleEdgesClosure(1, close);
//
//     std::string after = cc.printShortestEdgesString("11111111");
//
//     std::string expectedAfter =
//         "Name: John\n"
//         "COP4020 | Total Time: -1\n"
//         "STA3032 | Total Time: 6\n";
//
//     REQUIRE(after == expectedAfter);
// }
//
//
//
//
//
