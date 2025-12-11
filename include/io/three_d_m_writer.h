#ifndef PARTITION_INCLUDE_THREE_D_M_WRITER_H_
#define PARTITION_INCLUDE_THREE_D_M_WRITER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the ThreeDMWriter.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include <ostream>
#include "core/three_d_m_instance.h"
#include "interfaces/instance_writer.h"

#include <string>

namespace partition {

/**
 * @brief Writes 3DM instances to files.
 *
 * Single Responsibility: Handles serialization of 3DM instances.
 */
class ThreeDMWriter : public InstanceWriter<ThreeDMInstance> {
 public:
  auto WriteToFile(const ThreeDMInstance& instance,
                   const std::string& filename) const -> void override;
  auto WriteToStream(const ThreeDMInstance& instance,
                     std::ostream& output) const -> void override;
  auto GetFormatDescription() const -> std::string override;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_WRITER_H_
