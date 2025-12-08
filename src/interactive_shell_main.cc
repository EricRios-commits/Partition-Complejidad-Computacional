#include "io/three_d_m_reader.h"
#include "io/three_d_m_writer.h"
#include "io/partition_writer.h"
#include "reduction/three_d_m_to_partition_reducer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

void PrintHelp(const char* programName) {
    std::cout << std::endl;
    std::cout << "=== 3DM TO PARTITION CONVERTER ===" << std::endl << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << programName << " -i <input_file> -o <output_file>" << std::endl;
    std::cout << "  " << programName << " -h | --help" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i <file>     Input file containing the 3DM instance" << std::endl;
    std::cout << "  -o <file>     Output file for the Partition instance" << std::endl;
    std::cout << "  -h, --help    Show this help message" << std::endl << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  " << programName << " -i ../instances/3DM/3dm-1.txt -o output.txt" << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
    partition::ThreeDMReader reader;
    std::string filename;
    std::string output = "../instances/3DM/output_partition.txt";

    // -------------- ARGUMENT PARSING --------------
    for (int i = 1; i < argc; ++i) {
        if ((std::strcmp(argv[i], "-h") == 0) || (std::strcmp(argv[i], "--help") == 0)) {
            PrintHelp(argv[0]);
            return 0;
        }
        if (std::strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            filename = argv[i + 1];
            ++i;
        }
        else if (std::strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output = argv[i + 1];
            ++i;
        }
    }

    // -------------- INTERACTIVE MODE --------------
    if (filename.empty()) {
        std::cout << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "  3DM TO PARTITION CONVERTER" << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "No input file provided via command line." << std::endl << std::endl;
        std::cout << "Tip: You can also run:" << std::endl;
        std::cout << "  " << argv[0] << " -i <input_file> -o <output_file>" << std::endl;
        std::cout << "  " << argv[0] << " -h or --help for usage instructions" << std::endl << std::endl;


        while (true) {
            std::cout << "Enter the path to the 3DM instance file: ";
            std::getline(std::cin, filename);

            if (filename.empty()) {
                std::cout << "Filename cannot be empty. Try again." << std::endl << std::endl;
                continue;
            }

            std::ifstream testFile(filename);
            if (!testFile) {
                std::cout << "File not found. Check the path and try again." << std::endl << std::endl;
                continue;
            }

            break;
        }

        std::cout << "Enter the output file path (leave empty for default): ";
        std::string userOutput;
        std::getline(std::cin, userOutput);
        if (!userOutput.empty()) {
            output = userOutput;
        }
    }

    // -------------- PROCESSING --------------
    try {
        std::cout << std::endl << "Loading instance..." << std::endl;
        partition::ThreeDMInstance three_dm_instance = reader.ReadFromFile(filename);

        std::cout << std::endl << "=== ORIGINAL 3DM INSTANCE ===" << std::endl;
        std::cout << three_dm_instance.ToString() << std::endl;

        std::cout << std::endl << "Converting to Partition instance..." << std::endl;
        partition::ThreeDMToPartitionReducer reducer;
        partition::PartitionInstance partition_instance = reducer.Reduce(three_dm_instance);

        std::cout << std::endl << "=== CONVERTED PARTITION INSTANCE ===" << std::endl;
        std::cout << partition_instance.ToString() << std::endl;

        partition::PartitionWriter partition_writer;
        partition_writer.WriteToFile(partition_instance, output);

        std::cout << std::endl << "Output successfully written to:" << std::endl;
        std::cout << "  " << output << std::endl << std::endl;
        std::cout << "Done." << std::endl;

        return 0;
    } 
    catch (const std::exception& e) {
        std::cerr << std::endl << "ERROR: " << e.what() << std::endl;
        return 1;
    }
}
