#include <iostream>
#include <string>
#include <random>
#include "ArgParser.h"
#include "clip/clip.h"
using namespace std;

int randomNumber(int min, int max) {
	std::random_device dev;
	mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> number(min, max);
	return number(rng);
}

bool randomZero() {
	return randomNumber(1, 4) == 1;
}

void ones(string &output, int input) {
	while (input > 0) {
		output += "1+";
		input--;
	}
}

void sixtynines(string &output, int input) {
	bool evenOnStart = !(input % 2);
	while (input > 0) {
		if (evenOnStart && input % 2 == 0) output += "69^0+";
		else if (!evenOnStart && input % 2 == 1) output += "69^0+";
		else output += "420^0+";
		input--;
	}
}

void random(string &output, int input) {
	while (input > 0) {
		output += to_string(randomNumber(1, 5001)) + "^0+";
		input--;
	}
}

/*void set(std::string& output, int input, std::vector<int>& numbers) {
	if (input > static_cast<int>(numbers.size())) {
		std::cout << "WARNING: Requested more numbers than available!\n";
	}

	for (auto [i, it] = std::tuple{0, numbers.begin()}; i < input; ++i, ++it) {
		if (it == numbers.end()) {
			it = numbers.begin();
		}
		output += std::to_string(*it) + "^0+";
	}
}*/

void subtract(string &output, int input) {
	int initialVal = randomNumber(input + 1, 5001);
	output += to_string(initialVal) + "-";

	int toSubtract = initialVal - input;
	while (toSubtract > 0) {
		int currentValue = randomNumber(1, toSubtract);
		output += to_string(currentValue) + "-";
		toSubtract -= currentValue;
	}
}

void factorial(string &output, int input){
	int cache = 1;
	for (int i = 1;;i++) {
		if (!(cache * i > input) || abs(input - cache * i) < abs(input - cache)) {
			output += to_string(i) + "*";
			cache *= i;
			continue;
		}
		break;
	}
	bool higherValInUse = cache > input;
	if (cache != input) {
		output = output.substr(0, output.size() - 1);
		output += (higherValInUse ? "-" : "+") + to_string(abs(input - cache)) + "+";
	}
	if (input == 1) output = "1+";
}

void add(string &output, int input) {
	while (input > 0) {
		int randnum = randomNumber(1, input);
		output += to_string(randnum) + "+";
		input -= randnum;
	}
}

void addRandomZeroes(string& output, bool randomZeroes, void (*funcPtr)(string&, int)) {
	if (!randomZeroes || funcPtr == factorial) return;
	std::vector outputVector(output.begin(), output.end());

	const char OPERATOR = funcPtr == subtract ? '-' : '+';

	for (auto it = outputVector.begin(); it != outputVector.end(); ) {
		if (randomZero()) {
			it = outputVector.insert(it, '0');
			++it;
			it = outputVector.insert(it, OPERATOR);
			++it;
		}
		it += 2;
	}

	output = string(outputVector.begin(), outputVector.end());
}

int main(int argc, char* argv[]) {
	void (*funcPtr)(string&, int) = nullptr;

	int number;
	std::string mode;
	bool randomZeroes;

	ArgParser parser = ArgParser();
	parser.addOption("n", "number", ArgParser::ArgType::Int, "Number to convert", true);
	parser.addOption("m", "mode", ArgParser::ArgType::String, "Mode of operation", true);
	parser.addOption("h", "help", ArgParser::ArgType::None, "Prints help");
	parser.addOption("", "random-zeroes", ArgParser::ArgType::None, "Adds random zeroes to the output");

	if (!parser.parse(argc, argv)) {

	}
	if (parser.isSet("help")) {
		parser.printHelp();
		return 0;
	}

	number = parser.get<int>("number");
	mode = parser.get<std::string>("mode");
	randomZeroes = parser.isSet("randomZeroes");

	if (mode == "1") funcPtr = ones;
	else if (mode == "69") funcPtr = sixtynines;
	else if (mode == "random") funcPtr = random;
	// else if (mode == "set") funcPtr = set;
	else if (mode == "subtract") funcPtr = subtract;
	else if (mode == "factorial") funcPtr = factorial;
	else if (mode == "add") funcPtr = add;
	else {
		parser.printHelp();
		return 0;
	}

	string result;
	funcPtr(result, number);
	addRandomZeroes(result, randomZeroes, funcPtr);
	result = result.substr(0, result.size() - 1);

	cout << result << "\n";
	clip::set_text(result);

	return 0;
}
