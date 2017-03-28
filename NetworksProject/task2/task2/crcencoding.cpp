#include"crcencoding.h"

crcencoding::crcencoding()
{
	fGenerator = 0;
	fMessages = {};
	fCodewords = {};
}

uint32_t crcencoding::generatorCRC()
{
	//generator polynomial degree
	uint32_t gendeg = (int)log2(fGenerator);
	//codeword to be output
	uint32_t codeword;
	//obtain the remainder of the generator divided into the codeword
	uint32_t remainder;

	for (size_t i = 0; i < fMessages.size(); i++)
	{
		//initially just the message shifted by the generator polynomial degree
		codeword = (fMessages[i] << gendeg);
		//obtain the remainder of the generator divided into the codeword
		remainder = computeRemainderCRC(codeword, fGenerator);
		//binary subtract the calculated remainder from the codeword
		codeword ^= remainder;
		//append the codeword to the list of codewords
		fCodewords.push_back(codeword);

		//std::cout << "Codeword:  " << std::bitset<16>(codeword) << std::endl;
	}

	//return the last codeword in the list
	return codeword;
}

void crcencoding::verifierCRC()
{
	std::cout << "Running verifier..." << std::endl;
	bool condErr = false;
	int iErr = -2;

	for (size_t i = 0; i < fMessages.size(); i++)
	{
		//generator polynomial degree
		uint32_t gendeg = (int)log2(fGenerator);
		//obtain the remainder from the codeword and generator polynomial
		uint32_t verification = computeRemainderCRC(fCodewords[i], fGenerator);
		//check whether or not the remainder is zero
		if (verification) { condErr = true; iErr = i; }
		
	}

	if (condErr)
	{//if the remainder is nonzero, an error has occured in the bit stream
		if (fMessages.size() == 1)
		{
			std::cout << "The bit stream contains an error. Please retransmit." << std::endl << std::endl;
		}
		else
		{
			std::cout << "The bit stream contains an error at bytre" << iErr+1 << ". Please retransmit." << std::endl << std::endl;
		}

	}
	else
	{//if the remainder is zero, the message was transmitted with no detectable errors
		std::cout << "The bit stream was transmitted with no detectable errors." << std::endl << std::endl;
	}
}

uint32_t crcencoding::alterCRC(uint32_t const bitnumber, uint32_t index)
{
	if (index < fCodewords.size()) {
		//placement of the bit error
		uint32_t codewordbits = (int)log2(fCodewords[index]) + 1;
		uint32_t biterror = 1 << (codewordbits - bitnumber);

		//XOR the message with the bit error to flip the desired bit and create an incorrect bit stream
		fCodewords[index] ^= biterror;

		std::cout << "Bit error: " << std::bitset<32>(biterror) << std::endl;
		std::cout << "Codeword:  " << std::bitset<32>(fCodewords[index]) << std::endl << std::endl;

		return fCodewords[index];
	}
	else {
		std::cout << "Invalid index. Please use an index within range." << std::endl;
		return 0;
	}
}

uint32_t crcencoding::computeRemainderCRC(uint32_t const dividend, uint32_t const generator)
{
	uint32_t rcq; //Shift register and output contents

	int gendeg = (int)log2(generator); //generator degree
	int mesbits = (int)log2(dividend); //message degree; used to indicate the most significant bit

	int sizedif = mesbits - gendeg;

	rcq = dividend;

	for (int i = 0; i <= sizedif; i++)
	{
		//If the output of the shift register is 1, the contents of the required shift registers must be XOR
		//If the output of the shift register is 0, the contents must also be XOR, but this will just produce the same string, so the if statement must be skipped
		if ((rcq >> (mesbits - i)) == 1)
		{
			//XOR the previous remainder with the divisor.
			rcq ^= generator << (sizedif - i); //the i shifts the generator to the right by 1 bit on every loop

			//COULD ADD IF STATEMENT HERE TO BREAK LOOP EARLY
		}
	}

	//std::cout << "Remainder: " << std::bitset<8>(rcq) << std::endl << std::endl;

	return rcq;
}