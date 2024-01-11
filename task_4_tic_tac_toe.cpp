#include <iostream>

using namespace std;

int gameCells[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int freeCells = 9;
bool isPlayerFirst = true;

void resetCellValues();
void printMenu();
void printField();
void printDigitRow(int rowNumber);
void printGameRow(int rowNumber);
void userMove();
void computerMove();
bool isDraw();

int main()
{
    int choice = 0;
    while (true) {
        printMenu();
        cin >> choice;
        if (choice == 1) {
            isPlayerFirst = true;
            userMove();
        }
        else if (choice == 2) {
            isPlayerFirst = false;
            computerMove();
        }
        else if (choice == 0) {
            break;
        }
        resetCellValues();
        freeCells = 9;
    }
    return 0;
}

void resetCellValues()
{
    for (int i = 0; i < 9; i++) {
        gameCells[i] = 0;
    }
}

void printMenu()
{
    cout << endl;
    cout << "Who goes first?" << endl;
    cout << "1: Player" << endl;
    cout << "2: Computer" << endl;
    cout << "0: Exit" << endl;
    cout << "Your choice: ";
}

void printField()
{
    cout << endl << "—————————————    —————————————";
    cout << endl;
    for (int i = 0; i < 3; i++) {
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
    for (int i = 0; i < 3; i++) {
        int currentCell = gameCells[rowNumber * 3 + i];
        if (currentCell == -1) {
            cout << (isPlayerFirst ? "X" : "O");
        }
        else if (currentCell == 1) {
            cout << (isPlayerFirst ? "O" : "X");
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
    for (int i = 0; i < 3; i++) {
        cout << (rowNumber * 3 + i + 1) << " | ";
    }
}

void userMove()
{
    int number = 0;
    printField();
    // user move
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
    if (isDraw()) {
        return;
    }

    computerMove();
}

void computerMove()
{
    printField();
    while (true) {
        int randomNumber = rand() % 9;
        if (gameCells[randomNumber] == 0) {
            cout << endl << "Computer move: " << gameCells[randomNumber] << endl;
            gameCells[randomNumber] = 1;
            break;
        }
    }
    freeCells--;
    if (isDraw()) {
        return;
    }

    userMove();
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