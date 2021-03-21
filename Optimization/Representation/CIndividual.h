#ifndef L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
#define L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H

#include "../../Problem/CPcbProblem.h"
#include "CPath.h"

#define VIOLATION_TYPES 5
#define K1 0
#define K2 1
#define K3 2
#define K4 3
#define K5 4

class CIndividual {

public:

    explicit CIndividual(CPcbProblem *pc_problem);
    CIndividual(const CIndividual& cToCopy);
    ~CIndividual();

    void vInitializeRandomPaths();
    void vUpdate();
    void vMutate(int iPathIndex);

private:
    CPcbProblem *pc_problem;
    std::vector<CPath*> vc_paths;
    int **pi_board;
    int *pi_violations;
    double d_fitness;

    void v_set_random_paths();
    void v_bake();
    void v_set_violations();
    void v_initialize_path(int iIndex);

    static void v_allocate_matrix(int ***piMatrix, int iColumns, int iRows);
    static void v_initialize_matrix(int ***piMatrix, int iColumns, int iRows);
    static void v_deallocate_matrix(int **piMatrix, int iRows);
    void v_initialize_paths();
    void v_reset_board();
    void v_reset_violations();
    std::string s_get_points();
    std::string s_get_paths();

public:
    int *iGetViolations();

    void vSetFitness(double dFitness);
    double dGetFitness() const;
    std::string sToString();

    void vSetPath(int iIndex, CPath *pcPath);
    CPath *vGetPath(int iIndex);
};

#endif //L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
