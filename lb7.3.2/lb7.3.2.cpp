#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0);
void SortRowsByDuplicateCount(int** a, const int rowCount, const int colCount, int i = 0);
void BubbleSort(int** a, const int colCount, int rowCount, int i = 0, int j = 0);
int FindFirstNonNegativeColumn(int** a, const int rowCount, const int colCount, int j = 0);
int CountDuplicatesInRow(int* row, const int colCount, int i = 0, int j = 1);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;
    int rowCount, colCount;

    cout << "rowCount = ";
    cin >> rowCount;
    cout << "colCount = ";
    cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);

    Print(a, rowCount, colCount);

    SortRowsByDuplicateCount(a, rowCount, colCount);
    cout << "Matrix after sorting rows by the count of duplicate elements:" << endl;
    Print(a, rowCount, colCount);

    int nonNegativeCol = FindFirstNonNegativeColumn(a, rowCount, colCount);
    if (nonNegativeCol != -1)
        cout << "The first column with no negative elements is: " << nonNegativeCol << endl;
    else
        cout << "There are no columns without negative elements." << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    if (i < rowCount)
    {
        if (j < colCount)
        {
            a[i][j] = Low + rand() % (High - Low + 1);
            Create(a, rowCount, colCount, Low, High, i, j + 1);
        }
        else
        {
            Create(a, rowCount, colCount, Low, High, i + 1, 0);
        }
    }
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
    if (i < rowCount)
    {
        if (j < colCount)
        {
            cout << setw(4) << a[i][j];
            Print(a, rowCount, colCount, i, j + 1);
        }
        else
        {
            cout << endl;
            Print(a, rowCount, colCount, i + 1, 0);
        }
    }
}

int CountDuplicatesInRow(int* row, const int colCount, int i, int j)
{
    if (i >= colCount)
        return 0;
    if (j >= colCount)
        return CountDuplicatesInRow(row, colCount, i + 1, i + 2);
    if (row[i] == row[j])
        return 1 + CountDuplicatesInRow(row, colCount, i + 1, i + 2);
    return CountDuplicatesInRow(row, colCount, i, j + 1);
}

void BubbleSort(int** a, const int colCount, int rowCount, int i, int j)
{
    if (j < rowCount - i - 1)
    {
        if (CountDuplicatesInRow(a[j], colCount) > CountDuplicatesInRow(a[j + 1], colCount))
            swap(a[j], a[j + 1]);
        BubbleSort(a, colCount, rowCount, i, j + 1);
    }
    else if (i < rowCount - 1)
    {
        BubbleSort(a, colCount, rowCount, i + 1, 0);
    }
}

void SortRowsByDuplicateCount(int** a, const int rowCount, const int colCount, int i)
{
    BubbleSort(a, colCount, rowCount);
}

int FindFirstNonNegativeColumn(int** a, const int rowCount, const int colCount, int j)
{
    if (j >= colCount)
        return -1;
    for (int i = 0; i < rowCount; i++)
    {
        if (a[i][j] < 0)
            return FindFirstNonNegativeColumn(a, rowCount, colCount, j + 1);
    }
    return j;
}
