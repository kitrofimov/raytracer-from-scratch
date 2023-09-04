#pragma once
#include <filesystem>

constexpr int ERROR_CODE_SDL_INIT_FAIL = 1;
constexpr int ERROR_CODE_FILE_EXCEPTION = 2;
constexpr int ERROR_CODE_JSON_PARSE = 3;

constexpr double pi = 3.14159265358979323846;
const std::filesystem::path scene_file_path = "scene.json";
