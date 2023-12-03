#include "BigInt.h"


int main()
{

	MyInt::BigInt* num1 = new MyInt::BigInt("54");
	MyInt::BigInt* num2 = new MyInt::BigInt("0");

	try
	{
		MyInt::BigInt* num3 = &(*num1 - 3);
		std::cout << *num3 << std::endl;
		delete num3;
	}
	catch (const std::invalid_argument& e)	
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	delete num1;
	delete num2;

	return 0;
}