#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "clip/clip.h"
#include <string>
#include <random>
#include <ctime>
using namespace std;

void help(){
	cout << "Usage: M3z0idClient <number> [1/69/random/subtract]\n";
	cout << "Usage: M3z0idClient <number> [set] <number1>...\n";
}

int main(int argc, char* argv[]){
	int numberToConvert;
	string output;
	// Check if arguments were passed
    if (argc < 3) {
		help();
		goto exiting;
    }
	// Converts the number argument to int
	try {
		numberToConvert = stoi(argv[1]);
		if (numberToConvert < 0) {
			help();
			goto exiting;
		}
	}
	catch (const std::invalid_argument&) {
		help();
		goto exiting;
	}
	catch (const std::out_of_range&) {
		help();
		goto exiting;
	}
	// Checks the mode
	if (strcmp(argv[2], "1") == 0 || strcmp(argv[2], "69") == 0 || strcmp(argv[2], "random") == 0 || strcmp(argv[2], "set") == 0 || strcmp(argv[2], "subtract") == 0) {
		if (strcmp(argv[2], "1") == 0) {
			while (numberToConvert > 0) {
				output = output + "1+";
				numberToConvert--;
			}
		}
		if (strcmp(argv[2], "69") == 0) {
			while (numberToConvert > 0) {
				output = output + "69^0+";
				numberToConvert--;
				if (numberToConvert == 0) {
					break;
				}
				output = output + "420^0+";
				numberToConvert--;
			}
		}
		if (strcmp(argv[2], "random") == 0) {
			int seedRegenerator = time(0);
			while (numberToConvert > 0) {
				srand(seedRegenerator);
				seedRegenerator = seedRegenerator + (rand() % 421);
				int randnum = rand() % 5001;
				output = output + to_string(randnum) + "^0+";
				numberToConvert--;
			}
		}
		if (strcmp(argv[2], "set") == 0) {
			int i = 3;
			if ((argc - 3) > numberToConvert) {
				cout << "WARNING: Not all numbers will be used!\n";
			}
			while (numberToConvert > 0) {
				output = output + argv[i] + "^0+";
				numberToConvert--;
				if (i <= argc) {
					i++;
					if (i >= argc) {
						i = 3;
					}
				}
			}
		}
		if(strcmp(argv[2], "subtract") == 0){
		generate:
		int seed = time(0);
		srand(seed);
		int initialVal = rand() % 5001;
		if(initialVal <= numberToConvert) goto generate;
		output = to_string(initialVal) + "-";

		int toSubtract = initialVal - numberToConvert;
		while (toSubtract > 0){
			seed = seed + (rand() % 421);
			srand(seed);

			if(toSubtract == 1){
				output = output + "1-";
				toSubtract--;
			}
			else {
				int randnum = rand() % (toSubtract + 1);
				toSubtract = toSubtract - randnum;
				output = output + to_string(randnum) + "-";
			}
		}
	}
	}
	else {
		help();
		goto exiting;
	}
	output = output.substr(0, output.size() - 1);
	cout << output << "\n";
	// Copy to clipboard
	clip::set_text(output);
	exiting:
    return 0;
}
