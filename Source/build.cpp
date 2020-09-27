//
// Created by renew on 9/25/2020.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include "../Header/build.h"

int build(int w, int e, const Bridges &bridges) {
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
        std::vector<Bridges> allowedBridgeCombos = bridgesToBuild(bridges);

        int maxToll = 0;
        for(const auto &bridgeCombo: allowedBridgeCombos) {
            int toll = 0;
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


std::vector<Bridges> allPossibleBridgeCombinations(const Bridges &bridges, std::vector<Bridges> &allBridgeCombos) {
    Bridges bridgeCombo;
    for(int index = 0; index < std::pow(2, bridges.size()); index++) {
        for(int i = 0; i < bridges.size(); i++) {
            if(index & (1 << i))
                bridgeCombo.push_back(bridges[i]);
        }
        allBridgeCombos.push_back(bridgeCombo);
        bridgeCombo.clear();
    }
    return allBridgeCombos;
}


std::vector<Bridges> bridgesToBuild(const Bridges &bridges) {
    std::vector<Bridges> allBridgesCombos;
    std::vector<Bridges> allowedBridgesCombos;
    allPossibleBridgeCombinations(bridges, allBridgesCombos);

    for(const auto &bridgeCombo: allBridgesCombos) {
        for(const auto &firstBridge: bridgeCombo) {
            for(const auto &secondBridge: bridgeCombo) {
                if(firstBridge != secondBridge) {
                    if(doBridgesCross(firstBridge, secondBridge)) {
                        goto EndOfLoop;
                    }
                }
            }
        }
        allowedBridgesCombos.push_back(bridgeCombo);

        EndOfLoop:
        ;
    }
    return allowedBridgesCombos;
}

bool operator== (const Bridge &first, const Bridge &second) {
    return (first[0]==second[0] && first[1]==second[1] && first[2]==second[2]);
}

bool doBridgesCross(const Bridge &first, const Bridge &second) {
    return (first[0] < second[0] && first[1] > second[1]) ||
            (first[0] > second[0] && first[1] < second[1]) ||
            first[0] == second[0] || first[1] == second[1];
}

std::ostream& operator<< (std::ostream& os, const Bridge &bridgeToPrint){
    os << "{" << bridgeToPrint[0] << ", " << bridgeToPrint[1] << ", ";
    os << bridgeToPrint[2] << "}";
    return os;
}

std::ostream& operator<< (std::ostream& os, const Bridges &bridgesToPrint){
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
