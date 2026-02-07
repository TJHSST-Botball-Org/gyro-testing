#include <kipr/wombat.h>
#include <iostream>

double calibrate_gyroscope(){
    double gyro_z_sum = 0;
    int num_samples = 100;  // Number of samples for averaging
    for (int i = 0; i<num_samples; i++){
        double gz = gyro_z();  // Read gyroscope data
        gyro_z_sum += gz;  // Accumulate gyro z readings
    }
    double gyro_z_bias = gyro_z_sum / num_samples;  // Calculate bias for gyro z
	std::cout << gyro_z_bias;
    return gyro_z_bias;
}

void estimate_orientation(double zbias){
    double last_time = seconds();  // Store the initial time
    //std::cout << last_time;
    double orientation = 0;  // Initialize the orientation to 0
    for(int i = 0; i < 1500; i++){
        //gyro_calibrate();
        //float gx = gyro_x();
        //float gy = gyro_y();
        double gz = gyro_z() - zbias; // Read gyroscope data
        double current_time = seconds();  // Get the current time
        double delta_time = current_time - last_time;  // Calculate the time difference
        //std::cout << delta_time;
        orientation = orientation + gz * delta_time;  // Update the orientation based on angular velocity
        double orientation_deg = orientation / 8.248;
        last_time = current_time;  // Update last_time to current time
        std::cout << orientation_deg;  // Output the estimated orientation
        std::cout << "break";
        msleep(10); // Sleep 100ms for example to only integrate new gyro values
    }
}

int main(){
    double zb = calibrate_gyroscope();
	msleep(1500);
    estimate_orientation(zb);
    msleep(1500);
    zb = calibrate_gyroscope();
    msleep(1500);
    estimate_orientation(zb);
    return 0;
}
