#pragma once
#include "ModifiersForwards.h"
#include <algorithm>
#include <functional>
#include <getopt.h>
#include <iostream>

inline std::function<void(std::string&, int, bool)> getModeFromStr(std::string str) {
  std::ranges::transform(str, str.begin(), [](const unsigned char c) {  return std::tolower(c); });

  if (str == "1") return ones;
  if (str == "69") return sixtynines;
  if (str == "random") return randomMode;
  if (str == "subtract") return subtract;
  if (str == "add") return add;
  if (str == "factorial") return factorial;

  return nullptr;
}

typedef struct s_Options {
  std::function<void(std::string&, int, bool)> mode = nullptr;
  unsigned int number = -1;
  bool randomZeroes = false;
  bool printHelp = false;
} Options;

inline Options parseArgs(int argc, char *argv[]) {
  constexpr static option longOptions[] = {
    {"number", required_argument, nullptr, 'n'},
    {"mode", required_argument, nullptr, 'm'},
    {"random-zeroes", no_argument, nullptr, 'r'},
    {"help", no_argument, nullptr, 'h'},
  };

  Options options;

  int opt;
  int optIndex;
  while ((opt = getopt_long(argc, argv, "n:m:s:rh", longOptions, &optIndex)) != -1) {
    bool err = false;
    switch (opt) {
    case 'n':
      if (std::ranges::all_of(std::string(optarg), [](const char c) { return std::isdigit((unsigned char)c); })) options.number = std::atoi(optarg);
      else err = true;
      break;
    case 'm':
      options.mode = getModeFromStr(std::string(optarg));
      err = options.mode == nullptr;
      break;
    case 'r':
      options.randomZeroes = true;
      break;
    case 'h':
      options.printHelp = true;
      break;
    case '?':
    default: err = true;
    }

    if (err) {
      std::cerr << "Option " << (char)opt << " failed to parse.\n";
      return {};
    }
  }

  return options;
}