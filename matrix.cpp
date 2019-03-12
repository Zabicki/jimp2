#include <iostream>

using namespace std;

class Matrix
{
        friend ostream & operator<<(ostream & s1, Matrix & o1);
        friend istream & operator>>(istream & s1, Matrix & o1);
        double* p;
        int size;
public:
        Matrix(int size)
        {
                this->size = size;
                p = new double[size*size];
        }
        Matrix(Matrix & a1)
        {
                this->size = a1.size;
                p = new double[size*size];
                for (int i = 0; i < size * size; i++)
                        this->p[i] = a1.p[i];
        }



        Matrix & operator=(const Matrix & o1)
        {
                if (this == &o1)
                        return *this;
                delete [] this->p;
                this->size = o1.size;
                this->p = new double [o1.size * o1.size];
                for (int i = 0; i < o1.size * o1.size; ++i)
                        this->p[i] = o1.p[i];
                return *this;
        }
        Matrix operator+(Matrix & o1)
        {
                Matrix result;
                result = *this;
                if (result.size == o1.size)
                {
                        for (int i = 0; i < result.size * result.size; ++i)
                                result.p[i] += o1.p[i];
                }
                return result;
        }
        Matrix operator-(Matrix & o1)
        {
                Matrix result;
                result = *this;
                if (result.size == o1.size)
                {
                        for (int i = 0; i < result.size * result.size; ++i)
                                result.p[i] -= o1.p[i];
                        return result;
                }
        }
        int operator==(Matrix & o1)
        {
                int flag = 1;
                if (this->size == o1.size)
                {
                        for (int i = 0; i < this->size * this->size; ++i)
                        {
                                if (this->p[i] != o1.p[i])
                                {
                                        flag = 0;
                                        break;
                                }
                        }
                }
                return flag;
        }
        int operator!=(Matrix & o1)
        {
                int flag = 0;
                if (this->size == o1.size)
                {
                        for (int i = 0; i < this->size * this->size; ++i)
                        {
                                if (this->p[i] != o1.p[i])
                                {
                                        flag = 1;
                                        break;
                                }
                        }
                }
                else
                        flag = 1;
                return flag;
        }
        int operator>(Matrix & o1)
        {
                if (this->size == o1.size)
                {
                        int sum1 = 0, sum2 = 0;
                        for (int i = 0; i < this->size * this->size; i++)
                                sum1 += this->p[i];
                        for (int i = 0; i < this->size * this->size; i++)
                                sum2 += o1.p[i];
                        if (sum1 > sum2)
                                return 1;
                        else
                                return 0;
                }
        }
        int operator<(Matrix & o1)
        {
                if (this->size == o1.size)
                {
                        int sum1 = 0, sum2 = 0;
                        for (int i = 0; i < this->size * this->size; i++)
                                sum1 += this->p[i];
                        for (int i = 0; i < this->size * this->size; i++)
                                sum2 += o1.p[i];
                        if (sum1 > sum2)
                                return 0;
                        else
                                return 1;
                }
        }
        Matrix()
        {
                size = 0;
                p = NULL;
        }
        ~Matrix()
        {
                if (p != NULL)
                {
                        delete [] p;
                        p = NULL;
                }
        }
};

ostream & operator<<(ostream & s1, Matrix & o1)
{
        if (o1.p != NULL)
        {
                for (int i = 1; i <= o1.size * o1.size; ++i)
                {
                        cout << o1.p[i-1];
                        if (i % o1.size == 0 && i != 1)
                                cout << endl;
                }
        }
        return s1;
}
istream & operator>>(istream & s1, Matrix & o1)
{
        if (o1.p != NULL)
                delete [] o1.p;
        s1 >> o1.size;
        if (o1.size > 0)
        {
                o1.p = new double [o1.size * o1.size];
                for (int i = 0; i < o1.size * o1.size; ++i)
                        cin >> o1.p[i];
        }
        return s1;
}

int main(void)
{
        /*
        Matrix o1;
        Matrix o2;
        Matrix o3;
        Matrix o4;
        cin >> o1;
        cout << "o1 =\n" << o1;
        cin >> o2;
        cout << "o1 =\n" << o2;
        o3 = o1 + o2;
        cout << "o1 + o2 = \n" << o3 << endl;
        o4 = o1 - o2;
        cout << "o1 - o2 = \n" << o4 << endl;
        cout << o1;
        cout << o2;
        if (o1 == o2)
                cout << "Macierze sa rowne\n";
        else
                cout << "Macierze nie sa rowne\n";
        if (o1 != o2)
                cout << "Macierze nie sa rowne\n";
        else
                cout << "Macierze sa rowne\n";
        if (o1 > o2)
                cout << "Macierz o1 jest wieksza niz macierz o2\n";
        else
                cout << "Macierz o2 jest wieksza niz macierz o1\n";

        Matrix o5;
        cin >> o5;
        Matrix o6(o5);
        cout << o6;*/
        //o1 = o2;
        //o1 = o1;
        //cout << o1;
        //cout << o1;
        //o1.~Matrix();
        //o1.~Matrix();
        Matrix a,b,c;
        cin >> a >> b;
        c = a + b;
        cout << c;
        return 0;
}

