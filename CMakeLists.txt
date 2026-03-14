
cmake_minimum_required(VERSION "4.0")
project(HASHABLES VERSION "1.0" LANGUAGES C CXX)

option(NO_CXX "Build without a C++ Compiler or features (default: OFF)." OFF)

set(C_STD "17" CACHE STRING "The C standard revision to build with.")
set(CXX_STD "20" CACHE STRING "The C++ standard revision to build with.")

set(C_COMPILER "//default" CACHE STRING "The C compiler path to build with.")
set(CXX_COMPILER "//default" CACHE STRING "The C++ compiler path to build with.")

set(LIBSSL_PATH "//default" CACHE STRING "The dynamic library of libssl to link with (by default a static library will be used).")
set(LIBCRYPTO_PATH "//default" CACHE STRING "The dynamic library of libcrypto to link with (by default a static library will be used).")

set(OPENSSL_BUILT FALSE)


# Set C/C++ standard revisions based on input
set(CMAKE_C_STANDARD   ${C_STD})
set(CMAKE_CXX_STANDARD ${CXX_STD})

# Include the API layer
include_directories("${PROJECT_SOURCE_DIR}/api/include")

# Handle compiler fields being set to "//default"
if (C_COMPILER STREQUAL "//default")
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(C_COMPILER ${CMAKE_C_COMPILER})
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR BSD)
        set(C_COMPILER "/usr/bin/gcc")
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(C_COMPILER "/usr/bin/clang")
    else()
        message(FATAL_ERROR "Couldn't detect a C compiler based on your system, please specify one using -DC_COMPILER.")
    endif()
endif()
if (CXX_COMPILER STREQUAL "//default")
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(CXX_COMPILER ${CMAKE_CXX_COMPILER})
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR BSD)
        set(CXX_COMPILER "/usr/bin/g++")
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CXX_COMPILER "/usr/bin/clang++")
    else()
        message(FATAL_ERROR "Couldn't detect a C++ compiler based on your system, please specify one using -DCXX_COMPILER.")
    endif()
endif()


# Detect/Build and use libSSL and libCrypto
if (LIBSSL_PATH STREQUAL "//default")
    if (EXISTS "${PROJECT_SOURCE_DIR}/openssl/libssl.a")
        set(LIBSSL_PATH "${PROJECT_SOURCE_DIR}/openssl/libssl.a")
    elseif (EXISTS "${PROJECT_SOURCE_DIR}/openssl/libssl.lib")
        set(LIBSSL_PATH "${PROJECT_SOURCE_DIR}/openssl/libssl.lib")
    elseif (EXISTS "${PROJECT_SOURCE_DIR}/openssl/ssl.lib")
        set(LIBSSL_PATH "${PROJECT_SOURCE_DIR}/openssl/ssl.lib")
    else()
        message(FATAL_ERROR "Couldn't find libssl in any of the following paths:\n\t${PROJECT_SOURCE_DIR}/openssl/ssl.lib\n\t${PROJECT_SOURCE_DIR}/openssl/libssl.a\n\t${PROJECT_SOURCE_DIR}/openssl/libssl.lib")
    endif()

    add_library(LIBSSL STATIC IMPORTED)
    set(LIBSSL_STATIC TRUE)
else()
    if (NOT EXISTS ${LIBSSL_PATH})
        message(FATAL_ERROR "The specified path for libssl doesn't exist.")
    endif()

    add_library(LIBSSL SHARED IMPORTED)
    set(LIBSSL_STATIC FALSE)
endif()
if (LIBCRYPTO_PATH STREQUAL "//default")
    if (EXISTS "${PROJECT_SOURCE_DIR}/openssl/libcrypto.a")
        set(LIBCRYPTO_PATH "${PROJECT_SOURCE_DIR}/openssl/libcrypto.a")
    elseif (EXISTS "${PROJECT_SOURCE_DIR}/openssl/libcrypto.lib")
        set(LIBCRYPTO_PATH "${PROJECT_SOURCE_DIR}/openssl/libcrypto.lib")
    elseif (EXISTS "${PROJECT_SOURCE_DIR}/openssl/crypto.lib")
        set(LIBCRYPTO_PATH "${PROJECT_SOURCE_DIR}/openssl/crypto.lib")
    else()
        message(FATAL_ERROR "Couldn't find libcrypto in any of the following paths:\n\t${PROJECT_SOURCE_DIR}/openssl/crypto.lib\n\t${PROJECT_SOURCE_DIR}/openssl/libcrypto.a\n\t${PROJECT_SOURCE_DIR}/openssl/libcrypto.lib")
    endif()

    add_library(LIBCRYPTO STATIC IMPORTED)
    set(LIBSSL_STATIC TRUE)
else()
    if (NOT EXISTS ${LIBCRYPTO_PATH})
        message(FATAL_ERROR "The specified path for libcrypto doesn't exist.")
    endif()

    add_library(LIBCRYPTO SHARED IMPORTED)
    set(LIBSSL_STATIC FALSE)
endif()
set_target_properties(LIBSSL PROPERTIES IMPORTED_LOCATION ${LIBSSL_PATH})
set_target_properties(LIBCRYPTO PROPERTIES IMPORTED_LOCATION ${LIBCRYPTO_PATH})


file(GLOB_RECURSE LIBHASHABLES_CSRC "${PROJECT_SOURCE_DIR}/lib/src/c/*.c")
if (NO_CXX)
    add_library(LIBHASHABLES STATIC ${LIBHASHABLES_CSRC})
    set_target_properties(LIBHASHABLES PROPERTIES
        OUTPUT_NAME "hashables.c"
        LINKER_LANGUAGE C
    )
    # add shared library
    add_library(DLIBHASHABLES SHARED "${PROJECT_SOURCE_DIR}/dummyfiles/dummy.c")
    set_target_properties(DLIBHASHABLES PROPERTIES
        OUTPUT_NAME "hashables.c"
        LINKER_LANGUAGE C
    )
else()
    add_library(LIBHASHABLES STATIC ${LIBHASHABLES_CSRC} ${LIBHASHABLES_CXXSRC})
    set_target_properties(LIBHASHABLES PROPERTIES
        OUTPUT_NAME "hashables"
        LINKER_LANGUAGE CXX
        CXX_STANDARD_REQUIRED TRUE
    )
    # add shared library
    add_library(DLIBHASHABLES SHARED "${PROJECT_SOURCE_DIR}/dummyfiles/dummy.c")
    set_target_properties(DLIBHASHABLES PROPERTIES
        OUTPUT_NAME "hashables"
        LINKER_LANGUAGE CXX
        CXX_STANDARD_REQUIRED TRUE
    )
endif()
target_include_directories(LIBHASHABLES PRIVATE "${PROJECT_SOURCE_DIR}/openssl/include")
target_link_libraries(LIBHASHABLES LIBSSL LIBCRYPTO)
# link static library to shared to include precompiled object code into it
target_link_libraries(DLIBHASHABLES LIBHASHABLES)
if (NOT LIBSSL_STATIC)
    target_link_libraries(DLIBHASHABLES LIBSSL)
endif()
if (NOT LIBCRYPTO_STATIC)
    target_link_libraries(DLIBHASHABLES LIBCRYPTO)
endif()
