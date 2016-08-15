cmake_minimum_required(VERSION 3.3)
project(IntimateCodex)
set(APP_NAME IntimateCodex)

# ===================== Local Directories =====================
set(PROJECT_ROOT_DIRECTORY "..")

# ===================== oF Directory =====================
set(OF_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/libs/of_v0.9.3_linux64_release")

# ===================== Source Directory =====================
set(SOURCE_DIRECTORY "${PROJECT_ROOT_DIRECTORY}c/src")

# ===================== Compiler Flags =====================
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Set correct shared library search paths
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'lib/'")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,'lib/'")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# =========== Set Global Properties ==============
include(addons)
include(linux64)

# ===================== Source Files =====================
set(SOURCE_FILES
        ${ADDON_SOURCE_FILES}
		${SOURCE_DIRECTORY}/Background.cpp
		${SOURCE_DIRECTORY}/main.cpp
		${SOURCE_DIRECTORY}/ofApp.cpp
		${SOURCE_DIRECTORY}/TextInput.cpp
		${SOURCE_DIRECTORY}/Word.cpp)

# ===================== Headers Files =====================
set(HEADER_FILES
		${SOURCE_DIRECTORY}/Background.h
		${SOURCE_DIRECTORY}/ofApp.h
		${SOURCE_DIRECTORY}/TextInput.h
		${SOURCE_DIRECTORY}/Word.h)

# ===================== System Frameworks =====================

# =============================================================

# ===================== Include Dirs =====================

# ========================================================

# ===================== Libs =====================

# ================================================

# ============ Compile and Link ==================

add_executable(${APP_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Copy data files to the output directory
add_custom_command(TARGET IntimateCodex
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../data ${PROJECT_SOURCE_DIR}/bin/data)

# Create a lib directory for bundled shared libraries
add_custom_command(TARGET IntimateCodex
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/bin/lib/)

# Copy the fmod shared library to the lib directory
add_custom_command(TARGET IntimateCodex
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../libs/of_v0.9.3_linux64_release/libs/fmodex/lib/linux64/libfmodex.so ${PROJECT_SOURCE_DIR}/bin/lib/)

add_dependencies(${APP_NAME} of_shared)
target_link_libraries(${APP_NAME} $<TARGET_FILE:of_shared>)
target_link_libraries(${APP_NAME} ${OF_CORE_LIBS})


set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)