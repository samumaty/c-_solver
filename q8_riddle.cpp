#include <iostream>

#include "q8_riddle.hpp"

using namespace std;

//
// 8 Queens Riddle
//

q8_riddle_solver::q8_riddle_solver() 
{
    set_null_element(-1);
    set_size(8);
}

q8_riddle_solver::~q8_riddle_solver() {}



int 
q8_riddle_solver::get_next_element(int pos)
{
    if (moves_array[pos] == 7)
        return(-1);
    else
        return(moves_array[pos]+1);
    return(-1);
}


int
q8_riddle_solver::check_placement()
{
    int i, j;

    for(i=0;i<moves_count;i++)
    {
        for(j=i+1;j<moves_count;j++)
        {
            if (moves_array[i] == moves_array[j])
                return(0);
            if (i + moves_array[i] == j + moves_array[j])
                return(0);
            if (i - moves_array[i] == j - moves_array[j])
                return(0);
        }
    }

    return(moves_count);
}

void
q8_riddle_solver::print_solution(vector<int> sol)
{
    char str[4];
    str[2] = ' ';
    str[3] = '\0';
    
    for(char i = 0; i < 8; i ++)
    {
        str[0] = 'a' + i;
        str[1] = '1' + sol[i];
        cout << str;
    }
    cout << endl;
};

