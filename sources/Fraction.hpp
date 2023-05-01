#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
namespace ariel {
    class Fraction {
    private:
        int numerator, denominator;
        float value;

    public:
        Fraction() ;
        explicit Fraction(int numerator, int denominator) ;
        Fraction(const Fraction&);
        Fraction(Fraction&&) = default ;
        Fraction& operator=(const Fraction&) = default ;
        Fraction& operator=(Fraction&&) = default ;
        ~Fraction() = default ;
        explicit Fraction(float) ;
        int getNumerator() ;
        int getDenominator() ;
        int findLCM(int other_den) const;
        Fraction& reduceForm() ;
        Fraction operator+(const Fraction& other) const;

        friend Fraction operator+(const Fraction&, float) ;

        friend Fraction operator+(float, const Fraction&) ;

        Fraction operator-(const Fraction&) const;

        friend Fraction operator-(const Fraction&, float) ;

        friend Fraction operator-(float, const Fraction&) ;

        Fraction operator*(const Fraction&) const;

        friend Fraction operator*(const Fraction&, float) ;

        friend Fraction operator*(float, const Fraction&) ;

        Fraction operator/(const Fraction&) const;

        friend Fraction operator/(const Fraction&, float) ;

        friend Fraction operator/(float, const Fraction&) ;

        bool operator==(const Fraction&) const;

        friend bool operator==(const Fraction&, float) ;

        friend bool operator==(float, const Fraction&) ;

        bool operator>=(const Fraction&) const;

        friend bool operator>=(const Fraction&, float) ;

        friend bool operator>=(float, const Fraction&) ;

        bool operator<=(const Fraction&) const;

        friend bool operator<=(const Fraction&, float) ;

        friend bool operator<=(float, const Fraction&) ;

        bool operator>(const Fraction&) const;

        friend bool operator>(const Fraction&, float) ;

        friend bool operator>(float, const Fraction&) ;

        bool operator<(const Fraction&) const;

        friend bool operator<(const Fraction&, float) ;

        friend bool operator<(float, const Fraction&) ;

        Fraction &operator++() ;

        Fraction &operator--() ;

        Fraction operator++(int) ;

        Fraction operator--(int) ;

        friend std::ostream& operator<<(std::ostream&, const Fraction&) ;

        friend std::istream& operator>>(std::istream&, Fraction&) ;
    };


}
#endif