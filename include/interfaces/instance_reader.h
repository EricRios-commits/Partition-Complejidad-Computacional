#ifndef PARTITION_INCLUDE_INSTANCE_READER_H_
#define PARTITION_INCLUDE_INSTANCE_READER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the InstanceReader interface.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include <istream>
#include <memory>
#include <string>
#include <fstream>

namespace partition {

/**
 * @brief Interface for reading problem instances from files or streams.
 * @tparam Instance The type of instance to read.
 */
template <typename Instance>
class InstanceReader {
 public:
  virtual ~InstanceReader() = default;

  /**
   * @brief Reads an instance from a file.
   * @param filename Path to the input file.
   * @return The read instance.
   */
  virtual auto ReadFromFile(const std::string& filename) const -> Instance = 0;

  /**
   * @brief Reads an instance from a stream.
   * @param input The input stream.
   * @return The read instance.
   */
  virtual auto ReadFromStream(std::istream& input) const -> Instance = 0;

  /**
   * @brief Returns the supported file format description.
   * @return Format description string.
   */
  virtual auto GetFormatDescription() const -> std::string = 0;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_INSTANCE_READER_H_
