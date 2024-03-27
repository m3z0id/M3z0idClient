# M3z0id Client
This is a command utility to confuse people when counting on Discord. ([counting#5250](https://countingbot.com/) bot)
## Instalation
This project uses the [clip](https://github.com/dacap/clip) library (which is included) to copy the output to clipboard. This project uses [CMake](https://cmake.org/). You won't find an executable for Linux. I'm still working on making CMake work on Windows, so this will probably be the next commit.
## Usage
M3z0id Client currently has 5 modes - `1`, `69`, `random`, `subtract` and `set`.
### Modes `1`, `69`, `random` and `subtract`
The usage is: `M3z0idClient <number> [1/69/random/subtract]`
### Mode `set`
The usage is: `M3z0idClient <number> set <number1>, <number2>, <number3>, ...`
If the amount of set numbers is bigger than the number to convert, not all numbers will be used. Only the numbers defined first will be used.