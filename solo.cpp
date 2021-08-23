#include <vector>
#include <iostream>
#include <algorithm>

#include "solo.hpp"

using namespace std;

//
// Solo
//

enum
{
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3
} direction_e;

int solo_solver::BOARD_INIT_TABLE[] = {-1, -1,  1,  1,  1, -1, -1,
                                       -1, -1,  1,  1,  1, -1, -1,
                                        1,  1,  1,  1,  1,  1,  1,
                                        1,  1,  1,  0,  1,  1,  1,
                                        1,  1,  1,  1,  1,  1,  1,
                                       -1, -1,  1,  1,  1, -1, -1,
                                       -1, -1,  1,  1,  1, -1, -1};

int solo_solver::removed_pos_offset_tbl[] = {1, COLUMNS_COUNT, -1, -COLUMNS_COUNT};
int solo_solver::new_pos_offset_tbl[] = {2, 2*COLUMNS_COUNT, -2, -2*COLUMNS_COUNT};

solo_solver::solo_solver() 
{    
    set_null_element(-1);
    set_size(PEG_COUNT - 1);
    init_board();

}

solo_solver::~solo_solver() {};


void
solo_solver::init_board()
{
    int i;
    vector<int> v;

    for(i=0; i<BOARD_SIZE; i++)
        board_tbl[i] = BOARD_INIT_TABLE[i];
}

int
solo_solver::get_next_element(int pos)
{
    int move = moves_array[pos],
        board_pos = GET_BOARD_POS_M(move),
        dir = GET_DIR_M(move),
        i = 0, j;

    if (move >= 0)
    {
        // Undo last move
        board_tbl[board_pos] = 1;
        board_tbl[board_pos + removed_pos_offset_tbl[dir]] = 1;
        board_tbl[board_pos + new_pos_offset_tbl[dir]] = 0;

        // Search for a new move
        i = board_pos;
        for(j=dir+1; j<4; j++)
        {
            int val = MAKE_VAL_M(i, j);            
            if(is_move_legal(pos, val))
                return(val);
        }
        i++;
    }
    
    for(; i<BOARD_SIZE; i++)
    {
        for(j=0; j<4; j++)
        {
            int val = MAKE_VAL_M(i, j);            
            if(is_move_legal(pos, val))
                return(val);
        }
    }
    return(-1);
}

bool 
solo_solver::is_move_legal(int pos, int val) 
{
    int board_pos = GET_BOARD_POS_M(val),
        dir = GET_DIR_M(val),
        r = board_pos / COLUMNS_COUNT,
        c = board_pos % COLUMNS_COUNT;

    if  (!IS_IN_BOARD_M(board_pos) ||
         board_tbl[board_pos] != 1 )
        return(false);

    switch(dir)
    {
        case EAST:
            if (c >= COLUMNS_COUNT - 2 ||
                board_tbl[board_pos+1] != 1 ||
                board_tbl[board_pos+2] != 0)
                return(false);
            break;
        case SOUTH:
            if (r >= ROWS_COUNT - 2 ||
                board_tbl[board_pos + COLUMNS_COUNT] != 1 ||
                board_tbl[board_pos + 2*COLUMNS_COUNT] != 0)
                return(false);
            break;
        case WEST:
            if (c <= 1 ||
                board_tbl[board_pos-1] != 1 ||
                board_tbl[board_pos-2] != 0)
                return(false);
            break;
        case NORTH:
            if (r <= 1 ||
                board_tbl[board_pos - COLUMNS_COUNT] != 1 ||
                board_tbl[board_pos - 2*COLUMNS_COUNT] != 0)
                return(false);
            break;
    }

    return(true);
}

void 
solo_solver::print_solution(vector<int> sol)
{
    if (sol.size() != PEG_COUNT - 1)
        return;
    
    for(int i=0; i<PEG_COUNT - 1; i++)
    {
        cout << sol[i] << endl;
    }
    cout << endl;
}

void 
solo_solver::register_move(int pos, int val)
{
    int board_pos = GET_BOARD_POS_M(val),
        dir = GET_DIR_M(val);
    
    moves_array[pos] = val;

    board_tbl[board_pos] = 0;
    board_tbl[board_pos + removed_pos_offset_tbl[dir]] = 0;
    board_tbl[board_pos + new_pos_offset_tbl[dir]] = 1;

    //print_board();
    //print_solution(moves_array);
    //cout << "Moves count " << moves_count << endl;
    //
    //char c;
    ////cin >> c;
}

void 
solo_solver::unregister_last_move() 
{
    int last_val = moves_array[moves_count - 1];

    int board_pos = GET_BOARD_POS_M(last_val),
        dir = GET_DIR_M(last_val);

    board_tbl[board_pos] = 1;
    board_tbl[board_pos + removed_pos_offset_tbl[dir]] = 1;
    board_tbl[board_pos + new_pos_offset_tbl[dir]] = 0;

    moves_array[moves_count - 1] = -1;
    moves_count--;

    //print_board();
    //print_solution(moves_array);
    //cout << "Moves count " << moves_count << endl;
    //
    //char c;
    ////cin >> c;
}

void 
solo_solver::print_board()
{
    // -1 -> ' '
    //  0 -> 'O'
    //  1 -> 'X'
    char map_tbl[3] = {' ', 'O', 'X'};
    
    cout << endl;
    for(int i=0; i < BOARD_SIZE; i+=COLUMNS_COUNT)
    {
        for(int j=0; j < COLUMNS_COUNT; j++)
            cout << map_tbl[board_tbl[i + j]+1] << "\t";
        cout << endl;
    }
    cout << endl;
}

void
solo_solver::replay_solution()
{
    vector<int> sol_v = moves_array;
    char c;
    int i;

    // Re-init
    set_size(PEG_COUNT - 1);
    init_board();

    print_board();
    cin >> c;

    for(i=0; i<PEG_COUNT - 1; i++)
    {
        register_move(i, sol_v[i]);
        print_board();
        cin >> c;
    }
}
