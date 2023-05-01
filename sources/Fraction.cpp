#include "Fraction.hpp"
#include <ostream>
#include <cstdlib>
#include <exception>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ariel{

    const int max_int = std::numeric_limits<int>::max();
    const int min_int = std::numeric_limits<int>::min();

    ///-----Find the gcd of to integers-----
    int findGCD(int num1, int num2){
        while (num2 != 0) {
            int temp = num2;
            num2 = num1 % num2;
            num1 = temp;
        }
        return abs(num1);
    }

    ///-----Return the denominator of the current Fraction instance------
    int Fraction::getDenominator() {return denominator ;} ;

    ///-----Return the numerator of the current Fraction instance------
    int Fraction::getNumerator() {return numerator ;} ;

    ///-----Empty constructor - used for scanning a fraction from the user (>> operator)-----
    Fraction::Fraction(): numerator(0), denominator(1) {}

    ///-----Constructor for creating an instance of a fraction by getting: 1. Numerator 2. Denominator-----
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        //-----If the denominator supplied is 0 throw exception-----
        if(denominator == 0){
            throw std::invalid_argument("Cannot create fraction with denominator equals 0.") ;
        }

        //-----If the denominator supplied is negative, make it positive and switch signs of the numerator-----
        if(denominator < 0){
            this->numerator = (-numerator) ;
            this->denominator = (-denominator) ;
        }

        //-----Reduce the form of the new Fraction instance-----
        reduceForm() ;
    }

    ///-----Constructor for creating a fraction instance by getting a float value-----
    Fraction::Fraction(float f_num): numerator(f_num*1000), denominator(1000){
        //-----After the instantiation of the Fraction, reduce it`s form to the smallest representation-----
        reduceForm() ;
    }

    ///-----Copy constructor-----
    Fraction::Fraction(const Fraction &frac): numerator(frac.numerator), denominator(frac.denominator) { }

    ///-----Find the LCM between the current Fraction instance denominator and another denominator provided-----
    int Fraction::findLCM(int other_den) const{
        return abs((denominator * other_den)) / findGCD(denominator, other_den) ;
    }

    ///-----Reduce the form of the current fraction to it`s smallest possible form-----
    Fraction& Fraction::reduceForm() {
        int gcd = findGCD(numerator, denominator) ;
        numerator /= gcd ;
        denominator /= gcd ;
        return *this ;
    }


    ///----------------------------Overflow handling functions----------------------------------------
    ///-----Instead of using the regular *, +, - operators we will call these methods which will throw
    ///-----overflow exception if needed-----

    int pr_mult(int num1, int num2){
        long res = (long)num1 * num2 ;
        if(res < min_int || res > max_int){
            throw std::overflow_error("Overflow detected.") ;
        }
        return res ;
    }

    int pr_add(int num1, int num2){
        long res = (long)num1 + num2 ;
        if(res < min_int || res > max_int){
            throw std::overflow_error("Overflow detected.") ;
        }
        return res ;
    }
    int pr_sub(int num1, int num2){
        long res = (long)num1 - num2 ;
        if(res < min_int || res > max_int){
            throw std::overflow_error("Overflow detected.") ;
        }
        return res ;
    }
    /*----------------------------------------------------------------------------------------------------------
     * --------------------------------------Operators overloading----------------------------------------------
     * ---------------------------------------------------------------------------------------------------------*/

    ///-------------------------Members operator overloading methods----------------------------------------------

    Fraction Fraction::operator+(const Fraction& other) const{
        //-----Check if there is an overflow-----


        //-----Find the lcm of the both denominator and then add the both numerators after the extension of the
        //-----both fractions to the common denominator, then create a new fraction with the new denominator and the
        //-----added numerators------
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        return Fraction(pr_add(pr_mult(mult1, numerator), pr_mult(mult2, other.numerator)),
                        pr_mult(denominator, mult1)) ;
    }

    Fraction Fraction::operator-(const Fraction& other) const{
        //-----Find the lcm of the both denominator and then subtract the both numerators after the extension of the
        //-----both fractions to the common denominator, then create a new fraction with the new denominator and the
        //-----subtracted numerators------
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        return Fraction(pr_sub(pr_mult(mult1, numerator), pr_mult(mult2,other.numerator)), pr_mult(mult1 , denominator)) ;
    }

    Fraction Fraction::operator*(const Fraction& other) const{
        //-----Create new fraction holds the multiplication of both the numerator and the denominator-----
        return Fraction(pr_mult(numerator, other.numerator), pr_mult(denominator, other.denominator)) ;
    }

    Fraction Fraction::operator/(const Fraction& other) const{
        //-----If one of the numerators is 0, return the fraction (0/1) to prevent fraction with a 0 denominator-----
        if(other.numerator == 0){
            throw std::runtime_error("Cannot divide by 0.") ;
        }

        //-----Else return a new Fraction corresponds to the division of the current Fraction by the other provided-----
        return Fraction(pr_mult(numerator, other.denominator), pr_mult(denominator, other.numerator)) ;
    }

    bool Fraction::operator==(const Fraction& other) const{
        //-----All fractions instance are being maintained to be in their most reduced form, so f1 == f2 only if
        //-----their both numerators and denominators are equal-----
        float f_val1 = (float)numerator / denominator ;
        int temp = f_val1*1000 ;
        f_val1 = (float)temp / 1000 ;
        float f_val2 = (float)other.numerator / other.denominator ;
        temp = f_val2*1000 ;
        f_val2 = (float)temp / 1000 ;
        if(f_val1 == f_val2){
            return true ;
        }
        return false ;
    }

    bool Fraction::operator>=(const Fraction& other) const{
        //-----Find the common denominator for both fractions and then compare them by the extended numerators-----
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        if(numerator * mult1 >= other.numerator * mult2){
            return true ;
        }
        return false ;
    }

    bool Fraction::operator<=(const Fraction& other) const{
        //-----Find the common denominator for both fractions and then compare them by the extended numerators-----
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        if(numerator * mult1 <= other.numerator * mult2){
            return true ;
        }
        return false ;
    }

    bool Fraction::operator>(const Fraction& other) const{
        //-----Find the common denominator for both fractions and then compare them by the extended numerators-----
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        if(numerator * mult1 > other.numerator * mult2){
            return true ;
        }
        return false ;
    }

    bool Fraction::operator<(const Fraction& other) const{
        //-----Find the common denominator for both fractions and then compare them by the extended numerators-----
        int lcm = findLCM(other.denominator) ;
        int mult1 = lcm / denominator ;
        int mult2 = lcm / other.denominator ;
        if(numerator * mult1 < other.numerator * mult2){
            return true ;
        }
        return false ;
    }

    ///-----Add to the numerator of the fraction the amount of its denominator and return the instance reference-----
    Fraction& Fraction::operator++(){
        numerator += denominator ;
        reduceForm() ;
        return *this ;
    }

    ///-----Reduce from the numerator of the fraction the amount of its denominator and return the instance reference-----
    Fraction& Fraction::operator--(){
        numerator -= denominator ;
        reduceForm() ;
        return *this ;
    }

    ///-----Create a copy of the instance, then add to the instance itself 1, and return the copy-----
    Fraction Fraction::operator++(int){
        Fraction copy(*this) ;
        ++(*this) ;
        return copy ;
    }

    ///-----Create a copy of the instance, then subtract the instance by 1, and return the copy-----
    Fraction Fraction::operator--(int){
        Fraction copy(*this) ;
        --(*this) ;
        return copy ;
    }

    ///--------------------------------Non-members operator overloading methods-------------------------------------

    //-----At the non members operator overloading methods are friend functions, each operator will use the
    //-----corresponding member method, and the only difference is that those method supports the operators to run
    //-----with a fraction instance and a float instance. First, a Fraction instance will be created by the float value,
    //-----and then the member function will be called as it was two fractions from the start-----
    Fraction operator+(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return frac + tempFrac ;
    }

    Fraction operator+(const float value, const Fraction& frac){
        return frac + value ;
    }



    Fraction operator-(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return frac - tempFrac ;
    }

    Fraction operator-(const float value, const Fraction& frac){
        Fraction tempFrac(value) ;
        return tempFrac - frac ;
    }



    Fraction operator*(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return frac*tempFrac ;
    }

    Fraction operator*(const float value, const Fraction& frac){
        return frac * value ;
    }



    Fraction operator/(const Fraction& frac, const float value){
        if(value == 0){
            throw std::runtime_error("Cannot divide by 0") ;
        }
        Fraction tempFrac(value) ;
        return frac / tempFrac ;
    }

    Fraction operator/(const float value, const Fraction& frac){
        Fraction tempFrac(value) ;
        return tempFrac / frac ;
    }



    bool operator==(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return (frac==tempFrac) ;
    }

    bool operator==(const float value, const Fraction& frac){

        return (frac == value) ;
    }



    bool operator>=(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return frac >= tempFrac ;
    }

    bool operator>=(const float value, const Fraction& frac){
        Fraction tempFrac(value) ;
        return tempFrac >= frac ;
    }



    bool operator<=(const Fraction& frac, const float value){
        return (value >= frac) ;
    }

    bool operator<=(const float value, const Fraction& frac){
        return (frac >= value) ;
    }



    bool operator>(const Fraction& frac, const float value){
        Fraction tempFrac(value) ;
        return frac > tempFrac ;
    }

    bool operator>(const float value, const Fraction& frac){
        Fraction tempFrac(value) ;
        return tempFrac > frac ;
    }



    bool operator<(const Fraction& frac, const float value){
        return value > frac ;
    }

    bool operator<(const float value, const Fraction& frac){
        return frac > value ;
    }

    ///-----Send a given fraction to a given ostream, be the format (numerator/denominator)-----
    std::ostream& operator<<(std::ostream &os, const Fraction &frac){
        os << frac.numerator << "/" << frac.denominator ;
        return os;
    }

    ///-----Scan from a given istream two integers, or a float value, and create a Fraction instance into the given
    ///-----Fraction reference f-----
    std::istream& operator>>(std::istream &input, Fraction &frac){
        int num, den;
        float fl_num ;
        std::string str ;
        //-----Read in the numerator into a string first to be able to determine if it is an int or a float-----
        input >> str;

        //-----Try converting the string to int, if the size of the output smaller than the size of the original
        //-----string, it is not an integer, throw exception-----
        try{
            size_t size ;
            num = std::stoi(str, &size) ;
            if(size != str.size()) {
                throw std::runtime_error("The scanned argument is not an integer.") ;
            }
        }

            //-----Catch the exception, and try converting the string into a float, if the conversion was unsuccessfully
            //-----then the scanned argument is not an integer or a float, then throw exception, if the conversion succeed,
            //-----create a new Fraction instance by the float value into the f reference supplied-----
        catch(...){
            try{
                fl_num = std::stof(str) ;
                frac = Fraction(fl_num) ;
                std::string other_s ;
                input >> other_s ;
                if(!input.fail()) {
                    throw std::invalid_argument("Already scanned float.") ;
                }
                return input ;
            }catch(...){
                input.setstate(std::ios_base::failbit);
                throw std::runtime_error("The scanned argument is not an integer or a float.") ;
            }
        }

        //-----At this point reached, one integer has been successfully scanned as the numerator of the new Fraction,
        //-----then the user must insert another integer, if not, exception will be thrown, otherwise the new Fraction
        //-----will be created and inserted into the f reference supplied-----
        input >> den;
        if (input.fail()) {
            input.setstate(std::ios_base::failbit);
            throw std::runtime_error("Received other type then int") ;
        }

        if(den == 0){
            throw std::runtime_error("0 has been scanned as a denominator.") ;
        }
        //-----Create the fraction object-----
        frac = Fraction(num, den);
        return input;
    }
}