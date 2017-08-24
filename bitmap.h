#ifndef BITMAP_H_
#define BITMAP_H_

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
class BitMap
{
public:
    BitMap():m_size(0)
    {
        m_array.clear();
    }

    BitMap(size_t len):m_size(0)
    {
        m_array.resize((len>>5) + 1);
    }

public:
    void resize_map(size_t num)
    {
        m_array.resize((num >> 5)+1);
    }

    void set_map(size_t num)
    {
        size_t index = num>>5;
        size_t n = num % 32;

        if(m_array[index] & (1 << (31 - n)))
        {
            //cout<<index<<":Have data already!"<<endl;
            return;
        }
        else
        {
            m_array[index] |= (1<<n);
            ++m_size;
            return;
        }
    }

    bool reset_map(size_t num)
    {
        size_t index = num >> 5;
        size_t n = num % 32;

        if(m_array[index] & (1 << (31-n)))
        {
            m_array[index] &= (~(1 << (31-n)));
            --m_size;
            return true;
        }
        else
            return false;
    }

    bool check(size_t num)
    {
        size_t index = num >> 5;
        size_t n = num % 32;
        return (m_array[index] & (1 << n));
    }

private:
    vector<size_t> m_array;
    size_t m_size;
};



#endif // BITMAP_H_
