#ifndef L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
#define L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H

#include "../Problem/CPcbProblem.h"
#include "CPopulation.h"
#include <iostream>

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
