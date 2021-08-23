#ifndef __8_QUEENS_HPP__
#define __8_QUEENS_HPP__

#include "riddle_solver.hpp"

using namespace std;

//
// 8 Queens Riddle
//

class q8_riddle_solver : public riddle_solver_int
{
public:
    q8_riddle_solver();

    ~q8_riddle_solver();

protected:
    int get_next_element(int pos);
    int check_placement();

    void print_solution(vector<int> sol);
};

#endif //__8_QUEENS_HPP__