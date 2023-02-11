﻿
#include <iostream>
#include <iomanip>
#include <stdlib.h>
 
using namespace std;

uint8_t** array_gen(int sz_x, int sz_y) // array initialization
{
    uint8_t** array = new uint8_t * [sz_y];
    for (int i = 0; i < sz_y; i++) 
    {
        array[i] = new uint8_t[sz_x];
    }
    return array;
}


int random(int min_range, int max_range) // random values from min_range to max_range
{
    return rand() % (max_range - min_range + 1) + min_range;
}


uint8_t** window(uint8_t** array, int i, int j, int k_filter) // window (k_filter * k_filter) from original array
{
    uint8_t** array_sup = array_gen(k_filter, k_filter);
    for (int k1 = 0; k1 < k_filter; k1++)
    {
        for (int k2 = 0; k2 < k_filter; k2++)
        {
            array_sup[k1][k2] = array[i][j];
            j++;
        }
        j = j - k_filter;
        i++;
    }
    return array_sup;
}


uint8_t** production(uint8_t** array_1, float** array_2, int sz_x, int sz_y) // element-wise array multiplication
{
    uint8_t** array_pr = array_gen(sz_x, sz_y);
    for (int m = 0; m < sz_y; m++)
    {
        for (int n = 0; n < sz_x; n++)
        {
            array_pr[m][n] = (uint8_t)round(array_1[m][n] * array_2[m][n]);
        }
    }
    return array_pr;
}


uint8_t summary(uint8_t** array, int sz_x, int sz_y) // sum of all elements in array
{
    uint8_t sum = 0;
    for (int m = 0; m < sz_y; m++)
    {
        for (int n = 0; n < sz_x; n++)
        {
            sum = sum + array[m][n];
        }
    }
    return sum;
}


void filter2d(uint8_t** array, int sz_x, int sz_y, int k_filter) // filtering function
{
    float **kernel = new float* [k_filter];
    for (int i = 0; i < k_filter; i++)
    {
        kernel[i] = new float[k_filter];
    }

    for (int i = 0; i < k_filter; i++)
    {
        for (int j = 0; j < k_filter; j++)
        {
            kernel[i][j] = 1.0/(k_filter * k_filter);
        }
    }

    uint8_t** array_filtered = array_gen(sz_x, sz_y);
    for (int i = 0; i < sz_y; i++)
    {
        for (int j = 0; j < sz_x; j++)
        {
            array_filtered[i][j] = array[i][j];
        }
    }

    for (int i = 0; i < sz_y - k_filter + 1; i++)
    {
        for (int j = 0; j < sz_x - k_filter + 1; j++)
        {
            array_filtered[i + (k_filter - 1) / 2][j + (k_filter - 1) / 2] = summary(production(window(array, i, j, k_filter), kernel, k_filter, k_filter), k_filter, k_filter);
        }
    }

    cout << "Original array" << endl;
    for (int i = 0; i < sz_y; i++)
    {
        for (int j = 0; j < sz_x; j++)
        {
            cout << setw(4) << (int)array[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Kernel" << endl;
    for (int i = 0; i < k_filter; i++)
    {
        for (int j = 0; j < k_filter; j++)
        {
            cout << fixed << setprecision(2) << setw(6) << (float)kernel[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Filtered array" << endl;
    for (int i = 0; i < sz_y; i++) 
    {
        for (int j = 0; j < sz_x; j++) 
        {
            cout << setw(4) << (int)array_filtered[i][j];
        }
        cout << endl;
    }
    cout << endl; 
}


int main()
{
    int k_filter = 3; // 3x3, 5x5 and etc
    int sz_x = 10; // array sizes
    int sz_y = 10;
    int range = 255; // range from 0 to 255

    uint8_t** array = array_gen(sz_x, sz_y); 
    //srand(time(NULL)); // random starting point for values 

    for (int i = 0; i < sz_x; i++)
    {
        for (int j = 0; j < sz_y; j++)
        {
            array[i][j] = random(0, range);
        }
    }

    filter2d(array, sz_x, sz_y, k_filter); 

}