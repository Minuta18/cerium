# Building Cerium

This project uses CMake and requires a C++23 compatible compiler. It relies on OpenGL (with GLAD as the loader) and GLFW for the graphical backend. The RmlUi library is automatically fetched during the CMake configuration step.

## 1. Installing Dependencies

### Debian / Ubuntu
Update your package lists and install the required build tools, along with the GLFW and FreeType libraries:

```bash
sudo apt update
sudo apt install build-essential cmake git \
                 libgl1-mesa-dev \
                 libglfw3-dev \
                 libfreetype6-dev
```

### RHEL / Fedora

For RHEL-based distributions, install the dependencies using the DNF package manager:

```bash
sudo dnf install gcc-c++ cmake git \
                 mesa-libGL-devel \
                 glfw-devel \
                 freetype-devel
```

## 2. Setting Up GLAD

The GLAD loader must be generated and placed in the project tree before building.

1. Navigate to the [GLAD web generator](https://glad.dav1d.de/).
2. Select the following options:

* **Language:** C/C++
* **Specification:** OpenGL
* **API / gl:** Version 4.6 ( **Core** profile)

3. Click **Generate** and download the archive.
4. Extract the files into the `/lib/glad/` directory so the project structure looks like this:

```text
Cerium/
├── lib/
│   └── glad/
│       ├── include/
│       │   ├── glad/glad.h
│       │   └── KHR/khrplatform.h
│       └── src/
│           └── glad.c
├── src/
├── CMakeLists.txt
└── BUILD.md

```

## 3. Build

Use a standard out-of-source CMake build approach:

```bash
# Navigate to the project root
mkdir build
cd build

# Configure the project (CMake will automatically fetch RmlUi)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build . -j$(nproc)

```

After a successful build, the `CeriumApp` executable will be located in the `build/src/` directory.
