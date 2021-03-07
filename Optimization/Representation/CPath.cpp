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

std::tuple<int, int> CPath::iGetSegment(int iSegmentId) {
    return v_path.at(iSegmentId);
}

int CPath::iGetStartPoints(bool dimension) {
    if (dimension) return i_start_x;
    else return i_start_y;
}

void CPath::vSetRandomPath(int iMaxX, int iMaxY) {
    int i_temp = 0;
    int i_current_x = i_start_x;
    int i_current_y = i_start_y;
    int i_max_step = std::max(iMaxX, iMaxY);
    CRandom c_random = CRandom();

    while (i_current_x != i_end_x && i_current_y != i_end_y) {
        int i_direction = c_random.iRandomIntInclusiveRange(UP, LEFT);
        int i_step = c_random.iRandomIntInclusiveRange(1, i_max_step);

        switch (i_direction) {
            case UP:
                i_temp = i_current_y + i_step;
                if(i_temp < iMaxY) {
                    i_current_y = i_temp;
                } else {
                    i_step = iMaxY - i_current_y;
                    i_current_y = iMaxY;
                }
                break;
            case RIGHT:
                i_temp = i_current_x + i_step;
                if(i_temp < iMaxX) {
                    i_current_x = i_temp;
                } else {
                    i_step = iMaxX - i_current_x;
                    i_current_x = iMaxX;
                }
                break;
            case DOWN:
                i_temp = i_current_y - i_step;
                if(i_temp > 0) {
                    i_current_y = i_temp;
                } else {
                    i_step = i_current_y;
                    i_current_y = 0;
                }
                break;
            case LEFT:
                i_temp = i_current_x - i_step;
                if(i_temp > 0) {
                    i_current_x = i_temp;
                } else {
                    i_step = i_current_x;
                    i_current_x = 0;
                }
                break;
        }

        std::tuple<int, int> t_segment(i_direction, i_step);
        v_path.push_back(t_segment);
    }
}