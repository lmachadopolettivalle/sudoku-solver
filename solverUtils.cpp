#include "solverUtils.h"

bool usedInRow(GRID grid, int row, int number) {
	for (int i = 0; i < DIM; ++i) {
		if (grid[row][i] == number) {
			return true;
		}
	}

	return false;
}

bool usedInColumn(GRID grid, int col, int number) {
	for (int i = 0; i < DIM; ++i) {
		if (grid[i][col] == number) {
			return true;
		}
	}

	return false;
}

bool usedInSquare(GRID grid, int row, int col, int number) {
	int top = SQUARESIZE * (row / SQUARESIZE);
	int left = SQUARESIZE * (col / SQUARESIZE);
	int bottom = top + SQUARESIZE;
	int right = left + SQUARESIZE;

	for (int i = top; i < bottom; ++i) {
		for (int j = left; j < right; ++j) {
			if (grid[i][j] == number) {
				return true;
			}
		}
	}

	return false;
}

bool isEntryValid(GRID grid, int row, int col, int number) {
	return (!usedInRow(grid, row, number))
		&& (!usedInColumn(grid, col, number))
		&& (!usedInSquare(grid, row, col, number));
}

PAIR findEmptyPosition(GRID grid) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			if (grid[i][j] == EMPTY) {
				return std::make_pair(i, j);
			}
		}
	}

	return FULL;
}

bool isFullGridValid(GRID grid) {
	int number = 0;

	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			number = grid[i][j];
			grid[i][j] = EMPTY;

			if (!isEntryValid(grid, i, j, number)) {
				return false;
			}

			grid[i][j] = number;
		}
	}

	return true;
}

void printGrid(GRID grid, std::ostream & out) {
	//out << BARRIER;

	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			out << grid[i][j] << " ";
		}

		out << "\n";
	}

	//out << BARRIER;
}
