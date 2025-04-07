#include <iostream>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;


string decimal_a_binario(int num, int bits) {
    if (num >= 0) {
        
        string bin = bitset<32>(num).to_string().substr(32 - bits);
        return bin;
    } else {
    
        int positivo = pow(2, bits) + num;
        string bin = bitset<32>(positivo).to_string().substr(32 - bits);
        return bin;
    }
}

int binario_a_decimal(string binario) {
    int bits = binario.length();
    if (binario[0] == '1') {
        
        int valor = -pow(2, bits-1);
        for (int i = 1; i < bits; i++) {
            if (binario[i] == '1') {
                valor += pow(2, bits-1 - i);
            }
        }
        return valor;
    } else {
        return stoi(binario, nullptr, 2);
    }
}


void multiplicar_booth(int multiplicando, int multiplicador, int n_bits) {
    string M = decimal_a_binario(multiplicando, n_bits);
    string Q = decimal_a_binario(multiplicador, n_bits);
    
    string A(n_bits, '0');  
    string Q_ext = Q;        
    char Q_1 = '0';         
    
    cout << "Inicio:" << endl;
    cout << "A = " << A << " Q = " << Q_ext << " Q_1 = " << Q_1 << " M = " << M << endl;
    cout << "----------------------------------------" << endl;
    
    for (int i = 0; i < n_bits; i++) {
        cout << "Iteracion " << i+1 << ":" << endl;
        
        char ultimo_bit_Q = Q_ext.back();
        
        if (ultimo_bit_Q == '1' && Q_1 == '0') {
            int a_val = binario_a_decimal(A);
            int m_val = binario_a_decimal(M);
            A = decimal_a_binario(a_val - m_val, n_bits);
            cout << "  Operacion: A = A - M" << endl;
        } 
        else if (ultimo_bit_Q == '0' && Q_1 == '1') {
            int a_val = binario_a_decimal(A);
            int m_val = binario_a_decimal(M);
            A = decimal_a_binario(a_val + m_val, n_bits);
            cout << "  Operacion: A = A + M" << endl;
        }
        
        cout << "  Despues de operacion: A = " << A << " Q = " << Q_ext << endl;
        

        char bit_signo_A = A[0];
        
        string nuevo_A = string(1, bit_signo_A) + A.substr(0, n_bits-1);
        
        string nuevo_Q = string(1, A.back()) + Q_ext.substr(0, n_bits-1);
        
        Q_1 = Q_ext.back();
        
        A = nuevo_A;
        Q_ext = nuevo_Q;
        
        cout << "  Desplazamiento: A = " << A << " Q = " << Q_ext << " Q_1 = " << Q_1 << endl;
        cout << "----------------------------------------" << endl;
    }
    
    string resultado_bin = A + Q_ext;
    int resultado_dec = binario_a_decimal(resultado_bin);
    
    cout << "Resultado final:" << endl;
    cout << "Binario: " << resultado_bin << endl;
    cout << "Decimal: " << resultado_dec << endl;
}

int main() {
    int bits, num1, num2;
    
    cout << "Multiplicacion con algoritmo de Booth" << endl;
    cout << "Ingrese cantidad de bits: ";
    cin >> bits;
    cout << "Ingrese multiplicando: ";
    cin >> num1;
    cout << "Ingrese multiplicador: ";
    cin >> num2;
    
    multiplicar_booth(num1, num2, bits);
    
    return 0;
}
