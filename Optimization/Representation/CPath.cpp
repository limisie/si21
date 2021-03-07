#include "CPath.h"

CPath::CPath(int iStartX, int iStartY, int iEndX, int iEndY) {
    i_start_x = iStartX;
    i_start_y = iStartY;
    i_end_x = iEndX;
    i_end_y = iEndY;
}

CPath::CPath() {
    i_start_x = 0;
    i_start_y = 0;
    i_end_x = 0;
    i_end_y = 0;
}

std::vector<std::tuple<int, int>> CPath::vGetPath() {
    return std::vector<std::tuple<int, int>>();
}

void CPath::vSetPath(std::vector<std::tuple<int, int>> vPath) {
    v_path = vPath;
}

int CPath::iGetSegmentsQuantity() {
    return v_path.size();
}

void CPath::vSetRandomPath(int iMaxStep) {
    int i_current_x = i_start_x;
    int i_current_y = i_start_y;

    while (i_current_x != i_end_x && i_current_y != i_end_y) {
//        int i_direction =
        //TODO: ukladaj sciezke
        //problem: maksymalny krok o długości boku płytki?
    }
}
