//
// Created by renew on 9/25/2020.
//

#ifndef HOMEWORK2_BUILD_H
#define HOMEWORK2_BUILD_H

#include <vector>
#include <ostream>
#include <tuple>
using Bridge = std::vector<int>;
using Bridges = std::vector<Bridge>;
int build(int w, int e, const Bridges &bridges);
bool doBridgesCross(const Bridge &first, const Bridge &second);
std::vector<Bridges> bridgesToBuild(const Bridges&);
bool operator==(const Bridge &, const Bridge &);
std::vector<Bridges> allPossibleBridgeCombinations(const Bridges &, std::vector<Bridges> &);
//For development purposes
std::ostream& operator<< (std::ostream& os, const std::vector<std::tuple<Bridge, Bridge>>&);
std::ostream& operator<< (std::ostream& os, const Bridges&);
std::ostream& operator<< (std::ostream& os, const Bridge &);
#endif //HOMEWORK2_BUILD_H
