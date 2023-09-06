#pragma once
#include <filesystem>
#include <limits>

constexpr int ERROR_CODE_SDL_INIT_FAIL = 1;
constexpr int ERROR_CODE_FILE_EXCEPTION = 2;
constexpr int ERROR_CODE_JSON_PARSE = 3;

constexpr double pi = 3.14159265358979323846;
constexpr double qNaN = std::numeric_limits<double>::quiet_NaN();
const std::filesystem::path scene_file_path = "scene.json";
