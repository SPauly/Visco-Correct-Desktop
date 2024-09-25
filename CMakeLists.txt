# Visco-Correct-Desktop - Correction factors for centrifugal pumps
# Copyright (C) 2023  Simon Pauly
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# Contact via <https://github.com/SPauly/Visco-Correct-Desktop>
cmake_minimum_required(VERSION 3.14)

project(Visco-Correct-Desktop VERSION 1.0.0)

#####################################################
### Set project configuration
#####################################################

# Set the Version and SONAME 
set(VCD_VERSION ${PROJECT_VERSION})
set(VCD_SOVERSION 0)

# Set the build options
option(VCD_BUILD_TESTS "Build tests for Visco-Correct-Desktop" ON)
option(VCD_DIRECTX12 "Use DirectX for rendering" ON)

# Set the installation options (default to ON if building as a standalone project)
set(VCD_INSTALL_default ON)

# Install ViscosityCorrectCore into the build directory by default
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation directory" FORCE)

# Set the installation directories
set(VCD_INSTALL_INCLUDEDIR "include" CACHE STRING "Installation directory for headers")
set(VCD_INSTALL_CMAKEDIR "lib/cmake/Visco-Correct-Desktop" CACHE STRING "Installation directory for cmake config files")
set(VCD_INSTALL_SHAREDIR "share/Visco-Correct-Desktop" CACHE STRING "Installation directory for root certificates")


#####################################################
### Build imgui 
#####################################################

set(IMGUI_SRC 
    "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui.cpp"
    "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui_demo.cpp"
    "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp"
    "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp"
    "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp"
)

if(VCD_DIRECTX12)
    list(APPEND IMGUI_SRC "${PROJECT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_dx12.cpp")
    list(APPEND IMGUI_SRC "${PROJECT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_win32.cpp")
else()
    list(APPEND IMGUI_SRC "${PROJECT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_glfw.cpp")
    list(APPEND IMGUI_SRC "${PROJECT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp")
endif()

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC
    "${PROJECT_SOURCE_DIR}/third_party/imgui"
    "${PROJECT_SOURCE_DIR}/third_party/imgui/backends"
)

if(VCD_DIRECTX12)
    target_compile_definitions(imgui PRIVATE ImTextureID=ImU64)
    target_link_libraries(imgui PRIVATE d3d12.lib d3dcompiler.lib dxgi.lib)
endif()

#####################################################
### Build ViscosityCorrectCore
#####################################################

add_subdirectory(third_party/ViscoCorrectCore)

#####################################################
### Build ViscosityCorrectDesktop
#####################################################

set(VCD_SRC 
    "src/application.cpp"
    "src/calculator_view.cpp"
)

add_executable(Visco-Correct-Desktop
    ${VCD_SRC}
    "src/directx12_main.cpp"
)

add_dependencies(Visco-Correct-Desktop imgui ViscoCorrectCore)

target_include_directories(Visco-Correct-Desktop PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(Visco-Correct-Desktop PRIVATE ViscoCorrectCore imgui)

#####################################################
### Install Rules
#####################################################

# Install the executable
install(TARGETS Visco-Correct-Desktop
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    COMPONENT Visco-Correct-Desktop
)

# Install license and documentation files
install(FILES 
    LICENSE
    README.md
    "${PROJECT_SOURCE_DIR}/imgui.ini"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)