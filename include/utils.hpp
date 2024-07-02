#pragma once
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <curl/curl.h>
#include <string>

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
void download(std::string url, std::string path);