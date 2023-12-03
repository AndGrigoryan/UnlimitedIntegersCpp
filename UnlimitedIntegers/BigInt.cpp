#include "BigInt.h"

namespace MyInt
{
	//private
	BigInt* BigInt::MultiplyByDigit(short digit) const
	{
		std::string result = "";
		short carry = 0;

		for (int i = 0; i < this->digits.size() || carry; ++i)
		{
			if (i == result.size())
			{
				result.push_back('0');
			}

			short currentDigit;
			if (i < this->digits.size())
			{
				currentDigit = short(this->digits[i] - '0');
			}
			else
			{
				currentDigit = 0;
			}

			short product = currentDigit * digit + carry;
			carry = product / 10;
			result[i] = '0' + product % 10;
		}

		std::reverse(result.begin(), result.end());

		BigInt* tmp = new BigInt(result);

		return tmp;
	}

	void BigInt::MultiplyByPowerOf10(short power)
	{
		this->digits.insert(this->digits.begin(), power, '0');
	}

	bool BigInt::isZero() const
	{
		if (this->digits.size() == 1 && this->digits[0] == '0')
		{
			return true;
		}
		return false;
	}

	BigInt* BigInt::sumPositive(const BigInt& other) const
	{
		std::string result = "";

		int carry = 0;

		for (int i = 0; i < std::max(this->digits.size(), other.digits.size()) || carry; ++i)
		{
			if (i == result.size())
			{
				result.push_back('0');
			}


			int sum = carry;
			if (i < this->digits.size())
			{
				sum += int(this->digits[i] - '0');
			}
			if (i < other.digits.size())
			{
				sum += int(other.digits[i] - '0');
			}
			carry = sum / 10;
			result[i] = '0' + sum % 10;


		}

		std::reverse(result.begin(), result.end());

		BigInt* tmp = new BigInt(result);
		return tmp;
	}

	BigInt* BigInt::subtractPositive(const BigInt& other) const
	{
		std::string result = "";
		int borrow = 0;

		for (int i = 0; i < std::max(this->digits.size(), other.digits.size()) || borrow; ++i)
		{
			if (i == result.size())
			{
				result.push_back('0');
			}

			int diff = borrow;

			if (i < this->digits.size())
			{
				diff += int(this->digits[i] - '0');
			}
			if (i < other.digits.size())
			{
				diff -= int(other.digits[i] - '0');
			}

			if (diff < 0)
			{
				borrow = -1;
			}
			else
			{
				borrow = 0;
			}

			result[i] = (diff + 10) % 10 + '0';

		}

		while (result.size() > 1 && result.back() == '0')
		{
			result.pop_back();
		}

		std::reverse(result.begin(), result.end());

		BigInt* tmp = new BigInt(result);
		return tmp;
	}

	//public
	//constructor
	BigInt::BigInt(std::string num)
	{
		if (num[0] == '-')
		{
			this->isNegative = true;
			num = num.substr(1);
		}
		else
		{
			this->isNegative = false;
		}
		for (int i = num.size() - 1; i >= 0; --i)
		{
			this->digits.push_back(num[i]);
		}
	}

	BigInt& BigInt::operator=(const BigInt& other)
	{
		if (this != &other)
		{
			this->digits.clear();
			this->isNegative = other.isNegative;
			for (int i = 0; i < other.digits.size(); ++i)
			{
				this->digits.push_back(other.digits[i]);
			}
		}

		return *this;
	}

