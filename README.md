# verilog-unittest-sample
Sample project for unit testing Verilog modules with Verilator and GoogleTest.

## Build Instructions

To build the project, follow these steps:

```bash
cmake -S . -B build -G Ninja
ninja -C build
```

Once the project is built, you can run the Verilated simulation using the following command:

```bash
build/test_all
```

This command will perform a unit test of the module and output the results.
