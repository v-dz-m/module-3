#include <iostream>

using namespace std;

void printInvinsible(int heights[], int total, int step, int start);
bool isVisible(int height, int a, int x, int b);

int main()
{
    const int AREAS = 8;
    const int STEP = 2;
    const int START_HEIGHT = 4;
    int heights[AREAS] = { 5, 8, 11, 13, 15, 16, 20, 22 };

    cout << endl << "Module 3, task 1." << endl << "SURVEILLANCE SYSTEM. An array consists of elevation values of the terrain profile with constant horizontal step. Find areas that are invisible to the observer." << endl << endl;
    printInvinsible(heights, AREAS, STEP, START_HEIGHT);

    return 0;
}

void printInvinsible(int heights[], int total, int step, int start)
{
    for (int i = 0; i < total; i++) {
        if (!isVisible(heights[i], i + 1, step, start)) {
            cout << "Area [" << i << "] is invisible." << endl;
        }
    }
}

bool isVisible(int height, int a, int x, int b)
{
    return height > (a * x + b);
}