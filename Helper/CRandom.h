#ifndef L1_ALGORYTMY_GENETYCZNE_CRANDOM_H
#define L1_ALGORYTMY_GENETYCZNE_CRANDOM_H

#include <chrono>
#include <random>

class CRandom {

public:
    CRandom();
    explicit CRandom(unsigned int iSeed);

    void vSetSeed(unsigned int iSeed);
    int iRandomInt();
    int iRandomIntInclusiveRange(int iMin, int iMax);
    int iRandomIntInclusiveRange(double dMin, double dMax);
    double dRandomDouble();
    double dRandomDoubleInclusiveRange(double dMin, double dMax);

private:
    unsigned int i_seed;
    std::mt19937 mt_engine;
};

#endif //L1_ALGORYTMY_GENETYCZNE_CRANDOM_H
