#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int flag_prime = 0;
    cout << "Please enter an integer: ";
    float n;
    cin >> n;
    while((int)n != n)//if it is not an integer
    {
        cout << "ERROR! You entered a noninteger, please enter an integer: ";
        cin >> n;
    }

    if (n >= 2)//if n < 2, then no need to test and n is surely an integer
    {
        int n_int = int(n);//get the integer version to simplify coding
        int i, flag_dividable = 0;//check if there is any other divisor other than 1 and n itself
        for (i = 2; i <= sqrt(n_int); i++)//to test from 2 to sqrt(n) because of the symmetry of multiplying
        {
            if (n_int % i == 0) flag_dividable = 1;//if there is a divisor, set the flag
        }
        if (!flag_dividable) flag_prime = 1;//no other divisor, then it's a prime number and set the flag
    }

    cout << "The integer you entered is ";
    if(flag_prime)  cout << "a prime number.\n";
    else cout << "not a prime number.\n";
    return 0;
}
