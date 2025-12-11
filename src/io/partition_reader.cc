/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for PartitionReader.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "io/partition_reader.h"
#include <sstream>

namespace partition {
  auto PartitionReader::ReadFromFile(const std::string& filename) const
      -> PartitionInstance {
    std::ifstream file_stream(filename);
    if (!file_stream.is_open()) {
      throw std::runtime_error("Could not open file: " + filename);
    }
    return ReadFromStream(file_stream);
  }

  auto PartitionReader::ReadFromStream(std::istream& input) const
      -> PartitionInstance {
    PartitionInstance instance; 
    std::string line;
    int n;
    while (std::getline(input, line)) {
      auto comment_pos = line.find('#');
      if (comment_pos != std::string::npos) {
        line = line.substr(0, comment_pos);
      }
      std::istringstream iss(line);
      if (iss >> n) {
        break;
      }
    }    
    std::vector<PartitionElement> elements;
    elements.reserve(n);
    for (int i = 0; i < n; ++i) {
      while (std::getline(input, line)) {
        auto comment_pos = line.find('#');
        if (comment_pos != std::string::npos) {
          line = line.substr(0, comment_pos);
        }
        std::istringstream iss(line);
        std::string id;
        int64_t size;
        if (iss >> id >> size) {
          elements.emplace_back(id, size);
          break;
        }
      }
    }   
    instance.SetElements(elements);
    return instance;
  }

  auto PartitionReader::GetFormatDescription() const -> std::string {
    return "Partition instance format:\n"
          "- Line 1: n (number of elements)\n"
          "- Line 2+: Element ID and size, one per line as 'id size'";
  }
}  // namespace partition