#pragma once
#include <iostream>
namespace ariel{

class Fraction{
    private:
        int _numerator;
        int _denominator;

        //Side math methods
        Fraction& reduce();
        static int lcm(int val1, int val2);
        static int gcd(int val1, int val2);

    public:

        //Constructors
        Fraction(int numer=0, int denom=1);
        Fraction(double val);

        //Getters & Setters
        int getNumerator();
        int getDenominator();
        void setNumerator(int numer);
        void setDenominator(int denom);

        //Arithmetic operators
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(Fraction const &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        Fraction operator+(const double &other) const;
        Fraction operator-(const double &other) const;
        Fraction operator*(const double &other) const;
        Fraction operator/(const double &other) const;
        
        //Boolean operators
        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction& other) const;
        bool operator<(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;
        bool operator==(const double &other) const;
        bool operator<(const double &other) const;
        bool operator<=(const double &other) const;
        bool operator>(const double &other) const;
        bool operator>=(const double &other) const;
        
        //prefix inc
        Fraction& operator++();
        //postfix inc
        Fraction operator++(int dummy_flag);
        //prefix dec
        Fraction& operator--();
        //postfix dec
        Fraction operator--(int dummy_flag);

        // I/O operators.
        friend std::ostream& operator<<(std::ostream& output, const Fraction& fra);
        friend std::istream& operator>>(std::istream& input , Fraction& fra);

        // Friend operators
        friend Fraction operator*(double const &fr1, Fraction const &fr2);
        friend Fraction operator-(const double& fr1, const Fraction& fr2);
        friend Fraction operator*(const double& fr1, const Fraction& fr2);
        friend Fraction operator+(const double& fr1, const Fraction& fr2);
        friend Fraction operator/(const double& fr1, const Fraction& fr2);
        friend bool operator<(const double& fr1, const Fraction& fr2);
        friend bool operator<=(const double& fr1, const Fraction& fr2);
        friend bool operator>(const double& fr1, const Fraction& fr2);
        friend bool operator>=(const double& fr1, const Fraction& fr2);
        friend bool operator==(const double& fr1, const Fraction& fr2);
};

}