Build normally: cmake -B build && cmake --build build
Build with strict checks: cmake -B build -DENABLE_TIDY=ON && cmake --build build