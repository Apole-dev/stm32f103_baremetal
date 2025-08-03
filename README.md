# STM32F103 Bare-Metal Development Environment

A professional, modular, and reproducible bare-metal development environment for the STM32F103 (Blue Pill) microcontroller, built on Docker and a custom Makefile. This project is designed to provide a clean, portable, and CI/CD-ready foundation for robust embedded systems development, completely independent of vendor-provided HALs.

## Core Philosophy

* **Bare-Metal Control:** Direct hardware register access for maximum performance, control, and understanding. No black boxes.
* **Modularity:** A layered architecture (MCAL, BSP, Drivers, App) to ensure code is reusable, testable, and maintainable.
* **Reproducibility:** A Docker-based toolchain guarantees that anyone can build the project with the exact same environment, eliminating "it works on my machine" issues.

## Features

* **Dockerized Toolchain:** Includes `arm-none-eabi-gcc`, `gdb-multiarch`, and `openocd` in a self-contained, isolated environment.
* **Advanced Makefile:** Features automatic source file discovery, header dependency tracking, and separate `DEBUG`/`RELEASE` build configurations.
* **Layered Architecture:** Clean separation of concerns between the application logic, board-specific code, and low-level hardware access.
* **CI/CD Ready:** Integrated with GitHub Actions for automated builds and static analysis checks (`clang-format`, `clang-tidy`).

## Prerequisites

* Docker must be installed and running.

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/Apole-dev/stm32f103_baremetal.git

cd stm32f103_baremetal
````

### 2\. Build the Development Environment

This command uses the `Dockerfile` to build a local Docker image containing all the necessary tools. This only needs to be done once, or whenever the `Dockerfile` is updated.

```bash
./build-env.sh
```

(If you do not have the `build-env.sh` script, use the `docker build ...` command directly.)

### 3\. Compile the Project

Use the provided helper script to run `make` commands inside the Docker container.

  * To build the project:
    ```bash
    ./build.sh
    ```
  * To clean the build artifacts:
    ```bash
    ./build.sh clean
    ```
  * To flash the binary to the target:
    ```bash
    ./build.sh flash
    ```

## Hardware Target

This project is configured and tested for the following hardware:

  * **MCU:** STM32F103C8T6
  * **Board:** "Blue Pill" development board
  * **Crystal:** 8MHz HSE (High-Speed External)

