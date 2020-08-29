//
// Created by r3v334 on 2020/8/21.
//

#ifndef ROS_WS_SOLVER_H
#define ROS_WS_SOLVER_H

#include <vector>
#include <set>
#include <cmath>



struct Solver {
    struct Point {
        double x, y;
    };

    struct Edge {
        int from, to;
    };

    std::vector<Point> points = {
            {1e9, 1e9},
            {0.5, -0.1},    //1
            {5.47, -0.1},    //2
            {10.045, -1.3},     //3
            {15.446, -0.1},     //4
            {15.45, -5.149},    //5
            {15.388, -9.03},    //6
            {8.466, -9},    //7
            {3.863, -8.955},     //8
            {0.519, -8.949},   //9
            {6.993, -4.512},     //10
            {9.203, -2.306}      //11
    };

    std::vector<Edge> edges = {
            {1, 2},
            {1, 9},
            {2, 4},
            {2, 10},
            {3, 4},
            {3, 11},
            {4, 5},
            {5, 6},
            {5, 11},
            {6, 7},
            {7, 8},
            {7, 10},
            {8, 9},
            {8, 10},
    };

    std::vector<int> g[12];

    double ans = 1000;
    std::vector<int> ans_vec, tmp_vec;
    std::multiset<int> mid_points;
    int goal;

    double get_dis(int pos1, int pos2) {
        return sqrt(pow(points[pos1].x - points[pos2].x, 2) + pow(points[pos1].y - points[pos2].y, 2));
    }

    double get_theta_from_points(int pos1, int pos2, int pos3) {
        double dis1 = get_dis(pos1, pos2);
        double dis2 = get_dis(pos2, pos3);
        double dis3 = get_dis(pos1, pos3);

        double theta = acos((pow(dis2, 2) + pow(dis1, 2) - pow(dis3, 2)) / (2 * dis1 * dis2)) ;
        if (std::isnan(theta)) return 0;
        return theta / 3.14 * 180.0;
    }

    void dfs(int last, int cur, double tmp) {
        if (tmp >= ans) return;
        if (mid_points.empty()) {
            if (cur == goal) {
                ans_vec = tmp_vec;
                ans = tmp;
                return;
            }
        }

        bool has_any = mid_points.count(cur);
        mid_points.erase(cur);
        for (int next : g[cur]) {
            if (next == last) continue;
            double theta = get_theta_from_points(last, cur, next);
            if (theta > 50) {
                tmp_vec.push_back(next);
                dfs(cur, next, tmp + get_dis(cur, next));
                tmp_vec.pop_back();
            }
        }
        if (has_any) mid_points.insert(cur);
    }

    void init() {
        for (const auto & i : edges) {
            g[i.from].push_back(i.to);
            g[i.to].push_back(i.from);
        }
    }


};


#endif //ROS_WS_SOLVER_H