#ifndef __EINSTEINS_PROBLEM_HPP__
#define __EINSTEINS_PROBLEM_HPP__

#include "riddle_solver.hpp"

//#include <vector>
//#include <iostream>

using namespace std;

//
// Einstein's Riddle
//

//Brit        red      dogs     tea      Pall Mall
//Swede       green    birds    coffee   Dunhill
//Dane        white    cats     milk     blends
//Norwegian   yellow   horses   beer     Blue Master
//German      blue     fish     water    Prince

enum Nationality_E
{
    Brit        = 0,
    Swede       = 1,
    Dane        = 2,
    Norwegian   = 3,
    German      = 4
};

enum Colour_E
{
    red      = 0,
    green    = 1,
    white    = 2,
    yellow   = 3,
    blue     = 4
};

enum Pet_E
{
    dogs     = 0,
    birds    = 1,
    cats     = 2,
    horses   = 3,
    fish     = 4
};

enum Beverage_E
{
    tea      = 0,
    coffee   = 1,
    milk     = 2,
    beer     = 3,
    water    = 4
};

enum Smoke_E
{
    PallMall   = 0,
    Dunhill     = 1,
    blends      = 2,
    BlueMaster = 3,
    Prince      = 4
};

enum Property_E
{
    nationality = 0,
    colour = 1,
    pet = 2,
    beverage = 3,
    smoke = 4
};


#define IS_HOUSE_PROP_M(h, prop_type, val) (moves_array[5*(prop_type) + (h)] == (val))
#define IS_NOT_HOUSE_PROP_M(h, prop_type, val) (moves_array[5*(prop_type) + (h)] != (val) && \
                                                moves_array[5*(prop_type) + (h)] != -1)

class einsteins_riddle_solver : public riddle_solver<int>
{
public:
    einsteins_riddle_solver();

    ~einsteins_riddle_solver();

protected:
    int check_placement();
    int get_next_element(int pos);
    void print_solution(vector<int> sol);

    void register_move(int pos, int val);
    void unregister_last_move();


private:
    inline bool is_condition_fulfilled(int h,
                                       int prop1,
                                       int val1,
                                       int prop2,
                                       int val2);
    inline bool are_neighboors(int prop1,
                               int val1,
                               int prop2,
                               int val2);

    bool prop_used_tbl[5][5];    
};

#endif //__EINSTEINS_PROBLEM_HPP__