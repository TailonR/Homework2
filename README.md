# Solution to Homework2 CS411 UAF
This solution finds the optimal solution to the problem via exhaustive search

This project was developed in Clion

# The Problem
As stated in the Assignment_Instructions, the goal is to find the combination of 
bridges to build between cities where:
* No bridges cross
* No city can be reached by two bridges
* The toll can be charded the maximum amount

The definition for bridges crossing are if a < c && b > d or c < a && d > b

# Key Highlights
The biggest issue I had to tackle, that once solved everything fell into place, 
was getting the correct combination of bridges to build.
This was done with two functions:
```c++
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
```
This function uses bit operations to get all possible combinations of bridges. We needed to have all subsets of the 
given bridges in order know which combinations of bridges are allowed. A subtle difference, but I nneded to understand 
that I am dealing with subsets of bridges and not simply a combination of bridges.

```c++
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
```
This function uses the result of allPossibleBridgeCombinations and finds allowed combinations using the function doBridgesCross.
