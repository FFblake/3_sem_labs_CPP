#include <iostream>
#include <time.h>


class floatArray
{
private:
    float* arr;
    int size;

public:
    floatArray(int size = 1)
    {
        this->size = size;
        arr = (float*)malloc(sizeof(float) * size);
    }
    friend class intArray;
    void display()
    {
        std::cout << "Display float array:" << std::endl;
        for (int i = 0; i < size; i++)
        {
            if (i % 5 == 0 && i != 0)
            {
                std::cout << std::endl;
            }
            std::cout << arr[i] << "\t";
        }
        std::cout << std::endl;
    }
};

class intArray
{
private:
    int* arr;
    int size;

public:
    static int count;
    intArray(int size = 1)
    {
        this->size = size;
        arr = (int*)malloc(sizeof(int) * size);
        srand(count++);
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand() % 10;
        }
    }

    int& operator[](int i)
    {
        return arr[i];
    }

    void operator()(std::string s)
    {
        std::cout << s << std::endl;
    }

    intArray operator++()
    {
        for (int i = 0; i < this->size; i++)
        {
            this->arr[i]++;
        }
        return *this;
    }

    intArray operator++(int)
    {
        intArray temp(this->size);
        temp.size = this->size;
        for (int i = 0; i < this->size; i++)
        {
            temp.arr[i] = this->arr[i];
            this->arr[i]++;
        }
        return temp;
    }

    intArray operator+(const intArray& a)
    {
        int tsize = 0, gsize = 0, flag = 0;
        if (this->size > a.size)
        {
            tsize = a.size;
            gsize = this->size;
            flag = 1;
        }
        else
        {
            tsize = this->size;
            gsize = a.size;
            flag = 0;
        }
        intArray temp(gsize);
        temp.size = gsize;
        for (int i = 0; i < temp.size; i++)
        {
            if (i < tsize)
                temp.arr[i] = this->arr[i] + a.arr[i];
            else
            {
                if (flag)
                    temp.arr[i] = this->arr[i];
                else
                    temp.arr[i] = a.arr[i];
            }
        }
        return temp;
    }

    intArray operator-(const intArray& a)
    {
        int tsize = 0, gsize, flag = 0;
        if (this->size > a.size)
        {
            tsize = a.size;
            gsize = this->size;
            flag = 1;
        }
        else
        {
            tsize = this->size;
            gsize = a.size;
            flag = 0;
        }
        intArray temp(gsize);
        temp.size = gsize;
        for (int i = 0; i < temp.size; i++)
        {
            if (i < tsize)
                temp.arr[i] = this->arr[i] - a.arr[i];
            else
            {
                if (flag)
                    temp.arr[i] = this->arr[i];
                else
                    temp.arr[i] = a.arr[i];
            }
        }
        return temp;
    }

    bool operator<(const intArray& a)
    {
        if (this->size < a.size)
            return true;
        else
            return false;
    }

    bool operator>(const intArray& a)
    {
        if (this->size > a.size)
            return true;
        else
            return false;
    }

    floatArray toFloat()
    {
        floatArray temp(this->size);
        temp.size = this->size;
        for (int i = 0; i < this->size; i++)
        {
            temp.arr[i] = float(this->arr[i]);
        }
        return temp;
    }

    friend intArray operator--(intArray& a);
    friend intArray operator--(intArray& a, int);
    friend intArray operator+(intArray& a, const int b);
    friend bool operator==(const intArray& a, const int b);
    friend std::ostream& operator<<(std::ostream& out, const intArray& a);

    void display()
    {
        std::cout << "Display int array:" << std::endl;
        for (int i = 0; i < size; i++)
        {
            if (i % 4 == 0 && i != 0)
            {
                std::cout << std::endl;
            }
            std::cout << arr[i] << "\t";
        }
        std::cout << std::endl;
    }
};

intArray operator--(intArray& a)
{
    for (int i = 0; i < a.size; i++)
    {
        a.arr[i]--;
    }
    return a;
}

intArray operator--(intArray& a, int)
{
    intArray temp(a.size);
    temp.size = a.size;
    for (int i = 0; i < a.size; i++)
    {
        temp.arr[i] = a.arr[i];
        a.arr[i]--;
    }
    return temp;
}

intArray operator+(intArray& a, const int b)
{
    for (int i = 0; i < a.size; i++)
    {
        a.arr[i] += b;
    }
    return a;
}

bool operator==(const intArray& a, const int b)
{
    bool flag = true;
    for (int i = 0; i < a.size; i++)
    {
        if (a.arr[i] != b)
            flag = false;
    }
    return flag;
}

std::ostream& operator<<(std::ostream& out, const intArray& a)
{
    out << "Display array:" << std::endl;
    for (int i = 0; i < a.size; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            out << std::endl;
        }
        out << a.arr[i] << "\t";
    }
    out << std::endl;
    return out;
}

int intArray::count = 0;

int main()
{
    intArray arr = intArray(10);
    intArray mas = intArray(4);
    floatArray test;
    arr.display();
    mas.display();
    mas = mas - arr;
    mas.display();
    test = mas.toFloat();
    test.display();
    std::cout << (arr == 7) << std::endl;
    --arr;
    arr.display();
    ++arr;
    arr.display();

    arr > mas;
}
