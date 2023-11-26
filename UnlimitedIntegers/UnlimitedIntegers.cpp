#include <iostream>
#include <vector>
#include <string>


class BigInt
{
private:
	std::vector<char> digits;


	BigInt* MultiplyByDigit(short digit) const
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

	void MultiplyByPowerOf10(short power)
	{
		this->digits.insert(this->digits.begin(), power, '0');
	}

public:
	//constructor
	BigInt(std::string num)
	{
		for (int i = num.size() - 1; i >= 0; --i)
		{
			this->digits.push_back(num[i]);
		}
	}

	void print() const
	{
		for (auto it = digits.rbegin(); it != digits.rend(); ++it)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
	}

	BigInt& operator=(const BigInt& other)
	{
		if (this != &other)
		{
			this->digits.clear();
			for (int i = 0; i < other.digits.size(); ++i)
			{
				this->digits.push_back(other.digits[i]);
			}
		}

		return *this;
	}

	BigInt& operator+(const BigInt& other) const
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

		return *tmp;
	}

	BigInt& operator-(const BigInt& other) const
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


		return *tmp;

	}

	BigInt& operator*(const BigInt& other)
	{
		BigInt* result = new BigInt("0");

		if (other.digits.size() == 1 && other.digits[0] == '0')
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

		return *result;

	}

};

int main()
{

	BigInt num1("22");
	BigInt num2("0");

	BigInt num3 = num1 * num2;

	num3.print();

	return 0;
}