#ifndef __SOLO_HPP__
#define __SOLO_HPP__

#include <vector>

#include "riddle_solver.hpp"

using namespace std;

//
// Solo
//

#define MAKE_VAL_M(board_pos, dir) ((board_pos)*10 + (dir))
#define GET_BOARD_POS_M(val)       ((val) / 10)
#define GET_DIR_M(val)             ((val) % 10)
#define IS_IN_BOARD_M(pos)         (((pos) < BOARD_SIZE) && ((pos) >= 0))

#define REVERSE_DIR_M(dir) (((dir) > 1) ? (dir) - 2 : (dir) + 2)

class solo_solver : public riddle_solver<int>
{
public:
    solo_solver();

    ~solo_solver();

    void replay_solution();

    static int BOARD_INIT_TABLE[];
    static const int BOARD_SIZE = 49;
    static const int PEG_COUNT = 32;
    static const int ROWS_COUNT = 9;
    static const int COLUMNS_COUNT = 7;

protected:
    int get_next_element(int element);
    void print_solution(vector<int> sol);

    void register_move(int pos, int val);
    void unregister_last_move();

private:
    void init_board();
    void print_board();
    bool is_move_legal(int pos, int val);

    int board_tbl[BOARD_SIZE];
    static int removed_pos_offset_tbl[];
    static int new_pos_offset_tbl[];
};

#endif // __SOLO_HPP__