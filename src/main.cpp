#include "CLI11.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>

namespace fs = std::filesystem;

// ANSI Color Codes for beautiful terminal output
namespace Colors {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string DIM = "\033[2m";
    const std::string UNDERLINE = "\033[4m";
    
    // Colors
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    
    // Bright colors
    const std::string BRIGHT_BLACK = "\033[90m";
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";
    
    // Background colors
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
}

// Utility functions for beautiful output
class Logger {
public:
    static void info(const std::string& message) {
        std::cout << Colors::BRIGHT_BLUE << "ℹ " << Colors::RESET 
                  << Colors::BRIGHT_WHITE << message << Colors::RESET << std::endl;
    }
    
    static void success(const std::string& message) {
        std::cout << Colors::BRIGHT_GREEN << "✓ " << Colors::RESET 
                  << Colors::BRIGHT_WHITE << message << Colors::RESET << std::endl;
    }
    
    static void error(const std::string& message) {
        std::cerr << Colors::BRIGHT_RED << "✗ " << Colors::RESET 
                  << Colors::BRIGHT_WHITE << message << Colors::RESET << std::endl;
    }
    
    static void warning(const std::string& message) {
        std::cout << Colors::BRIGHT_YELLOW << "⚠ " << Colors::RESET 
                  << Colors::BRIGHT_WHITE << message << Colors::RESET << std::endl;
    }
    
    static void debug(const std::string& message) {
        std::cout << Colors::DIM << Colors::BRIGHT_BLACK << "DEBUG: " << message << Colors::RESET << std::endl;
    }
    
    static void section(const std::string& title) {
        std::cout << std::endl << Colors::BOLD << Colors::BRIGHT_CYAN 
                  << "▶ " << title << Colors::RESET << std::endl;
    }
};

// Progress bar implementation
class ProgressBar {
private:
    int width;
    std::string fill;
    std::string empty;
    
public:
    ProgressBar(int w = 50) : width(w), fill("█"), empty("░") {}
    
    void show(double progress, const std::string& message = "") {
        int filled = static_cast<int>(progress * width);
        std::cout << "\r" << Colors::BRIGHT_BLUE << "[";
        
        for (int i = 0; i < width; ++i) {
            if (i < filled) {
                std::cout << Colors::BRIGHT_GREEN << fill;
            } else {
                std::cout << Colors::DIM << empty;
            }
        }
        
        std::cout << Colors::BRIGHT_BLUE << "] " 
                  << Colors::BRIGHT_WHITE << std::setw(3) << static_cast<int>(progress * 100) << "%"
                  << Colors::RESET;
        
        if (!message.empty()) {
            std::cout << " " << Colors::DIM << message << Colors::RESET;
        }
        
        std::cout.flush();
        
        if (progress >= 1.0) {
            std::cout << std::endl;
        }
    }
};

// Template system for project scaffolding
class Template {
public:
    std::string name;
    std::string description;
    std::string color;
    std::vector<std::string> files;
    std::map<std::string, std::string> fileContents;
    
    Template(const std::string& n, const std::string& desc, const std::string& c) 
        : name(n), description(desc), color(c) {}
};

// Template manager
class TemplateManager {
private:
    std::vector<Template> templates;
    
    void initializeTemplates() {
        // Vanilla JavaScript template
        Template vanilla("vanilla", "Vanilla JavaScript", Colors::BRIGHT_YELLOW);
        vanilla.files = {"index.html", "main.js", "style.css", "package.json", "vite.config.js"};
        vanilla.fileContents["index.html"] = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
    <link rel="icon" type="image/svg+xml" href="/vite.svg" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Vite App</title>
</head>
<body>
    <div id="app"></div>
    <script type="module" src="/main.js"></script>
</body>
</html>)";
        
        vanilla.fileContents["main.js"] = R"(import './style.css'

document.querySelector('#app').innerHTML = `
  <div>
    <h1>Hello Vite!</h1>
    <p class="read-the-docs">
      Click on the Vite logo to learn more
    </p>
  </div>
`
)";
        
        vanilla.fileContents["style.css"] = R"(:root {
  font-family: Inter, system-ui, Avenir, Helvetica, Arial, sans-serif;
  line-height: 1.5;
  font-weight: 400;
  color-scheme: light dark;
  color: rgba(255, 255, 255, 0.87);
  background-color: #242424;
}

