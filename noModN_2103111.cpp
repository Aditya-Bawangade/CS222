// Author Name: Aditya Rajesh Bawangade

// Roll Number: 2103111

// Including the required header files
#include <iostream>
#include <utility>

// Using the std namespace for convenience
using namespace std;

// Declaring a division function which returns a pair
pair<int, int> dividenumbers(int a, int b)
{
    pair<int, int> ans;
    if (a < b)
    {
        ans.first = 0;
        ans.second = a;
        return ans;
    }

    ans = dividenumbers(a >> 1, b);
    ans.first = ans.first << 1;
    ans.second = ans.second << 1;
    if (a & 1 == 1)
    {
        ans.second = ans.second + 1;
    }
    if (ans.second >= b)
    {
        ans.first = ans.first + 1;
        ans.second = ans.second - b;
    }
    return ans;
}

// We now create a new divide function using the previously defined functions to handle negative inputs
pair<int, int> divide(int a, int b)
{
    if (a < 0 && b < 0)
    {
        a = -a;
        b = -b;
        return dividenumbers(a, b);
    }
    // We adjust the division such that, while taking a modulo b, when a is negative and b is
    // positive, we get the correct modulo value
    else if (a < 0 && b > 0)
    {
        a = -a;
        pair<int, int> ans = dividenumbers(a, b);
        ans.first = -ans.first;
        ans.second = b - ans.second;
        return ans;
    }
    else if (a > 0 && b < 0)
    {
        b = -b;
        pair<int, int> ans = dividenumbers(a, b);
        ans.first = -ans.first;
        return ans;
    }
    else
    {
        return dividenumbers(a, b);
    }
    return dividenumbers(a, b);
}
// We now define our class template
template <int N>
class noModN
{
    // Declaring the private data members
private:
    int num;

public:
    // Declaring the public functions and the default as well as the parameterised constructor
    noModN() {}
    noModN(int val)
    {
        pair<int, int> ans = divide(val, N);
        num = ans.second;
    }
    // Declaring a function to print the value
    void printModValue()
    {
        cout << num << endl;
        return;
    }
    // Overloading the + operator
    noModN operator+(noModN const &num2)
    {
        int temp = num + num2.num;
        noModN ans(temp);
        return ans;
    }
    // Overloading the - operator for a-b
    noModN operator-(noModN const &num2)
    {
        int temp = num - num2.num;
        noModN ans(temp);
        return ans;
    }
    // Overloading the unary minus
    noModN operator-()
    {
        int temp = -num;
        noModN ans(temp);
        return ans;
    }
    // Overloading the * operator
    noModN operator*(noModN const &num2)
    {
        int temp = num2.num * num;
        noModN ans(temp);
        return ans;
    }
    // Overloading the ++ operator as postfix
    noModN operator++(int)
    {
        noModN ans(*this);
        pair<int, int> result = divide(num + 1, N);
        num = result.second;
        return ans;
    }
    // Overloading the ++ operator as prefix
    noModN operator++()
    {
        int val = num + 1;
        noModN ans(val);
        return ans;
    }
};
// Main body of the function
int main()
{
    int a, b, c;
    cout << "Enter the three numbers: " << endl;
    cin >> a >> b >> c;

    noModN<37> a1(a);
    noModN<37> b1(b);
    noModN<37> c1(c);
    noModN<37> s1 = (a1 + b1) * c1;
    cout << "The value of (" << a << " + " << b << ")*" << c << " in modulo with 37 is as follows: ";
    s1.printModValue();
    noModN<37> s2 = -a1;
    cout << "The value of -" << a << " in modulo with 37 is as follows: ";
    s2.printModValue();
    noModN<37> s3 = a1 - b1;
    cout << "The value of " << a << " - " << b << " in modulo with 37 is as follows: ";
    s3.printModValue();
    noModN<37> s4 = a1++;
    cout << "The value of " << a << "++ in modulo with 37 is as follows: ";
    s4.printModValue();
    noModN<37> s5 = ++a1;
    cout << "The value of ++" << a << " in modulo with 37 is as follows: ";
    s5.printModValue();
    return 0;
}
