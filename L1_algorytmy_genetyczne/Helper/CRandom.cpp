#include "CRandom.h"

CRandom::CRandom() {
    mt_engine.seed(rand_dev());
}

CRandom::CRandom(unsigned int iSeed) {
    i_seed = iSeed;
    mt_engine.seed(i_seed);
}

void CRandom::vSetSeed(unsigned int iSeed) {
    if (iSeed != i_seed) {
        i_seed = iSeed;
        mt_engine.seed(i_seed);
    }
}

int CRandom::iRandomInt() {
    std::uniform_int_distribution<int> iDistribution(mt_engine._Min, mt_engine._Max);
    return iDistribution(mt_engine);
}

int CRandom::iRandomIntInclusiveRange(int iMin, int iMax) {
    std::uniform_int_distribution<int> iDistribution(iMin, iMax);
    return iDistribution(mt_engine);
}

int CRandom::iRandomIntInclusiveRange(double dMin, double dMax) {
    std::uniform_int_distribution<int> iDistribution(dMin, dMax);
    return iDistribution(mt_engine);
}

double CRandom::dRandomDouble() {
    std::uniform_real_distribution<double> dDistribution(mt_engine._Min, mt_engine._Max);
    return dDistribution(mt_engine);
}

double CRandom::dRandomDoubleInclusiveRange(double dMin, double dMax) {
    std::uniform_real_distribution<double> dDistribution(dMin, dMax);
    return dDistribution(mt_engine);
}
