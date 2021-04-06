template <typename T>
class MyArray
{
public:
    MyArray(int n = 1)
    {
        size = n;
        arr = new T[size];
    }

    class Iterator
    {
        T* cur;
    public:
        Iterator(T* first)
        {
            cur = first;
        }

        T& operator+ (int n)
        {
            return *(cur + n);
        }

        T& operator- (int n)
        {
            return *(cur - n);
        }

        T& operator++ ()
        {
            return *(cur++);
        }

        T& operator-- ()
        {
            return *(cur--);
        }

        T& operator++ (int)
        {
            return *(++cur);
        }

        T& operator-- (int)
        {
            return *(--cur);
        }

        bool operator== (const Iterator& it)
        {
            return it.cur == cur;
        }

        bool operator!= (const Iterator& it)
        {
            return it.cur != cur;
        }

        T& operator* ()
        {
            return *cur;
        }
    };

    T& operator[] (const int& n)
    {
        if (n > 0 && n < size)
            return arr[n];
        return arr[0];
    }

    ~MyArray()
    {
        if (!arr) delete[] arr;
    }

    Iterator begin()
    {
        return arr;
    }

    Iterator end()
    {
        return arr + size;
    }

private:
    T* arr;
    int size;
};