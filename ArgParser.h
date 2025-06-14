#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <variant>
#include <iomanip>

class ArgParser {
public:
    enum class ArgType { None, String, Int, Float };

    struct Option {
        std::string shortFlag;
        std::string longFlag;
        ArgType type;
        std::string description;
        bool required;
        bool isSet = false;
        std::variant<std::monostate, std::string, int, float> value;
    };

    void addOption(const std::string& shortFlag, const std::string& longFlag,
                   ArgType type, const std::string& description, bool required = false) {
        Option opt{shortFlag, longFlag, type, description, required};
        options.push_back(opt);
    }

    bool parse(int argc, char* argv[]) {
        std::unordered_map<std::string, Option*> flagMap;
        for (auto& opt : options) {
            if (!opt.shortFlag.empty())
                flagMap["-" + opt.shortFlag] = &opt;
            if (!opt.longFlag.empty())
                flagMap["--" + opt.longFlag] = &opt;
        }

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--help" || arg == "-h") {
                printHelp();
                return false;
            }

            auto it = flagMap.find(arg);
            if (it == flagMap.end()) {
                std::cerr << "Unknown option: " << arg << "\n";
                printHelp();
                return false;
            }

            Option* opt = it->second;
            opt->isSet = true;

            if (opt->type != ArgType::None) {
                if (i + 1 >= argc) {
                    std::cerr << "Option " << arg << " requires an argument.\n";
                    printHelp();
                    return false;
                }
                std::string val = argv[++i];
                try {
                    switch (opt->type) {
                        case ArgType::String:
                            opt->value = val;
                            break;
                        case ArgType::Int:
                            opt->value = std::stoi(val);
                            break;
                        case ArgType::Float:
                            opt->value = std::stof(val);
                            break;
                        default:
                            break;
                    }
                } catch (...) {
                    std::cerr << "Invalid argument for " << arg << ": " << val << "\n";
                    printHelp();
                    return false;
                }
            }
        }

        for (const auto& opt : options) {
            if (opt.required && !opt.isSet) {
                std::cerr << "Missing required option: ";
                if (!opt.longFlag.empty())
                    std::cerr << "--" << opt.longFlag;
                else if (!opt.shortFlag.empty())
                    std::cerr << "-" << opt.shortFlag;
                std::cerr << "\n";
                printHelp();
                return false;
            }
        }

        return true;
    }

    void printHelp() const {
        std::cout << "Usage:\n";
        for (const auto& opt : options) {
            std::ostringstream flags;
            if (!opt.shortFlag.empty()) flags << "-" << opt.shortFlag;
            if (!opt.shortFlag.empty() && !opt.longFlag.empty()) flags << ", ";
            if (!opt.longFlag.empty()) flags << "--" << opt.longFlag;

            std::string typeStr;
            switch (opt.type) {
                case ArgType::String: typeStr = "<string>"; break;
                case ArgType::Int: typeStr = "<int>"; break;
                case ArgType::Float: typeStr = "<float>"; break;
                default: break;
            }

            std::string requiredStr = opt.required ? " (required)" : "";

            std::cout << "  " << std::left << std::setw(25)
                      << flags.str() + " " + typeStr
                      << opt.description << requiredStr << "\n";
        }
        std::cout << "  " << std::left << std::setw(25)
                  << "-h, --help" << "Show this help message\n";
    }

    bool isSet(const std::string& longFlag) const {
        for (const auto& opt : options) {
            if (opt.longFlag == longFlag)
                return opt.isSet;
        }
        return false;
    }

    template<typename T>
    T get(const std::string& longFlag) const {
        for (const auto& opt : options) {
            if (opt.longFlag == longFlag && opt.isSet) {
                if (auto val = std::get_if<T>(&opt.value)) {
                    return *val;
                }
            }
        }
        throw std::runtime_error("Flag not set or wrong type: " + longFlag);
    }

private:
    std::vector<Option> options;
};
