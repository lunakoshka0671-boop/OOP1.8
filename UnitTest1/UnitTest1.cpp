
#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP1.8/Fraction.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Variant25Tests
{
    TEST_CLASS(FractionTests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Fraction a;

            Assert::AreEqual(string("0.00"), a.toString());
        }

        TEST_METHOD(TestConstructorAndInit)
        {
            Fraction a("12", 5);

            Assert::AreEqual(string("12.05"), a.toString());

            Fraction b;
            Assert::IsTrue(b.Init("3", 50, false));
            Assert::AreEqual(string("3.50"), b.toString());
        }

        TEST_METHOD(TestNegativeFraction)
        {
            Fraction a("-12", 45, false);

            Assert::AreEqual(string("-12.45"), a.toString());
        }

        TEST_METHOD(TestInvalidInit)
        {
            Fraction a("5", 25);

            Assert::IsFalse(a.Init("abc", 25, false));
            Assert::AreEqual(string("5.25"), a.toString());

            Assert::IsFalse(a.Init("5", 100, false));
            Assert::AreEqual(string("5.25"), a.toString());
        }

        TEST_METHOD(TestSettersAndGetters)
        {
            Fraction a;

            Assert::IsTrue(a.SetIntegerPart("15"));
            Assert::IsTrue(a.SetFractionalPart(25));
            Assert::IsTrue(a.SetNegative(true));

            Assert::AreEqual(string("15"), a.GetIntegerPart());
            Assert::AreEqual((unsigned short)25, a.GetFractionalPart());
            Assert::IsTrue(a.GetNegative());
            Assert::AreEqual(string("-15.25"), a.toString());

            Assert::IsFalse(a.SetIntegerPart("-2"));
            Assert::IsFalse(a.SetFractionalPart(100));
        }

        TEST_METHOD(TestAddition)
        {
            Fraction a("1", 75);
            Fraction b("0", 50);

            Assert::AreEqual(string("2.25"), (a + b).toString());
        }

        TEST_METHOD(TestSubtraction)
        {
            Fraction a("1", 25);
            Fraction b("2", 50);

            Assert::AreEqual(string("-1.25"), (a - b).toString());
        }

        TEST_METHOD(TestMultiplication)
        {
            Fraction a("2", 50);
            Fraction b("2", 0);

            Assert::AreEqual(string("5.00"), (a * b).toString());
        }

        TEST_METHOD(TestNegativeArithmetic)
        {
            Fraction a("-1", 50);
            Fraction b("0", 50);

            Assert::AreEqual(string("-1.00"), (a - b).toString());
            Assert::AreEqual(string("-0.75"), (a + b).toString());
        }

        TEST_METHOD(TestComparison)
        {
            Fraction a("3", 50);
            Fraction b("2", 75);

            Assert::IsTrue(a > b);
            Assert::IsTrue(b < a);
            Assert::IsTrue(a != b);
            Assert::IsTrue(a == Fraction("3", 50));
            Assert::IsTrue(a >= b);
            Assert::IsTrue(b <= a);
        }

        TEST_METHOD(TestZeroSign)
        {
            Fraction a("0", 0, true);

            Assert::AreEqual(string("0.00"), a.toString());
            Assert::IsFalse(a.GetNegative());
        }

        TEST_METHOD(TestLargeNumbers)
        {
            Fraction a("12345678901234567890", 25);
            Fraction b("10", 50);

            Assert::AreEqual(
                string("12345678901234567900.75"),
                (a + b).toString()
            );
        }
    };
}
