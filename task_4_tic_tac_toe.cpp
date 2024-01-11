#include <iostream>

using namespace std;

const int FIRST_AI_MOVES[] = { 4, 2, 6 };
const int CELL_AMOUNT = 9;
const int ROW_LENGTH = 3;

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
bool isDraw();

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
    for (int i = 0; i < ROW_LENGTH; i++) {
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
    for (int i = 0; i < ROW_LENGTH; i++) {
        int currentCell = gameCells[rowNumber * ROW_LENGTH + i];
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
    for (int i = 0; i < ROW_LENGTH; i++) {
        cout << (rowNumber * ROW_LENGTH + i + 1) << " | ";
    }
}

void userMove()
{
    int number = 0;
    printField();
    while (true) {
        cout << endl << "Please, select an empty cell for your move: ";
        cin >> number;
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
    printField();
    if (freeCells < CELL_AMOUNT) {
        while (true) {
            int randomNumber = rand() % CELL_AMOUNT;
            if (gameCells[randomNumber] == 0) {
                cout << endl << "AI move: " << (randomNumber + 1) << endl;
                gameCells[randomNumber] = 1;
                break;
            }
        }
        freeCells--;
        if (isWin(1)) {
            return;
        }
        if (isDraw()) {
            return;
        }
    }
    else {
        int move = FIRST_AI_MOVES[aiFirstCounter];
        aiFirstCounter = (aiFirstCounter + 1) % ROW_LENGTH;
        cout << endl << "AI move: " << (move + 1) << endl;
        gameCells[move] = 1;
    }

    userMove();
}

bool isWin(int current)
{
    if ((gameCells[0] == current && gameCells[1] == current && gameCells[2] == current) ||
        (gameCells[3] == current && gameCells[4] == current && gameCells[5] == current) ||
        (gameCells[6] == current && gameCells[7] == current && gameCells[8] == current) ||
        (gameCells[0] == current && gameCells[3] == current && gameCells[6] == current) ||
        (gameCells[1] == current && gameCells[4] == current && gameCells[7] == current) ||
        (gameCells[2] == current && gameCells[5] == current && gameCells[8] == current) ||
        (gameCells[0] == current && gameCells[4] == current && gameCells[8] == current) ||
        (gameCells[2] == current && gameCells[4] == current && gameCells[6] == current)) {
        printField();
        if (current == -1) {
            cout << endl << "User wins!" << endl;
        }
        else {
            cout << endl << "AI wins!" << endl;
        }
        return true;
    }
    return false;
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