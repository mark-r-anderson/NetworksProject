#include <iostream>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <bitset>

class crcencoding
{
public:
	crcencoding();

	//void SetMessage(uint32_t message) { fMessage = message; fMessages = {}; }
	//void SetCodeword(uint32_t codeword) { fCodeword = codeword; }

	void SetMessage(uint32_t message) { fMessages.push_back(message); }
	void SetMessage(std::string message) {
		for (char & c : message)
		{
			//std::cout << "One character: " << c << std::bitset<8>(c) << std::endl;
			fMessages.push_back(c);
		}
		std::cout << "Size: " << fMessages.size() << std::endl;
	}
	void SetGenerator(uint32_t generator) { fGenerator = generator; }
	void SetCodeword(uint32_t codeword, uint32_t index) {
		if (index < fCodewords.size()) { fCodewords[index] = codeword; }
	}

	uint32_t generatorCRC();
	void verifierCRC();
	uint32_t alterCRC(uint32_t const bitnumber, uint32_t const index = 0);

private:
	uint32_t GetRemainderCRC(uint32_t const message, uint32_t const generator);

	uint32_t fGenerator;

	std::vector<uint32_t> fMessages;
	std::vector<uint32_t> fCodewords;

	//uint32_t fMessage; //for a message specified as an interger or binary number
	//uint32_t fCodeword; //for a message specified as an interger or binary number
};