body {
  margin: 0;
  display: flex;
  place-items: center;
  min-width: 320px;
  min-height: 100vh;
}

#app {
  max-width: 1280px;
  margin: 0 auto;
  padding: 2rem;
  text-align: center;
}

h1 {
  font-size: 3.2em;
  line-height: 1.1;
}

@media (prefers-color-scheme: light) {
  :root {
    color: #213547;
    background-color: #ffffff;
  }
}
)";
        
        vanilla.fileContents["package.json"] = R"({
  "name": "vite-project",
  "private": true,
  "version": "0.0.0",
  "type": "module",
  "scripts": {
    "dev": "vite",
    "build": "vite build",
    "preview": "vite preview"
  },
  "devDependencies": {
    "vite": "^5.0.0"
  }
}
)";
        
        vanilla.fileContents["vite.config.js"] = R"(import { defineConfig } from 'vite'

export default defineConfig({
  // config options
})
)";
        
        templates.push_back(vanilla);
        
        // React template
        Template react("react", "React + JavaScript", Colors::BRIGHT_CYAN);
        react.files = {"index.html", "src/main.jsx", "src/App.jsx", "src/App.css", "src/index.css", "package.json", "vite.config.js"};
        react.fileContents["package.json"] = R"({
  "name": "vite-react-app",
  "private": true,
  "version": "0.0.0",
  "type": "module",
  "scripts": {
    "dev": "vite",
    "build": "vite build",
    "lint": "eslint . --ext js,jsx --report-unused-disable-directives --max-warnings 0",
    "preview": "vite preview"
  },
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0"
  },
  "devDependencies": {
    "@types/react": "^18.2.15",
    "@types/react-dom": "^18.2.7",
    "@vitejs/plugin-react": "^4.0.3",
    "eslint": "^8.45.0",
    "eslint-plugin-react": "^7.32.2",
    "eslint-plugin-react-hooks": "^4.6.0",
    "eslint-plugin-react-refresh": "^0.4.3",
    "vite": "^4.4.5"
  }
}
)";
        templates.push_back(react);
        
        // Vue template
        Template vue("vue", "Vue + JavaScript", Colors::BRIGHT_GREEN);
        vue.files = {"index.html", "src/main.js", "src/App.vue", "src/style.css", "package.json", "vite.config.js"};
        vue.fileContents["package.json"] = R"({
  "name": "vue-project",
  "version": "0.0.0",
  "private": true,
  "scripts": {
    "dev": "vite",
    "build": "vite build",
    "preview": "vite preview"
  },
  "dependencies": {
    "vue": "^3.3.4"
  },
  "devDependencies": {
    "@vitejs/plugin-vue": "^4.2.3",
    "vite": "^4.4.5"
  }
}
)";
        templates.push_back(vue);
        
        // TypeScript templates
        Template typescript("vanilla-ts", "Vanilla + TypeScript", Colors::BRIGHT_BLUE);
        templates.push_back(typescript);
        
        Template reactTs("react-ts", "React + TypeScript", Colors::BRIGHT_MAGENTA);
        templates.push_back(reactTs);
    }
    
public:
    TemplateManager() {
        initializeTemplates();
    }
    
    void displayTemplates() {
        Logger::section("Available Templates");
        for (size_t i = 0; i < templates.size(); ++i) {
            std::cout << Colors::BRIGHT_WHITE << "  " << (i + 1) << ". " 
                      << templates[i].color << templates[i].name << Colors::RESET
                      << Colors::DIM << " (" << templates[i].description << ")" << Colors::RESET 
                      << std::endl;
        }
        std::cout << std::endl;
    }
    
    Template* getTemplate(const std::string& name) {
        for (auto& tmpl : templates) {
            if (tmpl.name == name) {
                return &tmpl;
            }
        }
        return nullptr;
    }
    
    Template* getTemplate(int index) {
        if (index > 0 && index <= static_cast<int>(templates.size())) {
            return &templates[index - 1];
        }
        return nullptr;
    }
    
    const std::vector<Template>& getAllTemplates() const {
        return templates;
    }
};

// Project creator class
class ProjectCreator {
private:
    TemplateManager templateManager;
    
    bool createDirectory(const std::string& path) {
        try {
            if (!fs::exists(path)) {
                fs::create_directories(path);
                return true;
            }
            return false;
        } catch (const std::exception& e) {
            Logger::error("Failed to create directory: " + std::string(e.what()));
            return false;
        }
    }
    
