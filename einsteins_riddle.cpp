#include <iostream>

#include "einsteins_riddle.hpp"

using namespace std;

//
// Einstein's Riddle
//

//Brit        red      dogs     tea      Pall Mall
//Swede       green    birds    coffee   Dunhill
//Dane        white    cats     milk     blends
//Norwegian   yellow   horses   beer     Blue Master
//German      blue     fish     water    Prince

char prop_str[25][20] = {

"Brit       ", "red        ", "dogs       ", "tea        ", "Pall Mall  ",
"Swede      ", "green      ", "birds      ", "coffee     ", "Dunhill    ",
"Dane       ", "white      ", "cats       ", "milk       ", "blends     ",
"Norwegian  ", "yellow     ", "horses     ", "beer       ", "Blue Master",
"German     ", "blue       ", "fish       ", "water      ", "Prince     "};

einsteins_riddle_solver::einsteins_riddle_solver() 
{
    memset((void *) prop_used_tbl, 0, 25*sizeof(bool));
    set_null_element(-1);
    set_size(25);
}

einsteins_riddle_solver::~einsteins_riddle_solver() {}


inline bool
einsteins_riddle_solver::is_condition_fulfilled(int h,
                                                int prop1,
                                                int val1,
                                                int prop2,
                                                int val2)
{
    int pos1 = 5*prop1 + h,
        pos2 = 5*prop2 + h;
    
    if (moves_array[pos1] == val1 &&
        moves_array[pos2] != val2 &&
        moves_array[pos2] != -1)
        return(false);

    if (moves_array[pos2] == val2 &&
        moves_array[pos1] != val1 &&
        moves_array[pos1] != -1)
        return(false);

    return(true);
}

inline bool
einsteins_riddle_solver::are_neighboors(int prop1,
                                        int val1,
                                        int prop2,
                                        int val2)
{    
    if (IS_HOUSE_PROP_M(0, prop1, val1) &&
        IS_NOT_HOUSE_PROP_M(1, prop2, val2))
        return(false);

    if (IS_HOUSE_PROP_M(4, prop1, val1) &&
        IS_NOT_HOUSE_PROP_M(3, prop2, val2))
        return(false);

    for(int i = 1; i < 4; i ++)
        if (IS_HOUSE_PROP_M(i, prop1, val1) &&
            IS_NOT_HOUSE_PROP_M(i-1, prop2, val2) &&
            IS_NOT_HOUSE_PROP_M(i+1, prop2, val2))
            return(false);

    if (IS_HOUSE_PROP_M(0, prop2, val2) &&
        IS_NOT_HOUSE_PROP_M(1, prop1, val1))
        return(false);

    if (IS_HOUSE_PROP_M(4, prop2, val2) &&
        IS_NOT_HOUSE_PROP_M(3, prop1, val1))
        return(false);

    for(int i = 1; i < 4; i ++)
        if (IS_HOUSE_PROP_M(i, prop2, val2) &&
            IS_NOT_HOUSE_PROP_M(i-1, prop1, val1) &&
            IS_NOT_HOUSE_PROP_M(i+1, prop1, val1))
            return(false);

    return(true);
}

int
einsteins_riddle_solver::check_placement()
{
    for(int i = 0; i < 5; i++)
    {
        //the Brit lives in the red house        
        if (!is_condition_fulfilled(i,nationality,Brit,colour,red))
            return(0);

        //the Swede keeps dogs as pets
        if (!is_condition_fulfilled(i,nationality,Swede,pet,dogs))
            return(0);

        //the Dane drinks tea
        if (!is_condition_fulfilled(i,nationality,Dane,beverage,tea))
            return(0);

        //the green house is on the left of the white house
        if ((IS_HOUSE_PROP_M(i, colour, green) && i == 4) ||
            (IS_HOUSE_PROP_M(i, colour, green) &&
             IS_NOT_HOUSE_PROP_M(i+1, colour, white)))
            return(0);

        if ((IS_HOUSE_PROP_M(i, colour, white) && i == 0) ||
            (IS_HOUSE_PROP_M(i, colour, white) &&
             IS_NOT_HOUSE_PROP_M(i-1, colour, green)))
            return(0);

        //the green house's owner drinks coffee
        if (!is_condition_fulfilled(i,colour,green,beverage,coffee))
            return(0);

        //the person who smokes Pall Mall rears birds
        if (!is_condition_fulfilled(i,smoke,PallMall,pet,birds))
            return(0);

        //the owner of the yellow house smokes Dunhill
        if (!is_condition_fulfilled(i,colour,yellow,smoke,Dunhill))
            return(0);

        //the man living in the center house drinks milk
        if (IS_NOT_HOUSE_PROP_M(2, beverage, milk))
            return(0);

        //the Norwegian lives in the first house
        if (IS_NOT_HOUSE_PROP_M(0, nationality, Norwegian))
            return(0);

        //the owner who smokes BlueMaster drinks beer
        if (!is_condition_fulfilled(i,smoke,BlueMaster,beverage,beer))
            return(0);

        //the German smokes Prince
        if (!is_condition_fulfilled(i,nationality,German,smoke,Prince))
            return(0);
    }
        
    //the man who keeps horses lives next to the man who smokes Dunhill
    if (!are_neighboors(pet, horses, smoke, Dunhill))
        return(0);

    //the man who smokes blends lives next to the one who keeps cats
    if (!are_neighboors(smoke, blends, pet, cats))
        return(0);

    //the Norwegian lives next to the blue house
    if (!are_neighboors(nationality, Norwegian, colour, blue))
        return(0);

    //the man who smokes blends has a neighbor who drinks water
    if (!are_neighboors(smoke, blends, beverage, water))
        return(0);

    return(moves_count);
}

inline int
einsteins_riddle_solver::get_next_element(int pos)
{
    int prop_type = pos / 5;
    
    for(int i = 0; i < 5 ; i++)
    {
        if (!prop_used_tbl[prop_type][i] &&
            moves_array[pos] < i)
        {
            return(i);
        }
    }

    return(-1);
}

void 
einsteins_riddle_solver::register_move(int pos, 
                                       int val)
{
    int prop_type = pos / 5;
    int old_val = moves_array[pos];
    
    if (old_val != -1)
        prop_used_tbl[prop_type][old_val] = false;
    moves_array[pos] = val;
    prop_used_tbl[prop_type][val] = true;
}

void
einsteins_riddle_solver::unregister_last_move()
{
    int old_val = moves_array[moves_count - 1];
    int prop_type = (moves_count - 1) / 5;
    
    moves_array[moves_count - 1] = -1;
    prop_used_tbl[prop_type][old_val] = false;
    moves_count--;
}

void 
einsteins_riddle_solver::print_solution(vector<int> sol)
{
    cout << "[House 1]   [House 2]   [House 3]   [House 4]   [House 5]" << endl;
    
    for(int i = 0; i < 25; i+=5)
    {
        for(int j = 0; j < 5; j++)
        {
            //cout << ctx.moves_array[j + i] + 1 << "\t";
            int prop_type  = i / 5;
            int prop_val = sol[j + i];

            cout << prop_str[5*prop_val + prop_type] << " ";
        }
        cout << endl;
    }    
}

