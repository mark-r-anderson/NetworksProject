//
//  main.cpp
//  NetworksProject
//
//  Created by Patrick Dang-Ho on 2017-03-12.
//  Copyright © 2017 Patrick Dang-Ho. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <vector>

using namespace std;

// Array of all potential characters of a character sequence
static const char alphanum[] =
		"!\"#$%&\'()*+,-./0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
// Destination IP Address and PORT
static const string DESTINATION_IP = "1922332142";
static const string PORT = "883";
// Delimiter for the final output
static const char DELIMITER = '-';
// Strings to save for easy delimiter final output
string originalMessage, applicationHeader, presentationHeader, sessionHeader,
	transportHeader, networkHeader, dataLinkHeader;

// Converts a string to its bit sequence representation
string getBits (string message, int size) {
	string bitSequence;

	for (int i = 0; i < size; i++) {
		bitset<8>bits(message[i]);
		bitSequence += bits.to_string();
	}

	return bitSequence;
}

// Randomly generate a character sequence of length sequenceLength
string generateRandomCharacterSequence(int sequenceLength) {
	string sequence;

	for (int i = 0; i < sequenceLength; i++) {
		sequence = sequence + alphanum[rand() % sizeof(alphanum) - 1];
	}

	return sequence;
}

// Physical Layer processing - outputting the message as a bit sequence
// and bit sequence with delimiter
void toPhysicalLayer(string* message, int size) {
	if (!message->empty()) {
		string bitSequence = getBits(*message, size);

		// Final bit sequence message
		cout << "Final Message (size = " << size << ", bit sequence length = "
				<< bitSequence.length() << ")" << endl;
		cout << bitSequence << endl;

		// Final bit sequence message with delimiter
		cout << "Final Message with delimiter \'" << DELIMITER << "\'" << endl;
		cout <<	getBits(dataLinkHeader, dataLinkHeader.length()) << DELIMITER <<
				getBits(networkHeader, networkHeader.length()) << DELIMITER <<
				getBits(transportHeader, transportHeader.length()) << DELIMITER <<
				getBits(sessionHeader, sessionHeader.length()) << DELIMITER <<
				getBits(presentationHeader, presentationHeader.length()) << DELIMITER <<
				getBits(applicationHeader, applicationHeader.length()) << DELIMITER <<
				getBits(originalMessage, originalMessage.length()) << DELIMITER <<
				getBits(DESTINATION_IP, DESTINATION_IP.length()) << DELIMITER <<
				getBits(PORT, PORT.length()) << endl;
	}
}

// Add Data Link Layer header (header size = 8)
void addDataLinkLayerHeader(string* message, int size) {
	int dataLinkHeaderLength = 8;

	if (!message->empty()) {
		dataLinkHeader = generateRandomCharacterSequence(dataLinkHeaderLength);
		*message = dataLinkHeader + *message;
		size += dataLinkHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Data Link layer header applied (size = " << size << "):\n" << *message << endl;
		toPhysicalLayer(message, size);
	}
}

// Add Network Layer header (header size = 16) AND append the destination
// IP address and Port
void addNetworkLayerHeader(string* message, int size) {
	int networkHeaderLength = 16;

	if (!message->empty()) {
		networkHeader = generateRandomCharacterSequence(networkHeaderLength);
		*message = networkHeader + *message + DESTINATION_IP + PORT;
		size += networkHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Network layer header applied (size = " << size << "):\n" << *message << endl;
		addDataLinkLayerHeader(message, size);
	}
}

// Add Transport Layer header (header size = 32)
void addTransportLayerHeader(string* message, int size) {
	int transportHeaderLength = 32;

	if (!message->empty()) {
		transportHeader = generateRandomCharacterSequence(transportHeaderLength);
		*message = transportHeader + *message;
		size += transportHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Transport layer header applied (size = " << size << "):\n" << *message << endl;
		addNetworkLayerHeader(message, size);
	}
}

// Add Session Layer header (header size = 48)
void addSessionLayerHeader(string* message, int size) {
	int sessionHeaderLength = 48;

	if (!message->empty()) {
		sessionHeader = generateRandomCharacterSequence(sessionHeaderLength);
		*message = sessionHeader + *message;
		size += sessionHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Session layer header applied (size = " << size << "):\n" << *message << endl;
		addTransportLayerHeader(message, size);
	}
}

// Add Presentation Layer header (header size = 52)
void addPresentationLayerHeader(string* message, int size) {
	int presentationHeaderLength = 52;

	if (!message->empty()) {
		presentationHeader = generateRandomCharacterSequence(presentationHeaderLength);
		*message = presentationHeader + *message;
		size += presentationHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Presentation layer header applied (size = " << size << "):\n" << *message << endl;
		addSessionLayerHeader(message, size);
	}
}

// Add Application Layer header (header size = 64)
void addApplicationLayerHeader(string* message, int size) {
	int applicationHeaderLength = 64;

	if (!message->empty()) {
		applicationHeader = generateRandomCharacterSequence(applicationHeaderLength);
		*message = applicationHeader + *message;
		size += applicationHeaderLength;
		// Output message sequence after adding header
		cout << "Message after Application layer header applied (size = " << size << "):\n" << *message << endl;
		addPresentationLayerHeader(message, size);
	}
}

int main(int argc, const char* argv[]) {
	// Check if there is only one argument provided to the program
	if (argc != 2) {
		cout << "Error: Input to the program is ONE application message (up to 80 characters)" << endl;
		return -1;
	}
	string message(argv[1]);

	// Check the length of the message to be up to 80 characters long
	if (message.length() > 80) {
		cout << "Error: Application message too long (up to 80 characters)" << endl;
		return -1;
	}
	originalMessage = message;

	// Begin layered architecture workflow
	addApplicationLayerHeader(&message, message.length());

  return 0;
}
