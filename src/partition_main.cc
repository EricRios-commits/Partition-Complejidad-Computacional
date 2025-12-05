
#include "../include/io/partition_reader.h"
// #include "io/partition_reader.cc"

#include <iostream>

int main() {
  partition::PartitionReader reader;
  std::ifstream input("../instances/Partition/partition-1.txt");
  partition::PartitionInstance instance = reader.ReadFromStream(input);

  std::cout << "Partition Instance:" << std::endl;
  std::cout << instance.ToString() << std::endl;
  return 0;
}