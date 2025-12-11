#include "io/three_d_m_reader.h"
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Test runner for reduction code.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "reduction/three_d_m_to_partition_reducer.h"
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]) {
  // Parse command line arguments
  std::string input_file;
  
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      input_file = argv[i + 1];
      ++i;
    }
  }
  
  if (input_file.empty()) {
    std::cerr << "Usage: " << argv[0] << " -i <input_file>\n";
    std::cerr << "Example: " << argv[0] << " -i ../instances/3DM/3dm-1.txt\n";
    return 1;
  }
  
  try {
    partition::ThreeDMReader reader;
    partition::ThreeDMInstance three_dm_instance = reader.ReadFromFile(input_file);
    std::cout << "=== ORIGINAL 3DM INSTANCE ===" << std::endl;
    std::cout << three_dm_instance.ToString() << std::endl;
    partition::ThreeDMToPartitionReducer reducer;
    partition::PartitionInstance partition_instance = reducer.Reduce(three_dm_instance);
    std::cout << "\n=== CONVERTED PARTITION INSTANCE ===" << std::endl;
    std::cout << partition_instance.ToString() << std::endl;
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
