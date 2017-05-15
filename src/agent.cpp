/*
 * Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * agent.cpp
 * */
#include "agent.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <set>

Agent::Agent(Puzzle puzzle, Solver solver, Heuristic heuristic) :
	puzzle(puzzle), solver(solver), heuristic(heuristic)
{}

Agent::~Agent()
{}

void Agent::run()
{
	if (solver == Solver::GREEDY)
    {
		cout << "Solver: Greedy Search" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES) {
			cout << "Heuristic: Misplaced tiles" << endl;
		}

		else {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		greedy_search (heuristic);
	}
	if (solver == Solver::A_STAR)
    {
		cout << "Solver: A*" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES)
        {
			cout << "Heuristic: Misplaced tiles" << endl;
		}
		else
        {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		a_star(heuristic);
	}
}

int Agent::misplaced_tiles(Puzzle puzzle) {
	//TO DO

	int misplaced_tiles_count = 0;
	Puzzle solution=get_solution_state();
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (puzzle[row][col]!=solution[row][col])
				misplaced_tiles_count++;
		}
	}
	return misplaced_tiles_count;

}

int Agent::manhattan_distance(Puzzle puzzle) {
	//TO DO
	int manhattan_dist = 0;
	int solution_index_row,solution_index_col;
	Puzzle solution=get_solution_state();

	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			int sol_row = (puzzle[row][col] - 1) / NUM_ROWS;
			int sol_col = (puzzle[row][col] - 1) % NUM_ROWS;

			manhattan_dist+=(abs(sol_row - row) + abs(sol_col - col));
		}
	}
	return manhattan_dist;
}

void Agent::greedy_search(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.

	queue <pair<Puzzle, int>> fringe;
	set<string> visited_nodes;
	pair<Puzzle, int> current_state;
	fringe.push(make_pair(puzzle,distance_function(puzzle,heuristic)));
	while (!fringe.empty())
	{
		current_state=fringe.front();
		fringe.pop();
		if (visited_nodes.insert(get_state_string(current_state.first)).second)
		{
			if (current_state.second==0)
			{
				cout<<"Found solution::";
				print_puzzle(current_state.first);
				return;

			}
			else
			{
				vector<Puzzle> children =child_states(current_state.first);
				for (int i=0;i<children.size();i++)
				{
					fringe.push(make_pair(children[i],distance_function(children[i],heuristic)));
				}
			}
		}

	}

}

void Agent::a_star(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.

	//fringe will store the puzzle state along with cost attached, <estimated heuristic cost and cost so far >
	queue <pair<Puzzle, pair<int,int>>> fringe;

	set<string> visited_nodes;

	fringe.push(make_pair(puzzle,make_pair(distance_function(puzzle,heuristic),0))); //initial cost so far is 0
	while (!fringe.empty())
	{

	}




}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

/****************************************************************************/

//get_solution_state gives the solution matrix of the problem

Puzzle Agent::get_solution_state(){
	int array[NUM_ROWS*NUM_COLS];

	for (int i =1; i<=NUM_ROWS*NUM_COLS;i++)
	{
		array[i-1]=i;
	}
	array[NUM_ROWS*NUM_COLS-1]=0;

	Puzzle solution;
	int index = 0;
	for (int rows = 0; rows < NUM_ROWS; rows++)
	{
		for (int cols = 0; cols < NUM_COLS; cols++)
		{
			solution[rows][cols] = array[index++];
		}
	}
	return solution;
}

int Agent::distance_function(Puzzle puzzle, Heuristic heuristic) {
	int distance;

	if (heuristic==Heuristic::MISPLACED_TILES){
		distance=misplaced_tiles(puzzle);
	}
	else{
		distance=manhattan_distance(puzzle);
	}
return distance;

}


string Agent::get_state_string(Puzzle puzzle){
	string state="";
	for(int row=0; row<NUM_ROWS; row++){
		for(int col=0; col<NUM_COLS; col++){
			state+= to_string(puzzle[row][col]);
		}
	}
	return state;
}


vector<Puzzle> Agent::child_states(Puzzle puzzle)
{
	vector<Puzzle> children;

	for (int i=0; i<NUM_ROWS;i++)
	{
		for (int j=0;j<NUM_COLS;j++)
		{
			if (puzzle[i][j]==0)
			{
				//move up
				if ((i-1)<NUM_ROWS and (i-1)>=0)
				{
					Puzzle next = puzzle;
					swap(next[i][j], next[i-1][j]);
					children.push_back(next);
				}
				//move down
				if ((i+1)<NUM_ROWS and (i+1)>=0)
				{
					Puzzle next = puzzle;
					swap(next[i][j], next[i+1][j]);
					children.push_back(next);
				}
				//move left
				if ((j-1)<NUM_COLS and (j-1)>=0)
				{
					Puzzle next = puzzle;
					swap(next[i][j], next[i][j-1]);
					children.push_back(next);
				}
				//move right
				if ((j+1)<NUM_COLS and (j+1)>=0)
				{
					Puzzle next = puzzle;
					swap(next[i][j], next[i][j+1]);
					children.push_back(next);
				}


			}
		}
	}


	return children;
}
