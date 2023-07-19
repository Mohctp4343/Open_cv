

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class CircularBuffer
{
    private:
        uint8_t* buffer;
        size_t head;
        size_t tail;
        bool full;
        size_t k = 256;

    public:

        void buf_help()
        {
            cout << "Command list:" << endl
                << "help - show command list" << endl
                << "init - buffer initialization (256 elements)" << endl
                << "reset - buffer clear" << endl
                << "delete - buffer delete" << endl
                << "put - write a value into buffer" << endl
                << "get - read a value from buffer" << endl
                << "bufsize - total buffer size" << endl
                << "size - current buffer size" << endl 
                << "show - show current buffer" << endl
                << "stop - stop the progam" << endl << endl;
        }

        void buf_init(size_t size)
        {
          head = tail = 0;
          full = 0;
          buffer = new uint8_t[size];
          for (int i = 0; i < size; i++)
          {
              buffer[i] = 0;
          }
        }

        void buf_reset()
        {
            head = tail = 0;
            full = 0;
        }

        void buf_delete()
        {
            delete[] buffer;
        }

        void buf_write(uint8_t value) 
        {
            buffer[head] = value;

            if (isFull())
            {
                tail = (tail + 1) % k;
            }

            head = (head + 1) % k;

            full = (head == tail);
        }

        uint8_t buf_read() 
        {
            if (isEmpty())
            {
                return 0;
            }
            uint8_t value = buffer[tail];
            full = 0;
            tail = (tail + 1) % k;

            return value;
        }

        bool isEmpty()
        {
            return (!full && (head == tail));
        }

        bool isFull()
        {
            return full;
        }

        size_t buf_total_size()
        {
            return k;
        }

        size_t buf_current_size()
        {
            size_t size = k;

            if (!full)
            {
                if (head >= tail)
                {
                    size = head - tail;
                }
                else
                {
                    size = k + head - tail;
                }
            }

            return size;
        }
        void buf_show()
        {

        }
};


int main()
{
    CircularBuffer cbuf;
    cbuf.buf_help();

    string operations[10] = { "help", "init", "reset", "delete", "put", "get", "bufsize", "size", "show", "stop" };
    string str;
    int value;
    uint8_t read_value;
    int flag = 0;

    do
    {
        cout << endl << "Enter the operation:" << endl;
        cin >> str;

        if (str == operations[0])
        {
            cbuf.buf_help();
        }
        if (str == operations[1])
        {
            cbuf.buf_init(256);
            cout << "Buffer was initialized" << endl;
        }
        if (str == operations[2])
        {
            cbuf.buf_reset();
            cout << "Buffer was cleared" << endl;
        }
        if (str == operations[3])
        {
            cbuf.buf_delete();
            cout << "Buffer was deleted" << endl;
        }
        if (str == operations[4])
        {
            value = 0;
            cout << "Enter the value:" << endl;
            cin >> value;
            cbuf.buf_write(value);
            //cbuf.buf_write(reinterpret_cast<uint8_t>(&value));
        }
        if (str == operations[5])
        {
            read_value = cbuf.buf_read();
            if (0 == read_value)
            {
                cout << "Reading error - buffer is empty" << endl;
            }
            else
            {
                cout << "The value is - " << read_value << endl;
            }
        }
        if (str == operations[6])
        {
            cout << "Total buffer - " << cbuf.buf_total_size() << " elements" << endl;
        }
        if (str == operations[7])
        {
            cout << "Current buffer size - " << cbuf.buf_current_size() << "/256 elements" << endl;
        }
        if (str == operations[8])
        {
            
        } 
        if (str == operations[9])
        {
            flag = 1;
        }
        if (!(str == operations[0]) && !(str == operations[1]) && !(str == operations[2]) && !(str == operations[3]) && !(str == operations[4]) &&
            !(str == operations[5]) && !(str == operations[6]) && !(str == operations[7]) && !(str == operations[8]) && !(str == operations[9]))
        {
            cout << "Command was written incorrectly!" << endl << endl;
        }
          
    } while (0 == flag);

    return 0;
}


