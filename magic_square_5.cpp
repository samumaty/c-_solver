#include <vector>
#include <iostream>

#include "magic_square_5.hpp"

using namespace std;


//
// Magic Squares
//

int 
magic_square5_solver::map_tbl[25] = 
                      { 0,  1,  2,  3,  4,
                        5, 10, 15, 20,  6,
                        7,  8,  9, 11, 16,
                       21, 12, 13, 14, 17,
                       22, 18, 19, 23, 24};

int 
magic_square5_solver::map_rev_tbl[25] = 
                      { 0,  1,  2,  3,  4,
                        5,  9, 10, 11, 12,
                        6, 13, 16, 17, 18,
                        7, 14, 19, 21, 22,
                        8, 15, 20, 23, 24};

// Constructor - Destructor

magic_square5_solver::magic_square5_solver() 
{
    set_null_element(-1);
    set_size(25);  // Default size
}

magic_square5_solver::~magic_square5_solver() {}

void 
magic_square5_solver::set_size(int size)
{
    int i;
    
    size = 25;
    order = 5;

    riddle_solver<int>::set_size(size);
    line_sum = order*(order*order + 1)/2;

    // Initialise used_tbl
    if (!used_tbl.empty())
        used_tbl.clear();
    for(i=0; i<size; i++)
        used_tbl.push_back(false);
}

// Overrides

int
magic_square5_solver::get_next_element(int pos)
{
    for(int i=moves_array[pos]+1; i<size; i++)
    {
        if (!used_tbl[i])
            return(i);
    }

    return(-1);
}

int
magic_square5_solver::check_placement()
{
    if (moves_count == 0)
        return(0);

    // Scanning sequence:
    //
    // 1  2  3  4  5
    // 6 10 11 12 13
    // 7 14 17 18 19
    // 8 15 20 22 23
    // 9 16 21 24 25

    square_tbl[map_tbl[moves_count-1]] = moves_array[moves_count-1];

    switch (moves_count)
    {
        case 5:
            if (!test_row(0))
                return(0);
            break;
        case 9:
            if (!test_column(0))
                return(0);
            break;
        case 13:
            if (!test_row(1))
                return(0);
            break;
        case 16:
            if (!test_column(1))
                return(0);
            break;
        case 17:
            if (!test_reverse_diagonal())
                return(0);
            break;
        case 19:
            if (!test_row(2))
                return(0);
            break;
        case 21:
            if (!test_column(2))
                return(0);
            break;
        case 23:
            if (!test_row(3))
                return(0);
            break;
        case 24:
            if (!test_column(3))
                return(0);
            break;
        case 25:
            if (!test_row(4) ||
                !test_column(4) ||
                !test_diagonal())
                return(0);
            break;
    }

    return(moves_count);
}

void
magic_square5_solver::print_solution(vector<int> sol)
{
    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
            cout << (sol[map_rev_tbl[i*order + j]]+1) << "\t";
        cout << endl;
    }
    cout << endl;
};

inline void 
magic_square5_solver::register_move(int pos, int val) 
{
    if (moves_array[pos] > -1)
        used_tbl[moves_array[pos]] = false;

    square_tbl[map_tbl[pos]] = val; 
    
    moves_array[pos] = val;
    used_tbl[val] = true;
}

inline void 
magic_square5_solver::unregister_last_move() 
{
    used_tbl[moves_array[moves_count - 1]] = false;

    square_tbl[map_tbl[moves_count - 1]] = -1;

    moves_array[moves_count - 1] = -1;
    moves_count--;
}


// Implementation

inline bool
magic_square5_solver::test_row(int r)
{
    int j, sum, row_start;
    
    sum = 0;
    row_start = r*order;
    for(j=0;j<order;j++)
    {
        sum+=(square_tbl[row_start+ j]+1);
    }
    if (sum != line_sum)
        return(false);
    
    return(true);
}

inline bool
magic_square5_solver::test_column(int c)
{
    int j, sum;
    
    sum = 0;
    for(j=0;j<order;j++)
    {
        sum+=(square_tbl[j*order + c]+1);
    }
    if (sum != line_sum)
        return(false);
    
    return(true);
}

inline bool
magic_square5_solver::test_diagonal()
{
    int i, sum;

    sum = 0;
    for(i=0;i<order;i++)
    {
        sum+=(square_tbl[i*order+i]+1);
    }
    if (sum != line_sum)
        return(false);

    return(true);
}


inline bool
magic_square5_solver::test_reverse_diagonal()
{
    int i, sum;

    sum = 0;
    for(i=0;i<order;i++)
    {
        sum+=(square_tbl[i*order+order-1-i]+1);
    }
    if (sum != line_sum)
        return(false);

    return(true);
}


