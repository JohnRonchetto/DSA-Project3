#include "helper.h"
#include <regex>

using namespace std;

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

    // need delimiter as it didn't know which ) was closing the actual string
    const regex cInsert(                                                   // (.+) catches rest of the line
    R"del(^\s*insert\s+"([A-Za-z][A-Za-z ]*)"\s+(\d{8})\s+(\d+)\s+([1-6])\s+(.+)\s*$)del");

    const regex cRemove(R"(^\s*remove\s+(\d{8})\s*$)");
    const regex cDrop(R"(^\s*dropClass\s+(\d{8})\s+([A-Z]{3}\d{4})\s*$)");
    const regex cReplace(R"(^\s*replaceClass\s+(\d{8})\s+([A-Z]{3}\d{4})\s+([A-Z]{3}\d{4})\s*$)");
    const regex cRemoveClass(R"(^\s*removeClass\s+([A-Z]{3}\d{4})\s*$)");
    const regex cToggleEdges(R"(^\s*toggleEdgesClosure\s+(\d+)\s+(.+)\s*$)");
    const regex cCheckEdge(R"(^\s*checkEdgeStatus\s+(\d+)\s+(\d+)\s*$)");
    const regex cConnected(R"(^\s*isConnected\s+(\d+)\s+(\d+)\s*$)");
    const regex cShortest(R"(^\s*printShortestEdges\s+(\d{8})\s*$)");
    const regex cZone(R"(^\s*printStudentZone\s+(\d{8})\s*$)");
    const regex cVerify(R"(^\s*verifySchedule\s+(\d{8})\s*$)");

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

            const std::regex classCodeFormat(R"([A-Z]{3}\d{4})");

            while (ss >> code) {
                if (!std::regex_match(code, classCodeFormat)) {
                    return "unsuccessful";
                }
                classCodes.push_back(code);
            }

            // check that there are N class codes
            if (classCodes.size() != N) {
                return "unsuccessful";
            }

            return "insert";

        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cRemove)) {
        try {
            UFID = std::stoi(m[1].str());
            return "remove";
        } catch (...) {
            return "unsuccessful";
        }
    }
    if (std::regex_match(command, m, cDrop)) {
        try {
            UFID = std::stoi(m[1].str());
            // just have the single class code
            classCodes.push_back(m[2].str());
            return "dropClass";
        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cReplace)) {
        try {
            UFID = std::stoi(m[1].str());
            classCodes.push_back(m[2].str());
            classCodes.push_back(m[3].str());
            return "replaceClass";
        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cRemoveClass)) {
        try {
            classCodes.push_back((m[1].str()));
            return "removeClass";
        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cToggleEdges)) {
        try {
            N = stoi(m[1].str());

            // parse the edges
            string strIDs = m[2].str();
            stringstream ss(strIDs);
            int id;

            while (ss >> id) {
                locationIDs.push_back(id);
            }

            // make sure that N corresponds to the number of ids
            if (locationIDs.size() != 2*N) {
                return "unsuccessful";
            }

            return "toggleEdgesClosure";


        } catch (...) {
            return "unsuccessful";
        }
    }
    if (std::regex_match(command, m, cCheckEdge)) {
        try {
            int id1 = std::stoi(m[1].str());
            int id2 = std::stoi(m[2].str());

            locationIDs.push_back(id1);
            locationIDs.push_back(id2);

            return "checkEdgeStatus";

        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cConnected)) {
        try {
            int id1 = std::stoi(m[1].str());
            int id2 = std::stoi(m[2].str());

            locationIDs.push_back(id1);
            locationIDs.push_back(id2);

            return "isConnected";

        } catch (...) {
            return "unsuccessful";
        }
    }
    if (std::regex_match(command, m, cShortest)) {
        try {
            UFID = std::stoi(m[1].str());

            return "printShortestEdges";

        } catch (...) {
            return "unsuccessful";
        }
    }
    if (std::regex_match(command, m, cZone)) {
        try {
            UFID = stoi(m[1].str());

            return "printStudentZone";

        } catch (...) {
            return "unsuccessful";
        }

    }
    if (std::regex_match(command, m, cVerify)) {
        try {
            UFID = stoi(m[1].str());

            return "verifySchedule";

        } catch (...) {
            return "unsuccessful";
        }

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
        CC.insert(name, UFID, residenceID, classCodes);
        return true;
    }
    if (comm == "remove") {
        CC.remove(UFID);
        return true;
    }
    if (comm == "dropClass") {
        CC.dropClass(UFID, classCodes[0]);
        return true;
    }
    if (comm == "replaceClass") {
        CC.replaceClass(UFID, classCodes[0], classCodes[1]);
        return true;
    }
    if (comm == "removeClass") {
        CC.removeClass(classCodes[0]);
        return true;
    }
    if (comm == "toggleEdgesClosure") {
        CC.toggleEdgesClosure(N, locationIDs);
        return true;
    }
    if (comm == "checkEdgeStatus") {
        CC.checkEdgeStatus(locationIDs[0], locationIDs[1]);
        return true;
    }
    if (comm == "isConnected") {
        CC.isConnected(locationIDs[0], locationIDs[1]);
        return true;
    }
    if (comm == "printShortEdges") {
        CC.printShortestEdges(UFID);
        return true;
    }
    if (comm == "printStudentZone") {
        CC.printStudentZone(UFID);
        return true;
    }
    if (comm == "verifySchedule") {
        CC.verifySchedule(UFID);
        return true;
    }

    return false;
}