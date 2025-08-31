export module sofia.util.fs.reading;

import <filesystem>;
import <format>;
import <fstream>;
import <stdexcept>;

import sofia.util.typedefs;

export namespace sofia {
    [[nodiscard]] s8 read_file(const std::filesystem::path &path) {
        if (!std::filesystem::exists(path))
            throw std::runtime_error(std::format("File not found: {}", path.string()));

        std::ifstream file(path, std::ios::binary | std::ios::ate);

        if (!file)
            throw std::runtime_error(std::format("Failed to open a file: {}", path.string()));

        const std::streamsize size = file.tellg();

        if (size == static_cast<std::streamsize>(-1))
            throw std::runtime_error(std::format("Failed to get file size: {}", path.string()));

        if (size == 0)
            return {};

        s8 content(size, '\0');

        file.seekg(0);
        file.read(content.data(), size);

        if (!file)
            throw std::runtime_error(std::format("Failed to read file: {}", path.string()));

        return content;
    }
}