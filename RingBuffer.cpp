

#include <iostream>

using namespace std;

class CircularBuffer
{
    private:
        uint8_t* buffer;
        int head;
        int tail;
        bool full;

    public:

        void buf_init(int size)
        {
          head = tail = 0;
          full = 0;
          buffer = new uint8_t[size];
        }

        void buf_reset()
        {
            head = tail = 0;
            full = 0;
        }

        void buf_write(uint8_t value) 
        {
            buffer[head] = value;

            if (full)
            {
                tail = (tail + 1) % count;
            }

            head = (head + 1) % count;

            full = (head == tail);
        }

        uint8_t buf_read() 
        {
            if (isEmpty())
            {
                cout << "Error" << endl;
                return 0;
            }
            uint8_t value = buffer[tail];
            full = 0;
            tail = (tail + 1) % count;

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

        int buf_total_size()
        {
            return count;
        }

        int buf_current_size()
        {
            int size = count;

            if (!full)
            {
                if (head >= tail)
                {
                    size = head - tail;
                }
                else
                {
                    size = count + head - tail;
                }
            }

            return size;
        }
};


int main()
{
    
}


