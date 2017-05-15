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

Puzzle get_solution_state(){
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
			int tile_row = (puzzle[row][col] - 1) / NUM_ROWS;
			int tile_col = (puzzle[row][col] - 1) % NUM_ROWS;

			manhattan_dist+=(abs(tile_row - row) + abs(tile_col - col));
		}
	}
	return manhattan_dist;
}

void Agent::greedy_search(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
}

void Agent::a_star(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}
