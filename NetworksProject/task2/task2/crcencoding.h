#include <iostream>
#include <stdint.h>
#include <math.h>
#include <bitset>

class crcencoding
{
public:
	crcencoding();

	void SetMessage(uint8_t message) { fMessage = message; }
	void SetGenerator(uint8_t generator) { fGenerator = generator; }
	void SetCodeword(uint8_t codeword) { fCodeword = codeword;  }

	uint8_t generatorCRC();
	void verifierCRC();
	uint8_t alterCRC(uint8_t const bitnumber);

private:
	uint8_t GetRemainderCRC(uint8_t const message, uint8_t const generator);

	uint8_t fMessage;
	uint8_t fGenerator;
	uint8_t fCodeword;
};