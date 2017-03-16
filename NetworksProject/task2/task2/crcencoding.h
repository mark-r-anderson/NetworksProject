#include <iostream>
#include <stdint.h>
#include <math.h>
#include <bitset>

class crcencoding
{
public:
	crcencoding();

	void SetMessage(uint32_t message) { fMessage = message; }
	void SetGenerator(uint32_t generator) { fGenerator = generator; }
	void SetCodeword(uint32_t codeword) { fCodeword = codeword;  }

	uint32_t generatorCRC();
	void verifierCRC();
	uint32_t alterCRC(uint32_t const bitnumber);

private:
	uint32_t GetRemainderCRC(uint32_t const message, uint32_t const generator);

	uint32_t fMessage;
	uint32_t fGenerator;
	uint32_t fCodeword;
};