#include <string>

#include "bitmap.h"
#include "hash-fun.h"

using namespace std;

extern size_t BKDRHash(const char *str);
extern size_t SDBMHash(const char *str);
extern size_t RSHash(const char *str);
extern size_t APHash(const char *str);
extern size_t JSHash(const char *str);

template<class T>
struct hash_fun1
{
    size_t operator()(const T& key)
    {
        return BKDRHash(key.c_str());
    }
};

template<class T>
struct hash_fun2
{
    size_t operator()(const T& key)
    {
        return SDBMHash(key.c_str());
    }
};

template<class T>
struct hash_fun3
{
    size_t operator()(const T& key)
    {
        return RSHash(key.c_str());
    }
};

template<class T>
struct hash_fun4
{
    size_t operator()(const T& key)
    {
        return APHash(key.c_str());
    }
};

template<class T>
struct hash_fun5
{
    size_t operator()(const T& key)
    {
        return JSHash(key.c_str());
    }
};

template<class T = string,
         class func1 = hash_fun1<T>,
         class func2 = hash_fun2<T>,
         class func3 = hash_fun3<T>,
         class func4 = hash_fun4<T>,
         class func5 = hash_fun5<T>>
class BloomFilter
{
public:
    BloomFilter(size_t size)
    {
        m_capacity = m_get_next_prime(size);
        m_bitmap.resize_map(size);
    }

public:
    void set_key(const T& key)
    {
        size_t index1 = func1()(key);
        size_t index2 = func2()(key);
        size_t index3 = func3()(key);
        size_t index4 = func4()(key);
        size_t index5 = func5()(key);

        m_bitmap.set_map(index1 % m_capacity);
        m_bitmap.set_map(index2 % m_capacity);
        m_bitmap.set_map(index3 % m_capacity);
        m_bitmap.set_map(index4 % m_capacity);
        m_bitmap.set_map(index5 % m_capacity);
    }

    bool is_key_exist(const T& key)
    {
        size_t index1 = func1()(key);
        if(!m_bitmap.check(index1 % m_capacity))
        {
            return false;
        }

        size_t index2 = func2()(key);
        if(!m_bitmap.check(index2 % m_capacity))
        {
            return false;
        }

        size_t index3 = func3()(key);
        if(!m_bitmap.check(index3 % m_capacity))
        {
            return false;
        }

        size_t index4 = func4()(key);
        if(!m_bitmap.check(index4 % m_capacity))
        {
            return false;
        }

        size_t index5 = func5()(key);
        if(!m_bitmap.check(index5 % m_capacity))
        {
            return false;
        }

        return true;
    }

protected:
    unsigned long m_get_next_prime(unsigned long num)
    {
        const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		size_t pos = 0;
		num = _PrimeList[0];
		while (pos < _PrimeSize)
		{
			if (_PrimeList[pos]>=num)
            {
                num = _PrimeList[pos];
                break;
            }
            else
                pos++;
		}
		return num;
    }
private:

    BitMap m_bitmap;
    size_t m_capacity;
};
