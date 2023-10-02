

# Usage Documentation

## Introduction

This C++ program reads data from an input file, performs calculations to estimate roll and pitch angles, and writes the results to an output file. It provides an option for debugging to calculate and display the maximum roll angle difference.

  

## Command-line Usage

To compile the program, use the following command-line format:
```bash
g++ main.cpp -o estimator
```
This will result in the `estimator` binary being created, to run the program, use the following command-line format:

```bash
./estimator [flag]
```

- **`[flag]`**: An optional argument. If 1 is provided, comparison mode is enabled, and the program calculates and displays the maximum roll angle difference. If not provided or any other value is provided, comparison mode is disabled.

## Input File

The program expects an input file named attitude_exam.log, which should contain lines of data in the following format:

  
```
<timestamp_str;  accel_x_str;  accel_y_str;  accel_z_str>
```
  
  

- **`timestamp_str`**: A string representing a timestamp in milliseconds.

- **`accel_x_str`**, **`accel_y_str`**, **`accel_z_str`**: Strings representing accelerometer readings in millig-units.

## Output File

The program generates an output file named output.log. This file contains lines in the following format:

  
```bash
<timestamp;  a_roll;  a_pitch>
```
 - **`timestamp`**: The timestamp from the input file.
  - **`a_roll, a_pitch`**: The estimated roll and pitch angles in radians.

## Comparison Mode

When comparison mode is enabled (by providing a flag of 1 as the argument), the program calculates and displays the maximum roll angle difference. This difference is calculated as the absolute difference between the roll angle calculated by the stable approximation method and the precise roll angle, converted to degrees.

Example comparison output:
  
```bash
Roll: 0.123;
```
## Error Handling

The program performs error checking and handles the following exceptions:

 - **`Unable to open the input file`**: The program will display an error
   message and terminate.
   
 - **`Unable to open the output file`**: The program will display an error
   message and terminate. 

 - **`Division by zero in calculateRollPitch`**: The program will display an error
   message and terminate.

**Note:** Ensure that the input file attitude_exam.log exists in the same directory as the program


# Development of the Attitude Estimation Program

## Background
In the development of the Attitude Estimation Program, I began by studying the article "Tilt Sensing Using a Three-Axis Accelerometer" provided by NXP. This article introduced the concept of using a three-axis accelerometer for attitude estimation, specifically focusing on the aerospace rotation sequence.

## Initial Implementation
After gaining a solid understanding of the aerospace rotation sequence, I proceeded to implement the attitude estimation algorithm in C++. The initial implementation followed the precise calculations described in the NXP article. This method worked well; however, in the article it was said tjat this method could potentially cause errors when the `accel_z` component of the accelerometer readings was zero.

## Introducing the Stabilizing Factor
To address the potential issues related to division by zero, I continued reading the NXP article and discovered the method of introducing a stabilizing factor to the calculations. This modification aimed to prevent division by zero while still providing reasonable estimates of roll and pitch angles.

## Comparison of Methods
With both the precise and stabilized methods implemented, I decided to compare their results. Recognizing that the approximation introduced by the stabilizing factor might lead to small differences in angle estimates, I conducted a comparison between the two methods. I wanted to understand the extent of the differences and ensure that the stabilized method provided accurate results.

## Validation with Dataset
To validate the accuracy of the program, I used a provided dataset for testing. During the testing process, I observed that the biggest difference between the roll angles estimated by the two methods was approximately 0.05 degrees. Considering this difference to be within an acceptable range, I decided to make the stabilized calculation method the main function of the program. However, I retained the precise calculation method as an option for comparison purposes, particularly when working with different datasets.

In summary, the development of the Attitude Estimation Program involved studying the NXP article, implementing the algorithm, addressing potential issues, comparing methods, and validating the program's accuracy with the data provided.