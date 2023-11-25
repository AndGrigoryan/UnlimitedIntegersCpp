#include <iostream>
#include <vector>
#include <string>


class INumber
{
public:
	virtual void print() const = 0;
	virtual INumber* operator+(const INumber& other) const = 0;
};

class BigInt : public INumber 
{
private:
    std::vector<char> digits;

public:
	BigInt(std::string num)
	{
		for (int i = num.size() - 1; i >= 0; --i)
		{
			this->digits.push_back(num[i]);
		}
	}

	void print() const override
	{
		for (auto it = digits.rbegin(); it != digits.rend(); ++it)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
	}



	INumber* operator+(const INumber& other) const override
	{
		const BigInt& otherBigInt = dynamic_cast<const BigInt&>(other);
		std::string result = "";

		int carry = 0;

		for (int i = 0; i < std::max(this->digits.size(), otherBigInt.digits.size()) || carry; ++i)
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
			if (i < otherBigInt.digits.size())
			{
				sum += int(otherBigInt.digits[i] - '0');
			}
			carry = sum / 10;
			result[i] = '0' + sum % 10;

			
		}

		std::reverse(result.begin(), result.end());

		INumber* tmp = new BigInt(result);

		return tmp;
	}
};

int main()
{

	INumber* num1 = new BigInt("9999");
	INumber* num2 = new BigInt("2006");          

	INumber* num3 = *num1 + *num2;

	num1->print();
	num2->print();
	num3->print();


	delete num1;
	delete num2;
	delete num3;

	return 0;
}