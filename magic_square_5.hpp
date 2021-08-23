#ifndef __MAGIC_SQUARE_5_HPP__
#define __MAGIC_SQUARE_5_HPP__

#include <vector>

#include "riddle_solver.hpp"

using namespace std;


//
// Magic Squares
//

class magic_square5_solver : public riddle_solver<int>
{
public:
    magic_square5_solver();

    ~magic_square5_solver();

    void set_size(int size);

protected:	// Overrides

    int check_placement();
    int get_next_element(int pos);
    void print_solution(vector<int> sol);

    void register_move(int pos, int val);
    void unregister_last_move();

private:	// Implemenation
    
    inline bool test_row(int r);
    inline bool test_column(int c);
    inline bool test_diagonal();
    inline bool test_reverse_diagonal();

    int order;
    int line_sum;
    vector<bool> used_tbl;
    
    int square_tbl[25];
    static int map_tbl[25];
    static int map_rev_tbl[25];
};

#endif //__MAGIC_SQUARE_5_HPP__