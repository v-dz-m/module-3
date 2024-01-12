#include <iostream>
#include <windows.h>

using namespace std;

const int MAX_RECRUITS = 10;
const int SLEEP_TIME = 1000;
const DWORD FREQUENCY = 1000;
const DWORD DURATION = 1000;

void setInitialLine(bool recruits[], int numberRecruits);
void makeAboutTurn(bool recruits[], int numberRecruits);
void printRecruitLine(bool recruits[], int numberRecruits);

int main()
{
    int numberRecruits = 0;

    cout << endl << "Module 3, task 2. RECRUITS." << endl << endl;
    cout << "Please, enter the number of recruits, not bigger than " << MAX_RECRUITS << ": ";
    cin >> numberRecruits;
    bool recruits[numberRecruits];

    cout << endl << "SERGEANT: Column left!" << endl;
    Beep(FREQUENCY, DURATION);
    setInitialLine(recruits, numberRecruits);
    makeAboutTurn(recruits, numberRecruits);

    cout << endl << "SERGEANT: Attention!" << endl;
    Beep(FREQUENCY, DURATION);

    return 0;
}

void setInitialLine(bool recruits[], int numberRecruits)
{
    for (int i = 0; i < numberRecruits; i++) {
        recruits[i] = (rand() % 2);
    }
}

void makeAboutTurn(bool recruits[], int numberRecruits)
{
    bool hasChanged = true;
    while (hasChanged) {
        cout << endl << "Current line: ";
        printRecruitLine(recruits, numberRecruits);
        Sleep(SLEEP_TIME);

        hasChanged = false;
        for (int i = 1; i < numberRecruits; i++) {
            bool firstRecruit = recruits[i - 1];
            bool secondRecruit = recruits[i];
            if (firstRecruit && !secondRecruit) {
                recruits[i - 1] = secondRecruit;
                recruits[i] = firstRecruit;
                hasChanged = true;
                i++;
            }
        }
    }
}

void printRecruitLine(bool recruits[], int numberRecruits)
{
    for (int i = 0; i < numberRecruits; i++) {
        cout << (recruits[i] ? '>' : '<') << " ";
    }
    cout << std::endl;
}