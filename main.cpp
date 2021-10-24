#include "Coder/Coder.h"
#include "Decoder/Decoder.h"
#include <iostream>

std::string CStringToString(const char* c_string) {
    return std::string(c_string);
}

std::tuple<std::string, QUERY_TYPE, std::vector<std::string>> ParseArguments(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("");
    }
    std::string program_filename = CStringToString(argv[0]);
    std::string query_type_string = CStringToString(argv[1]);
    std::vector<std::string> parsed;
    for (size_t i = 2; i < static_cast<size_t>(argc); ++i) {
        parsed.push_back(CStringToString(argv[i]));
    }
    if (argc == 2) {
        if (query_type_string == "-h") {
            return {program_filename, QUERY_TYPE::HELP, parsed};
        } else {
            throw std::invalid_argument("");
        }
    } else if (argc == 3 && query_type_string == "-d") {
        return {program_filename, QUERY_TYPE::DECOMPRESS, parsed};
    } else {
        if (argc >= 4 && query_type_string == "-c") {
            return {program_filename, QUERY_TYPE::COMPRESS, parsed};
        } else {
            throw std::invalid_argument("");
        }
    }
}

int main(int argc, char* argv[]) {
    std::string program_name;
    QUERY_TYPE query_type;
    std::vector<std::string> parsed_arguments;
    try {
        std::tie(program_name, query_type, parsed_arguments) = ParseArguments(argc, argv);
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: Invalid argument" << std::endl;
        std::cout << "Launch with -h to see supported commands" << std::endl;
        return 1;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    try {
        if (query_type == QUERY_TYPE::HELP) {
            std::cout << "Commands:" << std::endl;
            std::cout << "1. " << program_name << " -c archive_name file1 [file2 ...]" << std::endl;
            std::cout << "2. " << program_name << " -d archive_name" << std::endl;
        } else if (query_type == QUERY_TYPE::DECOMPRESS) {
            Huffman::Decoder decompressor(parsed_arguments[0]);
            decompressor.Decode();
        } else {
            std::ofstream archive_file(parsed_arguments[0], std::ios::binary);
            Huffman::Coder compressor(archive_file);
            for (size_t i = 1; i < parsed_arguments.size(); ++i) {
                compressor.AddFile(parsed_arguments[i], i + 1 == parsed_arguments.size());
            }
            compressor.WriteTail();
        }
    } catch (const std::overflow_error& ex) {
        std::cout << "Error: " << ex.what() << " access error or it doesn't exist" << std::endl;
    } catch (const std::range_error& ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
