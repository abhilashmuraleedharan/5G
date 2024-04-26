# 5G Utilities

Welcome to the 5G Utilities repository! This project is designed to provide tools and programs that assist in understanding and optimizing 5G technology. Our utilities are written in C++ and can help you calculate key metrics such as data throughput, spectral efficiency, Shannon's Capacity, and more.

## Features

This repository includes utilities for:
- **Determining Shannon's Capacity**: This utility calculates the maximum theoretical bandwidth of a communication channel under certain conditions based on the bandwidth and signal-to-noise ratio.

## Getting Started

Follow these steps to clone and run the utilities in this repository:

### Prerequisites

You will need:
- A C++ compiler (GCC recommended)
- Make (optional, for using the Makefile)
- CMake (for compiling Google Test)

### Clone the Repo

First, clone this repository to your local machine:

```bash
git clone https://github.com/yourusername/5G.git
cd 5G
```

### Google Test Setup

This project uses Google Test as a submodule for its automated testing framework. Follow these steps to initialize and prepare Google Test:

1. Initialize the Google Test submodule:
   ```bash
   git submodule update --init --recursive
   ```

2. Compile Google Test:
   ```bash
   cd googletest
   mkdir build
   cd build
   cmake ..
   make
   cd ../../
   ```

### Build the Utilities

You can build the utilities individually or all at once. 

Here's how to compile them using the Makefile that includes Google Test:
```bash
make all
```

Here's how to compile them individually:
```bash
g++ -o WavelengthCalculator main_wavelength.cpp utilities.cpp -lm
g++ -o ShannonsCapacityCalculator main_shannons_capacity.cpp utilities.cpp -lm
```
### Run the Utilities

After building, you can run each utility by executing the corresponding executable. For example:

```bash
./WavelengthCalculator
./ShannonsCapacityCalculator
```

### Run Automated Tests

To run the automated tests for verifying the functionality of the utilities:

```bash
./utilities_test
```

## Contributing

We welcome contributions from the community. Here are some ways you can contribute:
- **Reporting bugs**: If you find any issues, please let us know by filing a bug report.
- **Suggesting enhancements**: Have ideas on how to make these utilities better? Share them with us!
- **Adding new utilities**: If you have a useful calculation that fits this project, please consider contributing it.
- **Writing automated test cases**: Help improve the reliability of our utilities by writing automated test cases using Google Test. See the `utilities_test.cpp` file for an example of how to write test cases for the `calculateWavelength` function. This is a great way to ensure that the functions work as expected and remain stable through future changes.

To contribute, please fork the repository and use a pull request to submit your changes for review. Ensure you follow the existing code style and add comments where necessary. For more substantial contributions, including new features and utilities, please open an issue to discuss your ideas before beginning work. This helps avoid duplicate efforts and ensures that your contribution fits seamlessly into the project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Contact

If you have any questions or feedback, please file an issue in this repository or contact me directly at `abhilashmuraleedharan@outlook.com`.

Happy Calculating!