    bool createFile(const std::string& path, const std::string& content) {
        try {
            // Create parent directories if they don't exist
            fs::path filePath(path);
            if (filePath.has_parent_path()) {
                fs::create_directories(filePath.parent_path());
            }
            
            std::ofstream file(path);
            if (file.is_open()) {
                file << content;
                file.close();
                return true;
            }
            return false;
        } catch (const std::exception& e) {
            Logger::error("Failed to create file: " + std::string(e.what()));
            return false;
        }
    }
    
    void simulateProgress(const std::string& task, int steps = 10) {
        ProgressBar progress(40);
        for (int i = 0; i <= steps; ++i) {
            double prog = static_cast<double>(i) / steps;
            progress.show(prog, task);
            std::this_thread::sleep_for(std::chrono::milliseconds(50 + (rand() % 100)));
        }
    }
    
public:
    bool createProject(const std::string& projectName, const std::string& templateName) {
        Logger::section("Creating Project: " + projectName);
        
        // Check if directory already exists
        if (fs::exists(projectName)) {
            Logger::error("Directory '" + projectName + "' already exists!");
            return false;
        }
        
        // Get template
        Template* tmpl = templateManager.getTemplate(templateName);
        if (!tmpl) {
            Logger::error("Template '" + templateName + "' not found!");
            return false;
        }
        
        Logger::info("Using template: " + tmpl->color + tmpl->name + Colors::RESET);
        
        // Create project directory
        if (!createDirectory(projectName)) {
            Logger::error("Failed to create project directory!");
            return false;
        }
        
        simulateProgress("Setting up project structure");
        
        // Create files
        int filesCreated = 0;
        for (const auto& file : tmpl->files) {
            std::string filePath = projectName + "/" + file;
            std::string content = "";
            
            if (tmpl->fileContents.find(file) != tmpl->fileContents.end()) {
                content = tmpl->fileContents[file];
            }
            
            if (createFile(filePath, content)) {
                filesCreated++;
            }
        }
        
        simulateProgress("Installing dependencies", 15);
        
        Logger::success("Created project '" + projectName + "' with " + std::to_string(filesCreated) + " files");
        
        // Display next steps
        std::cout << std::endl;
        Logger::section("Next Steps");
        std::cout << Colors::BRIGHT_WHITE << "  cd " << projectName << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  npm install" << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  npm run dev" << Colors::RESET << std::endl;
        std::cout << std::endl;
        
        return true;
    }
    
    void interactiveCreate() {
        std::string projectName, templateChoice;
        
        // ASCII Art Banner
        std::cout << std::endl;
        std::cout << Colors::BRIGHT_CYAN << R"(
██╗   ██╗██╗████████╗███████╗    ██████╗██╗     ██╗
██║   ██║██║╚══██╔══╝██╔════╝   ██╔════╝██║     ██║
██║   ██║██║   ██║   █████╗     ██║     ██║     ██║
╚██╗ ██╔╝██║   ██║   ██╔══╝     ██║     ██║     ██║
 ╚████╔╝ ██║   ██║   ███████╗   ╚██████╗███████╗██║
  ╚═══╝  ╚═╝   ╚═╝   ╚══════╝    ╚═════╝╚══════╝╚═╝
        )" << Colors::RESET << std::endl;
        
        std::cout << Colors::DIM << "              A fast, modern build tool" << Colors::RESET << std::endl;
        std::cout << std::endl;
        
        // Get project name
        std::cout << Colors::BRIGHT_WHITE << "Project name: " << Colors::RESET;
        std::getline(std::cin, projectName);
        
        if (projectName.empty()) {
            projectName = "vite-project";
            Logger::info("Using default project name: " + projectName);
        }
        
        // Display available templates
        templateManager.displayTemplates();
        
        // Get template choice
        std::cout << Colors::BRIGHT_WHITE << "Select a template (name or number): " << Colors::RESET;
        std::getline(std::cin, templateChoice);
        
        std::string selectedTemplate = "vanilla";
        
        // Try to parse as number first
        try {
            int templateIndex = std::stoi(templateChoice);
            Template* tmpl = templateManager.getTemplate(templateIndex);
            if (tmpl) {
                selectedTemplate = tmpl->name;
            }
        } catch (...) {
            // If not a number, use as template name
            if (!templateChoice.empty()) {
                selectedTemplate = templateChoice;
            }
        }
        
