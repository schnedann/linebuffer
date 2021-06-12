#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <ctime>
#include <sstream>



using namespace std;











/**
 *
 */
int main()
{
    uint16_t* data;
    cout << "Hello world!" << endl;
    data = new uint16_t[dVALUES];
    fillran(data,dVALUES);
    cout << "Unsorted:" << endl << List(data,dVALUES) << endl;
    Sort(data,dVALUES,Initgap(dVALUES));
    cout << "Sorted:" << endl << List(data,dVALUES) << endl;
    delete(data);
    return 0;
}
