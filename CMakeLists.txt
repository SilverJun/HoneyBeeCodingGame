cmake_minimum_required(VERSION 3.17)
project(HoneyBeeCodingGame)

set(CMAKE_CXX_STANDARD 17)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET(OS "windows")

    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    find_package(OpenGL REQUIRED)
#    find_package(PythonLibs REQUIRED)
    set(PYTHON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/python310/include")
    set(PYTHON_LIBRARIES "${CMAKE_SOURCE_DIR}/thirdparty/python310/libs/python310.lib")
    include_directories("${CMAKE_SOURCE_DIR}/include")
    include_directories(${PYTHON_INCLUDE_DIR})
    set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glew32.lib")
    set(GLFW_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glfw3.lib")
ELSE()
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        # Mac OS X specific code
        SET(OS "macos")
        LINK_DIRECTORIES(/usr/local/lib)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        SET(OS "linux")
    ENDIF()

    find_package(PkgConfig REQUIRED)

    find_package(OpenGL REQUIRED)
    pkg_check_modules(GLEW REQUIRED glew)
    pkg_check_modules(GLFW REQUIRED glfw3)
    pkg_check_modules(GLM REQUIRED glm)
    find_package(PythonLibs REQUIRED)

    message("check glew include: ${GLEW_INCLUDE_DIRS}")
    message("check glfw include: ${GLFW_INCLUDE_DIRS}")
    message("check glm include: ${GLM_INCLUDE_DIRS}")

    include_directories(${OPENGL_INCLUDE_DIR})
    include_directories(${GLEW_INCLUDE_DIRS})
    include_directories(${GLFW_INCLUDE_DIRS})
    include_directories(${GLM_INCLUDE_DIRS})
    # include_directories(${VULKAN_INCLUDE_DIRS})
    include_directories(${PYTHON_INCLUDE_DIRS})
ENDIF()

include_directories(${PROJECT_SOURCE_DIR}/thirdparty/fmod/${OS}/include)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})

message("check opengl library: ${OPENGL_gl_LIBRARY}")
message("check glew library: ${GLEW_LIBRARIES}")
message("check glfw library: ${GLFW_LIBRARIES}")
message("check python include: ${PYTHON_INCLUDE_DIR}")
message("check python library: ${PYTHON_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
file(GLOB FMOD_LIBRARIES "${PROJECT_SOURCE_DIR}/thirdparty/fmod/${OS}/lib/*.*")
target_link_libraries(${PROJECT_NAME} ${FMOD_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})

# target_link_libraries(${PROJECT_NAME} ${VULKAN_LIBRARIES})
