#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include "vector.cpp"

using namespace std;

int min(int a, int b)
{
    int res;
    if(a > b)
    {
        res = b;
    }
    else
    {
        res = a;
    }

    return res;
}

int get_minrun(int n)
	{
	    int r = 0;
	    while (n >= 64)
		{
	        r |= (n & 1);
	        n >>= 1;
	    }
	    return n + r;
	}

void insert_sort(Vector<int>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int curr = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > curr)
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = curr;
    }
}

void galloping(Vector<int> &arr, Vector<int> &sub, int &left_curr, int &right_curr, const int new_right, int &arr_curr, bool is_left)
{
    int galloping_curr = -1;
    if (is_left)
    {
        int left = left_curr;
        int right = sub.get_size();
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (sub[galloping_curr] < arr[right_curr])
            {
                for (int i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = sub[i];
                    arr_curr++;
                }
                left = galloping_curr;
                left_curr = galloping_curr;
            }
            else
                right = galloping_curr;
        }
    }
    else
    {
        int left = right_curr;
        int right = new_right;
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (arr[galloping_curr] < sub[left_curr])
            {
                for (int i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = arr[i];
                    arr_curr++;
                }
                left = galloping_curr;
                right_curr = galloping_curr;
            }
            else
                right = galloping_curr;
        }
    }
}

void merge(Vector<int>& arr, int left, int mid, int right)
{
    int len1 = mid - left + 1;
    int len2 = right - mid;

    Vector<int> left_arr(len1);
    Vector<int> right_arr(len2);

    for (int i = 0; i < len1; i++)
    {
        left_arr[i] = arr[left + i];
    }

    for (int i = 0; i < len2; i++)
    {
        right_arr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < len1 && j < len2)
    {
        if (left_arr[i] <= right_arr[j]) arr[k++] = left_arr[i++];
        else arr[k++] = right_arr[j++];
    }

    while (i < len1)
    {
        arr[k++] = left_arr[i++];
    }

    while (j < len2)
    {
        arr[k++] = right_arr[j++];
    }
}

void tim_sort(Vector<int>& arr)
{
    int n = arr.get_size();
    int min_run = get_minrun(n);

    for (int i = 0; i < n; i += min_run)
    {
        insert_sort(arr, i, min(i + min_run - 1, n - 1));
    }

    for (int size = min_run; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            if (mid < right)
            {
                merge(arr, left, mid, right);
            }
        }
    }
}

int main()
{
    srand(time (NULL));

    int size;
    cout << "Введите число элементов" << endl << ">>> ";
    cin >> size;

    Vector<int> vec(size+1);
    cout << vec;

    for (int i = 0; i < size; i++)
    {
        vec.push_back(rand() % 1001);
    }

    cout << vec;

    while(true)
    {
        int choice = 0;

        cout << "1) Изменить число элементов (сейчас: " << size << ")" << endl;
        cout << "2) Вывести массив" << endl;
        cout << "3) Отсортировать массив" << endl;
        cout << "0) Выход" << endl;
        cout << ">>> ";

        cin >> choice;
        cout << endl;

        if(choice == 1)
        {
            int new_size = 1;

            cout << "Cейчас элементов: " << size << endl;
            cout << "Новый размер = ";
            cin >> new_size;
            cout << endl;

            Vector<int> new_vec(new_size + 1);
            for (int i = 0; i < new_size; i++)
            {
                new_vec.push_back(rand() % 1001);
            }

            vec = new_vec;
            size = new_size;

            cout << vec;
            system("clear");
        }
        else if (choice == 2)
        {
            system("clear");
            cout << "Начальный массив: " << endl;
            cout << vec << endl;
        }
        else if (choice == 3)
        {
            tim_sort(vec);

            system("clear");
            cout << "Отсортированный массив: " << endl;
            cout << vec << endl;
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            system("clear");
            cout << "Вы ввели неверное значение!!!" << endl;
        }
    }
}
