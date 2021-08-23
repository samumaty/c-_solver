#include <iostream>

#include "q8_riddle.hpp"
#include "einsteins_riddle.hpp"
#include "magic_squares.hpp"
#include "magic_square_5.hpp"
#include "solo.hpp"

using namespace std;

int
main()
{ 
    q8_riddle_solver *queen_riddle;
    einsteins_riddle_solver *einsteins_riddle;
    magic_square_solver *magic_square;
    magic_square5_solver *magic_square5;
    solo_solver *solo;
    char c = 'n';
    
    while (c!= 'q' && c!= 'Q')
    {
        cout << endl << "Select puzzle to solve:" << endl;
        cout << "1: 8 Queens Riddle" << endl;
        cout << "2: Einstein's Riddle" << endl;
        cout << "3: Magic Square 3x3" << endl;
        cout << "4: Magic Square 4x4" << endl;
        cout << "5: Magic Square 5x5" << endl;
        cout << "6: Peg Solitaire" << endl;
        cout << "Press q to exit." << endl << endl;

        cin >> c;

        switch(c)
        {
        case '1':
            cout << "Solving 8 Queens Riddle..." << endl << endl;
            queen_riddle = new (q8_riddle_solver);
            queen_riddle->solve();
            queen_riddle->print_all();
            delete queen_riddle;
            break;
        case '2':
            cout << "Solving Einstein's Riddle..." << endl << endl;
            einsteins_riddle = new (einsteins_riddle_solver);
            einsteins_riddle->solve();
            einsteins_riddle->print_all();
            delete einsteins_riddle;
            break;
        case '3':
            cout << "Searching for Magic Squares 3x3..." << endl << endl;
            magic_square = new (magic_square_solver);
            magic_square->set_order(3);
            magic_square->solve();
            magic_square->print_all();
            delete magic_square;
            break;
        case '4':
            cout << "Searching for Magic Squares 4x4..." << endl << endl;
            magic_square = new (magic_square_solver);
            magic_square->set_order(4);
            magic_square->solve();
            cout << "Press a key to print solutions" << endl;
            cin >> c;
            magic_square->print_all();
            delete magic_square;
            break;
        case '5':
            cout << "Searching for Magic Squares 5x5..." << endl << endl;
            magic_square5 = new (magic_square5_solver);
            magic_square5->set_solutions_count(10);
            magic_square5->solve();
            cout << "Press a key to print solutions" << endl;
            cin >> c;
            magic_square5->print_all();
            delete magic_square5;
            break;
        case '6':
            cout << "Solving Peg Solitaire..." << endl << endl;
            solo = new (solo_solver);
            solo->set_solutions_count(1);
            solo->solve();
            solo->print_all();
            cout << "Press a key to replay solution." << endl;
            cin >> c;
            solo->replay_solution();
            delete solo;
            break;
        }
    }
}
