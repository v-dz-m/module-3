#include <iostream>

using namespace std;

const int MAX_N = 8;
int n = 0;
bool cube[MAX_N][MAX_N][MAX_N];

void fillCube();
void printCube();
bool isAnyLineClear();
bool isXLineClear(int y, int z);
bool isYLineClear(int x, int z);
bool isZLineClear(int x, int y);

int main()
{
    cout << endl << "Module 3, task 3." << endl << "GAP. A cube consists of n^3 little transparent and opaque cubes. Is there even a single gap?" << endl << endl;
    cout << "Please, enter n, not bigger than " << MAX_N << ": ";
    cin >> n;
    fillCube();
    printCube();
    cout << (isAnyLineClear() ? "One or more gaps exist in the cube." : "There are no gaps in the cube.") << endl;
}

void fillCube()
{
    cout << endl;
    if (n > 0) {
        cout << "Please, enter transparency values for cube cells (specified with coordinate axes: [x][y][z]).";
        cout << " 1 for transparent or 0 for opaque." << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cout << "Transparency value for [" << k << "][" << j << "][" << i << "]: ";
                cin >> cube[k][j][i];
            }
        }
    }
}

void printCube()
{
    cout << endl;
    for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
            for (int x = 0; x < n; x++) {
                cout << (cube[x][y][z] ? "░░" : "██");
            }
            cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isAnyLineClear()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (isXLineClear(i, j)) {
                return true;
            }
            if (isYLineClear(i, j)) {
                return true;
            }
            if (isZLineClear(i, j)) {
                return true;
            }
        }
    }

    return false;
}

bool isXLineClear(int y, int z)
{
    for (int i = 0; i < n; i++) {
        if (cube[i][y][z] == 0) {
            return false;
        }
    }

    return true;
}

bool isYLineClear(int x, int z)
{
    for (int i = 0; i < n; i++) {
        if (cube[x][i][z] == 0) {
            return false;
        }
    }

    return true;
}

bool isZLineClear(int x, int y)
{
    for (int i = 0; i < n; i++) {
        if (cube[x][y][i] == 0) {
            return false;
        }
    }

    return true;
}