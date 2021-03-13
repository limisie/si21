#include "COptimizer.h"

COptimizer::COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize, int iMode) {
    pc_problem = pcProblem;
    pd_penalties = pdPenalties;
    pc_population = new CPopulation(pc_problem, iPopulationSize);
    i_stop_condition_mode = iMode;
    i_iterations = 0;
    d_expected_fitness = 0;
}

COptimizer::~COptimizer() {
    pc_problem = nullptr;
    delete pc_population;
    pd_penalties = nullptr;
}

void COptimizer::vSetExpectedFitness(double dExpectedFitness) {
    d_expected_fitness = dExpectedFitness;
}

void COptimizer::vSetNumberOfIterations(int iIterations) {
    i_iterations = iIterations;
}

CIndividual *COptimizer::pcRandom() {
    while (!b_stop_condition()) {
        for (int ii = 0; ii < pc_population->iGetSize(); ii++) {
            if (ii != pc_population->iGetBestIndividualIndex()) {
                CIndividual *pc_individual = pc_population->pcInitializeRandomIndividual(ii);
                v_grade_individual(pc_individual);

                if (pc_individual->dGetFitness() < pc_population->dGetBestFitness()) {
                    pc_population->vSetBestFitness(pc_individual->dGetFitness());
                    pc_population->vSetBestIndividual(ii);
                }
            }
        }
        pc_population->vDie();
    }
    return pc_population->pcGetBestIndividual();
}

bool COptimizer::b_stop_condition() {
    switch (i_stop_condition_mode) {
        case 0:
            return i_iterations < pc_population->iGetGeneration();
        case 1:
            return d_expected_fitness > pc_population->dGetBestFitness();
    }
    return true;
}

void COptimizer::v_grade_individual(CIndividual *pcIndividual) {
    double d_grade = 0;
    int *pi_violations = pcIndividual->iGetViolations();

    for (int ii = 0; ii < VIOLATION_TYPES; ++ii) {
        d_grade += pd_penalties[ii] * (double)pi_violations[ii];
    }

    pcIndividual->vSetFitness(d_grade);
}

double COptimizer::dGetAdjustmentGrade(int iIndividual) {
    return pc_population->pcGetIndividual(iIndividual)->dGetFitness() / pc_population->dGetBestFitness();
}

double COptimizer::dGetFitness(int iIndividual) {
    return pc_population->pcGetIndividual(iIndividual)->dGetFitness();
}
