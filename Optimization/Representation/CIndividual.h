#ifndef L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
#define L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H

#include "../../Problem/CPcbProblem.h"
#include "CPath.h"

#define VIOLATION_TYPES 5

class CIndividual {

public:

    explicit CIndividual(CPcbProblem *pc_problem);
    ~CIndividual();

    void vInitializeRandomPaths();

private:
    CPcbProblem *pc_problem;
    CPath **pc_paths;
    int **pi_board;

    //k1 - liczba przecięć,
    //k2 - sumaryczna długość ścieżek,
    //k3 - sumaryczna liczba segmentów tworzących ścieżki.
    //k4 - liczba ścieżek poza płytką,
    //k5 - sumaryczna długość części ścieżek poza płytką.
    int *pi_violations;
    double d_fitness;

    int i_get_crossings();
    int i_get_length();
    int i_get_segments();
    int i_get_paths_outside();
    int i_get_length_outside();

    void v_set_random_paths(int iMaxStep);
    void v_bake();
    void v_set_violations();

    void v_deallocate_matrix(int **piMatrix, int iRows);
    void v_allocate_matrix(int ***piMatrix, int iColumns, int iRows);
    void v_initialize_matrix(int ***piMatrix, int iColumns, int iRows);
    void v_initialize_paths();
    void v_initialize_board();
    std::string s_get_points();

public:
    int *iGetViolations();

    void vSetFitness(double dFitness);
    double dGetFitness();

    CPath cGetPath(int id);
    std::string sToString();
};


#endif //L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
