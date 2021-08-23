#ifndef __MAGIC_SQUARES_HPP__
#define __MAGIC_SQUARES_HPP__

#include <vector>

#include "riddle_solver.hpp"

using namespace std;


//
// Magic Squares
//

class magic_square_solver : public riddle_solver<int>
{
public:
    magic_square_solver();

    ~magic_square_solver();

    void set_order(int ord);

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
    inline bool test_partial_row(int r, int c);
    inline bool test_partial_column(int c, int r);
    inline bool test_partial_diagonal(int r);
    inline bool test_partial_reverse_diagonal(int r);

    int order;
    int line_sum;
    vector<bool> used_tbl;
    vector<int> min_sum_tbl;
};

#endif //__MAGIC_SQUARES_HPP__