#ifndef PARTITION_INCLUDE_THREE_D_M_READER_H_
#define PARTITION_INCLUDE_THREE_D_M_READER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the ThreeDMReader.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include <istream>

#include "interfaces/instance_reader.h"
#include "core/three_d_m_instance.h"

namespace partition {

/**
 * @brief Reads 3DM instances from files.
 *
 * Expected format:
 *   - Line 1: q (size of each set)
 *   - Line 2: W elements (space-separated)
 *   - Line 3: X elements (space-separated)
 *   - Line 4: Y elements (space-separated)
 *   - Line 5+: Triples, one per line as "w x y"
 */
class ThreeDMReader : public InstanceReader<ThreeDMInstance> {
 public:
  auto ReadFromFile(const std::string& filename) const
      -> ThreeDMInstance override;
  auto ReadFromStream(std::istream& input) const -> ThreeDMInstance override;
  auto GetFormatDescription() const -> std::string override;
 private:
  auto FillSetFromLine(std::istream& input, std::set<std::string>& elements, size_t q, const std::string& set_name) const -> void;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_READER_H_
