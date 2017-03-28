#include"crcencoding.h"

int main(int argc, const char * argv[]) {
	crcencoding crc; //initialize crc object
	
	bool cond;
	uint32_t r;

	uint32_t message = 0b00001001;
	uint32_t polynomial = 0b0000111;
	uint32_t biterror = 1;

	std::string messagestr = "a";
	std::string polynomialstr;
	std::string temp;
	
	crc.SetMessage(message); //set the message to the default in case the user does not specify

	/*
	Prompt the user for inputs for the message, polynomial, and bit error in that order
	*/

	std::cout << "Enter \"a\" to type your message as ASCII" << std::endl;
	std::cout << "Enter \"b\" to type your message as binary" << std::endl;
	std::cout << "(Hit enter twice to use defaults that are already defined in the main class.)" << std::endl;
	getline(std::cin, temp); //get the user input
	if (temp.empty()) { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); } //if empty line (i.e. "enter", use default)
	else
	{
		/*
		Message
		*/
		std::cout << "Please enter a message to be sent." << std::endl;
		if (temp == "a")
		{
			std::cin >> messagestr;
			for (char & c : messagestr) {
				r = c;
				std::cout << "Message:    " << std::bitset<32>(r) << std::endl;
			}
			crc.SetMessage(messagestr);
		}
		//COULD RESTRUCTURE THIS LOOP BETTER...
		else if (temp == "b") 
		{
			do
			{
				std::cin >> message;
				cond = std::cin.fail();
				if (cond) { std::cout << "The message must be specified in binary representation. Please enter a valid number: " << std::endl; }
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			} while (cond);
			std::cout << "Message:    " << std::bitset<32>(message) << std::endl;
			crc.SetMessage(message);
		}
		//else if (temp == "h") {}
		else
		{
			do
			{
				std::cin >> message;
				cond = std::cin.fail();
				if (cond) { std::cout << "The message must be specified as a number. Please enter a valid number: " << std::endl; }
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			} while (cond);
			std::cout << "Message:    " << std::bitset<32>(message) << std::endl;
			crc.SetMessage(message);
		}
		
		/*
		Generator Polynomial
		*/
		std::cout << "Please enter a generator polynomial: " << std::endl;
		do
		{
			std::cin >> polynomial;
			cond = std::cin.fail();
			if (cond) { std::cout << "The generator polynomial must be specified with a number or binary representation. Please enter a valid number: " << std::endl; }
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		} while (cond);
		std::cout << "Polynomial: " << std::bitset<32>(polynomial) << std::endl;

		/*
		Bit error
		*/
		std::cout << "Please enter the bit at which you want to cause an error: " << std::endl;
		do
		{
			std::cin >> biterror;
			cond = std::cin.fail();
			if (cond) { std::cout << "The bit error must be specified with a number or binary representation. Please enter a valid number: " << std::endl; }
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		} while (cond);
	}
	
	/*
	Run the generator, verifier, alterer, and verifier in that order
	*/

	crc.SetGenerator(polynomial); //set the generator polynomial

	uint32_t codeword = crc.generatorCRC(); //generate the codeword; also saves it within the class
	
	crc.verifierCRC(); //verify the codeword that is stored in the class

	crc.alterCRC(biterror); //alter a bit in the codeword
	crc.verifierCRC(); //run the verifier on the altered codeword; should produce an error

	system("pause");

	return 0;
}