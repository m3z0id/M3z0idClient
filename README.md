# M3z0id Client
This is a command utility to confuse people when counting on Discord. ([counting#5250](https://countingbot.com/) bot)
## Installation
This project uses the [clip](https://github.com/dacap/clip) library (which is included) to copy the output to clipboard. This project uses [CMake](https://cmake.org/). You won't find an executable for Linux.
## Usage
M3z0id Client currently has 6 modes - `1`, `69`, `random`, `subtract`, `set` and `add`.
### Modes `1`, `69`, `random`, `subtract` and `set`.
The usage is: `M3z0idClient [--random-zeroes] <number> [1/69/random/subtract/set/add]`
### Mode `set`
The usage is: `M3z0idClient [--random-zeroes] <number> set <number1>, <number2>, <number3>, ...`
If the amount of set numbers is bigger than the number to convert, not all numbers will be used. Only the numbers defined first will be used.
