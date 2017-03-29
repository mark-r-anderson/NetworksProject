#include <iostream>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <bitset>
#include <iomanip>

class crcencoding
{
public:
	crcencoding();

	/*
	Setters
	*/

	void SetMessage(uint32_t message) { 
		fMessages = {};
		fMessages.push_back(message);
	}
	void SetMessage(std::string message) {
		fMessages = {};
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

	/*
	Getters
	*/

	std::vector<uint32_t> GetCodewords() { return fCodewords; }
	
	std::string GetCodeword() {
		char W;
		std::string longcodeword;
		for (size_t i=0; i < fCodewords.size(); i++)
		{
			for (size_t j = 4; j > 0; j--)
			{
				W = static_cast<char>(fCodewords[i] >> (8 * (j-1)));
				longcodeword.append(1, W);
				//std::cout << std::bitset<8>(fCodewords[i] >> (8 * (j-1))) << " - " << W << std::endl;
			}
		}
		//std::cout << longcodeword << std::endl;
		return longcodeword;
	}

	void generatorCRC();
	void verifierCRC();
	uint32_t alterCRC(uint32_t const bitnumber, uint32_t const index = 0);

private:
	uint32_t computeRemainderCRC(uint32_t const message, uint32_t const generator); /// Compute the remainder

	uint32_t fGenerator; /// Generator polynomial

	std::vector<uint32_t> fMessages; /// Vector to store the message(s) in, depending on the format entered
	std::vector<uint32_t> fCodewords; /// Vector to store the computed codeword(s) in, depending on the format entered
};