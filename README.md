![](https://github.com/senselogic/PCF/blob/master/LOGO/pcf.png)

# PCF : Point Cloud Format

Point cloud serialization library.

## Goals

* Simple
* Complete
* Compressible

## Features

* Per-component compression
* Spatial clustering
* Multiple scans
* Scan images

## Version

0.1

## Limitations

* The first three components are expected to :
  * be the point coordinates;
  * use the same compression method.
* The point order is not kept when the coordinate components are discretized.

## Author

Eric Pelzer (ecstatic.coder@gmail.com).

## License

This project is licensed under the GNU Lesser General Public License version 3.

See the [LICENSE.md](LICENSE.md) file for details.
