/*
 * @Author: Maize
 * @Date: 2021-09-26 23:10:16
 * @LastEditTime: 2021-09-28 19:55:28
 * @LastEditors: Please set LastEditors
 * @Description: VE280 2021 Fall Project 1
 * @FilePath: \Project\p1\p1.cpp
 */

#include <iostream>
#include <string>
#include <cmath>
// #include <cstdlib>
// TODO: debug test

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
    int number, type;
    // Ensure the input number is within range
    while (number > 10000000 || number < 0 || ((type != 1) && (type != 2) && (type != 3) && (type != 4)))
    {
        cout << "Please enter the integer and the test choice: ";
        cin >> number >> type;
    }
    string answer = judge(number, type);
    cout << answer << endl;
    return 0;
}

bool isTriangle(int number)
{
    int temp = sqrt(2 * number);
    for (int i = 0; i < temp; i++)
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
    for (int i = 0; i <= sqrt(number); i++)
    {
        for (int j = 2; j <= sqrt(number); j++)
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
        // TODO : j最大值
        for (int j = 0; (i+j) <= sqrt(number); j++)
        {
            sum = sum + (i + j) ^ 2;
            if (sum == number)
            {
                return true;
            }
        }
    }
    return false;
}

bool isAbundant(int number)
{
    int divisor[500000] = {0};
    int sum = 0;
    int fig = 0;
    for (int i = 2; i ^ 2 <= number; i++)
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
    if (sum > number)
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
        cout << "error" << endl;
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