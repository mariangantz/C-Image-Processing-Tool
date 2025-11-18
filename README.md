## C Image Processing Tool

This project is a comprehensive toolkit implemented entirely in **C**, designed for image manipulation and filtering. Its core is a powerful image processing library that operates on 3D matrix structures, accessible through a dynamic **Command Line Interface (CLI)**.

---

## Key Features

The project offers a wide range of operations, with efficient memory management for all data structures.

### 1. Geometric and Compositional Manipulations

- **Horizontal Flip**: Reverses pixels along the horizontal axis (`flip_horizontal`).
- **Left Rotation**: Rotates the image 90 degrees counter-clockwise (`rotate_left`).
- **Cropping**: Extracts a sub-region specified by coordinates and dimensions (`crop`).
- **Extension (Padding)**: Adds borders of specified dimensions and color around the image (`extend`).
- **Pasting (Overlay)**: Overlays a source image onto a destination image at a given starting position (`paste`).

### 2. Filtering and I/O

- **Convolution Filtering**: Applies user-defined convolution filters (of any size, e.g., 3x3, 5x5) for operations like blurring or sharpening (`apply_filter`).
- **BMP I/O**: Support for reading from and writing to 24-bit BMP files.

### 3. Architecture

- **Interactive CLI**: A robust command-line interface that allows for the dynamic loading, saving, manipulation, and management of multiple images and filters throughout the session.
- **Memory Management**: Custom functions are implemented for the efficient allocation (`aloc` / `alocare`) and deallocation (`fr` / `frri`) of three-dimensional image structures.

---

## Build and Run

The project uses a standard `Makefile` for compilation.

### Compilation

```bash
make interactive
