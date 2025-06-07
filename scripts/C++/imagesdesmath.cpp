#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * imagesdesmath.cpp programa que encuentra los números natuales del 0 al 10000000
 * tales que n = s(n)+p(n), donde s() es una función que suma todos sus dígitos mientras quep() es una función que los multiplica
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Julio 2024.
*/

// Suma todos los dígitos de un número
int S(int n) {
    string sn = to_string(n);
    int sum = 0;
    for (char c : sn){
        int digit;
        digit = c - '0';
        sum += digit;
    }
    return sum;
}
// Multiplica todos los dígitos de un número
int P(int n) {
    string sn = to_string(n);
    int product = 1;
    for (char c : sn){
        int digit;
        digit = c - '0';
        product = product * digit;
    }
    return product;
}

// MAIN
int main() {
    for(int num = 0; num < 10000000; num++){
        if(num == S(num) + P(num)){
            cout << num << endl;
        }
    }
    return 0;
}