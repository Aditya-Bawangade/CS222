// Aditya Rajesh Bawangade
// 2103111 CSE
// Q1 Q2 Q3 Assignment 3
#include <vector>    //for using vectors
#include <algorithm> //for using the reverse function to reverse the vector
#include <iostream>
using namespace std; // using namespace std for convinience

// Creating a function to return the conversion of an integer to the given base argument
vector<int> BaseConversion(int base, int num)
{
    vector<int> ans; // using a vector of integers to return the answer
    while (num >= 1)
    { // Using the standard method via a while loop to get the representation of the given number in base b
        ans.push_back(num % base);
        num /= base;
    }
    reverse(ans.begin(), ans.end()); // Using the reverse function as we have included algorithm header file to reverse the vector
    return ans;
}

// Defining a function to add two base b numbers
// The arguments are base, bigger number and smaller number respectively

vector<int> SumBaseB(int basee, vector<int> num1B, vector<int> num2S)
{
    int s1 = num1B.size();     // getting the sizes of the two vectors of numbers in the representation of base b format
    int s2 = num2S.size();
    if(s1<s2){
        return {-1};
    }
    int minim = min(s1, s2);  // Storing the minimum value of the sizes
    int diff = abs(s1 - s2); // Storing the difference
    vector<int> copyy;       // Creating a new vector copyy to take care when the sizes of the two numbers are different
                            // This variable stores the value of the smaller number and appends zeros as prefix
    for (int i = 0; i < diff; i++)
    { // Looping for setting prefix zeroes until required
        copyy.push_back(0);
    }
    for (int i = 0; i < minim; i++)
    { // Pushing the values from the smaller vector
        
            copyy.push_back(num2S[i]);
        
    }
    vector<int> ans; // Creating a vector to store our final answer
    int carry = 0;
    for (int i = s1 - 1; i >= 0; i--)
    { // Looping from the end to the beginning and performing the addition of every digit in base b format
        if ((carry + num1B[i] + copyy[i]) >= basee)
        {
            int a = (carry + num1B[i] + copyy[i]) % basee;
            ans.push_back(a);
            carry = 1;
        }
        else
        {
            int a = carry + num1B[i] + copyy[i];
            ans.push_back(a);
            carry = 0;
        }
    }
    if (carry != 0) {
        //Carry overflow
        ans.push_back(carry);
    }
    reverse(ans.begin(), ans.end()); // Reversing the final answer;
    return ans;
}
int main()
{   int b1,n1,n2;
    cout<<"Enter the  base: "<<endl;
    cin>>b1;
    cout<<"Enter the number: "<<endl;
    cin>>n1;
    vector<int> baseconv = BaseConversion(b1,n1);
    cout<<"The representation of "<<n1<<" in base "<<b1<<" is:";
    for(int i = 0 ; i < baseconv.size() ; i++){
        cout<<baseconv[i]<<" ";
    }
    cout<<endl;
    cout<<"Enter the second number"<<endl;
    cin>>n2;
    vector<int> baseconv2 = BaseConversion(b1,n2);
    cout<<"The representation of "<<n2<<" in base "<<b1<<" is:";
    for(int i = 0 ; i < baseconv2.size() ; i++){
        cout<<baseconv2[i]<<" ";
    }
    cout<<endl;
    vector<int> ans = SumBaseB(15, baseconv, baseconv2);
    cout<<"The sum of the two numbers "<<n1<<" & "<<n2<<" in base "<<b1<<" is as follows: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i]<<" ";
    }
}