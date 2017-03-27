#include"crcencoding.h"

int main(int argc, const char * argv[]) {
	bool cond;
	uint32_t r;

	uint32_t message = 0b00001001;
	uint32_t polynomial = 0b000111;
	uint32_t biterror = 1;

	std::string messagestr = "abc";
	std::string polynomialstr = "";
	std::string temp;
	
	//MESSAGE DEFAULTS TO ASCII, NOT GOOD!!!
	//KEEP LOOPING THROUGH TRY UNTIL VALID INTEGER IS ENTERED

	std::cout << "Please enter a message to be sent. Hit enter twice to use defaults that are already defined in the main class: " << std::endl;
	getline(std::cin, temp); //get the user input
	if (temp.empty()) { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); } //if empty line (i.e. "enter", use default)
	else {
		messagestr = temp;

		for (char & c : messagestr) {
			r = c;
			std::cout << "Message:    " << std::bitset<32>(r) << std::endl;
		}

		std::cout << "Please enter a generator polynomial: " << std::endl;
		do
		{
			std::cin >> polynomial;
			cond = std::cin.fail();
			if (cond) { std::cout << "The generator polynomial must be specified with a number or binary representation. Please enter a valid number: " << std::endl; }
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

		} while (cond);
			
		//getline(std::cin, temp); //get the user input
		//try { polynomial = stoi(temp); cond = true; }
		//catch (...) { std::cout << "The generator polynomial must be specified with a number or binary representation. Please enter a valid number." << std::endl; }
		//std::cout << "Polynomial: " << std::bitset<32>(polynomial) << std::endl;		

		std::cout << "Please enter the bit at which you want to cause an error: " << std::endl;
		
		//getline(std::cin, temp); //get the user input
		//try { biterror = stoi(temp); }
		//catch (...) { std::cout << "The bit error must be specified with a number or binary representation. Please enter a valid number." << std::endl; }
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
	if (std::cin.fail()) {
	std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
	std::cout << "Expected a number. However, you can enter an ASCII string here: " << std::endl;
	std::cin >> messagestr;
	if (std::cin.fail()) {
	std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
	}
	}
	*/
	//std::cin >> messagestr;

	/*
	do
	{
		std::cout << "Please enter a generator polynomial. Hit enter to use default: " << std::endl;
		std::cin >> polynomial;

		getline(std::cin, temp);

		if (temp.empty() || ) { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); } //if empty line (i.e. "enter", use default)

		cond = std::cin.fail();

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

	} while (cond);
	*/

	crcencoding crc;

	crc.SetMessage(messagestr);
	//crc.SetMessage(message); //set the message
	crc.SetGenerator(polynomial); //set the generator polynomial

	//SHOULD RETURN THE LIST OF CODEWORDS TO LOOP THROUGH
	uint32_t codeword = crc.generatorCRC(); //generate the codeword; also saves it within the class
	
	crc.verifierCRC(); //verify the codeword that is stored in the class

	crc.alterCRC(biterror); //alter a bit in the codeword
	crc.verifierCRC(); //run the verifier on the altered codeword; should produce an error

	system("pause");

	return 0;
}