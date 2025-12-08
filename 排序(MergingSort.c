#include <stdio.h>
#include <stdlib.h>

int data01[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
int data02[] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
int data03[] = {0, 23, 12, 55, 76, 35, 66, 86, 55, 47, 42, 2, 31, 44};
int data1[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
int data2[] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
int data3[] = {0, 23, 12, 55, 76, 35, 66, 86, 55, 47, 42, 2, 31, 44};
int length1 = sizeof(data1) / sizeof(data1[0]) - 1;
int length2 = sizeof(data2) / sizeof(data2[0]) - 1;
int length3 = sizeof(data3) / sizeof(data3[0]) - 1;
int visited[sizeof(data2) / sizeof(data2[0])] = {0};

void resetdata(int *data, int *source, int length)
{
    for (int i = 0; i < length + 1; i++)
    {
        data[i] = source[i];
    }
}

void InsertSort(int *data, int length)
{
    int current = 2;
    for (int i = 2; i < length + 1; i++)
    {
        if (data[current] < data[current - 1])
        {
            data[0] = data[current];
            data[current] = data[current - 1];
            int pos = current - 2;
            while (pos > 0 && data[0] < data[pos])
            {
                data[pos + 1] = data[pos];
                pos = pos - 1;
            }
            data[pos + 1] = data[0];
        }
        current++;
    }
    printf("InsertSort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data01, length1);
}

void BInertSort(int *data, int length)
{
    int current = 2;
    for (int i = 2; i < length + 1; i++)
    {
        if (data[current] < data[current - 1])
        {
            data[0] = data[current];
            int left = 1, right = current - 1;
            int mid;
            while (right >= left)
            {
                mid = (left + right) / 2;
                if (data[0] > data[mid])
                {
                    left = mid + 1;
                }
                else if (data[0] < data[mid])
                {
                    right = mid - 1;
                }
                else if (data[0] == data[mid])
                {
                    mid++;
                    break;
                }
            }
            for (int j = current - 1; j >= mid; j--)
            {
                data[j + 1] = data[j];
            }
            data[mid] = data[0];
        }
        current++;
    }
    printf("Binary InsertSort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data01, length1);
}

void ShellInsertSort(int *data, int length)
{
    for (int gap = length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap + 1; i < length + 1; i++)
        {
            if (data[i] < data[i - gap])
            {
                data[0] = data[i];
                data[i] = data[i - gap];
                int pos = i - gap - gap;
                while (pos > 0 && data[0] < data[pos])
                {
                    data[pos + gap] = data[pos];
                    pos = pos - gap;
                }
                data[pos + gap] = data[0];
            }
        }
    }
    printf("Shell InsertSort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data02, length2);
}

void BubbleSort(int *data, int length)
{
    for (int i = 0; i < length; i++)
    {
        int k = 0;
        for (int j = 2, temp; j < length + 1 - i; j++)
        {
            if (data[j] < data[j - 1])
            {
                temp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = temp;
                k = 1;
            }
        }
        if (k == 0)
        {
            break;
        }
    }
    printf("Bubble Sort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data01, length1);
}

// int data1[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
void quicksort(int *data, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = data[(left + right) / 2];
    int begin = left, end = right;
    while (begin <= end)
    {
        while (begin <= end && data[begin] < pivot)
        {
            begin++;
        }
        while (end >= begin && data[end] > pivot)
        {
            end--;
        }
        if (begin <= end)
        {
            data[0] = data[begin];
            data[begin] = data[end];
            data[end] = data[0];
            begin++;
            end--;
        }
    }
    quicksort(data, left, end);
    quicksort(data, begin, right);
}

void QuickSort(int *data, int left, int right, int length)
{
    quicksort(data, left, right);
    printf("Quick Sort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data01, length1);
}

void SimpleSelectionSort(int *data, int length)
{
    for (int j = 1; j < length + 1; j++)
    {
        int MIN = 999;
        int k = 0;
        for (int i = j; i < length + 1; i++)
        {
            if (data[i] < MIN)
            {
                MIN = data[i];
                k = i;
            }
        }
        data[0] = data[k];
        data[k] = data[j];
        data[j] = data[0];
    }
    printf("Simple Selection Sort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data01, length1);
}

void HeapAdjust(int *data, int length)
{
    for (int j = length / 2; j > 0; j--)
    {
        int k = 0;
        for (int i = length / 2; i > 0; i--)
        {
            if (data[2 * i] > data[i] && visited[2 * i] == 0)
            {
                data[0] = data[2 * i];
                data[2 * i] = data[i];
                data[i] = data[0];
                k = 1;
            }
            if (data[2 * i + 1] && data[2 * i + 1] > data[i] && visited[2 * i + 1] == 0)
            {
                data[0] = data[2 * i + 1];
                data[2 * i + 1] = data[i];
                data[i] = data[0];
                k = 1;
            }
        }
        if (k == 0)
        {
            break;
        }
    }
}

void HeapSort(int *data, int length)
{
    HeapAdjust(data, length);
    for (int i = length; i > 1; i--)
    {
        data[0] = data[i];
        data[i] = data[1];
        data[1] = data[0];
        visited[i] = 1;
        HeapAdjust(data, i - 1);
    }
    printf("Heap Sort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data02, length2);
}

int check(int *data, int length)
{
    for (int i = 1; i < length; i++)
    {
        if (data[i] > data[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

void MergingSort(int *data, int length)
{
    int L = 1;
    int T[length + 1];
    while (!check(data, length))
    {
        int left = 1;
        int right = L + left;
        int k = 1;
        while (left <= length)
        {
            int i = left;
            int j = right;
            while (i <= left - 1 + L && j <= right - 1 + L && i <= length && j <= length)
            {
                if (data[i] <= data[j])
                {
                    T[k++] = data[i++];
                }
                else
                    T[k++] = data[j++];
            }
            while (i <= left - 1 + L && i <= length)
            {
                T[k++] = data[i++];
            }
            while (j <= right - 1 + L && j <= length)
            {
                T[k++] = data[j++];
            }
            left = left + 2 * L;
            right = left + L;
        }
        for (int i = 1; i < length + 1; i++)
        {
            data[i] = T[i];
        }
        if (L < length)
            L = L * 2;
        else
            L = length;
    }
    printf("Merging Sort Result: ");
    for (int i = 1; i < length + 1; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    resetdata(data, data03, length3);
}

int main()
{
    InsertSort(data1, length1);
    BInertSort(data1, length1);
    ShellInsertSort(data2, length2);
    BubbleSort(data1, length1);
    QuickSort(data1, 1, length1, length1);
    SimpleSelectionSort(data1, length1);
    HeapSort(data2, length2);
    MergingSort(data3, length3);
    return 0;
}
