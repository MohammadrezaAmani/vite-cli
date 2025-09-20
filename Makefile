# Makefile for Vite CLI
# A modern C++ CLI tool inspired by Vite.js

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
LDFLAGS := -pthread

# Directories
SRCDIR := src
BUILDDIR := build
BINDIR := bin
INSTALLDIR := /usr/local/bin

# Files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET := $(BINDIR)/vite

# Build type
BUILD_TYPE ?= Release

# Set optimization flags based on build type
ifeq ($(BUILD_TYPE), Debug)
    CXXFLAGS += -g -O0 -DDEBUG
else
    CXXFLAGS += -O3 -DNDEBUG
endif

# Colors for pretty output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[1;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[1;37m
RESET := \033[0m

# Default target
.PHONY: all
all: banner $(TARGET)

# Banner
.PHONY: banner
banner:
	@echo "$(CYAN)"
	@echo "██╗   ██╗██╗████████╗███████╗    ██████╗██╗     ██╗"
	@echo "██║   ██║██║╚══██╔══╝██╔════╝   ██╔════╝██║     ██║"
	@echo "██║   ██║██║   ██║   █████╗     ██║     ██║     ██║"
	@echo "╚██╗ ██╔╝██║   ██║   ██╔══╝     ██║     ██║     ██║"
	@echo " ╚████╔╝ ██║   ██║   ███████╗   ╚██████╗███████╗██║"
	@echo "  ╚═══╝  ╚═╝   ╚═╝   ╚══════╝    ╚═════╝╚══════╝╚═╝"
	@echo "$(RESET)"
	@echo "$(WHITE)              Building Vite CLI...$(RESET)"
	@echo ""

# Create directories
$(BUILDDIR) $(BINDIR):
	@echo "$(BLUE)📁 Creating directory: $@$(RESET)"
	@mkdir -p $@

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "$(YELLOW)🔨 Compiling: $<$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	@echo "$(GREEN)🔗 Linking: $@$(RESET)"
	@$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ Build complete: $(TARGET)$(RESET)"
	@echo ""

# Debug build
.PHONY: debug
debug:
	@$(MAKE) BUILD_TYPE=Debug

# Release build (explicit)
.PHONY: release
release:
	@$(MAKE) BUILD_TYPE=Release

# Clean build files
.PHONY: clean
clean:
	@echo "$(RED)🧹 Cleaning build files...$(RESET)"
	@rm -rf $(BUILDDIR) $(BINDIR)
	@echo "$(GREEN)✅ Clean complete$(RESET)"

# Full rebuild
.PHONY: rebuild
rebuild: clean all

# Install system-wide
.PHONY: install
install: $(TARGET)
	@echo "$(BLUE)📦 Installing to $(INSTALLDIR)...$(RESET)"
	@sudo cp $(TARGET) $(INSTALLDIR)/
	@sudo chmod +x $(INSTALLDIR)/vite
	@echo "$(GREEN)✅ Installation complete$(RESET)"
	@echo "$(WHITE)You can now run 'vite' from anywhere!$(RESET)"

# Uninstall
.PHONY: uninstall
uninstall:
	@echo "$(RED)🗑️  Uninstalling...$(RESET)"
	@sudo rm -f $(INSTALLDIR)/vite
	@echo "$(GREEN)✅ Uninstall complete$(RESET)"

# Run the application
.PHONY: run
run: $(TARGET)
	@echo "$(CYAN)🚀 Running Vite CLI...$(RESET)"
	@echo ""
	@./$(TARGET) --help

# Run in interactive mode
.PHONY: run-interactive
run-interactive: $(TARGET)
	@echo "$(CYAN)🎯 Running in interactive mode...$(RESET)"
	@echo ""
	@./$(TARGET) create --interactive

# Test basic functionality
.PHONY: test
test: $(TARGET)
	@echo "$(MAGENTA)🧪 Running basic tests...$(RESET)"
	@echo ""
	@echo "$(YELLOW)Testing --version:$(RESET)"
	@./$(TARGET) --version
	@echo ""
	@echo "$(YELLOW)Testing --help:$(RESET)"
	@./$(TARGET) --help
	@echo ""
	@echo "$(YELLOW)Testing create command:$(RESET)"
	@./$(TARGET) create --help
	@echo ""
	@echo "$(GREEN)✅ Basic tests complete$(RESET)"

# Check dependencies
.PHONY: check-deps
check-deps:
	@echo "$(BLUE)🔍 Checking dependencies...$(RESET)"
	@echo "$(WHITE)C++ Compiler:$(RESET)"
	@which $(CXX) && $(CXX) --version | head -1 || echo "$(RED)❌ $(CXX) not found$(RESET)"
	@echo "$(WHITE)Make:$(RESET)"
	@which make && make --version | head -1 || echo "$(RED)❌ make not found$(RESET)"
	@echo ""

# Show build info
.PHONY: info
info:
	@echo "$(CYAN)📊 Build Information:$(RESET)"
	@echo "$(WHITE)  Target:$(RESET) $(TARGET)"
	@echo "$(WHITE)  Build Type:$(RESET) $(BUILD_TYPE)"
	@echo "$(WHITE)  Compiler:$(RESET) $(CXX)"
	@echo "$(WHITE)  Flags:$(RESET) $(CXXFLAGS)"
	@echo "$(WHITE)  Sources:$(RESET) $(SOURCES)"
	@echo "$(WHITE)  Objects:$(RESET) $(OBJECTS)"
	@echo ""

# Package for distribution
.PHONY: package
package: release
	@echo "$(MAGENTA)📦 Creating package...$(RESET)"
	@mkdir -p dist/vite-cli
	@cp $(TARGET) dist/vite-cli/
	@cp README.md dist/vite-cli/
	@cp -r src dist/vite-cli/
	@cp Makefile dist/vite-cli/
	@cp CMakeLists.txt dist/vite-cli/
	@cd dist && tar -czf vite-cli.tar.gz vite-cli/
	@echo "$(GREEN)✅ Package created: dist/vite-cli.tar.gz$(RESET)"

# Show help
.PHONY: help
help:
	@echo "$(CYAN)Vite CLI Build System$(RESET)"
	@echo ""
	@echo "$(WHITE)Available targets:$(RESET)"
	@echo "$(GREEN)  all$(RESET)             - Build the application (default)"
	@echo "$(GREEN)  debug$(RESET)           - Build with debug symbols"
	@echo "$(GREEN)  release$(RESET)         - Build optimized release version"
	@echo "$(GREEN)  clean$(RESET)           - Remove build files"
	@echo "$(GREEN)  rebuild$(RESET)         - Clean and build"
	@echo "$(GREEN)  install$(RESET)         - Install system-wide"
	@echo "$(GREEN)  uninstall$(RESET)       - Remove system installation"
	@echo "$(GREEN)  run$(RESET)             - Run with --help"
	@echo "$(GREEN)  run-interactive$(RESET) - Run in interactive mode"
	@echo "$(GREEN)  test$(RESET)            - Run basic functionality tests"
	@echo "$(GREEN)  package$(RESET)         - Create distribution package"
	@echo "$(GREEN)  check-deps$(RESET)      - Check build dependencies"
	@echo "$(GREEN)  info$(RESET)            - Show build information"
	@echo "$(GREEN)  help$(RESET)            - Show this help message"
	@echo ""
	@echo "$(WHITE)Examples:$(RESET)"
	@echo "$(YELLOW)  make$(RESET)                    # Build release version"
	@echo "$(YELLOW)  make debug$(RESET)              # Build debug version"
	@echo "$(YELLOW)  make clean install$(RESET)      # Clean build and install"
	@echo "$(YELLOW)  make run$(RESET)                # Build and run"
	@echo "$(YELLOW)  make BUILD_TYPE=Debug$(RESET)   # Explicit debug build"
	@echo ""

# Prevent make from treating files as targets
.PHONY: $(SOURCES)
