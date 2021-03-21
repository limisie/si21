#include "CIndividual.h"

CIndividual::CIndividual(CPcbProblem *pcProblem) {
    pc_problem = pcProblem;
    int i_paths = pc_problem->iGetPathsQuantity();
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);

    vc_paths = std::vector<CPath*>(i_paths);
    v_initialize_paths();

    v_allocate_matrix(&pi_board, i_board_x, i_board_y);

    pi_violations = new int[VIOLATION_TYPES];
    d_fitness = 0;
}

CIndividual::CIndividual(const CIndividual& cToCopy) {
    pc_problem = cToCopy.pc_problem;
    int i_paths = pc_problem->iGetPathsQuantity();
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);

    vc_paths = std::vector<CPath*>(i_paths);
    v_initialize_paths();
    for (int ii = 0; ii < cToCopy.vc_paths.size(); ++ii) {
        vc_paths[ii]->vSetPath(cToCopy.vc_paths[ii]);
    }

    v_allocate_matrix(&pi_board, i_board_x, i_board_y);
    for (int ii = 0; ii < i_board_y; ++ii) {
        for (int jj = 0; jj < i_board_x; ++jj) {
            pi_board[ii][jj] = cToCopy.pi_board[ii][jj];
        }
    }

    pi_violations = new int[VIOLATION_TYPES];
    for (int ii = 0; ii < VIOLATION_TYPES; ++ii) {
        pi_violations[ii] = cToCopy.pi_violations[ii];
    }

    d_fitness = cToCopy.d_fitness;
}

CIndividual::~CIndividual() {
    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        delete vc_paths[ii];
    }

    delete [] pi_violations;
    v_deallocate_matrix(pi_board, pc_problem->iGetPathsQuantity());
}

void CIndividual::vInitializeRandomPaths() {
    v_set_random_paths();
    v_bake();
    v_set_violations();
}

void CIndividual::vUpdate() {
    v_bake();
    v_set_violations();
}

void CIndividual::v_set_random_paths() {
    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        vc_paths[ii]->vSetRandomPath(pc_problem->iGetBoardDimension(true) - 1, pc_problem->iGetBoardDimension(false) - 1);
    }
}

void CIndividual::vMutate(int iPathIndex) {
    delete vc_paths[iPathIndex];
    v_initialize_path(iPathIndex);
    vc_paths[iPathIndex]->vSetRandomPath(pc_problem->iGetBoardDimension(true) - 1, pc_problem->iGetBoardDimension(false) - 1);
}

void CIndividual::v_bake() {
    v_reset_board();

    int i_current_x, i_current_y, i_new_position_x, i_new_position_y, i_direction, i_step, i_start, i_end = 0;
    bool b_direction = false;

    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        i_current_x = vc_paths[ii]->iGetStartPoints(true);
        i_current_y = vc_paths[ii]->iGetStartPoints(false);
        i_new_position_x = i_current_x;
        i_new_position_y = i_current_y;

        for (int jj = 0; jj < vc_paths[ii]->iGetSegmentsQuantity(); ++jj) {
            pi_board[i_current_y][i_current_x] += 1;

            i_direction = get<0> (vc_paths[ii]->iGetSegment(jj));
            i_step = get<1> (vc_paths[ii]->iGetSegment(jj));

            switch (i_direction) {
                case UP:
                    i_new_position_y -= i_step;
                    i_start = i_new_position_y;
                    i_end = i_current_y;
                    b_direction = false;
                    break;
                case RIGHT:
                    i_new_position_x += i_step;
                    i_start = i_current_x;
                    i_end = i_new_position_x;
                    b_direction = true;
                    break;
                case DOWN:
                    i_new_position_y += i_step;
                    i_start = i_current_y;
                    i_end = i_new_position_y;
                    b_direction = false;
                    break;
                case LEFT:
                    i_new_position_x -= i_step;
                    i_start = i_new_position_x;
                    i_end = i_current_x;
                    b_direction = true;
                    break;
            }
            for (int kk = i_start + 1; kk < i_end; ++kk) {
                if (b_direction) {
                    pi_board[i_current_y][kk] += 1;
                } else {
                    pi_board[kk][i_current_x] += 1;
                }
            }
            i_current_x = i_new_position_x;
            i_current_y = i_new_position_y;
        }
    }
}

