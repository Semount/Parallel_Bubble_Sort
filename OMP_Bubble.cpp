#include <iostream>
#include <omp.h>

using namespace std;

void FillArr(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    cout << endl << endl;
}

void ParallelBubbleSort(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        int v = 0;
        if (i % 2 == 0)
        {
#pragma omp parallel for private(v)
            for (int j = 0; j < size; j += 2)
                if (j < size - 1)
                    if (arr[j] > arr[j + 1])
                    {
                        v = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = v;
                    }
        }
        else
        {
#pragma omp parallel for private(v)
            for (int j = 1; j < size; j += 2)
                if (j < size - 1)
                    if (arr[j] > arr[j + 1])
                    {
                        v = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = v;
                    }
        }
    }
}

int main()
{
    double start, end, time;


    int* arr; // указатель для выделения памяти под массив
    int size; // размер массива

    // Ввод количества элементов массива
    cout << "N = ";
    cin >> size;

    if (size <= 0) {
        // Размер масива должен быть положитлеьным
        cout << "Invalid size" << endl;
        return 1;
    }

    arr = new int[size]; // выделение памяти под массив

    int numThreads;
    for (numThreads = 2; numThreads <= 12; numThreads += 1)
    {
        FillArr(arr, size);
        cout << "Bubble sort on " << numThreads << endl;
        start = omp_get_wtime();

        ParallelBubbleSort(arr, size);

        end = omp_get_wtime();
        time = end - start;
        cout << "Sorted array:" << endl;
        // Вывод отсортированного массива на экран
        for (int i = 0; i < size; i++) {
            if (i % 20 == 0) { cout << endl; }
            cout << arr[i] << " ";
        }
        cout << endl << "Sorting time: " << time << endl;
    }
    cout << "Sorted array:" << endl;
    // Вывод отсортированного массива на экран
    for (int i = 0; i < size; i++) {
        if (i % 20 == 0) { cout << endl; }
        cout << arr[i] << " ";
    }

    cout << endl << endl << "Sorting time: " << time;

    delete[] arr; // освобождение памяти;

    return 0;
}