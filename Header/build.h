// build.h
// Author: Tailon Russell
// Date: 9/25/2020.
// Purpose: The header file for the build function
//    and various other helper functions

#ifndef HOMEWORK2_BUILD_H
#define HOMEWORK2_BUILD_H

#include <vector>
using Bridge = std::vector<int>;
using Bridges = std::vector<Bridge>;
int build(int w, int e, const Bridges &bridges);
bool doBridgesCross(const Bridge &first, const Bridge &second);
std::vector<Bridges> bridgesToBuild(const Bridges&);
bool operator==(const Bridge &, const Bridge &);
std::vector<Bridges> allPossibleBridgeCombinations(const Bridges &, std::vector<Bridges> &);
#endif //HOMEWORK2_BUILD_H