void CIndividual::v_set_violations() {
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);
    int i_paths = pc_problem->iGetPathsQuantity();
    v_reset_violations();

    for (int ii = 0; ii < i_board_y; ++ii) {
        for (int jj = 0; jj < i_board_x; ++jj) {
            if(pi_board[ii][jj] > 1) {
                pi_violations[K1] += pi_board[ii][jj] - 1;
            }
        }
    }

    for (int ii = 0; ii < i_paths; ++ii) {
        pi_violations[K2] += vc_paths[ii]->iGetPathLength();
        pi_violations[K3] += vc_paths[ii]->iGetSegmentsQuantity();
    }
}

void CIndividual::v_allocate_matrix(int ***piMatrix, int iColumns, int iRows) {
    *piMatrix = new int *[iRows];
    for (int ii = 0; ii < iRows; ii++) {
        (*piMatrix)[ii] = new int[iColumns];
    }
}

void CIndividual::v_initialize_matrix(int ***piMatrix, int iColumns, int iRows) {
    for (int ii = 0; ii < iRows; ii++) {
        for (int jj = 0; jj < iColumns; ++jj) {
            (*piMatrix)[ii][jj] = 0;
        }
    }
}

void CIndividual::v_deallocate_matrix(int **piMatrix, int iRows) {
    for (int ii = 0; ii < iRows; ii++) {
        delete [] piMatrix[ii];
    }
    delete [] piMatrix;
}

void CIndividual::v_initialize_paths() {
    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        v_initialize_path(ii);
    }
}

void CIndividual::v_initialize_path(int iIndex) {
        int i_start_x = pc_problem->iGetPoints(iIndex)[0];
        int i_start_y = pc_problem->iGetPoints(iIndex)[1];
        int i_end_x = pc_problem->iGetPoints(iIndex)[2];
        int i_end_y = pc_problem->iGetPoints(iIndex)[3];

        vc_paths[iIndex] = new CPath(i_start_x, i_start_y, i_end_x, i_end_y);
}

void CIndividual::v_reset_board() {
    v_initialize_matrix(&pi_board, pc_problem->iGetBoardDimension(true), pc_problem->iGetBoardDimension(false));

    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        pi_board[pc_problem->iGetPoint(ii, 3)][pc_problem->iGetPoint(ii, 2)] += 1;
    }
}

void CIndividual::v_reset_violations() {
    for (int ii = 0; ii < VIOLATION_TYPES; ++ii) {
        pi_violations[ii] = 0;
    }
}

std::string CIndividual::s_get_points() {
    std::string s_board;
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);

    for (int i = 0; i < i_board_y; i++) {
        for (int j = 0; j < i_board_x; j++) {
            s_board += std::to_string(pi_board[i][j]) + " ";
        }
        s_board += "\n";
    }

    return s_board;
}

std::string CIndividual::s_get_paths() {
    std::string s_paths;

    for (int i = 0; i < vc_paths.size(); i++) {
        s_paths += vc_paths[i]->sToString();
    }

    return s_paths;
}

void CIndividual::vSetPath(int iIndex, CPath *pcPath) {
    vc_paths[iIndex]->vSetPath(pcPath);
}

CPath *CIndividual::vGetPath(int iIndex) {
    return vc_paths[iIndex];
}

void CIndividual::vSetFitness(double dFitness) {
    d_fitness = dFitness;
}

double CIndividual::dGetFitness() const {
    return d_fitness;
}

int *CIndividual::iGetViolations() {
    return pi_violations;
}

std::string CIndividual::sToString() {
    return s_get_points() +"fitness: " + std::to_string(d_fitness) + "\n";
}