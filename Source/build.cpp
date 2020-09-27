// build.cpp
// Author: Tailon Russell
// Date: 9/25/2020.
// Purpose: The source file for the build function
//    and various other helper functions

#include <iostream>
#include <algorithm>
#include <cmath>
#include "../Header/build.h"

// int build
// given the number of west and east cities and a list of bridges
//  return the max toll to charge of bridges built following client defined requirements
// Pre: bridges needs to be a valid vector of ints
int build(int w, int e, const Bridges &bridges) {
    if (bridges.empty()) { // given no bridges
        return 0;
    } else if (bridges.size() == 1) { // given one bridge
        return bridges[0][2];
    } else if(bridges.size() == 2) { // given two bridges
        if(doBridgesCross(bridges[0], bridges[1])) { // if bridges cross
            return std::max(bridges[0][2], bridges[1][2]);
        } else if (!doBridgesCross(bridges[0], bridges[1])) { //if bridges don't cross
            return bridges[0][2] + bridges[1][2];
        }
        return std::max(bridges[0][2], bridges[1][2]);

    } else { // given and arbitrary amount of bridges
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

// std::vector<Bridge> allPossibleBridgeCombinations
// given a list of Bridges and a list of lists of bridges generate all subsets of bridges
//   and return them
// This function is derived form the solution provide in this article
//    https://afteracademy.com/blog/print-all-subsets-of-a-given-set
std::vector<Bridges> allPossibleBridgeCombinations(const Bridges &bridges, std::vector<Bridges> &allBridgeCombos) {
    Bridges bridgeCombo;
    for(int index = 0; index < std::pow(2, bridges.size()); index++) {
        for(int i = 0; i < bridges.size(); i++) {
            if(index & (1 << i))  // Checks if the ith element is set
                bridgeCombo.push_back(bridges[i]);
        }
        allBridgeCombos.push_back(bridgeCombo);
        bridgeCombo.clear();
    }
    return allBridgeCombos;
}

//std::vector<Bridges> bridgesToBuild
// given a list of bridges
//  return a list of non-crossing bridges
std::vector<Bridges> bridgesToBuild(const Bridges &bridges) {
    std::vector<Bridges> allBridgesCombos;
    std::vector<Bridges> allowedBridgesCombos;
    allPossibleBridgeCombinations(bridges, allBridgesCombos);

    for(const auto &bridgeCombo: allBridgesCombos) { // For each combination of bridges
        for(const auto &firstBridge: bridgeCombo) {
            for(const auto &secondBridge: bridgeCombo) {
                if(firstBridge != secondBridge) { // If we are not looking at the same bridge
                    if(doBridgesCross(firstBridge, secondBridge)) { // Compare each bridge in the combo
                        goto EndOfLoop; // get out of the loop      //   to see if they cross
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

// bool operator==
// given two bridges
//   classify if they are equal or not
bool operator== (const Bridge &first, const Bridge &second) {
    return (first[0]==second[0] && first[1]==second[1] && first[2]==second[2]);
}

// bool doBridgesCross
// given two bridges
//   classify if they cross or not
bool doBridgesCross(const Bridge &first, const Bridge &second) {
    return (first[0] < second[0] && first[1] > second[1]) ||
            (first[0] > second[0] && first[1] < second[1]) ||
            first[0] == second[0] || first[1] == second[1];
}
