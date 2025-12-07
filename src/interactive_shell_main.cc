#include "io/three_d_m_reader.h"
#include "io/three_d_m_writer.h"
#include "io/partition_writer.h"
#include "reduction/three_d_m_to_partition_reducer.h"
#include <iostream>
#include <string>
#include <fstream>



int main() {
    partition::ThreeDMReader reader;
    std::string filename;

    while (true) {
        std::cout << "Load the 3DM instance to be transformed to partititon: ";
        std::getline(std::cin, filename);

        if (filename.empty()) {
            std::cout << "No filename entered. Try again.\n";
            continue;
        }
        break;
    }

    partition::ThreeDMInstance three_dm_instance = reader.ReadFromFile(filename);
    std::cout << "=== ORIGINAL 3DM INSTANCE ===" << std::endl;
    std::cout << three_dm_instance.ToString() << std::endl;
    partition::ThreeDMToPartitionReducer reducer;
    partition::PartitionInstance partition_instance = reducer.Reduce(three_dm_instance);
    std::cout << "\n=== CONVERTED PARTITION INSTANCE ===" << std::endl;
    std::cout << partition_instance.ToString() << std::endl;

    partition::PartitionWriter partition_writer;
    std::string output = "../instances/3DM/output_partition.txt";
    std::cout << "=== CONVERTED PARTITION IS PRINTED AT " + output + " ===" << std::endl;
    partition_writer.WriteToFile(partition_instance, output);
    return 0;
}
