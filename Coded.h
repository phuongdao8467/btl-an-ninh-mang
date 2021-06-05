#include <iostream>
#include <NTL/ZZ.h>
using namespace NTL;
using namespace std;
class Coded{
    private:
    ZZ p, q;
    ZZ mes;
    ZZ mesCoded;
    long l;
    ZZ d, e, n, phi_n;

    public:
    ZZ genBigPrime(long l){
        //tìm số nguyên tố lớn khi biết số lượng bit, ít nhất 500 bits
        ZZ n;
        n = RandomLen_ZZ(l);
        if (n % 2 == 0) n++;
        while (PrimeTest(n, 10) == 0){
            n += 2;
        }
        return n;
    }   

    ZZ findMaxDivisor(ZZ num1, ZZ num2){
        while (!IsZero(num2)) {
            ZZ r;
            rem(r, num1, num2);
            num1 = num2;
            num2 = r;
        }
        return num1;
    }
    // hàm tìm a^b mod n, sử dụng thuật toán square & multiply
    ZZ powerMod(const ZZ& a, const ZZ& b, const ZZ& n)
    {
        if (b == 0) return ZZ(1);

        long k = NumBits(b);

        ZZ f;
        f = 1;

        for (long i = k - 1; i >= 0; i--) {
            f = (f*f) % n;
            if (bit(b, i) == 1) f = (f*a) % n;
        }
        return f;
    }

    long MillerRabin(const ZZ& n, const ZZ& a)
    {
        ZZ q, mod_a;
        long j, k;

        if (a == 0) return 0;
        // (n-1) = 2^k * m
        k = 1;
        q = (n-1)/2;
        while (q % 2 == 0) {
            k++;
            q /= 2;
        }

        mod_a = powerMod(a, q, n); // mod_a = a^q % n
        if (mod_a == 1) return 1;

        j = 0;
        do {
            mod_a = (mod_a*mod_a) % n; 
            if (mod_a == n-1) return 1;
            j++;
        } while (j < k && mod_a != 1);

        return 0;
        
    }

    // kiểm tra tính nguyên tố
    long PrimeTest(const ZZ& n, long t)
    {
        if (n <= 1) return 0;
        ZZ x;
        long i;

        for (i = 0; i < t; i++) {
            x = RandomBnd(n);

            if (MillerRabin(n, x) == 0) 
                return 0;
        }
        return 1;
    }

    // tính khóa giải mã d khi cho khóa mã hóa e và hai số nguyên lớn
    void setD(){
        ZZ y0, y1, r, a, m, q, y;
        y0 = 0;
        y1 = 1;
        a = this->e;
        m = this->phi_n;
        while (a > 0){
            r = m % a;
            if (r == 0) break;
            q = m / a;
            y = y0 - y1*q;
            m = a;
            a = r;
            y0 = y1;
            y1 = y;
        }
        if (a > 1) cout << "something error!"<< endl;
        else {
            this->d = y;
            if (this->d < 0) this->d = this->d + this->phi_n;
        }
    }
    
    //tạo số e
    void setE(){
        //this->e = 65537;
        ZZ test_e;
        test_e = RandomBnd(this->phi_n);
        if (test_e % 2 == 0) test_e++;
        while (this->findMaxDivisor(test_e, phi_n) != 1){
            test_e += 2;
        }
        this->e = test_e;
    }
    //tạo bộ khóa ngẫu nhiên khi cho 2 số nguyên lớn
    void genKey(){
        this->q = this->genBigPrime(this->l);
        do{
            this->p = this->genBigPrime(this->l);
        } while (this->p == this->q);
        
        this->n = this->q*this->p;
        this->phi_n = (this->q - 1)*(this->p - 1);
        this->setE();
        this->setD();
    }
    // mã hóa khi cho message và e và d
    ZZ encoded(){
        this->genKey();
        this->mesCoded = this->powerMod(mes, e, n);
        return mesCoded;
    }
    // giải mã khi cho thông điệp mã hóa và d và n
    ZZ decode(){
        return this->powerMod(mesCoded, d, n);

    }
    void setMes(ZZ mes){
        this->mes = mes;
    }
    void setL(long l){
        this->l = l;
    }
};
