//Julio Eduardo Rodriguez Ruiz A00839165
#include <iostream>
using namespace std;

int factorial (int n){
    if (n == 0) {
        return 1;
    }
    return n * factorial(n-1);
}

int sumIterative (int n){
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int sumRecursive (int n){
    if (n == 0) {
        return 0;
    } 
    return n + sumRecursive(n-1);
}

int sumFormula (int n){
    return n*(n+1)/2;
}

int FibonacciIterative (int n){
    if (n <= 1) return n;
    int a = 1;
    int b = 1;
    int c;
    for (int i = 2; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int FibonacciRecursive (int n){
    if (n <= 2) {
        return 1;
    }
    return FibonacciRecursive(n-1) + FibonacciRecursive(n-2);
}

int BacteriasIterative (int n) {
    int poblacion = 1;
    for (int i = 0; i < n; ++i) {
        int nacimientos = (poblacion * 378) / 100;
        int fallecimientos = (poblacion * 234) / 100;
        
        poblacion = poblacion + nacimientos - fallecimientos;
    }
    
    return poblacion;
}

int BacteriasRecursive (int n) {
    if (n == 0) {
        return 1;
    }
    
    int poblacionAnterior = BacteriasRecursive(n - 1);
    int nacimientos = (poblacionAnterior * 378) / 100;
    int fallecimientos = (poblacionAnterior * 234) / 100;
    
    return poblacionAnterior + nacimientos - fallecimientos;
}

double investmentIterative(double cantidad, int meses) {
    for (int i = 0; i < meses; ++i) {
        cantidad = cantidad * 1.1875;
    }
    return cantidad;
}

double investmentRecursive(double cantidad, int meses) {
    if (meses == 0) {
        return cantidad;
    }
    return investmentRecursive(cantidad * 1.1875, meses - 1);
}

double powIterative(double n, int y) {
    double resultado = 1.0;
    for (int i = 0; i < y; ++i) {
        resultado = resultado * n;
    }
    return resultado;
}

double powRecursive(double n, int y) {
    if (y == 0) {
        return 1.0;
    }
    return n * powRecursive(n, y - 1);
}


int main() {
    int num = 8;
    
    // Variables para los problemas de inversion y potencia
    double capital = 1000.0;
    int mesesInversion = 6;
    int exponente = 3;

    //Factorial
    cout << "El factorial de " << num << " es " << factorial(num) << endl;
    //Suma
    cout << "La suma iterativa de " << num << " es " << sumIterative(num) << endl;
    cout << "La suma recursiva de " << num << " es " << sumRecursive(num) << endl;
    cout << "La suma con formula de " << num << " es " << sumFormula(num) << endl;
    //Fibonacci
    cout << "El numero de Fibonacci iterativo de " << num << " es " << FibonacciIterative(num) << endl;
    cout << "El numero de Fibonacci recursivo de " << num << " es " << FibonacciRecursive(num) << endl;
    //Bacterias 
    cout << "La poblacion de bacterias iterativa despues de " << num << " dias es " << BacteriasIterative(num) << endl;
    cout << "La poblacion de bacterias recursiva despues de " << num << " dias es " << BacteriasRecursive(num) << endl;
    //Inversion
    cout << "La inversion iterativa de " << capital << " en " << mesesInversion << " meses es " << investmentIterative(capital, mesesInversion) << endl;
    cout << "La inversion recursiva de " << capital << " en " << mesesInversion << " meses es " << investmentRecursive(capital, mesesInversion) << endl;
    //Potencia
    cout << "La potencia iterativa de " << num << " elevado a la " << exponente << " es " << powIterative(num, exponente) << endl;
    cout << "La potencia recursiva de " << num << " elevado a la " << exponente << " es " << powRecursive(num, exponente) << endl;
    
    return 0;
}