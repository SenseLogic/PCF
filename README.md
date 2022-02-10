![](https://github.com/senselogic/PCF/blob/master/LOGO/pcf.png)

# PCF

Point cloud file format.

## Goals

* Simplicity : uses simple data structures with direct access to the point components.
* Versatility : stores multiple scans with any number of components, properties and images.
* Compactness : minimizes the number of bits per component through spatial clustering.
* Performance : can store huge point clouds in memory and serialize them at high speed.
* Portability : implemented in both C++ and D, without using any external dependencies.

## Installation

### C++ version

Install g++ or [Visual C++ 2019 Community](https://docs.microsoft.com/en-us/visualstudio/releases/2019/redistribution#vs2019-download).

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
--dump : dump the point cloud
--write-pts <file path> : write a PTS point cloud file
--write-ptx <file path> : write a PTX point cloud file
--write-pcf <file path> : write a PCF point cloud file
```

### Examples

```bash
pcf --read-ptx cloud.ptx 8 0.001 --dump --write-pcf cloud.pcf
```

Reads a PTX point cloud file, dumps it, and writes a PCF point cloud file.

```bash
pcf --read-pcf test.pcf --dump --write-ptx test.ptx
```

Reads a PCF point cloud file, dumps it, and writes a PTX point cloud file.

## Version

0.3

## Limitations

* All scans share the same list of components.
* The first three components are expected to be the point coordinates.
* The point order is lost if the coordinate components are discretized.

## Author

Eric Pelzer (ecstatic.coder@gmail.com).

## License

This project is licensed under the GNU Lesser General Public License version 3.

See the [LICENSE.md](LICENSE.md) file for details.
