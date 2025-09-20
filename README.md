# Vite CLI

A fast, modern, and colorful command-line interface for web development projects, inspired by Vite.js. Built with C++ and CLI11 for maximum performance and beautiful terminal experience.

## Features

🚀 **Fast Project Scaffolding** - Create new projects instantly with beautiful templates  
🎨 **Colorful Output** - Rich, colorful terminal interface with progress bars and animations  
📦 **Multiple Templates** - Support for Vanilla JS, React, Vue, TypeScript, and more  
⚡ **Development Server** - Built-in development server simulation  
🔧 **Build System** - Production-ready build with optimization  
📊 **Progress Tracking** - Real-time progress bars for all operations  
🛠️ **Plugin System** - Extensible plugin architecture  
⚙️ **Configuration Management** - Easy project configuration  
💻 **Cross-Platform** - Works on Windows, macOS, and Linux

## Installation

### Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Build from Source

```bash
git clone https://github.com/MohammadrezaAmani/vite-cli.git
cd vite-cli
mkdir build && cd build
cmake ..
make
```

### Install System-wide

```bash
sudo make install
```

## Usage

### Create a New Project

#### Interactive Mode
```bash
vite create --interactive
```

#### Quick Create
```bash
vite create my-project
vite create my-react-app --template react
vite create my-vue-app --template vue
```

#### Available Templates
- `vanilla` - Vanilla JavaScript
- `vanilla-ts` - Vanilla TypeScript
- `react` - React + JavaScript
- `react-ts` - React + TypeScript
- `vue` - Vue + JavaScript
- `vue-ts` - Vue + TypeScript

### Development Commands

#### Start Development Server
```bash
vite dev
vite dev --port 3000
vite dev --open --host 0.0.0.0
```

#### Build for Production
```bash
vite build
vite build --outDir dist
vite build --no-minify
```

#### Preview Production Build
```bash
vite preview
vite preview --port 4173
```

### Configuration Management

#### List Configuration
```bash
vite config list
```

#### Set Configuration
```bash
vite config set port 3000
vite config set host localhost
```

### Plugin Management

#### List Available Plugins
```bash
vite plugin list
```

#### Install Plugin
```bash
vite plugin install @vitejs/plugin-react
vite plugin install vite-plugin-pwa
```

### Utility Commands

#### Project Information
```bash
vite info
```

#### Optimize Dependencies
```bash
vite optimize
```

#### Show Version
```bash
vite --version
```

#### Show Help
```bash
vite --help
vite <command> --help
```

## Command Reference

### Global Options

- `-v, --verbose` - Enable verbose output
- `--version` - Show version information
- `-h, --help` - Show help message

### Commands

| Command | Description | Options |
|---------|-------------|---------|
| `create` | Create a new project | `--template`, `--interactive` |
| `dev` | Start development server | `--port`, `--host`, `--open` |
| `build` | Build for production | `--outDir`, `--no-minify`, `--sourcemap` |
| `preview` | Preview production build | `--port` |
| `config` | Manage configuration | `list`, `set <key> <value>` |
| `plugin` | Manage plugins | `list`, `install <name>` |
| `info` | Show project information | - |
| `optimize` | Optimize dependencies | - |

## Examples

### Create a React TypeScript Project
```bash
vite create my-app --template react-ts
cd my-app
npm install
npm run dev
```

### Start Development Server with Custom Settings
```bash
vite dev --port 8080 --host 0.0.0.0 --open
```

### Build with Custom Output Directory
```bash
vite build --outDir build --sourcemap
```

### Interactive Project Creation
```bash
$ vite create --interactive

██╗   ██╗██╗████████╗███████╗    ██████╗██╗     ██╗
██║   ██║██║╚══██╔══╝██╔════╝   ██╔════╝██║     ██║
██║   ██║██║   ██║   █████╗     ██║     ██║     ██║
╚██╗ ██╔╝██║   ██║   ██╔══╝     ██║     ██║     ██║
 ╚████╔╝ ██║   ██║   ███████╗   ╚██████╗███████╗██║
  ╚═══╝  ╚═╝   ╚═╝   ╚══════╝    ╚═════╝╚══════╝╚═╝

              A fast, modern build tool

Project name: my-awesome-app

▶ Available Templates
  1. vanilla (Vanilla JavaScript)
  2. react (React + JavaScript)
  3. vue (Vue + JavaScript)
  4. vanilla-ts (Vanilla + TypeScript)
  5. react-ts (React + TypeScript)

Select a template (name or number): 2

✓ Created project 'my-awesome-app' with 5 files

▶ Next Steps
  cd my-awesome-app
  npm install
  npm run dev

🎉 Project created successfully! 🎉
```

## Color Scheme

The CLI uses a beautiful color scheme for enhanced readability:

- 🔵 **Blue** - Information and progress
- 🟢 **Green** - Success messages
- 🔴 **Red** - Errors and warnings
- 🟡 **Yellow** - Warnings and highlights
- 🟣 **Magenta** - Special elements
- 🟦 **Cyan** - Headers and sections
- ⚪ **White** - Primary text
- ⚫ **Gray** - Secondary text and debug info

## Configuration

The CLI supports project-level configuration through `vite.config.json`:

```json
{
  "port": "5173",
  "host": "localhost",
  "outDir": "dist",
  "template": "react"
}
```

## Architecture

### Core Components

- **Logger** - Colorful logging system with emoji support
- **ProgressBar** - Animated progress tracking
- **TemplateManager** - Project template management
- **ProjectCreator** - Project scaffolding engine
- **DevServer** - Development server simulation
- **Builder** - Production build system
- **ConfigManager** - Configuration management
- **PluginManager** - Plugin system

### Built with

- **CLI11** - Modern command-line parsing
- **C++17** - Modern C++ features
- **STL Filesystem** - File system operations
- **ANSI Colors** - Terminal color support

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Development

### Build in Debug Mode
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Run Tests
```bash
make test
```

### Custom Build Targets
```bash
make clean-build      # Clean and rebuild
make run             # Run with --help
make run-interactive # Run in interactive mode
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by [Vite.js](https://vitejs.dev/) by Evan You
- Built with [CLI11](https://github.com/CLIUtils/CLI11) by Henry Schreiner
- Terminal colors based on ANSI escape codes

## Roadmap

- [ ] Add more project templates
- [ ] Implement real HTTP server
- [ ] Add plugin development SDK
- [ ] Support for custom template repositories
- [ ] Integration with package managers
- [ ] Hot module replacement simulation
- [ ] Bundle analyzer
- [ ] Performance profiling
- [ ] Docker support
- [ ] CI/CD integrations

---

Made with ❤️ and C++