

#include <iostream>
#include <cmath>
#include <cstring>
#include <bitset>
#include <iomanip>

using namespace std;

char* array_init(string str)
{
    size_t length = str.length();
    char* s_in = new char[length] {};

    for (int i = 0; i < length; i++)
    {
        s_in[i] = str[i];
    }

    for (int i = 0; i < length; i++)
    {
        cout << s_in[i];
    }
    cout << endl << "Initial length: " << 8 * str.length() << endl;
    return s_in;
}


void print_string_as_binary(char* str, size_t length) 
{
    cout << "Initial binary array:" << endl;
    for (int i = 0; i < length; i++) 
    {
        cout << bitset<8>(str[i]) << ' ';
    }
    cout << endl << endl;
}

void print_string_as_hexadimal(char* str, size_t length)
{
    cout << "Initial hexadimal array:" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << hex << uppercase << bitset<8>(str[i]).to_ulong() << ' ';
    }
    cout << endl << endl;
}

void print_as_binary(bitset<128> bit_array, size_t byte_count)
{
    cout << "Multiplyed binary array:" << endl;
    for (size_t i = 0; i < byte_count; i++)
    {
        bitset<8> bit_mask;
        for (size_t j = 0; j < 8; j++)
        {
            bit_mask[7 - j] = bit_array[(i * 8) + j];
        }
        cout << bit_mask << ' ';
    }
    cout << endl << endl;
}

void print_as_hexadimal(bitset<128> bit_array, size_t byte_count)
{
    cout << "Multiplyed hexadimal array:" << endl;
    for (size_t i = 0; i < byte_count; i++)
    {
        bitset<8> bit_mask;
        for (size_t j = 0; j < 8; j++)
        {
            bit_mask[7 - j] = bit_array[(i * 8) + j];
        }
        cout << hex << uppercase << bit_mask.to_ulong() << ' ';
    }
    cout << endl << endl;
}

bool test_bit(const char value, const char bit_number)
{
    return value & (1 << bit_number);
}

void multiply_bits(string str, double multiply_coefficient)
{
    size_t l = str.length();
    char* s_in = array_init(str); 
    
    
    double x = multiply_coefficient;
    double x_integer, length_integer;
    double x_fractional = modf(x, &x_integer);
    double length_fractional = modf(l * 8 * x, &length_integer);

    size_t length_new = 0;

    while (length_integer > length_new)
    {
        length_new += 8;
    }

    cout << "New length: " << length_new << endl << endl;

    bitset<128> bit_array_out; 
    

    double fractional_count = 0;
    bool flag = true;
    
    size_t k = 0;

    for (size_t i = 0; i < l; i++)
    {
        
        for (size_t j = 0; j < 8; j++)
        {
            size_t bit_count = (size_t)round(x_integer);
            fractional_count += x_fractional;

            if (fractional_count >= 1)
            {
                bit_count++;
                flag = false;
                fractional_count--;
            }
            if ((((i + 1) * (j + 1) - 1) == length_new - 1) && (fractional_count >= 0.5) && flag)
            {
                bit_count++;
            }

            bool bit_value = test_bit(s_in[i], 7 - j);

            if (bit_value)
            {
                for (size_t n = 0; n < bit_count; n++)
                {
                    bit_array_out[n + k] = true;
                }
            }
            
            k += bit_count;
            flag = true;
        }
        
    }

    size_t length_char;

    if (x_fractional > 0)
    {
        length_char = (size_t)round(length_new / 8) + 1;
    }
    else
    {
        length_char = (size_t)round(length_new / 8);
    }


    print_string_as_binary(s_in, l);
    print_string_as_hexadimal(s_in, l);
    cout << "Bit array" << endl << bit_array_out << endl << endl;
    print_as_binary(bit_array_out, length_char);
    print_as_hexadimal(bit_array_out, length_char);

    delete[] s_in; 
    
}

int main()
{
    string str = "abc";
    multiply_bits(str, 2.0);
    cout << endl; 
}

