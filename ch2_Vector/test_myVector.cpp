#include <iostream>
#include "myVector.h"

int main()
{
    myVector<int> v1(10, 1);
    myVector<int> v2;

    cout << v1 << endl;
    cout << v2 << endl;
    v2 = v1;
    cout << v2 << endl;

    myVector<int> v3(v2);
    cout << v3 << endl;

    system("pause");

    return 0;
}