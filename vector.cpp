#include <iostream>
using namespace std;

template<typename V>
class Vector
{
    public:
        Vector()
        {
            arr = nullptr; size = 0;

        }

        Vector(int new_size)
        {
            arr = new V[new_size];
            full_size = new_size;
            size = 0;
        }

        void push_back(V new_value)
        {
            this->add(size, new_value);
        }

        void add(int pos, V value)
        {
            ensure_capacity();
            for (int i = size - 1; i > pos-2; i--)
                arr[i+1] = arr[i];
            arr[pos - 1] = value;
            size++;
        }

        void remove(int pos)
        {
            for (int i = pos - 1; i < full_size; i++)
                arr[i] = arr[i+1];
            size--;
        }

        void ensure_capacity()
        {
            if (size >= full_size - 1)
            {
                V* new_arr = new V[full_size * 2];
                for (int i = 0; i < size; i++)
                {
                    new_arr[i] = arr[i];
                }
                delete[] arr;
                arr = new_arr;
            }
        }

        int get_size()
        {
            return size;
        }

        V get_value(int pos)
        {
            return arr[pos - 1];
        }

        V& operator[] (int index)
        {
            return arr[index];
        }

        friend ostream& operator<<(ostream& os, Vector<V>& vec)
        {
            for (size_t i = 0; i < vec.get_size(); i++)
            {
                os << vec[i] << " ";
            }
            os << endl;
            return os;
        }

    private:
        V* arr;
        int size;
        int full_size;
};
