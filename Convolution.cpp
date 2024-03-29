﻿
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

 
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


void array_del_int(uint8_t** array, int sz_y) // array deleting 
{
    for (int i = 0; i < sz_y; i++)
    {
        delete [] array[i] ;
    }
    delete[] array;
}


void array_output(uint8_t** array, int sz_x, int sz_y) // array output on console
{
    for (int i = 0; i < sz_y; i++)
    {
        for (int j = 0; j < sz_x; j++)
        {
            cout << setw(4) << (int)array[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


int random(int min_range, int max_range) // random values from min_range to max_range
{
    return rand() % (max_range - min_range + 1) + min_range;
}


void window(uint8_t** array_in, uint8_t** array_out, int i, int j, int k_filter) // window (k_filter * k_filter) from original array
{
    for (int k1 = 0; k1 < k_filter; k1++)
    {
        for (int k2 = 0; k2 < k_filter; k2++)
        {
            array_out[k1][k2] = array_in[i][j];
            j++;
        }
        j = j - k_filter;
        i++;
    }
}


void production(uint8_t** array_in, uint8_t** array_out, double** kernel, int sz_x, int sz_y) // element-wise array multiplication
{
    for (int m = 0; m < sz_y; m++)
    {
        for (int n = 0; n < sz_x; n++)
        {
            array_out[m][n] = (uint8_t)round(array_in[m][n] * kernel[m][n]);
        }
    }
}


double summary(uint8_t** array, int sz_x, int sz_y) // sum of all elements in array
{
    double sum = 0;
    for (int m = 0; m < sz_y; m++)
    {
        for (int n = 0; n < sz_x; n++)
        {
            sum = sum + array[m][n];
        }
    }
    return sum / (sz_x * sz_y);
}


void filter2d(uint8_t** array, int sz_x, int sz_y, int k_filter) // filtering function
{

    uint8_t** array_sup = array_gen(k_filter, k_filter);

    for (int i = 0; i < sz_y - k_filter + 1; i++)
    {
        for (int j = 0; j < sz_x - k_filter + 1; j++)
        {
            window(array, array_sup, i, j, k_filter);
            array[i + (k_filter - 1) / 2][j + (k_filter - 1) / 2] = (uint8_t)round(summary(array_sup, k_filter, k_filter));
        }
    }

    array_del_int(array_sup, k_filter);
}


int main()
{
    int k_filter = 3; // 3x3, 5x5 and etc
    int sz_x = 10; // array sizes
    int sz_y = 10;
    int range = 255; // range from 0 to 255

    uint8_t** array = array_gen(sz_x, sz_y); 
    //srand(time(NULL)); // random starting point for values 

    for (int i = 0; i < sz_y; i++)
    {
        for (int j = 0; j < sz_x; j++)
        {
            array[i][j] = random(0, range);
        }
    }

    cout << "Original array" << endl;
    array_output(array, sz_x, sz_y);

    filter2d(array, sz_x, sz_y, k_filter); 

    cout << "Filtered array" << endl;
    array_output(array, sz_x, sz_y);

    array_del_int(array, sz_y);

    _CrtDumpMemoryLeaks();
}
