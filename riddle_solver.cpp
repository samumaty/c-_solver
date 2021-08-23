#include <iostream>

#include "riddle_solver.hpp"

using namespace std;

//
// Public functions
//

template <class move_t>
riddle_solver<move_t>::riddle_solver() 
{
    sol_number_max = 0;
    size = 0;
}

template <class move_t>
riddle_solver<move_t>::~riddle_solver() 
{}

template <class move_t>
void riddle_solver<move_t>::set_solutions_count(int n) 
{
    sol_number_max = n;
}

template <class move_t>
void riddle_solver<move_t>::set_size(int s)
{
    size = s;
    
    if (!moves_array.empty())
        moves_array.clear();
    for(int i = 0; i < size; i++)
        moves_array.push_back(move_null);
    moves_count = 0;
}

template <class move_t>
void riddle_solver<move_t>::set_null_element(move_t mn)
{
    move_null = mn;
}

template <class move_t>
bool riddle_solver<move_t>::solve()
{
    unsigned long solutions =0,
                  steps = 0,
                  total = 0;
    bool searched_all = false;

    while(!searched_all)
    {
        if (check_placement() == size)
        {
            solutions++;
            steps++;
            sol_v.push_back(moves_array);
            if (sol_number_max == solutions)
            {
                searched_all = true;
            }
            else
            {
                // Go back until a valid combination is found
                do
                {
                    searched_all = !go_back();
                    steps++;
                } while(!searched_all && check_placement() == 0);
            }
        }
        else
        {
            // Make the next move
            if (!make_next_move())
            {
                // Go back until a valid combination is found
                do
                {
                    searched_all = !go_back();
                    steps++;
                } while(!searched_all && check_placement() == 0);
            }
            else
            {
                // Debugging info
				steps++;
                if (steps > 9999999)
                {
                    cout << "1000000 steps, moves made = " << check_placement() << endl;
                    cout << "Solutions so far = " << solutions << endl;
                    steps = 0;
                    total++;
                    if (total % 10 == 0)
                        print_solution(moves_array);
                }
            }
        }
    }

    cout << "Found " << solutions << " solution(s)." << endl;
    cout << "steps: " << steps + total*1000000 << endl;
    return(solutions > 0);
}

template <class move_t>
void riddle_solver<move_t>::print_all()
{
    if (!sol_v.empty())
    {
        vector<vector<int> >::iterator v_iter = sol_v.begin();
        
        cout << endl << "Solution(s):" << endl;        
        while(v_iter != sol_v.end())
        {
            print_solution(*v_iter++);
        }
    }
    else
    {
        cout << "No solutions found!" << endl;
    }
}

//
// Private functions
//
template <class move_t>
bool riddle_solver<move_t>::make_next_move()
{
    move_t j;

    if (moves_count == size)
        return(false);

    moves_count++;
    j = get_next_element(moves_count-1);
    while(j!=move_null)
    {
        moves_array[moves_count-1] = j;
        if (check_placement() > 0)
        {
            register_move(moves_count - 1, j);
            return(true);
        }
        j = get_next_element(moves_count-1);
    }

    moves_array[moves_count-1] = move_null;
    moves_count--;
    return(false);
}

template <class move_t>
bool riddle_solver<move_t>::go_back()
{
    while(moves_count > 1 && 
          get_next_element(moves_count - 1) == move_null)
          unregister_last_move();
    
    if (moves_count == 1 &&
        get_next_element(0) == move_null)
    {
        return(false);
    }
    else
    {
        register_move(moves_count - 1, 
                      get_next_element(moves_count-1));
    }

    return(true);
}

//
// Protected virtual functions
//

template <class move_t>
move_t riddle_solver<move_t>::get_next_element(int pos)
{
    return(move_null);
}

template <class move_t> 
int riddle_solver<move_t>::check_placement() 
{
    return(moves_count);
}

template <class move_t> 
void riddle_solver<move_t>::register_move(int pos, move_t move)
{
    moves_array[pos] = move;
}

template <class move_t>
void riddle_solver<move_t>::unregister_last_move() 
{
    moves_array[moves_count - 1] = move_null;
    moves_count--;
}

