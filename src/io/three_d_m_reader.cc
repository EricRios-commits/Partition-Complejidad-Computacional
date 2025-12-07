
#include "io/three_d_m_reader.h"
#include "core/three_d_m_instance.h"
#include <fstream>
#include <sstream>

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
    size_t q = 0;
    std::set<std::string> w_elements, x_elements, y_elements;
    
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
        case 0: { // Read q value
          if (!(line_stream >> q)) {
            throw std::runtime_error("Invalid format: q value must be a valid integer");
          }
          if (q <= 0) {
            throw std::runtime_error("Invalid format: q must be a positive integer");
          }
          instance.SetQ(q);
          break;
        }
        case 1: { // Read W elements
          FillSetFromLine(line_stream, w_elements, q, "W");
          instance.SetW(w_elements);
          break;
        }
        case 2: { // Read X elements
          FillSetFromLine(line_stream, x_elements, q, "X");
          instance.SetX(x_elements);
          break;
        }
        case 3: { // Read Y elements
          FillSetFromLine(line_stream, y_elements, q, "Y");
          instance.SetY(y_elements);
          break;
        }
        default: { // Read triples
          std::string w, x, y;
          line_stream >> w >> x >> y;
          
          // Check if all three elements were read
          if (w.empty() || x.empty() || y.empty()) {
            throw std::runtime_error("Invalid format: Triple must have exactly 3 elements (found incomplete triple at line " + 
                                   std::to_string(line_number + 1) + ")");
          }
          
          // Validate that elements belong to the correct sets
          if (w_elements.find(w) == w_elements.end()) {
            throw std::runtime_error("Invalid format: Element '" + w + 
                                   "' in triple is not in set W");
          }
          if (x_elements.find(x) == x_elements.end()) {
            throw std::runtime_error("Invalid format: Element '" + x + 
                                   "' in triple is not in set X");
          }
          if (y_elements.find(y) == y_elements.end()) {
            throw std::runtime_error("Invalid format: Element '" + y + 
                                   "' in triple is not in set Y");
          }
          
          instance.AddTriple(Triple(w, x, y));
          break;
        }
      }
      ++line_number;
    }
    
    // Validate that we read all required lines
    if (line_number < 4) {
      throw std::runtime_error("Invalid format: File is incomplete (missing required sets)");
    }
    
    if (!instance.IsValid()) {
      throw std::runtime_error("Invalid instance: One or more sets do not match the specified size q");
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

  auto ThreeDMReader::FillSetFromLine(std::istream& input, std::set<std::string>& elements, size_t q, const std::string& set_name) const -> void {
    std::string element;
    while (input >> element) {
      elements.insert(element);
    }
    if (elements.empty()) {
      throw std::runtime_error("Invalid format: " + set_name + " set cannot be empty");
    }
    if (elements.size() != q) {
      throw std::runtime_error("Invalid format: " + set_name + " set size (" + 
                               std::to_string(elements.size()) + 
                               ") does not match q (" + std::to_string(q) + ")");
    }
  }
};