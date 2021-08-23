#include <vector>
#include <iostream>

#include "magic_squares.hpp"

using namespace std;


//
// Magic Squares
//

// Constructor - Destructor

magic_square_solver::magic_square_solver() 
{
    set_null_element(-1);
    set_size(9);  // Default size
}

magic_square_solver::~magic_square_solver() {}

void 
magic_square_solver::set_order(int ord) 
{
    order = ord;
    size = order * order;
    set_size(size);
}


void 
magic_square_solver::set_size(int size)
{
    int i;
    
    switch (size)
    {
        case 9:
            order = 3;
            break;
        case 16:
            order = 4;
            break;
        case 25:
            order = 5;
            break;
        default:
            size = 9;
            order = 3;
    }

    riddle_solver<int>::set_size(size);
    line_sum = order*(order*order + 1)/2;

    // Initialise used_tbl
    if (!used_tbl.empty())
        used_tbl.clear();
    for(i=0; i<size; i++)
        used_tbl.push_back(false);

    // initialise min_sum_tbl
    int min_sum = line_sum;

    if (!min_sum_tbl.empty())
        min_sum_tbl.clear();
    for(i=0; i<order; i++)
    {
        min_sum_tbl.insert(min_sum_tbl.begin(),min_sum);
        min_sum -= size - i;
    }
}

// Overrides

int
magic_square_solver::get_next_element(int pos)
{
    for(int i=moves_array[pos]+1; i<size; i++)
    {
        if (!used_tbl[i])
            return(i);
    }

    return(-1);
}

int
magic_square_solver::check_placement()
{
    int r, c;

    if (moves_count == 0)
        return(0);

    r = (moves_count-1) / order;
    c = (moves_count-1) % order;

    // A row has just been completed
    if (c == order-1)
    {
        if (!test_row(r))
            return(0);
    }    
    
    if (r == order - 1)
    {
        // Reverse diagonal has been completed
        if (c == 0)
        {
            if (!test_reverse_diagonal())
                return(0);
        }
        // Diagonal has been completed
        if (c == order - 1)
        {
            if (!test_diagonal())
                return(0);
        }

        // A column has just been completed
        if (!test_column(c))
            return(0);
    }
    else
    {
		// Test partial row, column, diagonal
		if (c != order-1 && !test_partial_row(r, c))
			return(0);
		if (!test_partial_column(c, r))
            return(0);
        if (c == r && !test_partial_diagonal(r))
            return(0);
        if ((c == order - r - 1) && !test_partial_reverse_diagonal(r))
            return(0);
    }

    return(moves_count);
}

void
magic_square_solver::print_solution(vector<int> sol)
{
    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
            cout << (sol[i*order + j]+1) << "\t";
        cout << endl;
    }
    cout << endl;
};

void 
magic_square_solver::register_move(int pos, int val) 
{
    if (moves_array[pos] > -1)
        used_tbl[moves_array[pos]] = false;
    moves_array[pos] = val;
    used_tbl[val] = true;
}

void 
magic_square_solver::unregister_last_move() 
{
    used_tbl[moves_array[moves_count - 1]] = false;
    moves_array[moves_count - 1] = -1;
    moves_count--;
}


// Implementation

inline bool
magic_square_solver::test_row(int r)
{
    int j, sum, row_start;
    
    sum = 0;
    row_start = r*order;
    for(j=0;j<order;j++)
    {
        sum+=(moves_array[row_start+ j]+1);
    }
    if (sum != line_sum)
        return(false);
    
    return(true);
}

inline bool
magic_square_solver::test_column(int c)
{
    int j, sum;
    
    sum = 0;
    for(j=0;j<order;j++)
    {
        sum+=(moves_array[j*order + c]+1);
    }
    if (sum != line_sum)
        return(false);
    
    return(true);
}

inline bool
magic_square_solver::test_partial_row(int r,
                                      int c)
{
    int j, sum;

    sum = 0;
    for(j=0;j<=c;j++)
    {
        sum+=(moves_array[r*order + j]+1);
    }
    if (sum >= line_sum)
        return(false);
    else if (sum < min_sum_tbl[c])
        return(false);
    
    return(true);
}

inline bool
magic_square_solver::test_partial_column(int c,
                                         int r)
{
    int j, sum;

    sum = 0;
    for(j=0;j<=r;j++)
    {
        sum+=(moves_array[j*order + c]+1);
    }
    if (sum >= line_sum)
        return(false);
    else if (sum < min_sum_tbl[r])
        return(false);
    
    return(true);
}

inline bool
magic_square_solver::test_diagonal()
{
    int i, sum;

    sum = 0;
    for(i=0;i<order;i++)
    {
        sum+=(moves_array[i*order+i]+1);
    }
    if (sum != line_sum)
        return(false);

    return(true);
}

inline bool
magic_square_solver::test_partial_diagonal(int r)
{
    int i, sum;

    sum = 0;
    for(i=0;i<=r;i++)
    {
        sum+=(moves_array[i*order+i]+1);
    }
    if (sum >= line_sum)
        return(false);
    else if (sum < min_sum_tbl[r])
        return(false);

    return(true);
}

inline bool
magic_square_solver::test_reverse_diagonal()
{
    int i, sum;

    sum = 0;
    for(i=0;i<order;i++)
    {
        sum+=(moves_array[i*order+order-1-i]+1);
    }
    if (sum != line_sum)
        return(false);

    return(true);
}

inline bool
magic_square_solver::test_partial_reverse_diagonal(int r)
{
    int i, sum;

    sum = 0;
    for(i=0;i<=r;i++)
    {
        sum+=(moves_array[i*order+order-1-i]+1);
    }
    if (sum >= line_sum)
        return(false);
    else if (sum < min_sum_tbl[r])
        return(false);

    return(true);
}