	bool BigInt::operator>=(const BigInt& other)
	{
		if (this->digits.size() > other.digits.size())
		{
			return true;
		}
		if (this->digits.size() == other.digits.size())
		{
			for (int i = this->digits.size() - 1; i >= 0; --i)
			{
				if (this->digits[i] < other.digits[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;

	}

	BigInt& BigInt::operator+(BigInt& other)
	{
		if (this->isNegative && other.isNegative)
		{
			//negative + negative = -(-negative + -negative)
			this->isNegative = false;
			other.isNegative = false;
			BigInt* result = sumPositive(other);
			result->isNegative = true;
			return *result;
		}
		else if (this->isNegative && !other.isNegative)
		{
			//negative + positive = positive - -negative
			this->isNegative = false;
			BigInt* result = &other.operator-(*this);
			return *result;

		}
		else if (!this->isNegative && other.isNegative)
		{
			//positive + negative = positive - positive
			other.isNegative = false;
			BigInt* result = &this->operator-(other);
			return *result;
		}
		else
		{
			return *sumPositive(other);
		}
	}

	BigInt& BigInt::operator+(int num)
	{
		std::string tmp = std::to_string(num);

		BigInt* other = new BigInt(tmp);

		BigInt* result = &this->operator+(*other);
		return *result;
	}

	BigInt& BigInt::operator-(BigInt& other)
	{
		if (this->isNegative && !other.isNegative)
		{
			// negative - positive = -(-negative + positive)
			this->isNegative = false;
			BigInt* result = &operator+(other);
			result->isNegative = true;
			return *result;
		}
		else if (!this->isNegative && other.isNegative)
		{
			//positive - negative = positive + -negative
			other.isNegative = false;
			BigInt* result = &operator+(other);
			result->isNegative = false;
			return *result;
		}
		else if (this->isNegative && other.isNegative)
		{
			//negative - negative = -(-negative + -negative)
			this->isNegative = false;
			other.isNegative = false;
			BigInt* result = &operator+(other);
			result->isNegative = true;
			return *result;
		}
		else if (!operator>=(other))
		{
			//positve - BigPositive = -(BigPositive - positve)
			BigInt* result = &other.operator-(*this);
			result->isNegative = true;
			return *result;
		}
		else
		{
			return *subtractPositive(other);
		}
	}

	BigInt& BigInt::operator-(int num)
	{
		std::string tmp = std::to_string(num);

		BigInt* other = new BigInt(tmp);

		BigInt* result = &this->operator-(*other);
		return *result;
	}

	BigInt& BigInt::operator*(const BigInt& other) const
	{
		BigInt* result = new BigInt("0");

		if (other.isZero() || this->isZero())
		{
			return *result;
		}

		for (int i = 0; i < other.digits.size(); ++i)
		{
			short digit = other.digits[i] - '0';
			BigInt* partialProduct = MultiplyByDigit(digit);
			partialProduct->MultiplyByPowerOf10(i);
			*result = *result + *partialProduct;
		}

		result->isNegative = this->isNegative ^ other.isNegative;

		return *result;

	}

	BigInt& BigInt::operator*(int num)
	{
		std::string tmp = std::to_string(num);

		BigInt* other = new BigInt(tmp);

		BigInt* result = &this->operator*(*other);
		return *result;
	}

	BigInt& BigInt::operator/(const BigInt& other)
	{
		if (other.isZero())
		{
			throw std::invalid_argument("Can't divide by zero.");
		}

		BigInt* result = new BigInt("0");

		if (this->isZero())
		{
			return *result;
		}

		BigInt divisor(other);

		result->isNegative = this->isNegative ^ other.isNegative;

		BigInt* tmp = new BigInt("1");

		while (*this >= divisor)
		{
			*this = *this - divisor;
			*result = *result + *tmp;
		}

		delete tmp;
		return *result;
	}

	BigInt& BigInt::operator/(int num)
	{
		std::string tmp = std::to_string(num);

		BigInt* other = new BigInt(tmp);

		BigInt* result = &this->operator/(*other);
		return *result;
	}

	std::ostream& operator<<(std::ostream& os, const BigInt& num)
	{
		if (num.isNegative)
		{
			os << '-';
		}
		for (int i = num.digits.size() - 1; i >= 0; i--)
		{
			os << num.digits[i];
		}
		return os;
	}
}
