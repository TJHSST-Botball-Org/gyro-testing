#include <kipr/wombat.h>
#include <iostream>

void estimate_orientation(){
    double last_time = seconds();  // Store the initial time
    //std::cout << last_time;
    double orientation = 0;  // Initialize the orientation to 0
    while (true){
        //gyro_calibrate();
        //float gx = gyro_x();
        //float gy = gyro_y();
        double gz = gyro_z(); // Read gyroscope data
        double current_time = seconds();  // Get the current time
        double delta_time = current_time - last_time;  // Calculate the time difference
        //std::cout << delta_time;
        orientation = orientation + gz * delta_time;  // Update the orientation based on angular velocity
        double orientation_deg = orientation / 8.2875;
        last_time = current_time;  // Update last_time to current time
        std::cout << orientation_deg;  // Output the estimated orientation
        std::cout << std::endl;
        msleep(10); // Sleep 100ms for example to only integrate new gyro values
    }
}

int main(){
    gyro_calibrate();
	msleep(1500);
    estimate_orientation();
    return 0;
}
