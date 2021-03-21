#include "CPath.h"

#include <utility>

CPath::CPath(int iStartX, int iStartY, int iEndX, int iEndY) {
    i_start_x = iStartX;
    i_start_y = iStartY;
    i_end_x = iEndX;
    i_end_y = iEndY;
    i_path_length = 0;
    v_path = std::vector<std::tuple<int, int>>();
}

CPath::CPath() {
    i_start_x = 0;
    i_start_y = 0;
    i_end_x = 0;
    i_end_y = 0;
    i_path_length = 0;
    v_path = std::vector<std::tuple<int, int>>();
}

std::vector<std::tuple<int, int>> CPath::vGetPath() {
    return v_path;
}

void CPath::vSetPath(CPath *pcPath) {
    std::vector<std::tuple<int, int>> v_path_to_copy = pcPath->vGetPath();
    v_path = std::move(v_path_to_copy);
    i_path_length = pcPath->iGetPathLength();
}

int CPath::iGetSegmentsQuantity() {
    return v_path.size();
}

std::tuple<int, int> CPath::iGetSegment(int iSegmentId) {
    return v_path.at(iSegmentId);
}

int CPath::iGetStartPoints(bool dimension) const {
    if (dimension) return i_start_x;
    else return i_start_y;
}

int CPath::i_get_direction(bool bX, int iCurrent) {
    int i_end;
    int i_directions[2];
    int i_direction = -1;

    if (bX) {
        i_directions[0] = RIGHT;
        i_directions[1] = LEFT;
        i_end = i_end_x;
    } else {
        i_directions[0] = DOWN;
        i_directions[1] = UP;
        i_end = i_end_y;
    }

    if (iCurrent < i_end) {
        i_direction = i_directions[0];
    } else if (iCurrent > i_end){
        i_direction = i_directions[1];
    }
    return i_direction;
}

int CPath::i_get_random_direction(int iCurrentX, int iCurrentY) {
    CRandom c_random = CRandom();

    int i_direction_x = i_get_direction(true, iCurrentX);
    int i_direction_y = i_get_direction(false, iCurrentY);
    std::vector<int> vi_directions = std::vector<int>();

    if (i_direction_x != -1) {
        vi_directions.push_back(i_direction_x);
    } else {
        vi_directions.push_back(RIGHT);
        vi_directions.push_back(LEFT);
    }
    if (i_direction_y != -1) {
        vi_directions.push_back(i_direction_y);
    } else {
        vi_directions.push_back(UP);
        vi_directions.push_back(DOWN);
    }
//    if (vi_directions.empty()) {
//        vi_directions.push_back(UP);
//        vi_directions.push_back(RIGHT);
//        vi_directions.push_back(DOWN);
//        vi_directions.push_back(LEFT);
//    }

    int i_random_direction = vi_directions[c_random.iRandomInt() % vi_directions.size()];
    return i_random_direction;
}


int CPath::i_get_random_step() {
    return 0;
}

void CPath::vSetRandomPath(int iMaxX, int iMaxY) {
    int i_temp;
    int i_current_x = i_start_x;
    int i_current_y = i_start_y;
    int i_max_step = std::max(iMaxX, iMaxY);
    CRandom c_random = CRandom();

    i_path_length = 0;
    while (i_current_x != i_end_x || i_current_y != i_end_y) {
        int i_direction = i_get_random_direction(i_current_x, i_current_y);
        int i_step = c_random.iRandomIntInclusiveRange(1, i_max_step);

        switch (i_direction) {
            case UP:
                i_temp = i_current_y - i_step;
                if(i_temp > 0) {
                    i_current_y = i_temp;
                } else {
                    i_step = i_current_y;
                    i_current_y = 0;
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
                i_temp = i_current_y + i_step;
                if(i_temp < iMaxY) {
                    i_current_y = i_temp;
                } else {
                    i_step = iMaxY - i_current_y;
                    i_current_y = iMaxY;
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
        if (i_step > 0) {
            if(!v_path.empty() && get<0> (v_path.back()) == i_direction) {
                get<1>(v_path.back()) = get<1>(v_path.back()) + i_step;
            } else {
                std::tuple<int, int> t_segment(i_direction, i_step);
                v_path.push_back(t_segment);
            }
            i_path_length += i_step;
        }
    }

}

int CPath::iGetPathLength() {
    return i_path_length;
}

std::string CPath::sToString() {
    std::string s_path;
    for (int ii = 0; ii < v_path.size(); ++ii) {
        s_path += std::to_string(get<0>(v_path[ii])) + " ";
        s_path += std::to_string(get<1>(v_path[ii])) + "\n";
    }
    return s_path;
}
