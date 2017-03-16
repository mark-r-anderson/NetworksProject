#include"crcencoding.h"

int main(int argc, const char * argv[]) {
	uint8_t message = 0b00001001;
	uint8_t polynomial = 0b000111;

	crcencoding crc;

	crc.SetMessage(message);
	crc.SetGenerator(polynomial);
	uint8_t codeword = crc.generatorCRC();

	//std::cout << std::bitset<8>(codeword) << std::endl;

	//crc.SetCodeword(codeword);
	crc.verifierCRC();

	crc.alterCRC(1);
	crc.verifierCRC();

	system("pause");

	return 0;
}