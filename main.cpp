#include "solverUtils.h"
#include <string>
#include <fstream>
#include <sstream>

bool solveSudoku(GRID grid) {
	PAIR empty = findEmptyPosition(grid);

	if (empty == FULL) {
		return isFullGridValid(grid);
	}

	int row = empty.first;
	int col = empty.second;

	for (int num = 1; num <= DIM; ++num) {
		if (isEntryValid(grid, row, col, num)) {
			grid[row][col] = num;

			if (solveSudoku(grid)) {
				return true;
			}

			grid[row][col] = EMPTY;
		}
	}

	return false;
}

void loadGrid(std::ifstream & input, GRID & grid) {
	for (int i = 0; i < DIM; ++i) {
		std::string line;
		std::getline(input, line);

		std::stringstream sstream;

		sstream << line;
		for (int j = 0; j < DIM; ++j) {
			int bufferInt = 0;
			sstream >> bufferInt;

			grid[i][j] = bufferInt;
		}
		sstream.str("");
	}
}

int main(int argc, char** argv) {
	/*
	GRID grid = {
	{5, 0, 0, 0, 4, 0, 0, 0, 0},
	{0, 0, 0, 6, 0, 0, 0, 0, 1},
	{9, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 5, 8, 0},
	{0, 0, 7, 0, 0, 3, 0, 0, 0},
	{0, 6, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 8, 0, 9, 5, 0},
	{0, 3, 1, 7, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 4, 0, 0}
	};
	*/

	if (argc != 2) {
		std::cerr << "USAGE: "
			      << argv[0]
				  << " <filename>\n";
		return 1;
	}

	std::ifstream input(argv[1]);

	GRID grid;
	loadGrid(input, grid);

	if (solveSudoku(grid)) {
		printGrid(grid, std::cout);
	}
	else {
		std::cout << "OOPS\n";
	}

	return 0;
}
