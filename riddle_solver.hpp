#ifndef __RIDDLE_SOLVER_HPP__
#define __RIDDLE_SOLVER_HPP__

#include <vector>

using namespace std;

/** 
  @class riddle_solver
  
  An "abstract" template class for solving riddles. It must be subclassed by a real 
  riddle class. Class move_t can be any native type (usally int or double) or any 
  other class that provides an overload for = operator. Some or all of the virtual 
  functions must be overriden.
  */
template <class move_t>
class riddle_solver
{
public:
	/** Constructor. */
    riddle_solver<move_t>();

	/**	Destructor. */
    ~riddle_solver<move_t>();

	/**   
	Solves the riddle using inductive searching algorithm. If not instructed otherwise
	(by restricting the number of solutions to search for), all possible combinations 
	are searched.
	
	@result Returns true if one or more solutions have been found.
	*/
    bool solve();

	/**   
	Prints all solutions found.
	*/
    void print_all();

	/**  
	Sets the maximum number of solutions to search for. If 0 is given, solve function 
	will scan all possible combinations.
	
	@param n Maximum number of solutions to search for.
	*/
    void set_solutions_count(int n);

	/**  
	Sets the size of the riddle, that is the size of the table it must be filled 
	to solve the riddle.
	
	@param s Riddle's size.
	*/
    void set_size(int s);

	/**   
	Sets null element. When null element is given as input to get_next_element function,
	the first element in the ordered element list will be returned. Null element cannot 
	be used to fill a cell.
	
	@param mn Null element.
	*/
    void set_null_element(move_t mn);

private:
	/**  
	tries to fill the next cell in the table. If this is impossible it will return 
	false. The algorithm must then return to a previous cell. It must not be overriden.
	
	@result Returns true if it was possible to make a new move.
	*/
    bool make_next_move();
    
	/**  
	It tries to find another valid element in a previous cell. It will go back as many 
	cells as required. If this impossible, false will be returned and the searching 
	will stop. It must not be overriden.
	
	@result Returns true if a new valid element in a previous cell has been found.
	*/	
	bool go_back();    
    
protected:	// virtual functions

	/**  
	Checks if the subriddle of size moves_count is solved. It may be overriden. It is 
	declared virtual, because it is called from solve function of the base class. 
	When called in the context of a subclass, solve function must call check_placement 
	of the subclass and not this version.
	
	@result Returns moves_count if the subriddle is solved, 0 otherwise.
	*/
    virtual int check_placement();
    
	/** 
	Gets next element from the elements ordered list.
	
	@param pos Position of cell that contains the element to be replaced by the
	next one found. A new cell will contain null element, so that we start the
	searching from the first element in the list. It must be overriden.
	@result Returns next element.
	*/	
	virtual move_t get_next_element(int pos);
    
	/**
	Registers move at specified position. In its simplest form, it just inserts 
	element move at cell pos. It may be overriden.
	
	@param pos Position of cell to place the element.
	@param move Element to be placed.
	*/	
	virtual void register_move(int pos, move_t move);
    
	/** 
	Undoes last move (at position moves_count - 1). In its simplest form, it just 
	removes the element placed at the last cell and fills it with null element. It may 
	be overriden.
	*/	
	virtual void unregister_last_move();

	/**
	Prints solution in the standard output.
	
	@param sol Vector containing the solution.
	*/    
	virtual void print_solution(vector<move_t> sol) {;};

protected:	// Data members

	/// Table storing the moves made.
    vector<move_t> moves_array;
    
	/// Riddle's size (moves_array size).
	int size;
    
	/// Number of moves made so far.
	int moves_count;

private:
    /// Null element.
	move_t move_null;
    
	/// Maximum number of solutions to look for.
	int sol_number_max;
    
	/// Vector for storing all solutions found.
	vector<vector<move_t> > sol_v;
};

//Explicit Instantiation
template class riddle_solver<int>;

typedef riddle_solver<int> riddle_solver_int;

#endif //__RIDDLE_SOLVER_HPP__