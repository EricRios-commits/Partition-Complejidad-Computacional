#include <iostream>
#include <string>
#include "./io/three_d_m_reader.cc"
#include "./io/partition_writer.cc"

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
    partition::ThreeDMInstance instance = reader.ReadFromFile(filename);

    std::cout << "3D-Matching Instance:" << std::endl;
    std::cout << instance.ToString() << std::endl;


    //Reduccion

    partition::PartitionWriter writer;
    std::ofstream output("../instances/partition/output_partition.txt");
    writer.WriteToStream(instance, output);
    return 0;
}
