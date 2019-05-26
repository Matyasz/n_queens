/**************************************************************************************************
 * Author  : Taylor Matyasz
 * Date    : April 23, 2019
 * Project : Iterative solution to n-Queens problem
 * ************************************************************************************************/

#include <iostream>
#include <vector>

// TODO: Replace this with a system arg
#define N 25

using namespace std;


// Queen class, created basically just to mimic a Python tuple.
class Queen {
  private:
    int row, col;

  public:
    Queen(int l, int r) {
      row = l;
      col = r;
    }

    void get_position(int *r, int *c) {
      *r = row;
      *c = col;
    }
};

void simple_print_board(const vector<Queen> *);
void print_board(const vector<Queen> *);
bool boardIsValid(vector<Queen> *);

void iterativeNQueensSolution(vector<Queen> *);
void recursiveNQueensSolution(vector<Queen> *);
bool recursiveNQueensSolution(vector<Queen>, int);

/**************************************************************************************************
 * Function  : main
 * Purpose   : Instantiates the board for the n-queens problem and calls the functions to
 *             solve the problem and print the solution.
 * ************************************************************************************************/
int main() {
  cout << "Solution for " << N << "-queens:" << endl << endl;

  vector<Queen> sBoard;
  recursiveNQueensSolution(&sBoard);

  print_board(&sBoard);

  return 0;
}

/**************************************************************************************************
 * Function  : resursiveNQueensSolution
 * Inputs    : (none)
 * Outputs   : vector<Queen> * - A pointer to the board containing the solution
 * Purpose   : Solve the n-queens problem recursively
 * ************************************************************************************************/
bool recursiveNQueensSolution(vector<Queen> *psBrd, int col) {
  if (N <= col){
    return true;
  }

  for (int row = 0; row < N; row++){
    Queen q(row, col);
    psBrd->push_back(q);

    if (boardIsValid(psBrd) && recursiveNQueensSolution(psBrd, col + 1)) {
      return true;
    }
    psBrd->pop_back();
  }
  return false;
}

/**************************************************************************************************
 * Function  : resursiveNQueensSolution
 * Inputs    : (none)
 * Outputs   : vector<Queen> * - A pointer to the board containing the solution
 * Purpose   : Solve the n-queens problem recursively
 * ************************************************************************************************/
void recursiveNQueensSolution(vector<Queen> *psBrd) {
  recursiveNQueensSolution(psBrd, 0);
}

/**************************************************************************************************
 * Function  : iterativeNQueensSolution
 * Inputs    : (none)
 * Outputs   : vector<Queen> * - A pointer to the board containing the solution
 * Purpose   : Solve the n-queens problem iteratively
 * ************************************************************************************************/
void iterativeNQueensSolution(vector<Queen> *psBrd) {

}

/**************************************************************************************************
 * Function  : validate_placement
 * Inputs    : vector<Queen> * psBrd - A pointer to the board to validate
 * Outputs   : (bool) valid          - Whether or not the board represents a valid configuration
 * Purpose   : Determine if adding a new queen at a given location would
 *             result in an invalid board, where a queen is under attack
 * ************************************************************************************************/
bool boardIsValid(vector<Queen> *psBrd) {
  Queen newQ = psBrd->back();
  psBrd->pop_back();

  int newRow, newCol;
  newQ.get_position(&newRow, &newCol);

  for (auto q : *psBrd) {
    int row, col;
    q.get_position(&row, &col);

    float slope = ((float) row - newRow) / ((float) col - newCol);
    if (row == newRow || col == newCol || 1.0 == (slope * slope)) {
      psBrd->push_back(newQ);
      return false;
    }
  }

  psBrd->push_back(newQ);
  return true;
}

/**************************************************************************************************
 * Function  : simple_print_board
 * Inputs    : vector<Queen> * psBrd - A pointer to the board to print
 * Outputs   : (none)
 * Purpose   : Print the board as just a list of indices where a queen has been placed
 * ************************************************************************************************/
void simple_print_board(const vector<Queen> *psBrd) {
  for (auto q : *psBrd) {
    int row, col;
    q.get_position(&row, &col);

    cout << "(" << row << ", " << col << ") ";
  }
  cout << endl;
}

/**************************************************************************************************
 * Function  : print_board
 * Inputs    : vector<Queen> * psBrd - A pointer to the board to print
 * Outputs   : (none)
 * Purpose   : Print the board as just a more visually appealing matrix
 * ************************************************************************************************/
void print_board(const vector<Queen> *psBrd) {
  int queens[N];

  for (auto q : *psBrd) {
    int row, col;
    q.get_position(&row, &col);

    queens[row] = col;
  }

  for (int i = 0; i < (2 * N) + 1; i++){
    cout << "_";
  }
  cout << endl;

  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      if (col == queens[row]) {
        cout << "|Q";
      } else {
        cout << "|_";
      }
    }

    cout << "|" << endl;
  }
  cout << endl;
}