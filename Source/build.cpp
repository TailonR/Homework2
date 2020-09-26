//
// Created by renew on 9/25/2020.
//

#include "../Header/build.h"
int build(int w, int e, const std::vector<Bridge> &bridges) {
    if (bridges.size() == 1) {
        return bridges[0][2];
    } else if (bridges.size() == 2) {
        if (!doBridgesCross(bridges[0], bridges[1])) {
            return std::max(bridges[0][2], bridges[1][2]);
        }
    }else {
        return 0;
    }
}

bool doBridgesCross(const Bridge &first, const Bridge &second) {
    return true;
}
