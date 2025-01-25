# 3D printer Enclosure Manager

This project contains a program to manage a 3D printer enclosure it contains a 12v fan controlled by a mosfet
and a temperature sensor.

## Documentation

This project has two components the embedded code located in ./target with an
entry point in main.c and the driver which can be found in ./driver-rust/ and
has an entry point in main.rs.

### Communications

The driver and the embedded controller communicate using the custom can protocol
defined in the ./target/libs folder. It uses the following packet identifiers

| Identifier | Function | Direction |
| - | - | - |
| 0x00 | Get Fan speed in RPM | PC->MCU |
| 0x01 | Set Fan speed | PC->MCU |
| 0x02 | Get Temperature in C last 4 digits are after decimal place | PC->MCU |

### Testing

This project uses the [unity](https://github.com/ThrowTheSwitch/Unity) test framework to allow unity testing. This is supplemented by the [FFF](https://github.com/meekrosoft/fff) Fake Function Framework used for faking where needed. The tests are located in `./tests/` and use cmake for execution. It can be manually executed from the host directory using:

```bash
cmake -B build tests
cmake --build build --parallel
ctest --test-dir build --output-on-error
```

Or using the provided bash script as follows:

```bash
source run_tests.sh
```