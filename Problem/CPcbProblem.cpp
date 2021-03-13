#include "CPcbProblem.h"
#include "CPcbProblemLoader.h"


CPcbProblem::CPcbProblem(int iBoardX, int iBoardY, std::vector<int> vPoints) {
    i_board_size_x = iBoardX;
    i_board_size_y = iBoardY;
    i_paths_quantity = vPoints.size() / 4;
    vSetPoints(std::move(vPoints));

    s_file_name = nullptr;
}

CPcbProblem::CPcbProblem(std::string sFileName) {
    s_file_name = std::move(sFileName);

    i_board_size_x = 0;
    i_board_size_y = 0;
    i_paths_quantity = 0;
    pi_points = nullptr;
}

CPcbProblem::~CPcbProblem() {
    v_deallocate_matrix(pi_points, i_paths_quantity);
}

void CPcbProblem::vLoadFromFile() {
    auto cLoader = CPcbProblemLoader(this);
    cLoader.vLoad();
}

void CPcbProblem::vSetBoard(int iX, int iY) {
    i_board_size_x = iX;
    i_board_size_y = iY;
}

void CPcbProblem::vSetPoints(std::vector<int> vPoints) {
    i_paths_quantity = vPoints.size() / PATH_POINTS;
    v_allocate_matrix(&pi_points, PATH_POINTS, i_paths_quantity);

    for (int ii = 0; ii < i_paths_quantity; ii++) {
        for (int jj = 0; jj < PATH_POINTS; jj++) {
            pi_points[ii][jj] = vPoints.at(ii * PATH_POINTS + jj);
        }
    }
}

std::string CPcbProblem::sGetFile() {
    return s_file_name;
}

int CPcbProblem::iGetPathsQuantity() {
    return i_paths_quantity;
}

void CPcbProblem::v_deallocate_matrix(int **piMatrix, int iRows) {
    for (int ii = 0; ii < iRows; ii++) {
        delete piMatrix[ii];
    }
    delete piMatrix;
}

void CPcbProblem::v_allocate_matrix(int ***piMatrix, int iColumns, int iRows) {
    *piMatrix = new int *[iRows];
    for (int ii = 0; ii < iRows; ii++) {
        (*piMatrix)[ii] = new int[iColumns];
    }
}

std::string CPcbProblem::s_get_points() {
    std::string s_pcb_problem;
    for (int i = 0; i < i_paths_quantity; i++) {
        for (int j = 0; j < PATH_POINTS; j++) {
            s_pcb_problem += std::to_string(pi_points[i][j]) + " ";
        }
        s_pcb_problem += "\n";
    }
    return s_pcb_problem;
}

std::string CPcbProblem::sToString() {
    return "Board size: " + std::to_string(i_board_size_x) + " x " + std::to_string(i_board_size_y) + "\n" + s_get_points();
}

int CPcbProblem::iGetBoardDimension(bool dimension) {
    if (dimension) return i_board_size_x;
    else return i_board_size_y;
}

int CPcbProblem::iGetPoint(int iRow, int iColumn) {
    return pi_points[iRow][iColumn];
}

int *CPcbProblem::iGetPoints(int iPathId) {
    return pi_points[iPathId];
}
