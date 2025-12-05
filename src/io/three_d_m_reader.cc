
#include <fstream>
#include <sstream>

#include "../../include/io/three_d_m_reader.h"
#include "../../include/core/three_d_m_instance.h"
#include "../core/three_d_m_instance.cc"

namespace partition {
  auto ThreeDMReader::ReadFromFile(const std::string& filename) const -> ThreeDMInstance {
    std::ifstream file_stream(filename);
    if (!file_stream.is_open()) {
      throw std::runtime_error("Could not open file: " + filename);
    }
    return ReadFromStream(file_stream);
  }

  auto ThreeDMReader::ReadFromStream(std::istream& input) const -> ThreeDMInstance {
    ThreeDMInstance instance;
    std::string line;
    int line_number = 0;
    while (std::getline(input, line)) {
      auto comment_pos = line.find('#');
      if (comment_pos != std::string::npos) {
        line = line.substr(0, comment_pos);
      }

      line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
      if (line.empty()) {
        continue;  // Skip empty lines
      }

      std::istringstream line_stream(line);
      switch (line_number) {
        case 0: {
          int q;
          line_stream >> q;
          instance.SetQ(q);
          break;
        }
        case 1: {
          std::set<std::string> w_elements;
          std::string element;
          while (line_stream >> element) {
          w_elements.insert(element);
          }
          instance.SetW(w_elements);
          break;
        }
        case 2: {
          std::set<std::string> x_elements;
          std::string element;
          while (line_stream >> element) {
          x_elements.insert(element);
          }
          instance.SetX(x_elements);
          break;
        }
        case 3: {
          std::set<std::string> y_elements;
          std::string element;
          while (line_stream >> element) {
          y_elements.insert(element);
          }
          instance.SetY(y_elements);
          break;
        }
        default: {
          std::string w, x, y;
          line_stream >> w >> x >> y;
          if (!w.empty() && !x.empty() && !y.empty()) {
            instance.AddTriple(Triple(w, x, y));
          }
          break;
        }
      }
      ++line_number;
    }
    return instance;
  }

  auto ThreeDMReader::GetFormatDescription() const -> std::string {
    return "Three-Dimensional Matching format:\n"
           "- Line 1: q (size of each set)\n"
           "- Line 2: W elements (space-separated)\n"
           "- Line 3: X elements (space-separated)\n"
           "- Line 4: Y elements (space-separated)\n"
           "- Line 5+: Triples, one per line as 'w x y'";
  }
};