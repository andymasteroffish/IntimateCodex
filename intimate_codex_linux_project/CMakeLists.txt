cmake_minimum_required(VERSION 3.3)
project(IntimateCodex)
set(APP_NAME IntimateCodex)

# ===================== Local Directories =====================
set(PROJECT_ROOT_DIRECTORY "/home/jarl/Programming/IntimateCodex")

# ===================== oF Directory =====================
set(OF_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/libs/of_v0.9.3_linux64_release")

# ===================== Source Directory =====================
set(SOURCE_DIRECTORY "../src")

# ===================== Compiler Flags =====================
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
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
add_dependencies(${APP_NAME} of_shared)
target_link_libraries(${APP_NAME} $<TARGET_FILE:of_shared>)
target_link_libraries(${APP_NAME} ${OF_CORE_LIBS})


set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
