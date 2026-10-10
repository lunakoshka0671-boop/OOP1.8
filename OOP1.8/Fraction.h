#pragma once
#include <string>

using namespace std;

class Fraction
{
private:
    class DigitString
    {
    private:
        string digits;

    public:
        DigitString();
        DigitString(string value);

        string GetDigits() const;
        bool SetDigits(string value);
        bool Init(string value);

        void Read();
        void Display() const;
        string toString() const;

        DigitString operator+(const DigitString& other) const;
        DigitString operator-(const DigitString& other) const;
        DigitString operator*(const DigitString& other) const;
        DigitString operator/(const DigitString& other) const;
        DigitString operator%(const DigitString& other) const;

        DigitString operator+() const;
        DigitString operator-() const;

        bool operator==(const DigitString& other) const;
        bool operator!=(const DigitString& other) const;
        bool operator<(const DigitString& other) const;
        bool operator>(const DigitString& other) const;
        bool operator<=(const DigitString& other) const;
        bool operator>=(const DigitString& other) const;

        DigitString& operator++();
        DigitString operator++(int);
        DigitString& operator--();
        DigitString operator--(int);
    };

    DigitString integerPart;
    unsigned short fractionalPart;
    bool negative;

    static DigitString ToScaled(const Fraction& value);
    static Fraction FromScaled(DigitString value);

public:
    Fraction();
    Fraction(string integer, unsigned short fraction);
    Fraction(string integer, unsigned short fraction, bool sign);

    string GetIntegerPart() const;
    unsigned short GetFractionalPart() const;
    bool GetNegative() const;

    bool SetIntegerPart(string value);
    bool SetFractionalPart(unsigned short value);
    bool SetNegative(bool value);

    bool Init(string integer, unsigned short fraction, bool sign);

    void Read();
    void Display() const;
    string toString() const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
};

