// Author Name: Aditya Rajesh Bawangade

// Roll Number: 2103111

// Including the required header files
#include <iostream>
// the header file utility is to be able to use pairs
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
    pair<int,pair<int,int>> extendedEuclid(int a, int b){
        
        if(b==0){
            pair<int,pair<int,int>> ans;
            ans.first = a;
            ans.second.first = 1;
            ans.second.second = 0;
            return ans;
        }
        pair<int,pair<int,int>> ans = extendedEuclid(b,divide(a,b).second);
        pair<int,pair<int,int>> finans;
        finans.first = ans.first;
        finans.second.first = ans.second.second;
        finans.second.second = (ans.second.first)-(divide(a,b).first)*(ans.second.second);
        return finans;
        
    }
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
    noModN findInverse(noModN a){
        if(extendedEuclid(a.num,N).first == 1){
            int ans = extendedEuclid(a.num,N).second.first;
            noModN returnVar(ans);
            return returnVar;
        }
        throw runtime_error("This is a runtime error as you tried dividing by zero 🙄🙄🙄");
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
    noModN operator/(noModN const &num2){
        noModN denom = findInverse(num2);
        return denom*(*this);
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

   
    noModN<60> a1(6);
    noModN<60> b1(31);
    
    noModN<60> s1 = a1/b1;
    
    s1.printModValue();
    
}