        // Create the project
        if (createProject(projectName, selectedTemplate)) {
            // Celebration animation
            std::cout << std::endl;
            for (int i = 0; i < 3; ++i) {
                std::cout << "\r" << Colors::BRIGHT_YELLOW << "🎉 " << Colors::BRIGHT_GREEN 
                          << "Project created successfully! " << Colors::BRIGHT_YELLOW << "🎉" << Colors::RESET;
                std::cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cout << "\r" << Colors::BRIGHT_YELLOW << "✨ " << Colors::BRIGHT_GREEN 
                          << "Project created successfully! " << Colors::BRIGHT_YELLOW << "✨" << Colors::RESET;
                std::cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            std::cout << std::endl << std::endl;
        }
    }
    
    TemplateManager& getTemplateManager() {
        return templateManager;
    }
};

// Configuration manager
class ConfigManager {
private:
    std::map<std::string, std::string> config;
    std::string configPath;
    
public:
    ConfigManager() : configPath("vite.config.json") {
        loadConfig();
    }
    
    void loadConfig() {
        if (fs::exists(configPath)) {
            std::ifstream file(configPath);
            // Simple key-value parsing (in a real implementation, use JSON library)
            std::string line;
            while (std::getline(file, line)) {
                size_t pos = line.find('=');
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    config[key] = value;
                }
            }
        }
    }
    
    void saveConfig() {
        std::ofstream file(configPath);
        for (const auto& pair : config) {
            file << pair.first << "=" << pair.second << std::endl;
        }
    }
    
    void set(const std::string& key, const std::string& value) {
        config[key] = value;
        saveConfig();
        Logger::success("Config updated: " + key + " = " + value);
    }
    
    std::string get(const std::string& key, const std::string& defaultValue = "") {
        if (config.find(key) != config.end()) {
            return config[key];
        }
        return defaultValue;
    }
    
    void list() {
        Logger::section("Configuration");
        if (config.empty()) {
            std::cout << Colors::DIM << "  No configuration found." << Colors::RESET << std::endl;
        } else {
            for (const auto& pair : config) {
                std::cout << Colors::BRIGHT_WHITE << "  " << pair.first << Colors::RESET 
                          << " = " << Colors::BRIGHT_CYAN << pair.second << Colors::RESET << std::endl;
            }
        }
        std::cout << std::endl;
    }
};

// Development server simulator
class DevServer {
public:
    void start(int port = 5173, bool open = false) {
        Logger::section("Starting Development Server");
        
        // Simulate server startup
        ProgressBar progress(30);
        std::vector<std::string> startupTasks = {
            "Loading configuration",
            "Initializing plugins",
            "Scanning dependencies",
            "Building optimized deps",
            "Starting server"
        };
        
        for (size_t i = 0; i < startupTasks.size(); ++i) {
            double prog = static_cast<double>(i + 1) / startupTasks.size();
            progress.show(prog, startupTasks[i]);
            std::this_thread::sleep_for(std::chrono::milliseconds(300 + (rand() % 200)));
        }
        
        std::cout << std::endl;
        Logger::success("Development server started!");
        
        // Display server info
        std::cout << std::endl;
        std::cout << Colors::BRIGHT_GREEN << "➜" << Colors::RESET 
                  << "  " << Colors::BOLD << "Local:" << Colors::RESET 
                  << "   " << Colors::BRIGHT_CYAN << "http://localhost:" << port << "/" << Colors::RESET << std::endl;
                  
        std::cout << Colors::BRIGHT_GREEN << "➜" << Colors::RESET 
                  << "  " << Colors::BOLD << "Network:" << Colors::RESET 
                  << " " << Colors::BRIGHT_CYAN << "use --host to expose" << Colors::RESET << std::endl;
        
        std::cout << std::endl;
        std::cout << Colors::DIM << "ready in " << Colors::BRIGHT_WHITE << "850ms" << Colors::RESET << std::endl;
        std::cout << std::endl;
        
        if (open) {
            Logger::info("Opening browser...");
            // In a real implementation, this would open the browser
        }
        
        // Simulate file watching
        Logger::info("Watching for file changes...");
        std::cout << Colors::DIM << "Press Ctrl+C to stop" << Colors::RESET << std::endl;
    }
};

