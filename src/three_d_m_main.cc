
#include "../include/io/three_d_m_reader.h"
#include "../include/io/three_d_m_writer.h"
#include "./io/three_d_m_reader.cc"
#include "./io/three_d_m_writer.cc"

#include <iostream>

int main(int argc, char* argv[]) {
  partition::ThreeDMReader reader;
  std::ifstream input(argv[1]);
  partition::ThreeDMInstance instance = reader.ReadFromStream(input);

  std::cout << "3D-Matching Instance:" << std::endl;
  std::cout << instance.ToString() << std::endl;

  partition::ThreeDMWriter writer;
  std::ofstream output("../instances/3DM/output_partition.txt");
  writer.WriteToStream(instance, output);

  return 0;
}