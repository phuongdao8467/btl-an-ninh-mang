#include <iostream>
#include <NTL/ZZ.h>
#include "Coded.h"
#include <chrono>
#include <ctime> 

using namespace NTL;
using namespace std;

int main(){   
    Coded test;
    ZZ mes;
    long l;
    char exit = 'n';
    while(true){
        cout << endl << "nhap mes: ";
        cin >> mes;
        test.setMes(mes);
        cout << "nhap so luong bit: ";
        cin >> l;
        test.setL(l);

        auto start = chrono::system_clock::now();

        cout << endl << "ma hoa: " << test.encoded() << endl << endl;
        cout << "giai ma: " << test.decode() << endl << endl;

        auto end = chrono::system_clock::now();
        chrono::duration<double> duration_seconds = end - start;
        cout << "Thoi gian ma hoa: " << duration_seconds.count() << "s" << endl << endl;

        cout << "Thoat chuong trinh? [y/n] ";
        cin >> exit;
        cout << endl;
        if (exit == 'y') return 0;
    }
    return 0;
}
//g++ -o main main.cpp -L. -lNTL -I ..\refs\WinNTL-11_4_4\include