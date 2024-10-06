# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include/GL
LDFLAGS = -lGLEW -lGL -lglfw -lm
SRC_DIR = src
BUILD_DIR = build
SHADER_DIR = shaders
EXECUTABLE = triangle_app

# Encuentra todos los archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Regla por defecto
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Regla para compilar los archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean