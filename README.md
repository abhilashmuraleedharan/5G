# 5G Utilities

Welcome to the 5G Utilities repository! This collection of tools assists in understanding and optimizing 5G telecommunications technology. Each utility is designed to perform specific calculations, such as determining data throughput, spectral efficiency, Shannon's Capacity, and more.

## Repository Structure

The project is organized into following directories:

- **/utilities/**: Contains individual directories for each utility.
- **/shared/**: Contains shared source code and headers used across multiple utilities.
- **/tests/**: Holds test cases for the utilities, using Google Test for automated testing.

Each utility within the `/utilities/` directory is structured as follows:

```
/utilities/WavelengthCalculator/
    ├── src/
    │   └── main.cpp
    └── include/
        └── ... (any additional headers)
```

## Getting Started

To clone and run the utilities in this repository, follow these steps:

### Prerequisites

- A modern C++ compiler supporting C++11
- CMake version 3.14 or higher
- Google Test installed on your system

### Clone the Repo

Clone this repository to your local machine:

```bash
git clone https://github.com/abhilashmuraleedharan/5G.git
cd 5G
```

### Google Test Setup

The automated testing framework uses Google Test, which is included as a submodule. To set it up, run:

```bash
git submodule update --init --recursive
```

### Configure and Build

From the root directory of the project:

```bash
mkdir build
cd build
cmake ..
make
```

This will generate the executable files for all utilities and place them inside the `build` directory.

### Running the Utilities

After building, you can run the utilities from within the `build` directory. For example:

```bash
./WavelengthCalculator
```

Replace `WavelengthCalculator` with the name of the utility you want to run.

### Running Automated Tests

To run the automated tests compiled with the utilities, use the following command:

```bash
./utilities_test
```

This will execute all tests linked with the Google Test framework.

## Contributing

If you're interested in contributing to this project, I welcome your input and support. Here are some ways you can contribute:

- **Reporting bugs**: If you find any issues, please let me know by filing a bug report.
- **Suggesting enhancements**: Have ideas on how to make these utilities better? Please share!
- **Adding new utilities**: Contribute your own utility by following the steps mentioned in the next section.
- **Writing automated test cases**: Improve the reliability of the utilities by writing automated test cases in the `/tests/` directory.

Please follow the existing code style, and provide clear documentation for your contributions. For significant changes, please open an issue to discuss what you would like to change.
If you have developed a new utility that you'd like to share, please follow these guidelines to ensure it integrates smoothly with the existing structure.

### Adding New Utilities

When contributing new utilities, please ensure you add a corresponding CMake build configuration for your utility and tests in the `CMakeLists.txt` file.

```
/utilities/
├── YourNewUtility/
│   ├── src/
│   │   └── main.cpp
│   └── include/
│       └── ... (any additional header files)
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Contact

If you have any questions or feedback, please file an issue in this repository or contact me directly at `abhilashmuraleedharan@outlook.com`.

Enjoy the utilities, and happy coding!
