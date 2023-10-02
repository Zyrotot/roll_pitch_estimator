#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Constants
const double STABILIZING_FACTOR = 0.01;
const double RAD_TO_DEG = 180.0 / M_PI;

// Function to calculate roll and pitch using aerospace rotation sequence
void calculateRollPitch(double ax, double ay, double az, double &roll, double &pitch) {
    if (az == 0.0) {
        cerr << "Error: Division by zero in calculateRollPitch." << endl;
        return;
    }
    
    roll = atan2(ay, az);
    pitch = atan2(-ax, sqrt(ay * ay + az * az));
}

// Function to calculate roll and pitch using aerospace rotation sequence with stabilization
void calculateApproximateRollPitch(double ax, double ay, double az, double &roll, double &pitch) {
    int sign = (az >= 0) ? 1 : -1;

    double denominator = sqrt(az * az + (STABILIZING_FACTOR * ax * ax));
    roll = atan2(ay, sign * denominator);
    pitch = atan2(-ax, sqrt(ay * ay + az * az));
}

// Function to process each line from the input file
void processLine(const string &line, ofstream &outputFile, double &biggest_diff_roll, bool debug) {
    stringstream ss(line);
    string timestamp_str, accel_x_str, accel_y_str, accel_z_str;
    getline(ss, timestamp_str, ';');
    getline(ss, accel_x_str, ';');
    getline(ss, accel_y_str, ';');
    getline(ss, accel_z_str, ';');

    double timestamp = stod(timestamp_str);
    double accel_x = stod(accel_x_str) / 1000.0; // Convert to g-unit
    double accel_y = stod(accel_y_str) / 1000.0; // Convert to g-unit
    double accel_z = stod(accel_z_str) / 1000.0; // Convert to g-unit

    double a_roll, a_pitch;
    calculateApproximateRollPitch(accel_x, accel_y, accel_z, a_roll, a_pitch);

    outputFile << timestamp << "; " << a_roll << "; " << a_pitch << endl;

    if (debug) {
        double roll, pitch;
        calculateRollPitch(accel_x, accel_y, accel_z, roll, pitch);

        double diff_roll = (roll - a_roll) * RAD_TO_DEG;

        cout << "Roll: " << diff_roll << ";" << endl;

        if (diff_roll > biggest_diff_roll) {
            biggest_diff_roll = diff_roll;
        }
    }
}

int main(int argc, char *argv[]) {
    bool debug = false;

    if (argc == 2) {
        if (string(argv[1]) == "1") {
            debug = true;
        }
    }
    ifstream inputFile("attitude_exam.log");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    ofstream outputFile("output.log");
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    string line;
    double biggest_diff_roll = 0.0;

    while (getline(inputFile, line)) {
        processLine(line, outputFile, biggest_diff_roll, debug);
    }

    if (debug) {
        cout << "Biggest roll angle difference: " << biggest_diff_roll << ";" << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