// Build system
class Builder {
public:
    void build(bool minify = true, const std::string& outDir = "dist") {
        Logger::section("Building for Production");
        
        // Display build configuration
        if (minify) {
            Logger::info("Minification enabled");
        } else {
            Logger::info("Minification disabled");
        }
        
        // Simulate build process
        ProgressBar progress(40);
        std::vector<std::string> buildTasks = {
            "Cleaning output directory",
            "Analyzing dependencies",
            "Bundling modules",
            "Optimizing assets",
            minify ? "Minifying code" : "Preserving code formatting",
            "Generating source maps",
            "Writing output files"
        };
        
        for (size_t i = 0; i < buildTasks.size(); ++i) {
            double prog = static_cast<double>(i + 1) / buildTasks.size();
            progress.show(prog, buildTasks[i]);
            std::this_thread::sleep_for(std::chrono::milliseconds(400 + (rand() % 300)));
        }
        
        std::cout << std::endl;
        Logger::success("Build completed!");
        
        // Display build stats
        std::cout << std::endl;
        Logger::section("Build Statistics");
        std::cout << Colors::BRIGHT_WHITE << "  Output directory: " << Colors::BRIGHT_CYAN 
                  << outDir << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  Bundle size: " << Colors::BRIGHT_GREEN 
                  << (minify ? "142.43 kB" : "284.12 kB") << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  Gzipped size: " << Colors::BRIGHT_GREEN 
                  << (minify ? "46.21 kB" : "78.45 kB") << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  Build time: " << Colors::BRIGHT_YELLOW 
                  << "2.84s" << Colors::RESET << std::endl;
        std::cout << std::endl;
    }
    
    void preview(int port = 4173) {
        Logger::section("Preview Production Build");
        Logger::success("Preview server started!");
        
        std::cout << std::endl;
        std::cout << Colors::BRIGHT_GREEN << "➜" << Colors::RESET 
                  << "  " << Colors::BOLD << "Local:" << Colors::RESET 
                  << "   " << Colors::BRIGHT_CYAN << "http://localhost:" << port << "/" << Colors::RESET << std::endl;
        std::cout << std::endl;
    }
};

// Plugin manager
class PluginManager {
private:
    std::vector<std::string> availablePlugins = {
        "@vitejs/plugin-react",
        "@vitejs/plugin-vue",
        "@vitejs/plugin-svelte",
        "vite-plugin-eslint",
        "vite-plugin-pwa",
        "vite-plugin-windicss"
    };
    
public:
    void list() {
        Logger::section("Available Plugins");
        for (size_t i = 0; i < availablePlugins.size(); ++i) {
            std::cout << Colors::BRIGHT_WHITE << "  " << (i + 1) << ". " 
                      << Colors::BRIGHT_CYAN << availablePlugins[i] << Colors::RESET << std::endl;
        }
        std::cout << std::endl;
    }
    
