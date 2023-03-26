// Aditya Rajesh Bawangade
// Roll Number 2103111

// Including the neccessary libraries
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <math.h>

// Using std namespace for convenience

using namespace std;

// Using templates and the parameter b
template <int b>
class base_b
{
private:
    // Defining the private members
    vector<int> vec;

public:
    // Defining the default and parameterised constructors
    base_b()
    {
        vec = vector<int>();
    }
    base_b(int val)
    {
        if (val == 0)
        {
            vec.push_back(0);
        }
        while (val > 0)
        {
            vec.push_back(val % b);
            val /= b;
        }
    }

    // Defining the print function
    void print()
    {
        int j = vec.size() - 1;
        // Poppinf the preceding zeroes
        while (j >= 1)
        {
            if (vec[j] != 0)
            {
                break;
            }
            vec.pop_back();
            j--;
        }
        for (int i = vec.size() - 1; i >= 0; i--)
        {
            cout << vec[i] << " ";
        }
        cout << endl;
        return;
    }

    base_b operator+(base_b const &smaller)
    {
        // Using the high school method
        base_b ans;
        int carry = 0;
        int i = 0;
        int j = 0;
        // Looping until we arrive at the left most place and the carry is exhausted i.e. becomes zero
        while (i < vec.size() || j < vec.size() || carry > 0)
        {
            int sum = carry;
            if (i < vec.size())
            {
                sum += vec[i];
            }
            if (j < smaller.vec.size())
            {
                sum += smaller.vec[i];
            }
            carry = sum / b;
            ans.vec.push_back(sum % b);
            i++;
            j++;
        }
        // Returning a base_b object as an answer
        return ans;
    }
    base_b operator-(base_b const &smaller)
    {
        // Using this pointer to copy the contents to a temporary object of base_b Class for ease
        base_b ans, larger = (*this);
        int borrow = 0;

        std::vector<int> temp = smaller.vec;
        // Checking for the larger number and swapping if neccessary
        if (vec.size() < temp.size())
        {
            swap(larger.vec, temp);
        }
        // Looping until we reach the end of the bigger number
        for (int i = 0; i < larger.vec.size(); i++)
        {
            int diff = larger.vec[i] - borrow;
            if (i < temp.size())
            {
                diff -= temp[i];
            }
            if (diff < 0)
            {
                borrow = 1;
                // Incrementing the difference
                diff += b;
            }
            else
            {
                borrow = 0;
            }
            // Pushing the diff mod b so as to maintain the base to b
            ans.vec.push_back(diff % b);
        }

        // Popping the preceding zeroes
        while (ans.vec.size() > 1 && ans.vec.back() == 0)
        {
            ans.vec.pop_back();
        }

        return ans;
    }

    base_b operator*(base_b const &smaller)
    {
        // Defining an object for use
        base_b ans;
        int carry = 0;
        // Resizing a new vector to accomodate the size of the output answer
        vector<int> result(vec.size() + smaller.vec.size() + 1, 0);
        for (int i = 0; i < vec.size(); i++)
        {
            for (int j = 0; j < smaller.vec.size(); j++)
            { // Multiplying and storing the number in base b format until the end
                result[i + j] += vec[i] * smaller.vec[j];
                result[i + j + 1] += result[i + j] / b;
                result[i + j] %= b;
            }
        }
        // Resizing the vector of the return object
        ans.vec.resize(result.size());
        copy(result.begin(), result.end(), ans.vec.begin());
        // Popping the unneccessaru zeroes
        while (ans.vec.size() > 1 && ans.vec.back() == 0)
        {
            ans.vec.pop_back();
        }
        return ans;
    }
    int operator<(base_b const &other)
    {
        // Overloading the less than operator to use in division
        int a = 0, k = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            a = a + pow(b, i) * vec[i];
        }
        for (int i = 0; i < other.vec.size(); i++)
        {
            k = k + pow(b, i) * other.vec[i];
        }
        if (a < k)
        {
            return 1;
        }
        return 2;
    }
    base_b leftshift()
    { // Using a left shift operation for division
        base_b temp;
        temp.vec.assign(vec.begin(), vec.end());
        if (vec.size() == 0)
        {
            return temp;
        }

        temp.vec.insert(temp.vec.begin(), 0);

        return temp;
    }
    base_b rightshift()
    { // Using a rightshifting Operation for division
        base_b temp;
        temp.vec.assign(vec.begin(), vec.end());
        temp.vec.erase(temp.vec.begin());
        if (temp.vec.size() == 0)
        {
            temp.vec.push_back(0);
            return temp;
        }

        return temp;
    }
    // Creating a divide function of type base b which returns a pair
    pair<base_b, base_b> divide(base_b num2)
    {
        // creating a pair of base_b objects and using the division algorithm
        pair<base_b, base_b> p;
        base_b zero(0);
        base_b one(1);
        // Checing if numerator is smaller
        if (*this < num2 == 1)
        {
            p.first = zero;
            p.second = *this;

            return p;
        }
        int tp = vec[0];
        // Storing the element to be popped
        base_b right_ind(tp);
        // Rightshifting the numerator and calling the function recursively
        p = (this->rightshift()).divide(num2);

        // Leftshifting and saving
        p.first = p.first.leftshift();
        p.second = p.second.leftshift();

        // Adding the popped element during rightshift
        p.second = p.second + right_ind;

        // Reducing the remainder and incrementing the remainder if neccessary
        while (p.second < num2 == 2)
        {
            p.second = p.second - num2;
            p.first = p.first + *(new base_b(1));
        }
        return p;
    }
    base_b operator/(base_b smaller)
    {
        // Overloading the division operator using the divide function
        pair<base_b, base_b> p = this->divide(smaller);

        base_b ans;
        ans = p.first;
        return ans;
    }

    // Defining an increment function for base b to overload ++
    base_b incrementBaseb(base_b &num)
    {
        base_b one(1);
        num = num + one;
        return num;
    }
    base_b operator++()
    {
        base_b ans;
        // Overloading ++i
        ans.vec = incrementBaseb(vec);
        return ans;
    }
    base_b operator++(int)
    {
        // Overloading i++
        base_b ans = *this;
        vec = incrementBaseb(vec);
        return ans;
    }
};
// Main function
int main()
{
    int x, y, z;
    cout << "Enter the three variables namely x, y, z: ";
    cin >> x >> y >> z;

    base_b<37> x1(x), y1(y), z1(z);
    base_b<37> ans1 = (x1 + y1) * z1;

    ans1.print();
    base_b<37> ans2 = (x1 / y1);

    ans2.print();
    base_b<37> ans3 = x++;
    ans3.print();
    base_b<37> ans4 = ++x;
    ans4.print();

    return 0;
}
