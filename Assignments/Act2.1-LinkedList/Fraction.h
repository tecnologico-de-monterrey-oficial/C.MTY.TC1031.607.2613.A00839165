#ifndef Fraction_h
#define Fraction_h

#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int den) : numerator(num), denominator(den == 0 ? 1 : den) {}

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    void setNumerator(int num) { numerator = num; }
    void setDenominator(int den) { denominator = (den == 0 ? 1 : den); }

    // Requerido para findData, deleteData y updateData
    bool operator==(const Fraction& other) const {
        return (numerator * other.denominator) == (other.numerator * denominator);
    }

    // Requerido para imprimir limpiamente la lista
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};

#endif /* Fraction_h */
