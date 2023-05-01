#include <cmath>
#include <limits>
#include "Fraction.hpp"
using namespace std;
using namespace ariel;

    Fraction::Fraction(int numer, int denom){
        if(numer!=denom){
            if (((numer > numeric_limits<int>::max() || numer < numeric_limits<int>::min()) && denom != 1)
                || ((denom > numeric_limits<int>::max() || denom < numeric_limits<int>::min()) && numer != 1)){
                throw overflow_error("Numerator or denominator exceeds maximum integer value");
            }
        }
        if(denom== 0){
            if(numer == 0){
                _numerator=numer;
                _denominator=denom;
            }
            else{
                throw invalid_argument("Division in zero!");
            }
        }
        else{
            if(numer<0&&denom<0 || numer>0 && denom<0){       // -a / -b || a / -b
                _numerator=-numer;
                _denominator=-denom;
            }
            else if(numer==denom){
                _numerator=1;
                _denominator=1;
            }
            else{                                           // -a / b || a / b
                _numerator=numer;
                _denominator=denom; 
            }
        }      
    }
    Fraction::Fraction(double val){
    int mult = pow(10, 3);        // 3 digits after the dot
    int numer = static_cast<int>(round(val * mult));
    int denom = mult;

    int gcdv = gcd(numer, denom);
    _numerator = numer / gcdv;
    _denominator = denom / gcdv;
    }

    int Fraction::gcd(int val1, int val2){
        if(val2==0){
            return abs(val1);
        }
        return gcd(val2, val1%val2);
    }
    int Fraction::lcm(int val1, int val2){
        int gcdval = gcd(val1,val2);
        return (val1 / gcdval) * val2;
    }
    Fraction& Fraction::reduce() {
        int gcdval = gcd(_numerator, _denominator);
        _numerator /= gcdval;
        _denominator /= gcdval;
        if(_numerator<10&&_denominator<10){
            return *this;
        }
        double val = static_cast<double>(_numerator) / _denominator;
        int mult = pow(10, 3); // 3 digits after the dot
        val = round(val * mult) / mult; // round to 3 digits after the dot
        int numer = static_cast<int>(round(val * mult));
        int denom = mult;
        gcdval = gcd(numer, denom);
        _numerator = numer / gcdval;
        _denominator = denom / gcdval;
        return *this;
    }
    int Fraction::getNumerator(){
        return _numerator;
    }
    int Fraction::getDenominator(){
        return _denominator;
    }
    void Fraction::setNumerator(int numer){
        _numerator=numer;
    }
    void Fraction::setDenominator(int denom){
        _denominator=denom;
    }

    Fraction Fraction::operator+(const Fraction& other) const {
        int ndenom = lcm(_denominator, other._denominator);
        long long nnume = static_cast<long long>(_numerator) * (ndenom / _denominator) + static_cast<long long>(other._numerator) * (ndenom / other._denominator);
        if (nnume > std::numeric_limits<int>::max() || nnume < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Addition causes overflow or underflow");
        }
        return Fraction(static_cast<int>(nnume), ndenom).reduce();
    }

    Fraction Fraction::operator-(const Fraction& other) const {
        if (static_cast<long long>(_numerator) - other._numerator > std::numeric_limits<int>::max() ||
            static_cast<long long>(_numerator) - other._numerator < std::numeric_limits<int>::min() ||
            static_cast<long long>(_denominator) - other._denominator > std::numeric_limits<int>::max() ||
            static_cast<long long>(_denominator) - other._denominator < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Subtraction causes overflow or underflow");
        }
        Fraction neg_other(-other._numerator, other._denominator);
        return *this + neg_other;
    }
   
    Fraction Fraction::operator*(const Fraction& other) const {
        long long nnume = static_cast<long long>(_numerator) * other._numerator;
        long long ndenom = static_cast<long long>(_denominator) * other._denominator;
        if (nnume > std::numeric_limits<int>::max() || nnume < std::numeric_limits<int>::min() ||
            ndenom > std::numeric_limits<int>::max() || ndenom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Multiplication causes overflow or underflow");
        }
        return Fraction(static_cast<int>(nnume), static_cast<int>(ndenom)).reduce();
    }
    
    Fraction Fraction::operator/(const Fraction& other) const {
        if (other._numerator == 0) {
            throw std::runtime_error("Division by zero!");
        }
        Fraction copy1 = *this;
        Fraction copy2 = other;

        long long nnume = static_cast<long long>(copy1._numerator) * copy2._denominator;
        long long ndenom = static_cast<long long>(copy1._denominator) * copy2._numerator;
        if (ndenom > std::numeric_limits<int>::max() || ndenom < std::numeric_limits<int>::min() ||
            nnume > std::numeric_limits<int>::max() || nnume < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Division causes overflow or underflow");
        }
        copy1.reduce();
        copy2.reduce();
        return Fraction(static_cast<int>(nnume), static_cast<int>(ndenom)).reduce();
    }

    Fraction Fraction::operator+(const double &other) const{
        return *this + Fraction(other);
    }
    Fraction Fraction::operator-(const double &other) const{
        return  *this - Fraction(other);
    }
    Fraction Fraction::operator*(const double &other) const{
        return (*this) * Fraction(other);
    }
    Fraction Fraction::operator/(const double &other) const{
        if(other == 0){
            throw runtime_error("Division in zero!");
        }
        return *this / Fraction(other);
    }
    bool Fraction::operator==(const Fraction &other) const {
        if(_numerator==0&&other._numerator==0){
            return true;
        }
        int gcdval = gcd(_numerator, _denominator);
        int ogcdval = gcd(other._numerator, other._denominator);
        Fraction tmp1((int)(_numerator / gcdval),(int)(_denominator / gcdval));
        Fraction tmp2((int)(other._numerator / ogcdval),(int)(other._denominator / ogcdval));
        tmp1.reduce();
        tmp2.reduce();
        return (tmp1._numerator == tmp2._numerator && tmp1._denominator == tmp2._denominator);
    }
    bool Fraction::operator<(const Fraction &other) const{
        int lcmv = lcm(_denominator,other._denominator);
        int this_numer = _numerator * (lcmv / _denominator);
        int other_numer = other._numerator * (lcmv / other._denominator);
        return this_numer < other_numer;
    }
    bool Fraction::operator>(const Fraction &other) const{
        int lcmv = lcm(_denominator,other._denominator);
        int this_numer = _numerator * (lcmv / _denominator);
        int other_numer = other._numerator * (lcmv / other._denominator);
        return this_numer > other_numer;
    }
    bool Fraction::operator>=(const Fraction &other) const{
        return (*this > other) || (*this == other);
    }
    bool Fraction::operator<=(const Fraction &other) const{
        return (*this < other) || (*this == other);
    }    

    bool Fraction::operator==(const double &other) const{
        return *this == Fraction(other);
    }
    bool Fraction::operator<(const double &other) const{
        return *this < Fraction(other);
    }
    bool Fraction::operator>(const double &other) const{
        return *this > Fraction(other);
    }
    bool Fraction::operator<=(const double &other) const{
        return (*this < other) || (*this == other);
    }
    bool Fraction::operator>=(const double &other) const{
        return (*this > other) || (*this ==other);
    }
    bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
    }
    //prefix inc
    Fraction& Fraction::operator++(){
        _numerator+=_denominator;
        return *this;
    }
    //postfix inc
    Fraction Fraction::operator++(int dummy_flag){
        Fraction copy=*this;
        _numerator+=_denominator;
        return copy;
    }
    //prefix dec
    Fraction& Fraction::operator--(){
        _numerator-=_denominator;
        return *this;
    }
    //postfix dec
    Fraction Fraction::operator--(int dummy_flag){
        Fraction copy=*this;
        _numerator-=_denominator;
        return copy;
    }
    ostream& ariel::operator<<(ostream& output, const Fraction& fra){
        Fraction copy=fra;
        if(fra._numerator>0&&fra._denominator<0){
            copy.setNumerator(-copy._numerator);
            copy.setDenominator(-copy._denominator);
        }
        if(fra.gcd(fra._numerator,fra._denominator)>=2){
            copy.reduce();
            output << copy._numerator << "/" << copy._denominator;
            return output;
        }
        else{
            output << copy._numerator << "/" << copy._denominator;
            return output;
        }
    }

    istream& ariel::operator>>(istream& input , Fraction& fra){
        int numerator, denominator;
        char separator;
        ios::pos_type startPosition = input.tellg();
            input >> numerator;         // numer
        if(input.fail()){
            input.clear();
            input.seekg(startPosition);
            throw invalid_argument("expected numerator");
        }
        if(input.peek() == '.'){            //if gets .
            input.clear();
            input.seekg(startPosition);
            throw runtime_error("Only int digits.");
        }
        if(input.peek() == '/' || input.peek() == ','){     // if has sepr
            input >> separator;             //sepr
            input >> denominator;           //denom
            if(input.fail()){
                input.clear();
                input.seekg(startPosition);
                throw invalid_argument("expected deperator and denominator");
            }
            if(denominator == 0){       // if denom 0
                input.clear();
                input.seekg(startPosition);
                throw runtime_error("Divide by zero!");
            }
            else if(input.peek() == '.'){   //if gets . denom
                input.clear();
                input.seekg(startPosition);
                throw runtime_error("Only int digits.");
            }
            else{
                fra.setNumerator(numerator);
                fra.setDenominator(denominator);
                return input;
            }
            input.setstate(std::ios_base::failbit);
            return input;
        }
        else{
            input >> denominator;           //denom
            if(input.fail()){
                input.clear();
                input.seekg(startPosition);
                throw invalid_argument("expected denominator");
            }
            if(denominator == 0){       // if denom 0
                input.clear();
                input.seekg(startPosition);
                throw runtime_error("Divide by zero!");
            }
            else if(input.peek() == '.'){   //if gets . denom
                input.clear();
                input.seekg(startPosition);
                throw runtime_error("Only int digits.");
            }
            else{
                fra.setNumerator(numerator);
                fra.setDenominator(denominator);
                return input;
            }
            input.setstate(std::ios_base::failbit);
            return input;              
        }
    }
    
    Fraction ariel::operator-(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1-fr2;    
    }
    Fraction ariel::operator+(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1+fr2;    
    }
    Fraction ariel::operator*(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1*fr2; 
    }
    Fraction ariel::operator/(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1/fr2;
    }
    bool ariel::operator<(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1<fr2;
    }
    bool ariel::operator<=(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1<=fr2;        
    }
    bool ariel::operator>(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1>fr2;
    }
    bool ariel::operator>=(const double& fr1, const Fraction& fr2){
        Fraction tf1(fr1);
        return tf1>=fr2;
    }
    bool ariel::operator==(const double& fr1, const Fraction& fr2){
        return fr2==fr1;
    }