#include <iostream>
#include<vector>

#include "bloomfilter.h"

using std::cout;
using std::endl;
using std::vector;

int main()
{
    int capacity;
    cout<<"Input the capacity:"<<endl;
    cin>>capacity;
    BloomFilter<> bfilter(capacity);
    int flag = 0;
    while(flag != 3)
    {
        cout<<"choose your operation:"<<"\n\t[1 is set, 2 is query, 3 is quit]"<<endl;
        cin>>flag;
        if(flag == 1)
        {
            cout<<"input the key you want to set:"<<endl;
            string str;
            cin>>str;
            bfilter.set_key(str.c_str());
            cout<<"set done"<<endl;
        }

        else if(flag == 2)
        {
            cout<<"input the key you want to query:"<<endl;
            string str;
            cin>>str;
            if(bfilter.is_key_exist(str.c_str()))
                cout<<str<<" have existed in the storage"<<endl;
            else
                cout<<str<<" not exist yet"<<endl;
        }
        else if(flag == 3)
            break;
        else
            cout<<"choose the right operation please"<<endl;
    }
    return 0;
}
