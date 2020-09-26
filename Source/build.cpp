//
// Created by renew on 9/25/2020.
//

#include "../Header/build.h"
int build(int w, int e, const std::vector<Bridge> &bridges) {
    if (bridges.size() == 1) {
        return bridges[0][2];
    } else if (bridges.size() == 2) {
        if(bridges[0][0] == bridges[1][0] || bridges[0][1] == bridges[1][1]) {
            return std::max(bridges[0][2], bridges[1][2]);
        } else if (!doBridgesCross(bridges[0], bridges[1])) {
            return bridges[0][2] + bridges[1][2];
        }
        return std::max(bridges[0][2], bridges[1][2]);
    } else {
        return 0;
    }
}

bool doBridgesCross(const Bridge &first, const Bridge &second) {
    return (first[0] < second[0] && first[1] > second[1]) ||
            (first[0] > second[0] && first[1] < second[1]);
}
