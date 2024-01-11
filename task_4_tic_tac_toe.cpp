#include <iostream>

using namespace std;

const int FIRST_AI_MOVES[] = { 4, 2, 6 };
const int CELL_AMOUNT = 9;
const int LINE_LENGTH = 3;

const int WIN_LINES = 8;
const int WIN_LINE_INDEXES[WIN_LINES][LINE_LENGTH] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
const int BEST_LINES = 24;
const int BEST_LINE_INDEXES[BEST_LINES][LINE_LENGTH] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}, {0, 2, 1}, {3, 5, 4}, {6, 8, 7}, {0, 6, 3}, {1, 7, 4}, {2, 8, 5}, {0, 8, 4}, {2, 6, 4}, {1, 2, 0}, {4, 5, 3}, {7, 8, 6}, {3, 6, 0}, {4, 7, 1}, {5, 8, 2}, {4, 8, 0}, {4, 6, 2} };

int gameCells[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int freeCells = CELL_AMOUNT;
bool isUserFirst = true;
int aiFirstCounter = 0;

void resetCells();
void printMenu();
void printField();
void printDigitRow(int rowNumber);
void printGameRow(int rowNumber);
void userMove();
void aiMove();
bool isWin(int current);
void printWin(int current);
bool isDraw();
int firstAIMove();
int secondAIMove();
int bestAIMove();
int getBestLineCell(int current);
int repelAIMove();
int randomAIMove();

int main()
{
    int choice = 0;
    while (true) {
        printMenu();
        cin >> choice;
        if (choice == 1) {
            isUserFirst = true;
            userMove();
        }
        else if (choice == 2) {
            isUserFirst = false;
            aiMove();
        }
        else if (choice == 0) {
            break;
        }
        resetCells();
    }
    return 0;
}

void resetCells()
{
    for (int i = 0; i < CELL_AMOUNT; i++) {
        gameCells[i] = 0;
    }
    freeCells = CELL_AMOUNT;
}

void printMenu()
{
    cout << endl;
    cout << "Who goes first?" << endl;
    cout << "1: User" << endl;
    cout << "2: AI" << endl;
    cout << "0: Exit" << endl;
    cout << "Your choice: ";
}

void printField()
{
    cout << endl << "—————————————    —————————————";
    cout << endl;
    for (int i = 0; i < LINE_LENGTH; i++) {
        printDigitRow(i);
        cout << "   ";
        printGameRow(i);
        cout << endl;
        cout << "—————————————    —————————————";
        cout << endl;
    }
}

void printGameRow(int rowNumber)
{
    cout << "| ";
    for (int i = 0; i < LINE_LENGTH; i++) {
        int currentCell = gameCells[rowNumber * LINE_LENGTH + i];
        if (currentCell == -1) {
            cout << (isUserFirst ? "X" : "O");
        }
        else if (currentCell == 1) {
            cout << (isUserFirst ? "O" : "X");
        }
        else {
            cout << " ";
        }
        cout << " | ";
    }
}

void printDigitRow(int rowNumber)
{
    cout << "| ";
    for (int i = 0; i < LINE_LENGTH; i++) {
        cout << (rowNumber * LINE_LENGTH + i + 1) << " | ";
    }
}

void userMove()
{
    int number = 0;
    printField();
    while (true) {
        cout << endl << "Please, select an empty cell for your move: ";
        cin >> number;
        if (number <= 0 || number > CELL_AMOUNT) {
            cout << "Your number is not a cell number, try again...";
            continue;
        }
        if (gameCells[number - 1] == 0) {
            gameCells[number - 1] = -1;
            break;
        }
        cout << "This cell is taken, try again..." << endl;
    }
    freeCells--;
    if (isWin(-1)) {
        return;
    }
    if (isDraw()) {
        return;
    }

    aiMove();
}

void aiMove()
{
    int move = -1;
    printField();
    if (freeCells == CELL_AMOUNT) {
        move = firstAIMove();
    }
    else if (freeCells == CELL_AMOUNT - 1) {
        move = secondAIMove();
    }
    else {
        move = bestAIMove();
    }
    gameCells[move] = 1;

    cout << endl << "AI move: " << (move + 1) << endl;

    freeCells--;
    if (isWin(1)) {
        return;
    }
    if (isDraw()) {
        return;
    }
    userMove();
}

bool isWin(int current)
{
    for (int i = 0; i < WIN_LINES; i++) {
        // check all win line cells taken by current
        bool isWinLine = true;
        for (int j = 0; j < LINE_LENGTH; j++) {
            if (gameCells[WIN_LINE_INDEXES[i][j]] != current) {
                isWinLine = false;
                break;
            }
        }
        if (isWinLine) {
            printWin(current);
            return true;
        }
    }

    return false;
}

void printWin(int current)
{
    printField();
    if (current == -1) {
        cout << endl << "User wins!" << endl;
    }
    else {
        cout << endl << "AI wins!" << endl;
    }
}

bool isDraw()
{
    if (freeCells > 0) {
        return false;
    }
    printField();
    cout << endl << "This is a draw!" << endl;

    return true;
}

int firstAIMove()
{
    int move = FIRST_AI_MOVES[aiFirstCounter];
    aiFirstCounter = (aiFirstCounter + 1) % LINE_LENGTH;

    return move;
}

int secondAIMove()
{
    if (gameCells[4] == 0) {
        return 4;               // if the middle cell is empty take it
    }

    return (rand() % 4) * 2;    // otherwise take a random corner cell
}

int bestAIMove()
{
    int bestCell = getBestLineCell(1);
    if (bestCell > -1) {
        return bestCell;
    }

    return repelAIMove();
}

int getBestLineCell(int current)
{
    for (int i = 0; i < BEST_LINES; i++) {
        if (gameCells[BEST_LINE_INDEXES[i][0]] == current && gameCells[BEST_LINE_INDEXES[i][1]] == current && gameCells[BEST_LINE_INDEXES[i][2]] == 0) {
            return BEST_LINE_INDEXES[i][2];
        }
    }

    return -1;
}

int repelAIMove()
{
    return randomAIMove();
}

int randomAIMove()
{
    while (true) {
        int randomNumber = rand() % CELL_AMOUNT;
        if (gameCells[randomNumber] == 0) {
            return randomNumber;
        }
    }
}