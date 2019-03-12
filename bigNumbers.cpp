#include <iostream>
#include <stdio.h>
#include <termios.h>
#include "getchLinuxEquivalent.cpp"

using namespace std;

static struct termios old, new1;

/* Initialize new1 terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new1 = old; /* make new1 settings same as old settings */
    new1.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        new1.c_lflag |= ECHO; /* set echo mode */
    } else {
        new1.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &new1); /* use these new1 terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
int getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

class BigNumbers {
    friend class BigNumbersChild;
protected:
    int* number;
    unsigned int size;
public:
    friend istream& operator>>(istream& s1, BigNumbers& l1);
    friend ostream& operator<<(ostream& s1, BigNumbers& l1);
    BigNumbers() {
        size = 0;
        number = NULL;
    }
    ~BigNumbers() {
        if (number != NULL) {
            delete[] number;
            size = 0;
        }
    }

    BigNumbers operator+(BigNumbers& a) {
        bool toAddOne = false;
        BigNumbers newNumber;
        int* tmpTab;
        int tmpSum; //sum of 2 numbers
        int size;
        int biggerSize;
        int* biggerTable;
        int* smallerTable;
        int longerIterator = 0;
        int shorterIterator = 0;

        if (this->size <= a.size) {
            size = this->size;
            biggerSize = a.size;
            biggerTable = a.number;
            smallerTable = this->number;
        }
        else {
            size = a.size;
            biggerSize = this->size;
            biggerTable = this->number;
            smallerTable = a.number;
        }
        shorterIterator = size - 1;
        longerIterator = biggerSize - 1;

        for (int i = size - 1; i >= 0; --i) {
            tmpSum = this->number[i] + a.number[i];
            if (toAddOne) {
                tmpSum++;
                toAddOne = false;
            }
            if (tmpSum > 9) {
                toAddOne = true;
                tmpSum %= 10;
            }
            tmpTab = new int[newNumber.size];
            for (int j = 0; j < newNumber.size; ++j) {
                tmpTab[j] = newNumber.number[j];
            }
            delete newNumber.number;
            newNumber.size++;
            newNumber.number = new int[newNumber.size - 1];
            for (int j = 0; j < newNumber.size - 1; ++j) {
                newNumber.number[j] = tmpTab[j];
            }
            delete tmpTab;
            newNumber.number[newNumber.size - 1] = tmpSum;
        }

        if (newNumber.size < biggerSize) {
            for (int i = newNumber.size; i < biggerSize; ++i) {
                tmpSum = biggerTable[i];
                if (toAddOne) {
                    tmpSum++;
                    toAddOne = false;
                }
                tmpTab = new int[newNumber.size];
                for (int j = 0; j < newNumber.size; ++j) {
                    tmpTab[j] = newNumber.number[j];
                }
                delete newNumber.number;
                newNumber.size++;
                newNumber.number = new int[newNumber.size - 1];
                for (int j = 0; j < newNumber.size - 1; ++j) {
                    newNumber.number[j] = tmpTab[j];
                }
                delete tmpTab;
                newNumber.number[newNumber.size - 1] = tmpSum;
            }
        }

        //reverse return table
        tmpTab = new int[newNumber.size];
        for (int i = 0; i < newNumber.size; ++i) {
            tmpTab[i] = newNumber.number[newNumber.size - 1 - i];
        }
        for (int i = 0; i < newNumber.size; ++i) {
            newNumber.number[i] = tmpTab[i];
        }
        delete tmpTab;
        return newNumber;
    }
};

//works fine
istream& operator>>(istream& s1, BigNumbers& l1) {
    int* tmpTab = NULL;
    int tmpInt = 0;
    int tmpSize = 0;
    while ((tmpInt = getch()) != 10) {
        tmpInt -= 48; //converting from ASCII code to actual number
        tmpTab = new int[l1.size];
        for (int i = 0; i < l1.size; ++i) {
            tmpTab[i] = l1.number[i];
        }
        tmpSize = l1.size;
        delete l1.number;
        l1.number = new int[tmpSize + 1];
        for (int i = 0; i < l1.size; ++i) {
            l1.number[i] = tmpTab[i];
        }
        l1.number[tmpSize] = tmpInt;
        l1.size++;
        delete tmpTab;
    }
    return s1;
}

//works fine
ostream& operator<<(ostream& s1, BigNumbers &l1) {
    for (int i = 0; i < l1.size; ++i) {
        s1 << l1.number[i];
    }
    return s1;
}

class BigNumbersChild : public BigNumbers {
public:
    //BigNumbersChild();
    //~BigNumbersChild();
    bool operator==(BigNumbers& a) {
        if (this->size == a.size) {
            for (int i = 0; i < this->size; ++i) {
                if (this->number[i] != a.number[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    BigNumbersChild& operator=(const BigNumbers& a) {
        if (this == &a) {
            return *this;
        }
        delete []this->number;
        this->number = new int[a.size];
        this->size = a.size;
        for (int i = 0; i < this->size; ++i) {
            this->number[i] = a.number[i];
        }
        return *this;
    }

    bool operator!=(BigNumbers& a) {
        return !(*this == a);
    }

    bool operator>(BigNumbers& a) {
        if (this->size > a.size) {
            return true;
        }
        else if (this->size == a.size) {
            for (int i = 0; i < this->size; ++i) {
                if (this->number[i] > a.number[i]) {
                    return true;
                }
                else if (this->number[i] < a.number[i]) {
                    return false;
                }
            }
            //then they are equal
            return false;
        }
        return false;
    }

    bool operator<(BigNumbers& a) {
        return !(*this > a);
    }

    bool operator>=(BigNumbers& a) {
        return (*this > a || *this == a);
    }

    bool operator<=(BigNumbers& a) {
        return (*this < a || *this == a);
    }
};

int main() {
    BigNumbers a, b;
    BigNumbersChild c, d;
    cin >> a;
    cin >> b;
    cout << a << endl;
    cout << b << endl;
    c = (a + b);
    d = b;
    cout << c << endl << d << endl;
    return 0;
}
