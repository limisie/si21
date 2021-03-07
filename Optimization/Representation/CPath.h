#ifndef L1_ALGORYTMY_GENETYCZNE_CPATH_H
#define L1_ALGORYTMY_GENETYCZNE_CPATH_H

#include "../../Helper/CRandom.h"

#include <tuple>
#include <vector>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class CPath {

public:
    CPath();
    CPath(int iStartX, int iStartY, int iEndX, int iEndY);

    void vSetRandomPath(int iMaxX, int iMaxY);

    int iGetStartPoints(bool dimension);
    std::tuple<int, int> iGetSegment(int iSegmentId);
    int iGetSegmentsQuantity();
    static std::vector<std::tuple<int, int>> vGetPath();
    void vSetPath(std::vector<std::tuple<int, int>> vPath);

private:
    int i_start_x;
    int i_start_y;
    int i_end_x;
    int i_end_y;

    std::vector<std::tuple<int, int>> v_path;
};


#endif //L1_ALGORYTMY_GENETYCZNE_CPATH_H
