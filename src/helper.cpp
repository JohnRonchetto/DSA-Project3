#include "helper.h"
#include <regex>

std::string parseCommand(const std::string &command,
                        std::string &name,
                        int &UFID,
                        int &residenceID,
                        int &N,
                        std::vector<std::string> &classCodes,
                        std::vector<int> &locationIDs) {

    name.clear();
    UFID = -1;
    residenceID = -1;
    N = 0;
    classCodes.clear();
    locationIDs.clear();


    const std::regex cInsert(R"CMD(^\s*insert\s+"([A-Za-z][A-Za-z ]*)"\s+(\d{8})\s+(\d+)\s+(\d+)\s+(.+)\s*$)CMD");
    const regex cRemove(R"(^\s*remove\s+(\d{8})\s*$)");
    const regex cDrop(R"(^\s*dropClass\s+(\d{8})\s+([A-Z0-9]+)\s*$)");
    const regex cReplace(R"(^\s*replaceClass\s+(\d{8})\s+([A-Z0-9]+)\s+([A-Z0-9]+)\s*$)");
    const regex cRemoveClass(R"(^\s*removeClass\s+([A-Z0-9]+)\s*$)");
    const regex cToggleEdges(R"(^\s*toggleEdgesClosure\s+(\d+)\s+(.+)\s*$)");
    const regex cCheckEdge(R"(^\s*checkEdgeStatus\s+(\d+)\s+(\d+)\s*$)");
    const regex cConnected(R"(^\s*isConnected\s+(\d+)\s+(\d+)\s*$)");
    const regex cShortest(R"(^\s*printShortestEdges\s+(\d+)\s*$)");
    const regex cZone(R"(^\s*printStudentZone\s+(\d+)\s*$)");
    const regex cVerify(R"(^\s*verifySchedule\s+(\d+)\s*$)");

    std::smatch m;

    if (std::regex_match(command, m, cInsert)) {
        try {
            name = m[1].str();
            UFID = std::stoi(m[2].str());
            residenceID = std::stoi(m[3].str());
            N = std::stoi(m[4].str());

            string codesStr = m[5].str();
            std::stringstream ss(codesStr);
            string code;

            while (ss >> code) {
                classCodes.push_back(code);
            }

            // Must have exactly N class codes
            if (static_cast<int>(classCodes.size()) != N) {
                return "unsuccessful";
            }

            return "insert";

        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cRemove)) {

        return "remove";
    }
    if (std::regex_match(command, m, cDrop)) {

        return "dropClass";
    }
    if (std::regex_match(command, m, cReplace)) {

        return "replaceClass";
    }
    if (std::regex_match(command, m, cRemoveClass)) {

        return "removeClass";
    }
    if (std::regex_match(command, m, cToggleEdges)) {

        return "toggleEdgesClosure";
    }
    if (std::regex_match(command, m, cCheckEdge)) {

        return "checkEdgeStatus";
    }
    if (std::regex_match(command, m, cConnected)) {

        return "isConnected";
    }
    if (std::regex_match(command, m, cShortest)) {

        return "printShortestEdges";
    }
    if (std::regex_match(command, m, cZone)) {

        return "printStudentZone";
    }
    if (std::regex_match(command, m, cVerify)) {

        return "verifySchedule";
    }


    return "unsuccessful";
}

bool verifyCommand(const std::string &command, CampusCompass &CC) {

    // dummy variables
    std::string name;
    int UFID, residenceID, N;
    vector<std::string> classCodes;
    std::vector<int> locationIDs;

    const std::string comm = parseCommand(command, name, UFID, residenceID, N, classCodes, locationIDs);

    if (comm == "insert") {
        // CC.insert(name, UFID, residenceID, N, classCodes)
        return true;
    }
    if (comm == "remove") {

        return true;
    }
    if (comm == "dropClass") {

        return true;
    }
    if (comm == "replaceClass") {

        return true;
    }
    if (comm == "removeClass") {

        return true;
    }
    if (comm == "toggleEdgesClosure") {

        return true;
    }
    if (comm == "checkEdgeStatus") {

        return true;
    }
    if (comm == "isConnected") {

        return true;
    }
    if (comm == "printShortEdges") {

        return true;
    }
    if (comm == "printStudentZone") {

        return true;
    }
    if (comm == "verifySchedule") {

        return true;
    }

    return false;
}