#include <iostream>

using namespace std;

const int FIRST_AI_MOVES[] = { 4, 2, 6 };
const int CELL_AMOUNT = 9;
const int LINE_LENGTH = 3;
const int MIDDLE_CELL_INDEX = 4;
const int WIN_LINES = 8;
const int USER_MARK = 2;
const int AI_MARK = 1;

const int WIN_LINE_INDEXES[WIN_LINES][LINE_LENGTH] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };

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
int getUserMove();
void aiMove();
int getAIMove();
bool isWin(int current);
void printWin(int current);
bool isDraw();
int firstAIMove();
int secondAIMove();
int thirdAIMove();
int forthAIMove();
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
        if (currentCell == USER_MARK) {
            cout << (isUserFirst ? "X" : "O");
        }
        else if (currentCell == AI_MARK) {
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
    printField();
    int number = getUserMove();
    freeCells--;
    if (isWin(USER_MARK)) {
        return;
    }
    if (isDraw()) {
        return;
    }

    aiMove();
}

int getUserMove()
{
    int number = 0;
    while (true) {
        cout << endl << "Please, select an empty cell for your move: ";
        cin >> number;
        if (number <= 0 || number > CELL_AMOUNT) {
            cout << "Your number is not a cell number, try again...";
            continue;
        }
        if (gameCells[number - 1] == 0) {
            gameCells[number - 1] = USER_MARK;
            break;
        }
        cout << "This cell is taken, try again..." << endl;
    }

    return number;
}

void aiMove()
{
    int move = -1;
    printField();
    move = getAIMove();
    gameCells[move] = AI_MARK;

    cout << endl << "AI move: " << (move + 1) << endl;

    freeCells--;
    if (isWin(AI_MARK)) {
        return;
    }
    if (isDraw()) {
        return;
    }
    userMove();
}

int getAIMove()
{
    if (freeCells == CELL_AMOUNT) {
        return firstAIMove();
    }
    if (freeCells == CELL_AMOUNT - 1) {
        return secondAIMove();
    }
    else if (freeCells == CELL_AMOUNT - 2) {
        return thirdAIMove();
    }
    else if (freeCells == CELL_AMOUNT - 3) {
        return forthAIMove();
    }
    else {
        return bestAIMove();
    }
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
    if (current == USER_MARK) {
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
    if (gameCells[MIDDLE_CELL_INDEX] == 0) {
        return MIDDLE_CELL_INDEX;               // if the middle cell is empty, take it
    }

    return rand() % 4 * 2;                      // otherwise take a random corner cell (1, 3, 5, 7)
}

int thirdAIMove()
{
    if (gameCells[MIDDLE_CELL_INDEX] == 0) {
        return MIDDLE_CELL_INDEX;
    }

    while (true) {
        int randomNumber = rand() % 4 * 2;
        if (gameCells[randomNumber] == 0) {
            return randomNumber;
        }
    }
}

int forthAIMove()
{
    for (int i = 1; i < CELL_AMOUNT - 2; i += 2) {
        for (int j = i + 2; j < CELL_AMOUNT; j += 2) {
            int first = gameCells[i];
            int second = gameCells[j];
            if (first == USER_MARK && second == USER_MARK) {    // check: are two even cells taken by player?
                return i + j - 4;                               // if so, take closer corner cell
            }
        }
    }

    return repelAIMove();
}

int bestAIMove()
{
    int bestCell = getBestLineCell(AI_MARK);
    if (bestCell > -1) {
        return bestCell;
    }

    return repelAIMove();
}

int getBestLineCell(int current)
{
    for (int i = 0; i < WIN_LINES; i++) {
        if (gameCells[WIN_LINE_INDEXES[i][0]] == current && gameCells[WIN_LINE_INDEXES[i][1]] == current && gameCells[WIN_LINE_INDEXES[i][2]] == 0) {
            return WIN_LINE_INDEXES[i][2];
        }
        if (gameCells[WIN_LINE_INDEXES[i][0]] == current && gameCells[WIN_LINE_INDEXES[i][2]] == current && gameCells[WIN_LINE_INDEXES[i][1]] == 0) {
            return WIN_LINE_INDEXES[i][1];
        }
        if (gameCells[WIN_LINE_INDEXES[i][1]] == current && gameCells[WIN_LINE_INDEXES[i][2]] == current && gameCells[WIN_LINE_INDEXES[i][0]] == 0) {
            return WIN_LINE_INDEXES[i][0];
        }
    }

    return -1;
}

int repelAIMove()
{
    int bestCell = getBestLineCell(USER_MARK);
    if (bestCell > -1) {
        return bestCell;
    }

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