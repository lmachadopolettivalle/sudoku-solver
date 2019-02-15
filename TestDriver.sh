#!/bin/bash
if [ $# -gt 0 ]
then
	echo "USAGE: $0"
	exit 1
fi

# Solver task file
SOLVER="SOLVER.tsk"

# Compile source code into executable (solver)
SRCS=$(ls *.cpp 2> /dev/null)
g++ -o "$SOLVER" $SRCS

# Directories with games and solutions
TEST_DIR="tests"
GAMES_DIR="$TEST_DIR/games"
SOLUTIONS_DIR="$TEST_DIR/solutions"

# Obtain all file names in GAMES_DIR
cd $GAMES_DIR
GAMES_FILES=$(ls *txt 2> /dev/null)
cd ../..

# Buffer file to hold output of $SOLVER
BUFFER="buffer_file.txt"

# For each game, solve it and compare to expected solution
# Count number of successes
successes=0
total=0
for game_file in $GAMES_FILES; do
	echo "######################################"
	solution_file="solution_$game_file"
	echo $solution_file

	./$SOLVER $GAMES_DIR/$game_file > $BUFFER

	diff $BUFFER $SOLUTIONS_DIR/$solution_file

	if [ $? == 0 ]; then
		successes=$(($successes+1))
	fi
	total=$(($total+1))

	rm $BUFFER
done

echo "Success rate: $successes / $total"

if [ "$successes" -eq "$total" ]; then
	exit 0
else
	exit 1
fi
