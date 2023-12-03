#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


namespace MyInt
{
	class BigInt
	{
	private:
		std::vector<char> digits;
		bool isNegative;

		BigInt* MultiplyByDigit(short digit) const;

		void MultiplyByPowerOf10(short power);

		bool isZero() const;

		BigInt* sumPositive(const BigInt& other) const;

		BigInt* subtractPositive(const BigInt& other) const;

	public:
		//constructor
		BigInt(std::string num);

		friend std::ostream& operator<<(std::ostream& os, const BigInt& num);

		BigInt& operator=(const BigInt& other);

		bool operator>=(const BigInt& other);

		BigInt& operator+(BigInt& other);

		BigInt& operator+(int num);

		BigInt& operator-(BigInt& other);

		BigInt& operator-(int num);

		BigInt& operator*(const BigInt& other) const;

		BigInt& operator*(int num);

		BigInt& operator/(const BigInt& other);

		BigInt& operator/(int num);

	};
};

namespace MyInt {
	std::ostream& operator<<(std::ostream& os, const BigInt& num);
}