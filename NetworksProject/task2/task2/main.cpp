#include"crcencoding.h"

int main(int argc, const char * argv[]) {
	crcencoding crc; //initialize crc object
	
	bool cond; //ensure that the user entered the correct type
	uint32_t r; //cast the character of an ASCII string to an integer r
	std::bitset<32> binarymessage; //used to cast input as a binary to the message

	uint32_t message = 0b01001001; //default message
	uint32_t polynomial = 0b00000111; //default polynomial
	uint32_t biterror = 1; //default bit error

	std::string messagestr = "a";
	std::string temp;
	
	crc.SetMessage(message); //set the message to the default in case the user does not specify
	crc.SetGenerator(polynomial); //set the polynomial to the default is the user does not specify

	/*
	Prompt the user for inputs for the message, polynomial, and bit error in that order
	Can skip the inputs and use a set of default parameters
	*/

	std::cout << "Enter \"a\" to type your message as ASCII" << std::endl;
	std::cout << "Enter \"b\" to type your message in binary" << std::endl;
	std::cout << "Enter \"h\" to type your message in hexidecimal" << std::endl;
	std::cout << "Enter \"o\" to type your message in octal" << std::endl;
	std::cout << "Enter \"d\" (or anything else) to type your message in decimal" << std::endl;
	std::cout << "Hit enter twice to use defaults that are already defined in the main class." << std::endl;
	getline(std::cin, temp); //get the user input
	if ( temp.empty() ) { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); } //if empty line (i.e. "enter", use default)
	else
	{
		if (temp == "a")
		{
			/*
			Message
			*/
			std::cout << "Please enter a message to be sent: ";
			std::cin >> messagestr;
			for (char & c : messagestr) {
				r = c;
				std::cout << "Message:\t\t" << std::bitset<32>(r) << std::endl;
			}
			crc.SetMessage(messagestr);
		}
		else
		{
			/*
			Message
			Can be binary, hexidecimal, octal, or decimal inputs
			*/

			std::cout << "Please enter a message to be sent: ";
			do
			{
				if (temp == "b") { std::cin >> binarymessage; message = binarymessage.to_ulong(); }
				else if (temp == "h") { std::cin >> std::hex >> message; }
				else if (temp == "o") { std::cin >> std::oct >> message; }
				else { std::cin >> message; }

				cond = std::cin.fail();
				if (cond) { std::cout << "Please use a valid entry, as selected above: "; }
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			} while (cond);
			std::cout << "Message:\t\t" << std::bitset<32>(message) << std::endl;
			crc.SetMessage(message); //set the message

			/*
			Generator Polynomial
			Can be binary, hexidecimal, octal, or decimal inputs
			*/

			std::cout << "Please enter a generator polynomial: ";
			do
			{
				if (temp == "b") { std::cin >> binarymessage; polynomial = binarymessage.to_ulong(); }
				else if (temp == "h") { std::cin >> std::hex >> polynomial; }
				else if (temp == "o") { std::cin >> std::oct >> polynomial; }
				else { std::cin >> polynomial; }

				cond = std::cin.fail();
				if (cond) { std::cout << "Please use a valid entry, as selected above: "; }
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			} while (cond);
			std::cout << "Polynomial:\t\t" << std::bitset<32>(polynomial) << std::endl;
			crc.SetGenerator(polynomial); //set the generator polynomial
		}

		/*
		Bit error
		Must be a decimal input
		*/

		std::cout << "Please enter the bit at which you want to cause an error: ";
		do
		{
			std::cin >> biterror;
			cond = std::cin.fail();
			if (cond) { std::cout << "The bit error must be specified with an integer. Please use a valid entry: "; }
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		} while (cond);
	}
	std::cout << std::endl;
	
	/*
	Run the generator and then the verifier
	*/

	crc.generatorCRC(); //generate the codeword; stored in the object
	crc.verifierCRC(); //verify the codeword that is stored in the object

	std::string codeword = crc.GetCodeword(); //retrieve the codeword in ASCII, if desired

	/*
	Run the alter program and then the verifier
	*/

	crc.alterCRC(biterror); //alter a bit in the codeword
	crc.verifierCRC(); //run the verifier on the altered codeword; should produce an error

	system("pause");

	return 0;
}