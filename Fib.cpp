#include <iostream>
#include <iomanip>
#include <cmath>

long Fib(int n);

int main()
{
    using namespace std;
    cout << "Please enter an positive integer: ";
    float n;
    cin >> n;
    while(abs(n-int(n)) > 1e-6||n < 1)//if it is not an positive integer
    {
        cout << "ERROR! What you entered is not legal, please enter an positive integer: ";
        cin >> n;
    }

    cout << "The first " << int(n) << " terms of the Fibonacci Sequence is:";
    cout.setf(ios::left);//output is flush left
    for (int i = 0; i < n; i++)
    {
        if ((i % 6) == 0) cout << endl;//6 numbers in a row
        int a = Fib(i);
        cout << setw(10) << a;//the maximum width of a number is 15
    }
    return 0;
}

long Fib(int n)
{
    if(n <= 2) return 1;
    else return (Fib(n - 1) + Fib(n - 2));
}

