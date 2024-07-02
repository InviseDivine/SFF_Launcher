cmake_minimum_required(VERSION 3.5.0)
project(SFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCES
    "src/*.cpp"
    "libs/imgui/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(libs/openssl-cmake ${CMAKE_CURRENT_BINARY_DIR}/libs/openssl-cmake)

add_library(OpenSSL::SSL STATIC IMPORTED)
add_library(OpenSSL::Crypto STATIC IMPORTED)
set_target_properties(OpenSSL::SSL PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/openssl-cmake/openssl-prefix/src/openssl/usr/local/lib/libssl.a)
set_target_properties(OpenSSL::Crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libs/openssl-cmake/openssl-prefix/src/openssl/usr/local/lib/libcrypto.a)
set(OPENSSL_ROOT_DIR ${CMAKE_BINARY_DIR}/libs/openssl-cmake/openssl-prefix/src/openssl/usr/local)
set(OPENSSL_INCLUDE_DIR ${CMAKE_BINARY_DIR}/libs/openssl-cmake/openssl-prefix/src/openssl/usr/local/include)

set(HAVE_OPENSSL_CRYPTO_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_ERR_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_PEM_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_RSA_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_SSL_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_X509_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_OPENSSL_RAND_H TRUE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_STATUS TRUE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_SCREEN FALSE CACHE INTERNAL "" FORCE)
set(HAVE_RAND_EGD FALSE CACHE INTERNAL "" FORCE)
set(CURL_USE_SCHANNEL TRUE CACHE INTERNAL "" FORCE)
set(CURL_BUILD_EXE FALSE CACHE INTERNAL "" FORCE)
set(ENABLE_EXPORTS ON "" CACHE INTERNAL "" FORCE)
set(HTTP_ONLY OFF "" CACHE INTERNAL "" FORCE)
set(GLEW_USE_STATIC_LIBS ON "" CACHE INTERNAL "" FORCE)
set(CMAKE_USE_WINSSL ON)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glew/build/cmake)
add_subdirectory(libs/curl)
add_subdirectory(libs/bit7z)
if (UNIX)
    find_package(OpenGL REQUIRED)
    set(GL_INCLUDES ${OPENGL_INCLUDE_DIRS})
    set(GL_LIBS ${OPENGL_LIBRARIES})
else()
    set(GL_INCLUDES "")
    set(GL_LIBS opengl32)
endif()

target_link_libraries(${PROJECT_NAME} glfw ${GL_LIBS} libcurl OpenSSL::SSL bit7z)
target_include_directories(${PROJECT_NAME} PRIVATE 
    "include/"
    "libs/imgui/"
    "libs/glfw/include/"
    "libs/glew/include/"
    "libs/stb/"
    "libs/curl/include/"
    "libs/curl/include/"
    "include/openssl-cmake"
    "libs/bit7z"
    ${GL_INCLUDES}
)