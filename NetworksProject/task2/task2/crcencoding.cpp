#include"crcencoding.h"

crcencoding::crcencoding()
{
	fMessage = 0;
	fGenerator = 0;
	fCodeword = 0;
}

uint32_t crcencoding::generatorCRC()
{
	//generator polynomial degree
	uint32_t gendeg = (int)log2(fGenerator);

	//codeword to be output; initially just the message shifted by the generator polynomial degree
	uint32_t codeword = (fMessage << gendeg);

	//obtain the remainder of the gnerator divided into the codeword
	uint32_t remainder = GetRemainderCRC(codeword, fGenerator);

	//binary subtract the calculated remainder from the codeword
	codeword ^= remainder;

	std::cout << "Codeword:  " << std::bitset<8>(codeword) << std::endl;

	fCodeword = codeword;

	//return the codeword
	return codeword;
}

void crcencoding::verifierCRC()
{
	//generator polynomial degree
	uint32_t gendeg = (int)log2(fGenerator);

	//obtain the remainder from the codeword and generator polynomial
	uint32_t verification = GetRemainderCRC(fCodeword, fGenerator);

	//check whether or not the remainder is zero
	if (verification)
	{//if the remainder is nonzero, an error has occured in the bit stream
		std::cout << "The bit stream contains an error. Please retransmit." << std::endl << std::endl;
	}
	else
	{//if the remainder is zero, the message was transmitted with no detectable errors
		std::cout << "The bit stream was transmitted with no detectable errors." << std::endl << std::endl;
	}
}

uint32_t crcencoding::alterCRC(uint32_t const bitnumber)
{
	//placement of the bit error
	uint32_t codewordbits = (int)log2(fCodeword) + 1;
	uint32_t biterror = 1 << (codewordbits - bitnumber);

	//XOR the message with the bit error to flip the desired bit and create an incorrect bit stream
	fCodeword ^= biterror;

	std::cout << "Bit error: " << std::bitset<8>(biterror) << std::endl;
	std::cout << "Codeword:  " << std::bitset<8>(fCodeword) << std::endl << std::endl;

	return fCodeword;
}

uint32_t crcencoding::GetRemainderCRC(uint32_t const dividend, uint32_t const generator)
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

	std::cout << "Remainder: " << std::bitset<8>(rcq) << std::endl << std::endl;

	return rcq;
}