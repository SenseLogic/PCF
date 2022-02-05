![](https://github.com/senselogic/PCF/blob/master/LOGO/pcf.png)

# PCF : Point Cloud Format

Point cloud serialization library.

## Goals

* Simplicity : uses simple data structures and a straightforward serialization format
* Versatility : stores multiple scans with any number of components, images or properties
* Portability : implemented both in C++ and D, without using any external dependencies
* Compactness : minimizes the number of bits per component through spatial clustering

## Installation

### C++ version

Install CMake and a C++ compiler (g++, Visual C++).

Build the executable with the following command lines :

```bash
cd CODE/CPP/TOOL
./make.sh
```

### D version

Install the [DMD 2 compiler](https://dlang.org/download.html) (using the MinGW setup option on Windows).

Build the executable with the following command lines :

```bash
cd CODE/D/TOOL
./make.sh
```

## Command line

```
pcf [options]
```

### Options

```
--read-pts <file path> <position bit count> <position precision> : read a PTS point cloud file
--read-ptx <file path> <position bit count> <position precision> : read a PTX point cloud file
--read-pcf <file path : read a PCF point cloud file
--write-pts <file path : write a PTS point cloud file
--write-ptx <file path : write a PTX point cloud file
--write-pcf <file path : write a PCF point cloud file
```

### Examples

```bash
pcf --read-ptx cloud.ptx 8 0.001 --write-pcf cloud.pcf
```

Reads a PTX point cloud file and writes a PCF point cloud file.

```bash
pcf --read-pcf test.pcf --write-ptx test.ptx
```

Reads a PCF point cloud file and writes a PTX point cloud file.

## Version

0.1

## Limitations

* All scans share the same list of components.
* The first three components are expected to be the point coordinates.
* The point order is lost if the coordinate components are discretized.

## Author

Eric Pelzer (ecstatic.coder@gmail.com).

## License

This project is licensed under the GNU Lesser General Public License version 3.

See the [LICENSE.md](LICENSE.md) file for details.
