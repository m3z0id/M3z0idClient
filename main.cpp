#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "clip/clip.h"
#include "mode.h"
#include <string>
#include <random>
#include <ctime>
using namespace std;

int mode;
int numberToConvert;
bool randomZeroes = false;

void help(char* exec) {
	cout << "Usage: " << exec << " [--random-zeroes] <number> [1/69/random/subtract/add]\n";
	cout << "Usage: " << exec << " [--random-zeroes] <number> [set] <number1>...\n";
}

int randomNumber(int min, int max) {
	std::random_device dev;
	mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> number(min, max);
	return number(rng);
}

bool randomZero() {
	return randomNumber(1, 4) == 1;
}

int parseCommand(int argc, char* argv[], int& numberToConvert, int& mode, bool& randomZeroes) {
	if (argc < 3) {
		help(argv[0]);
		return -1;
	}

	int argIndex = 1;

	if (strcmp(argv[1], "--random-zeroes") == 0) {
		randomZeroes = true;
		argIndex++;
	}

	if (argIndex >= argc - 1) {
		help(argv[0]);
		return -1;
	}

	try {
		numberToConvert = stoi(argv[argIndex]);
		argIndex++;
	}
	catch (const std::invalid_argument&) {
		help(argv[0]);
		return -1;
	}
	catch (const std::out_of_range&) {
		help(argv[0]);
		return -1;
	}

	// Parse the mode based on the next argument
	if (strcmp(argv[argIndex], "1") == 0) mode = ONES;
	else if (strcmp(argv[argIndex], "69") == 0) mode = SIXTYNINES;
	else if (strcmp(argv[argIndex], "random") == 0) mode = RANDOM;
	else if (strcmp(argv[argIndex], "set") == 0) mode = SET;
	else if (strcmp(argv[argIndex], "subtract") == 0) mode = SUBTRACT;
	else if (strcmp(argv[argIndex], "add") == 0) mode = ADD;
	else {
		help(argv[0]);
		return -1;
	}

	return 0;
}

string ones(int input, bool randomZeroes) {
	cout << "ones with number " << to_string(input) << "\n";
	string output = "";
	while (input > 0) {
		output += "1+";
		if (randomZeroes && randomZero()) output += "0+";
		input--;
	}
	return output;
}

string sixtynines(int input, bool randomZeroes) {
	string output = "";
	bool evenOnStart = !(input % 2);
	while (input > 0) {
		if (evenOnStart && input % 2 == 0) output += "69^0+";
		else if (!evenOnStart && input % 2 == 1) output += "69^0+";
		else output += "420^0+";
		if (randomZeroes && randomZero()) output += "0+";
		input--;
	}
	return output;
}

string random(int input, bool randomZeroes) {
	string output = "";
	while (input > 0) {
		output += to_string(randomNumber(randomZeroes ? 0 : 1, 5001)) + "^0+";
		if (randomZeroes && randomZero()) output += "0+";
		input--;
	}
	return output;
}

string set(int input, bool randomZeroes, int argc, char* argv[]) {
	string output = "";
	int i = randomZeroes ? 4 : 3;
	if ((argc - i) > input) {
		cout << "WARNING: Not all numbers will be used!\n";
	}
	while (input > 0) {
		if (i < argc) {
			output += argv[i];
			output += "^0+";
			if (randomZeroes && randomZero()) output += "0+";
			input--;
			i++;
		}
		else {
			i = randomZeroes ? 4 : 3;
		}
	}
	return output;
}

string subtract(int input, bool randomZeroes) {
	string output = "";
	int initialVal = randomNumber(input + 1, 5001);
	output += to_string(initialVal) + "-";

	int toSubtract = initialVal - input;
	while (toSubtract > 0) {
		int currentValue = randomNumber(randomZeroes ? 0 : 1, toSubtract);
		output += to_string(currentValue) + "-";
		if (randomZeroes && randomZero()) output += "0-";
		toSubtract -= currentValue;
	}
	return output;
}

string add(int input, bool randomZeroes) {
	string output = "";
	while (input > 0) {
		int randnum = randomNumber(randomZeroes ? 0 : 1, input);
		output += to_string(randnum) + "+";
		if (randomZeroes && randomZero()) output += "0+";
		input -= randnum;
	}
	return output;
}

int main(int argc, char* argv[]) {
	string output = "";
	if (parseCommand(argc, argv, numberToConvert, mode, randomZeroes) == -1) return -1;

	switch (mode) {
	case ONES:
		output = ones(numberToConvert, randomZeroes);
		break;
	case SIXTYNINES:
		output = sixtynines(numberToConvert, randomZeroes);
		break;
	case RANDOM:
		output = random(numberToConvert, randomZeroes);
		break;
	case SET:
		output = set(numberToConvert, randomZeroes, argc, argv);
		break;
	case SUBTRACT:
		output = subtract(numberToConvert, randomZeroes);
		break;
	case ADD:
		output = add(numberToConvert, randomZeroes);
		break;
	}

	output = output.substr(0, output.size() - 1);
	cout << output << "\n";
	clip::set_text(output);

	return 0;
}
