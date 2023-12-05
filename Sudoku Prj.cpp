#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define DIM 9   //is a preprocessor directive in C or C++ programming, and it defines a macro.
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

// Prints the Sudoku grid
void print_grid(int grid[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        cout << SPACE << SPACE << SPACE << SPACE << endl;
        cout << NEW_ROW << endl;
        for (int j = 0; j < DIM; j++)
        {
            cout << SPACE;
            if (BLANK == grid[i][j])
            {
                cout << SPACE;
            }
            else
            {
                cout << grid[i][j];
            }
            cout << SPACE;
            cout << LINE;
        }
    }
    cout << endl << NEW_ROW << endl << endl;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified row matches the given number.
bool used_in_row(int grid[DIM][DIM], int row, int num)
{
    for (int col = 0; col < DIM; col++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number.
bool used_in_col(int grid[DIM][DIM], int col, int num)
{
    for (int row = 0; row < DIM; row++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

bool used_in_box(int grid[DIM][DIM], int box_start_row, int box_start_col, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + box_start_row][col + box_start_col] == num)
            {
                return true;
            }
    return false;
}

bool is_safe(int grid[DIM][DIM], int row, int col, int num)
{
    // Check if 'num' is not already placed in the current row,
    // current column, and current 3x3 box
    return !used_in_row(grid, row, num) &&
        !used_in_col(grid, col, num) &&
        !used_in_box(grid, row - row % 3, col - col % 3, num);
}

std::pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
    for (int row = 0; row < DIM; row++)
        for (int col = 0; col < DIM; col++)
            if (grid[row][col] == BLANK)
            {
                return std::make_pair(row, col);
            }
    return GRID_FULL;
}

bool solve_sudoku(int grid[DIM][DIM], int solution[DIM][DIM])
{
    // If the Sudoku grid has been filled, we are done
    if (GRID_FULL == get_unassigned_location(grid))
    {
        // Copy the solved grid into the solution array
        for (int i = 0; i < DIM; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                solution[i][j] = grid[i][j];
            }
        }
        return true;
    }

    // Get an unassigned Sudoku grid location
    std::pair<int, int> row_and_col = get_unassigned_location(grid);
    int row = row_and_col.first;
    int col = row_and_col.second;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(grid, row, col, num))
        {
            // Make tentative assignment
            grid[row][col] = num;

            if (solve_sudoku(grid, solution))
            {
                // No need to backtrack here, as we want to find all solutions
            }

            grid[row][col] = BLANK;
        }
    }

    return false;
}



void generate_sudoku_puzzle(int grid[DIM][DIM])
{
    // Clear the grid
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            grid[i][j] = BLANK;
        }
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Fill the diagonal boxes
    for (int box = 0; box < 3; box++)
    {
        for (int num = 1; num <= 9; num++)
        {
            int attempts = 0;
            while (true)
            {
                int row = rand() % 3 + box * 3;
                int col = rand() % 3 + box * 3;
                if (grid[row][col] == BLANK)
                {
                    if (!used_in_row(grid, row, num) && !used_in_col(grid, col, num))
                    {
                        grid[row][col] = num;
                        break;
                    }
                }

                attempts++;

                // If too many attempts have been made, clear the grid and start over
                if (attempts > 50)
                {
                    for (int i = 0; i < DIM; i++)
                    {
                        for (int j = 0; j < DIM; j++)
                        {
                            grid[i][j] = BLANK;
                        }
                    }
                    box = -1; // Start over
                    break;
                }
            }
        }
    }

    // Solve the generated puzzle to ensure it has a unique solution
    
}


int main()
{
    cout << "*******************************\n\n\tSudoku Game\n\n*******************************" << endl << endl;
    cout << "***********RULES TO SOLVE***********\n\n";
    cout << "1. Each row must contain the numbers from 1 to 9, without repetitions" << endl;
    cout<<  "2.Each column must contain the numbers from 1 to 9, without repetitions" << endl;
    cout<<  "3.Each box must contain the numbers from 1 to 9, without repetitions" << endl;
    

    int grid[DIM][DIM];
    int solution[DIM][DIM]; // Create a grid for the solution

    generate_sudoku_puzzle(grid); // Generate the Sudoku puzzle
    print_grid(grid);
    solve_sudoku(grid, solution);
    
    // Attempt to solve the puzzle
   

    while (true)
    {
        int row, col, num;

        cout << "Enter the row (1-9), column (1-9), and number (1-9) to fill (0 to exit): ";
        cin >> row >> col >> num;

        if (row == 0 || col == 0 || num == 0)
        {
            cout << "Exiting the game. Goodbye!" << endl;
            break;
        }

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9)
        {
            cout << "Invalid input. Please enter valid row, column, and number (1-9)." << endl;
            continue;
        }

        if (grid[row - 1][col - 1] != BLANK)
        {
            cout << "You can't change this cell. Please choose an empty cell." << endl;
            continue;
        }

        if (!is_safe(grid, row - 1, col - 1, num))
        {
            cout << "Invalid move. This number cannot be placed here." << endl;
            continue;
        }

        grid[row - 1][col - 1] = num;

        // Check if the input matches the solution at this position
            if (num == solution[row - 1][col - 1])
            {
                cout << "Your input matches the solution at this position." << endl << endl;
                print_grid(grid);
            }
            else
            {
                cout << "Your input does not match the solution at this position." << endl << endl;
                grid[row - 1][col - 1] = BLANK; // Clear the cell if the input is incorrect
            }
        
    }

    return 0;
}
