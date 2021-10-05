/*
 * @Author: Maize
 * @Date: 2021-09-26 23:10:16
 * @LastEditTime: 2021-10-05 22:59:02
 * @LastEditors: Please set LastEditors
 * @Description: VE280 2021 Fall Project 1
 * @FilePath: \Project\p1\p1.cpp
 */

#include <fstream>
#include <string>
#include <cmath>
using namespace std;

// Judge whether the input number is Triangle number
bool isTriangle(int number);

// Judge whether the input number is Power number
bool isPower(int number);

// Judge whether the input number is Sum of consecutive squares
bool isSquareSum(int number);

// Judge whether the input number is Abundant number
bool isAbundant(int number);

// Judge the input number and type then output the final answer
string judge(int number, int type);

int main()
{
    ofstream out("output.txt", ios::out);
    for (int i = 9730000; i < 9740000; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            string answer = judge(i, j);
            out << i << " " << j << " " << answer << endl;
        }
    }
    out.close();
    return 0;
}

bool isTriangle(int number)
{
    int temp = sqrt(2 * number);
    for (int i = 0; i <= temp; i++)
    {
        if (number == 0.5 * temp * (temp + 1))
        {
            return true;
        }
    }
    return false;
}

bool isPower(int number)
{
    if (number == 1)
    {
        return true;
    }
    for (int i = 0; i <= sqrt(number); i++)
    {
        for (int j = 2; j <= log2(number); j++)
        {
            if (number == pow((double)i, j))
            {
                return true;
            }
        }
    }
    return false;
}

bool isSquareSum(int number)
{
    int sum = 0;
    for (int i = 0; i <= sqrt(number); i++)
    {
        for (int j = 0; (i + j) <= sqrt(number); j++)
        {
            sum = sum + (i + j) * (i + j);
            if (sum == number)
            {
                return true;
            }
        }
        sum = 0;
    }
    return false;
}

bool isAbundant(int number)
{
    int divisor[500000] = {0};
    int sum = 0;
    int fig = 0;
    // Collect divisors larger than 1
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            divisor[fig++] = i;
            if (i != number / i)
                divisor[fig++] = number / i;
        }
    }
    for (int i = 0; i < fig; i++)
    {
        sum = sum + divisor[i];
    }
    // Adding divisor 1 to sum
    if ((sum + 1) > number)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string judge(int number, int type)
{
    bool answer;
    string output;
    switch (type)
    {
    case 1:
        answer = isTriangle(number);
        break;
    case 2:
        answer = isPower(number);
        break;
    case 3:
        answer = isSquareSum(number);
        break;
    case 4:
        answer = isAbundant(number);
        break;
    default:
        //  cout << "error" << endl;
        return "error";
    }
    if (answer == true)
    {
        output = "Pass";
    }
    else
    {
        output = "Fail";
    }
    return output;
}