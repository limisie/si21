#ifndef L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
#define L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H

//k1 - liczba przecięć,
//k2 - sumaryczna długość ścieżek,
//k3 - sumaryczna liczba segmentów tworzących ścieżki.
//k4 - liczba ścieżek poza płytką,
//k5 - sumaryczna długość części ścieżek poza płytką.

#include "../Problem/CPcbProblem.h"
#include "CPopulation.h"

class COptimizer {

public:
    COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize);
    ~COptimizer();

    void vInitRandomPopulation();
    void vGadePopulation();
    void vShowPopulation();

    double dGetAdjustmentGrade(int iIndividual);
    double dGetFitness(int iIndividual);

private:
    CPcbProblem *pc_problem;
    CPopulation *pc_population;
    double *pd_penalties;
    double d_best_individual_grade;

    void v_grade_individual(int iIndividual);

};

#endif //L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
