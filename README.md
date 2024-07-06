
# Image Resizing with OpenCV and Custom Implementations

## Overview

This project is an assignment focused on image resizing using OpenCV and custom C++ implementations. The assignment evaluates the understanding of OpenCV, writing optimal C/C++ code, debugging, and performance optimization. The project involves three main steps:
1. Resizing an image using OpenCV's `cv::resize` function with three different interpolation methods.
2. Measuring the timing for 1000 iterations of each interpolation method.
3. Implementing custom resizing functions and comparing their performance with OpenCV's functions.

## Assignment Tasks

### Task 1: Image Resizing using OpenCV

- **Function Used:** `cv::resize`
- **Interpolation Methods:**
  - `INTER_NEAREST`
  - `INTER_LINEAR`
  - `INTER_CUBIC`
- **Input Image:** [G178_2-1080.BMP](https://avproglobal.egnyte.com/fl/V6JZASnouL)
- **Output Images:**
  - `Nearest.png`
  - `Linear.png`
  - `Cubic.png`

### Task 2: Measure Timing for 1000 Iterations

- **Methods:**
  - `INTER_NEAREST`
  - `INTER_LINEAR`
  - `INTER_CUBIC`
- **Timing Calculation:**
  - Measure the time taken for 1000 iterations of each method.

### Task 3: Custom Implementation

- **Custom Function:**
  - Implement custom functions for image resizing equivalent to `cv::resize`.
- **Comparison:**
  - Compare the output of the custom functions with OpenCV's functions for correctness.
  - Measure and compare the performance (timing) for all three methods of interpolation.

## Code Overview

### Dependencies

- OpenCV

### Building the Project

1. Ensure you have OpenCV installed on your system.
2. Clone the repository or download the project files.
3. Navigate to the project directory.

#### Compile the Code

```bash
g++ -o main Main.cpp `pkg-config --cflags --libs opencv4`
```

#### Run the Application

```bash
./main
```

### Explanation of Key Functions

- **`stepOne`**:
  - Resizes the input image using OpenCV's `cv::resize` function with three interpolation methods.
  - Saves the resized images.
- **`stepTwo`**:
  - Measures and prints the time taken for 1000 iterations of each interpolation method.
- **`customNearest`**:
  - Implements a custom nearest neighbor interpolation.
  - Saves the resized image.
  
### Example Output

- **Timing for 1000 iterations:**
  - `INTER_NEAREST`: [ ] ms
  - `INTER_LINEAR`: [ ] ms
  - `INTER_CUBIC`: [ ] ms

- **Resized Images:**
  - `Nearest.png`
  - `Linear.png`
  - `Cubic.png`
  - `CustomNearestResult.png`

### Notes

- Ensure to use a complete CPU to maximize performance and avoid running any compute-intensive workload while measuring performance.
- For all resize operations, the new height is `original_height / 2` and the new width is `original_width / 2`.

## Submission Instructions

- Provide a clear README.md explaining how to build and run the application locally.
- Include any necessary dependencies and installation instructions.
- Include comments where necessary.
- Submit the assignment via a Git repository or a compressed file.
