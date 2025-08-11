# D-ASE (Digital-Analog Simulation Engine)

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)]()
[![Version](https://img.shields.io/badge/version-1.0.0-green.svg)]()

**🎯 A complete analog computer simulation system with Excel-style web interface**

D-ASE bridges the gap between modern web interfaces and high-performance analog computer simulation, allowing users to design and simulate complex analog circuits through intuitive drag-and-drop operations.

![D-ASE Interface](images/dase-interface.png)

## 🌟 Features

- **📊 Excel-Style Interface** - Familiar spreadsheet-like design environment
- **🔄 Real-Time Simulation** - High-performance C++ analog computer engine
- **🎛️ Drag-and-Drop Modules** - Intuitive circuit design with visual modules
- **📐 Mathematical Templates** - Pre-built circuits for famous equations (Lorenz, Van der Pol, etc.)
- **⚡ JSON Communication** - Seamless web-to-engine data exchange
- **🔧 Professional Tools** - Circuit validation, auto-wiring, and debugging
- **📚 Comprehensive Documentation** - Full API documentation with Doxygen

## 🚀 Quick Start

### Prerequisites
```bash
# Windows
- Visual Studio 2022 (C++ tools)
- Modern web browser
- CMake 3.10+ (optional)

# Linux/macOS
- GCC 7+ or Clang 5+
- CMake 3.10+
- Modern web browser
```

### Installation

#### Option 1: Download Release
```bash
# Download latest release from GitHub
wget https://github.com/yourusername/D-ASE/releases/latest/download/D-ASE-v1.0.0.zip
unzip D-ASE-v1.0.0.zip
cd D-ASE
```

#### Option 2: Build from Source
```bash
git clone https://github.com/yourusername/D-ASE.git
cd D-ASE

# Windows (Visual Studio)
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Linux/macOS
mkdir build && cd build
cmake ..
make -j4
```

### Quick Demo
```bash
# 1. Open web interface
open web/index.html  # macOS
start web/index.html # Windows

# 2. Design circuit (drag modules to cells)
# 3. Export design
# 4. Run simulation
./bin/json_bridge     # Linux/macOS
bin\json_bridge.exe   # Windows

# 5. View results in web_results.json
```

## 📖 Documentation

- **[User Guide](docs/user-guide.md)** - Complete usage instructions
- **[API Documentation](https://yourusername.github.io/D-ASE/)** - Generated with Doxygen
- **[Examples](examples/)** - Sample analog computer circuits
- **[Development Guide](docs/development.md)** - Contributing guidelines

## 🧮 Supported Analog Modules

### Basic Operations
| Module | Formula | Description |
|--------|---------|-------------|
| **Amplifier** | `K × input` | Scale by gain factor |
| **Summer** | `A + B + C` | Add multiple inputs |
| **Integrator** | `∫ input dt` | Accumulate over time |
| **Differentiator** | `d/dt input` | Rate of change |

### Signal Generators
| Module | Formula | Description |
|--------|---------|-------------|
| **Sine** | `A sin(ωt + φ)` | Sine wave generator |
| **Cosine** | `A cos(ωt + φ)` | Cosine wave generator |
| **Square** | `sgn(sin(ωt))` | Square wave generator |
| **Noise** | `random()` | Random signal generator |

### Control Functions
| Module | Formula | Description |
|--------|---------|-------------|
| **Limiter** | `clamp(input, min, max)` | Clamp values |
| **Switch** | `condition ? A : B` | Conditional switching |
| **Delay** | `input(t - τ)` | Time delay element |
| **Sample/Hold** | `hold(input, trigger)` | Sample and hold |

## 🎨 Example Circuits

### Lorenz Attractor
```cpp
// Classic chaotic system
dx/dt = σ(y - x)
dy/dt = x(ρ - z) - y  
dz/dt = xy - βz
```

### Van der Pol Oscillator
```cpp
// Self-sustaining oscillator
d²x/dt² - μ(1 - x²)(dx/dt) + x = 0
```

### Predator-Prey System
```cpp
// Population dynamics
dx/dt = αx - βxy
dy/dt = δxy - γy
```

## 🏗️ Architecture

```
┌─────────────────┐    JSON     ┌─────────────────┐
│   Web Browser   │   Files     │  C++ Engine     │
│  (Excel Grid)   │ ←────────→  │ (Analog Sim)    │
│   index.html    │             │  *.exe files    │
└─────────────────┘             └─────────────────┘
        ↑                               ↑
   User Interface                 High Performance
   Drag & Drop                    Analog Simulation
```

### File Structure
```
D-ASE/
├── 📄 README.md              # This file
├── 📄 LICENSE                # GNU GPL v3 License
├── 📄 Doxyfile              # Doxygen configuration
├── 📄 CMakeLists.txt        # CMake build file
├── 📁 src/                  # C++ source code
│   ├── analog.cpp           # Core engine
│   ├── webserver.cpp        # Web interface layer
│   ├── bridge.cpp           # Communication bridge
│   └── json_bridge.cpp      # JSON processor
├── 📁 include/              # Header files
│   └── dase/
├── 📁 web/                  # Web interface
│   └── index.html           # Main interface
├── 📁 examples/             # Example circuits
│   ├── lorenz.json
│   ├── vanderpol.json
│   └── predator_prey.json
├── 📁 docs/                 # Documentation
└── 📁 tests/                # Unit tests
```

## 🔧 Development

### Building Documentation
```bash
# Generate Doxygen documentation
doxygen Doxyfile

# Or with CMake
cmake --build . --target docs
```

### Running Tests
```bash
# CMake tests
ctest

# Manual testing
./bin/test
```

### Contributing
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📊 Performance

- **Processing Speed**: Real-time for circuits with 1000+ modules
- **Memory Usage**: < 100MB for typical simulations
- **File Size**: JSON exports typically < 100KB
- **Accuracy**: Double precision (64-bit) arithmetic

## 🤝 Community

- **GitHub Issues**: Bug reports and feature requests
- **Discussions**: Design discussions and Q&A
- **Wiki**: Community documentation and tutorials
- **Examples**: Share your analog computer designs

## 📜 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

### Why GPL v3?

We chose GPL v3 to ensure that D-ASE remains free and open source, and that any improvements or derivatives also benefit the community. This protects the open nature of analog computer simulation research and education.

## 🙏 Acknowledgments

- Inspired by classic analog computers and modern web technologies
- Built with love for the analog computer simulation community
- Special thanks to contributors and beta testers

## 📈 Roadmap

- **v1.1**: WebSocket real-time communication
- **v1.2**: 3D visualization of analog circuits
- **v1.3**: Cloud-based simulation engine
- **v2.0**: Multi-user collaborative design

---

**⭐ Star this repository if D-ASE helps your analog computer projects!**

[Report Bug](https://github.com/yourusername/D-ASE/issues) · [Request Feature](https://github.com/yourusername/D-ASE/issues) · [Documentation](https://yourusername.github.io/D-ASE/) · [Examples](examples/)