/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for ThreeDMWriter.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "io/three_d_m_writer.h"
#include "core/three_d_m_instance.h"

#include <fstream>

namespace partition {
  auto ThreeDMWriter::WriteToFile(const ThreeDMInstance& instance, const std::string& filename) const -> void {
    std::ofstream file_stream(filename);
    if (!file_stream.is_open()) {
      throw std::runtime_error("Could not open file: " + filename);
    }
    WriteToStream(instance, file_stream);
  }

  auto ThreeDMWriter::WriteToStream(const ThreeDMInstance& instance, std::ostream& output) const -> void {
    output << "W " << instance.w().size() << "\n";
    for (const auto& w_elem : instance.w()) {
      output << w_elem << " ";
    }
    output << "\nX " << instance.x().size() << "\n";
    for (const auto& x_elem : instance.x()) {
      output << x_elem << " ";
    }
    output << "\nY " << instance.y().size() << "\n";
    for (const auto& y_elem : instance.y()) {
      output << y_elem << " ";
    }
    output << "\nTriples " << instance.triples().size() << "\n";
    for (const auto& triple : instance.triples()) {
      output << triple.ToString() << "\n";
    }
  }
  auto ThreeDMWriter::GetFormatDescription() const -> std::string {
    return "Three-Dimensional Matching format:\n"
           "W <number_of_W_elements>\n"
           "<W_element_1> <W_element_2> ... <W_element_n>\n"
           "X <number_of_X_elements>\n"
           "<X_element_1> <X_element_2> ... <X_element_n>\n"
           "Y <number_of_Y_elements>\n"
           "<Y_element_1> <Y_element_2> ... <Y_element_n>\n"
           "Triples <number_of_triples>\n"
           "<w1> <x1> <y1>\n"
           "<w2> <x2> <y2>\n"
           "...\n"
           "<wm> <xm> <ym>\n";
  }
};