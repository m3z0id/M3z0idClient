#include "../clip/clip.h"
#include "ModifiersForwards.h"
#include "ArgParser.h"
#include <iostream>
#include <random>
#include <string>

int randomNumber(int min, int max) {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution dist(min, max);
  return dist(rng);
}

bool randomZero() {
    return randomNumber(1, 4) == 1;
}

void ones(std::string &output, uint32_t input, bool randomZeroes) {
  while (input > 0) {
    output += "1+";
    if (randomZeroes) output += (randomZero() ? "0+" : "");
    input--;
  }
}

void sixtynines(std::string &output, uint32_t input, bool randomZeroes) {
  const bool evenOnStart = !(input % 2);
  while (input > 0) {
    if (evenOnStart && input % 2 == 0)
      output += "69^0+";
    else if (!evenOnStart && input % 2 == 1)
      output += "69^0+";
    else
      output += "420^0+";

    if (randomZeroes) output += (randomZero() ? "0+" : "");
    input--;
  }
}

void randomMode(std::string &output, uint32_t input, bool randomZeroes) {
  while (input > 0) {
    output += std::to_string(randomNumber(1, 5001)) + "^0+";
    if (randomZeroes) output += (randomZero() ? "0+" : "");
    input--;
  }
}

void add(std::string &output, uint32_t input, bool randomZeroes) {
  while (input > 0) {
    const int randNum = randomNumber(1, (int)input);
    output += std::to_string(randNum) + "+";
    if (randomZeroes) output += (randomZero() ? "0+" : "");
    input -= randNum;
  }
}

void subtract(std::string &output, uint32_t input, bool randomZeroes) {
  const int initialVal = randomNumber((int)input + 1, 5001);
  output += std::to_string(initialVal) + "-";

  int toSubtract = (int)initialVal - input;
  while (toSubtract > 0) {
    const int currentValue = randomNumber(1, toSubtract);
    output += std::to_string(currentValue) + "-";
    if (randomZeroes) output += (randomZero() ? "0-" : "");
    toSubtract -= currentValue;
  }
}

void factorial(std::string &output, uint32_t input, bool randomZeroes) {
  int cache = 1;
  for (int i = 1;; i++) {
    if (cache * i <= input || abs(input - cache * i) < abs(input - cache)) {
      output += std::to_string(i) + "*";
      cache *= i;
    } else
      break;
  }
  const bool higherValInUse = cache > input;

  if (cache != input) {
    output = output.substr(0, output.size() - 1);
    output += (higherValInUse ? "-" : "+") + std::to_string(abs(input - cache)) + "+";
  }

  if (input == 1)
    output = "1+";
}

int main(int argc, char* argv[]) {
    const Options options = parseArgs(argc, argv);
    if (options.mode == nullptr) return 1;

    std::string result;
    options.mode(result, options.number, options.randomZeroes);
    result.pop_back();

    std::cout << result << "\n";
    clip::set_text(result);

    return 0;
}
