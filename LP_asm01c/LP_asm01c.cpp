#include <iostream>
#include <stdio.h>
#pragma comment(lib,"C:\\Workplace\\1University\\second_cource\\Prog_Languages\\Labs\\Prog_Langs_3sem\\Debug\\LP_asm01a.lib")
using namespace std;

extern "C" int _stdcall getmin(int*, int);
extern "C" int _stdcall getmax(int*, int);

int main()
{
    int arr[10] = { -10, 2, -3, -888, -10, -31, -39, -312, -111, -321 };
    int min = getmin(arr, 10);
    int max = getmax(arr, 10);
    cout << max - min;

    return 0;
}