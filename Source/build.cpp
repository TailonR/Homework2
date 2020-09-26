//
// Created by renew on 9/25/2020.
//

#include <iostream>
#include <algorithm>
#include "../Header/build.h"

int build(int w, int e, const std::vector<Bridge> &bridges) {
    if (bridges.empty()) {
        return 0;
    } else if (bridges.size() == 1) {
        return bridges[0][2];
    } else if(bridges.size() == 2) {
        if(bridges[0][0] == bridges[1][0] || bridges[0][1] == bridges[1][1]) {
            return std::max(bridges[0][2], bridges[1][2]);
        } else if (!doBridgesCross(bridges[0], bridges[1])) {
            return bridges[0][2] + bridges[1][2];
        }
        return std::max(bridges[0][2], bridges[1][2]);

    } else {
        std::vector<std::tuple<Bridge, Bridge>> crossing;

        std::cout << "Possible Bridges:\n" << bridges << "\n" << std::endl;

        crossingBridges(bridges, crossing);
        std::vector<std::vector<Bridge>> allowedBridgeCombos = bridgesToBuild(w, e, bridges);

        std::cout << "Crossing: \n" << crossing << std::endl;

        int maxToll = 0;
        for(const auto &bridgeCombo: allowedBridgeCombos) {
            int toll = 0;
            std::cout << "Bridges: \n" << bridgeCombo << "\n" << std::endl;
            for(const auto &bridge: bridgeCombo) {
                toll += bridge[2];
            }
            if (toll > maxToll) {
                maxToll = toll;
            }
        }

        return maxToll;
    }
}

std::vector<std::vector<Bridge>> bridgesToBuild(int w, int e, const std::vector<Bridge> &bridges) {
//    Bridge maxSingleBridge = singleBridgeMaxToll(bridges);
    std::vector<std::vector<Bridge>> allNonCrossingBridgesCombos;
    std::vector<Bridge> nonCrossingBridgeCombos;
//    bool crossing = false;
    for(const auto& firstBridge: bridges) {
        nonCrossingBridgeCombos.clear();
        nonCrossingBridgeCombos.push_back(firstBridge);
        for(const auto& secondBridge: bridges) {
            if(firstBridge != secondBridge) {
                if(!doBridgesCross(firstBridge, secondBridge)) {
                    nonCrossingBridgeCombos.push_back(secondBridge);
                    if(nonCrossingBridgeCombos.size() == std::min(w,e)-1) {
                        allNonCrossingBridgesCombos.push_back(nonCrossingBridgeCombos);
                        nonCrossingBridgeCombos.clear();
                    }
                }
            }
        }
        allNonCrossingBridgesCombos.push_back(nonCrossingBridgeCombos);
    }
    return allNonCrossingBridgesCombos;
}
bool operator== (const Bridge &first, const Bridge &second) {
    return (first[0]==second[0] && first[1]==second[1] && first[2]==second[2]);
}

bool doBridgesCross(const Bridge &first, const Bridge &second) {
    return (first[0] < second[0] && first[1] > second[1]) ||
            (first[0] > second[0] && first[1] < second[1]) ||
            first[0] == second[0] || first[1] == second[1];
}
bool doBridgesStartOrEndTheSame(const Bridge &first, const Bridge &second) {
    return (first[0] == second[0] || first[1] > second[1]) ||
            (first[0] > second[0] && first[1] < second[1]);
}

void crossingBridges(const std::vector<Bridge> &bridges, std::vector<std::tuple<Bridge, Bridge>> &pairsOfBridges) {
    for(const auto& firstBridge: bridges) {
        for(const auto& secondBridge: bridges) {
            if (firstBridge != secondBridge) {
                if (doBridgesCross(firstBridge, secondBridge)) {
                    pairsOfBridges.emplace_back(firstBridge, secondBridge);
                }
            } else {

            }
        }
    }
}

Bridge singleBridgeMaxToll(const std::vector<Bridge> &bridges) {
    int toll = 0;
    for (const auto& bridge: bridges) {
        if (bridge[2] > toll) {
            toll = bridge[2];
        }
    }
    return *std::find_if(bridges.begin(), bridges.end(), [&toll](const Bridge& i) { return i[2] == toll; });
}

std::ostream& operator<< (std::ostream& os, const Bridge &bridgeToPrint){
    os << "{" << bridgeToPrint[0] << ", " << bridgeToPrint[1] << ", ";
    os << bridgeToPrint[2] << "}";
    return os;
}

std::ostream& operator<< (std::ostream& os, const std::vector<Bridge> &bridgesToPrint){
    for(const auto& bridge: bridgesToPrint) {
        os << "{" << bridge[0] << ", " << bridge[1] << ", ";
        os << bridge[2] << "} ";
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const std::vector<std::tuple<Bridge, Bridge>> &bridgesToPrint){
    for(const auto& bridges: bridgesToPrint) {
        os << "{" << std::get<0>(bridges)[0] << ", " << std::get<0>(bridges)[1] << ", ";
        os << std::get<0>(bridges)[2] << "}";
        os << " && " << "{" << std::get<1>(bridges)[0]  << ", " << std::get<1>(bridges)[1] << ", ";
        os << std::get<1>(bridges)[2] << "}";
        os << "\n\n";
    }
    return os;
}
