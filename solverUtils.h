#include <vector>
#include <iostream>

#define DIM 9
#define SQUARESIZE 3
#define EMPTY 0
#define FULL std::make_pair(-1, -1)
#define BARRIER "##################\n"

typedef int GRID[DIM][DIM];
typedef std::pair<int, int> PAIR;

bool usedInRow(GRID grid, int row, int number);

bool usedInColumn(GRID grid, int col, int number);

bool usedInSquare(GRID grid, int row, int col, int number);

bool isEntryValid(GRID grid, int row, int col, int number);

PAIR findEmptyPosition(GRID grid);

bool isFullGridValid(GRID grid);

void printGrid(GRID grid, std::ostream & out);