    void install(const std::string& plugin) {
        Logger::info("Installing plugin: " + plugin);
        ProgressBar progress(20);
        
        for (int i = 0; i <= 20; ++i) {
            double prog = static_cast<double>(i) / 20;
            progress.show(prog, "Installing " + plugin);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        Logger::success("Plugin installed: " + plugin);
    }
};

int main(int argc, char** argv) {
    CLI::App app{"Vite CLI - A fast, modern build tool for web development", "vite"};
    
    // Global flags
    bool verbose = false;
    bool version = false;
    
    app.add_flag("-v,--verbose", verbose, "Enable verbose output");
    app.add_flag("--version", version, "Show version information");
    
    // Create command
    auto create = app.add_subcommand("create", "Create a new project");
    std::string projectName;
    std::string templateName = "vanilla";
    bool interactive = false;
    
    create->add_option("name", projectName, "Project name");
    create->add_option("-t,--template", templateName, "Template to use");
    create->add_flag("-i,--interactive", interactive, "Use interactive mode");
    
    // Dev command
    auto dev = app.add_subcommand("dev", "Start development server");
    int devPort = 5173;
    bool openBrowser = false;
    std::string host = "localhost";
    
    dev->add_option("-p,--port", devPort, "Port number");
    dev->add_flag("--open", openBrowser, "Open browser automatically");
    dev->add_option("--host", host, "Host to bind to");
    
    // Build command
    auto build = app.add_subcommand("build", "Build for production");
    std::string outDir = "dist";
    bool minify = true;
    bool sourcemap = true;
    
    build->add_option("-o,--outDir", outDir, "Output directory");
    build->add_flag("--no-minify", [&](bool) { minify = false; }, "Disable minification");
    build->add_flag("--sourcemap", sourcemap, "Generate source maps");
    
    // Preview command
    auto preview = app.add_subcommand("preview", "Preview production build");
    int previewPort = 4173;
    preview->add_option("-p,--port", previewPort, "Port number");
    
    // Config command
    auto config = app.add_subcommand("config", "Manage configuration");
    auto configList = config->add_subcommand("list", "List all configuration");
    auto configSet = config->add_subcommand("set", "Set configuration value");
    
    std::string configKey, configValue;
    configSet->add_option("key", configKey, "Configuration key")->required();
    configSet->add_option("value", configValue, "Configuration value")->required();
    
    // Plugin command
    auto plugin = app.add_subcommand("plugin", "Manage plugins");
    auto pluginList = plugin->add_subcommand("list", "List available plugins");
    auto pluginInstall = plugin->add_subcommand("install", "Install a plugin");
    
    std::string pluginName;
    pluginInstall->add_option("name", pluginName, "Plugin name")->required();
    
    // Info command
    auto info = app.add_subcommand("info", "Show project information");
    
    // Optimize command
    auto optimize = app.add_subcommand("optimize", "Optimize dependencies");
    
    try {
        app.parse(argc, argv);
        
        // Handle version flag
        if (version) {
            std::cout << Colors::BOLD << Colors::BRIGHT_CYAN << "vite" << Colors::RESET 
                      << " version " << Colors::BRIGHT_GREEN << "5.0.0" << Colors::RESET << std::endl;
            return 0;
        }
        
        // Initialize instances
        ProjectCreator creator;
        DevServer devServer;
        Builder builder;
        ConfigManager configManager;
        PluginManager pluginManager;
        
        // Handle subcommands
        if (*create) {
            if (interactive || projectName.empty()) {
                creator.interactiveCreate();
            } else {
                creator.createProject(projectName, templateName);
            }
        }
        else if (*dev) {
            if (verbose) {
                Logger::debug("Starting development server with verbose output");
            }
            devServer.start(devPort, openBrowser);
        }
        else if (*build) {
            if (verbose) {
                Logger::debug("Building for production with output directory: " + outDir);
            }
            builder.build(minify, outDir);
        }
        else if (*preview) {
            if (verbose) {
                Logger::debug("Starting preview server on port " + std::to_string(previewPort));
            }
            builder.preview(previewPort);
        }
        else if (*configList) {
            configManager.list();
        }
        else if (*configSet) {
            configManager.set(configKey, configValue);
        }
        else if (*pluginList) {
            pluginManager.list();
        }
        else if (*pluginInstall) {
            pluginManager.install(pluginName);
        }
        else if (*info) {
            Logger::section("Project Information");
            std::cout << Colors::BRIGHT_WHITE << "  Current directory: " << Colors::BRIGHT_CYAN 
                      << fs::current_path().string() << Colors::RESET << std::endl;
        
            if (fs::exists("package.json")) {
                Logger::info("Package.json found");
            }
            if (fs::exists("vite.config.js") || fs::exists("vite.config.ts")) {
                Logger::info("Vite configuration found");
            }
        
            std::cout << Colors::BRIGHT_WHITE << "  Node.js version: " << Colors::BRIGHT_GREEN 
                      << "v18.17.0" << Colors::RESET << std::endl;
            std::cout << Colors::BRIGHT_WHITE << "  NPM version: " << Colors::BRIGHT_GREEN 
                      << "9.6.7" << Colors::RESET << std::endl;
            std::cout << std::endl;
        }
        else if (*optimize) {
            Logger::section("Optimizing Dependencies");
            ProgressBar progress(25);
        
            std::vector<std::string> optimizeTasks = {
                "Scanning dependencies",
                "Pre-bundling dependencies",
                "Optimizing chunks",
                "Writing cache"
            };
        
            for (size_t i = 0; i < optimizeTasks.size(); ++i) {
                double prog = static_cast<double>(i + 1) / optimizeTasks.size();
                progress.show(prog, optimizeTasks[i]);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        
            Logger::success("Dependencies optimized!");
        }
        else {
            // Show help if no subcommand is provided
            std::cout << app.help() << std::endl;
        }
        
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    } catch (const std::exception &e) {
        Logger::error("An error occurred: " + std::string(e.what()));
        return 1;
    }

    return 0;
}