//
// Created by renew on 9/25/2020.
//

#ifndef HOMEWORK2_BUILD_H
#define HOMEWORK2_BUILD_H

#include <vector>
#include <ostream>
#include <tuple>
using Bridge = std::vector<int>;
//using Bridges = std::vector<Bridge>;
int build(int w, int e, const std::vector<Bridge> &bridges);
bool doBridgesCross(const Bridge &first, const Bridge &second);
bool doBridgesStartOrEndTheSame(const Bridge &first, const Bridge &second);
void crossingBridges(const std::vector<Bridge> &bridges, std::vector<std::tuple<Bridge, Bridge>> &pairsOfCrossingBridges);
//Bridge singleBridgeMaxToll(const std::vector<Bridge> &bridges);
std::vector<std::vector<Bridge>> bridgesToBuild(int , int, const std::vector<Bridge>&);
bool operator==(const Bridge &, const Bridge &);
//For development purposes
std::ostream& operator<< (std::ostream& os, const std::vector<std::tuple<Bridge, Bridge>>&);
std::ostream& operator<< (std::ostream& os, const std::vector<Bridge>&);
std::ostream& operator<< (std::ostream& os, const Bridge &);
#endif //HOMEWORK2_BUILD_H
