#include "COptimizer.h"

COptimizer::COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize) {
    pc_problem = pcProblem;
    pd_penalties = pdPenalties;
    pc_population = new CPopulation(pc_problem, iPopulationSize);
}

COptimizer::~COptimizer() {
    pc_problem = nullptr;
    delete pc_population;
    pd_penalties = nullptr;
}

void COptimizer::vInitRandomPopulation() {
    pc_population->vInitRandomPopulation();
}

void COptimizer::vGadePopulation() {
    for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
        v_grade_individual(ii);
    }
}

void COptimizer::vShowPopulation() {
    for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
        std::cout << pc_population->pcGetIndividual(ii)->sToString() << std::endl;
    }
}

void COptimizer::v_grade_individual(int iIndividual) {
    double d_grade = 0;
    CIndividual *pc_individual = pc_population->pcGetIndividual(iIndividual);
    int *pi_violations = pc_individual->iGetViolations();

    for (int ii = 0; ii < VIOLATION_TYPES; ++ii) {
        d_grade += pd_penalties[ii] * pi_violations[ii];
    }

    pc_individual->vSetFitness(d_grade);

    pc_individual = nullptr;
    pi_violations = nullptr;
    delete pc_individual;
    delete pi_violations;
}

double COptimizer::dGetAdjustmentGrade(int iIndividual) {
    return pc_population->pcGetIndividual(iIndividual)->dGetFitness() / d_best_individual_grade;
}

double COptimizer::dGetFitness(int iIndividual) {
    return pc_population->pcGetIndividual(iIndividual)->dGetFitness();
}
