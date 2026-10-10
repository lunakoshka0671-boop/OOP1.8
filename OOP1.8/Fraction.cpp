
#include "Fraction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

namespace
{
    bool IsValid(const string& s)
    {
        if (s.empty())
            return false;

        size_t start = (s[0] == '-') ? 1 : 0;

        if (start == s.size())
            return false;

        for (size_t i = start; i < s.size(); i++)
        {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }

        return true;
    }

    string Normalize(string s)
    {
        bool negative = !s.empty() && s[0] == '-';
        size_t start = negative ? 1 : 0;

        while (start + 1 < s.size() && s[start] == '0')
            start++;

        string result = s.substr(start);

        if (result == "0")
            return "0";

        return negative ? "-" + result : result;
    }

    bool IsNegative(const string& s)
    {
        return !s.empty() && s[0] == '-';
    }

    string AbsString(const string& s)
    {
        return IsNegative(s) ? s.substr(1) : s;
    }

    int CompareAbs(const string& a, const string& b)
    {
        if (a.size() > b.size()) return 1;
        if (a.size() < b.size()) return -1;

        if (a > b) return 1;
        if (a < b) return -1;

        return 0;
    }

    string AddAbs(const string& a, const string& b)
    {
        string result;
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry)
        {
            int sum = carry;

            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';

            result.push_back(char('0' + sum % 10));
            carry = sum / 10;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    // Викликається, коли a >= b
    string SubAbs(const string& a, const string& b)
    {
        string result;
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int borrow = 0;

        while (i >= 0)
        {
            int digit = a[i--] - '0' - borrow;
            int sub = (j >= 0) ? b[j--] - '0' : 0;

            if (digit < sub)
            {
                digit += 10;
                borrow = 1;
            }
            else
                borrow = 0;

            result.push_back(char('0' + digit - sub));
        }

        reverse(result.begin(), result.end());
        return Normalize(result);
    }

    string MulAbs(const string& a, const string& b)
    {
        if (a == "0" || b == "0")
            return "0";

        vector<int> result(a.size() + b.size(), 0);

        for (int i = (int)a.size() - 1; i >= 0; i--)
        {
            for (int j = (int)b.size() - 1; j >= 0; j--)
            {
                int product = (a[i] - '0') * (b[j] - '0');
                int sum = product + result[i + j + 1];

                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string answer;

        for (int digit : result)
            answer += char('0' + digit);

        return Normalize(answer);
    }

    string DivAbs(const string& a, const string& b)
    {
        if (b == "0")
            throw domain_error("Division by zero");

        string quotient;
        string remainder = "0";

        for (char digit : a)
        {
            if (remainder == "0")
                remainder = string(1, digit);
            else
                remainder += digit;

            remainder = Normalize(remainder);

            int q = 0;

            while (CompareAbs(remainder, b) >= 0)
            {
                remainder = SubAbs(remainder, b);
                q++;
            }

            quotient.push_back(char('0' + q));
        }

        return Normalize(quotient);
    }

    string AddSigned(const string& a, const string& b)
    {
        bool na = IsNegative(a);
        bool nb = IsNegative(b);

        string aa = AbsString(a);
        string bb = AbsString(b);

        if (na == nb)
        {
            string result = AddAbs(aa, bb);
            return na && result != "0" ? "-" + result : result;
        }

        int cmp = CompareAbs(aa, bb);

        if (cmp == 0)
            return "0";

        string result;
        bool negative;

        if (cmp > 0)
        {
            result = SubAbs(aa, bb);
            negative = na;
        }
        else
        {
            result = SubAbs(bb, aa);
            negative = nb;
        }

        return negative && result != "0" ? "-" + result : result;
    }

    int CompareSigned(const string& a, const string& b)
    {
        bool na = IsNegative(a);
        bool nb = IsNegative(b);

        if (na && !nb) return -1;
        if (!na && nb) return 1;

        int cmp = CompareAbs(AbsString(a), AbsString(b));

        return na ? -cmp : cmp;
    }
}

// =====================================================
// Реалізація вкладеного класу DigitString
// =====================================================

Fraction::DigitString::DigitString()
{
    digits = "0";
}

Fraction::DigitString::DigitString(string value)
{
    digits = "0";
    SetDigits(value);
}

string Fraction::DigitString::GetDigits() const
{
    return digits;
}

bool Fraction::DigitString::SetDigits(string value)
{
    if (!IsValid(value))
    {
        digits = "0";
        return false;
    }

    digits = Normalize(value);
    return true;
}

bool Fraction::DigitString::Init(string value)
{
    return SetDigits(value);
}

void Fraction::DigitString::Read()
{
    string value;

    do
    {
        cout << "Input an integer: ";
        cin >> value;
    } while (!Init(value));
}

void Fraction::DigitString::Display() const
{
    cout << toString();
}

string Fraction::DigitString::toString() const
{
    return digits;
}

Fraction::DigitString
Fraction::DigitString::operator+(const DigitString& other) const
{
    return DigitString(AddSigned(digits, other.digits));
}

Fraction::DigitString
Fraction::DigitString::operator-(const DigitString& other) const
{
    string b = other.digits;

    if (b != "0")
        b = IsNegative(b) ? AbsString(b) : "-" + b;

    return DigitString(AddSigned(digits, b));
}

Fraction::DigitString
Fraction::DigitString::operator*(const DigitString& other) const
{
    string result = MulAbs(AbsString(digits), AbsString(other.digits));

    if (IsNegative(digits) != IsNegative(other.digits)
        && result != "0")
        result = "-" + result;

    return DigitString(result);
}

Fraction::DigitString
Fraction::DigitString::operator/(const DigitString& other) const
{
    string result = DivAbs(AbsString(digits), AbsString(other.digits));

    if (IsNegative(digits) != IsNegative(other.digits)
        && result != "0")
        result = "-" + result;

    return DigitString(result);
}

Fraction::DigitString
Fraction::DigitString::operator%(const DigitString& other) const
{
    string a = AbsString(digits);
    string b = AbsString(other.digits);

    string quotient = DivAbs(a, b);
    string product = MulAbs(quotient, b);
    string result = SubAbs(a, product);

    if (IsNegative(digits) && result != "0")
        result = "-" + result;

    return DigitString(result);
}

Fraction::DigitString
Fraction::DigitString::operator+() const
{
    return *this;
}

Fraction::DigitString
Fraction::DigitString::operator-() const
{
    if (digits == "0")
        return DigitString("0");

    return DigitString(IsNegative(digits)
        ? AbsString(digits) : "-" + digits);
}

bool Fraction::DigitString::operator==(const DigitString& other) const
{
    return digits == other.digits;
}

bool Fraction::DigitString::operator!=(const DigitString& other) const
{
    return !(*this == other);
}

bool Fraction::DigitString::operator<(const DigitString& other) const
{
    return CompareSigned(digits, other.digits) < 0;
}

bool Fraction::DigitString::operator>(const DigitString& other) const
{
    return other < *this;
}

bool Fraction::DigitString::operator<=(const DigitString& other) const
{
    return !(*this > other);
}

bool Fraction::DigitString::operator>=(const DigitString& other) const
{
    return !(*this < other);
}

Fraction::DigitString& Fraction::DigitString::operator++()
{
    *this = *this + DigitString("1");
    return *this;
}

Fraction::DigitString Fraction::DigitString::operator++(int)
{
    DigitString temp = *this;
    ++(*this);
    return temp;
}

Fraction::DigitString& Fraction::DigitString::operator--()
{
    *this = *this - DigitString("1");
    return *this;
}

Fraction::DigitString Fraction::DigitString::operator--(int)
{
    DigitString temp = *this;
    --(*this);
    return temp;
}

// =====================================================
// Реалізація класу Fraction
// =====================================================

Fraction::Fraction()
    : integerPart("0"), fractionalPart(0), negative(false)
{
}

Fraction::Fraction(string integer, unsigned short fraction)
    : integerPart("0"), fractionalPart(0), negative(false)
{
    Init(integer, fraction, false);
}

Fraction::Fraction(string integer, unsigned short fraction, bool sign)
    : integerPart("0"), fractionalPart(0), negative(false)
{
    Init(integer, fraction, sign);
}

string Fraction::GetIntegerPart() const
{
    return integerPart.toString();
}

unsigned short Fraction::GetFractionalPart() const
{
    return fractionalPart;
}

bool Fraction::GetNegative() const
{
    return negative;
}

bool Fraction::SetIntegerPart(string value)
{
    DigitString temp;

    if (!temp.Init(value) || temp < DigitString("0"))
        return false;

    integerPart = temp;

    if (integerPart == DigitString("0") && fractionalPart == 0)
        negative = false;

    return true;
}

bool Fraction::SetFractionalPart(unsigned short value)
{
    if (value > 99)
        return false;

    fractionalPart = value;

    if (integerPart == DigitString("0") && fractionalPart == 0)
        negative = false;

    return true;
}

bool Fraction::SetNegative(bool value)
{
    negative = value;

    if (integerPart == DigitString("0") && fractionalPart == 0)
        negative = false;

    return true;
}

bool Fraction::Init(string integer, unsigned short fraction, bool sign)
{
    return SetIntegerPart(integer) &&
        SetFractionalPart(fraction)
        && SetNegative(sign);
}

void Fraction::Read()
{
    string input;

    while (true)
    {
        cout << "Input a number (example: -12.45): ";
        cin >> input;

        size_t pos = input.find('.');

        if (pos == string::npos)
        {
            cout << "Use a decimal point, for example 12.45.\n";
            continue;
        }

        string integer = input.substr(0, pos);
        string fractionString = input.substr(pos + 1);

        if (fractionString.empty() || fractionString.size() > 2)
        {
            cout << "Use one or two decimal digits.\n";
            continue;
        }

        bool validFraction = true;

        for (char c : fractionString)
        {
            if (c < '0' || c > '9')
            {
                validFraction = false;
                break;
            }
        }

        if (!validFraction)
        {
            cout << "Invalid fractional part.\n";
            continue;
        }

        if (fractionString.size() == 1)
            fractionString += "0";

        unsigned short fraction =
            static_cast<unsigned short>(stoi(fractionString));

        if (Init(integer, fraction, false))
            return;

        cout << "Invalid value. Try again.\n";
    }
}

void Fraction::Display() const
{
    cout << toString();
}

string Fraction::toString() const
{
    stringstream sout;

    if (negative)
        sout << '-';

    sout << integerPart.toString()
        << '.'
        << setw(2) << setfill('0')
        << fractionalPart;

    return sout.str();
}

// Перетворення дробу на ціле число сотих
Fraction::DigitString Fraction::ToScaled(const Fraction& value)
{
    DigitString hundred("100");

    DigitString result =
        value.integerPart * hundred +
        DigitString(to_string(value.fractionalPart));

    if (value.negative && result != DigitString("0"))
        result = -result;

    return result;
}

// Перетворення цілих сотих на дріб
Fraction Fraction::FromScaled(DigitString value)
{
    bool sign = value < DigitString("0");

    if (sign)
        value = -value;

    DigitString integer = value / DigitString("100");
    DigitString fraction = value % DigitString("100");

    Fraction result;
    result.Init(
        integer.toString(),
        static_cast<unsigned short>(stoi(fraction.toString())),
        sign
    );

    return result;
}

Fraction Fraction::operator+(const Fraction& other) const
{
    return FromScaled(ToScaled(*this) + ToScaled(other));
}

Fraction Fraction::operator-(const Fraction& other) const
{
    return FromScaled(ToScaled(*this) - ToScaled(other));
}

Fraction Fraction::operator*(const Fraction& other) const
{
    DigitString product = ToScaled(*this) * ToScaled(other);
    DigitString result = product / DigitString("100");

    return FromScaled(result);
}

bool Fraction::operator==(const Fraction& other) const
{
    return ToScaled(*this) == ToScaled(other);
}

bool Fraction::operator!=(const Fraction& other) const
{
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const
{
    return ToScaled(*this) < ToScaled(other);
}

bool Fraction::operator>(const Fraction& other) const
{
    return other < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
    return !(*this > other);
}

bool Fraction::operator>=(const Fraction& other) const
{
    return !(*this < other);
}
