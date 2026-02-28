#include <kipr/wombat.h>
#include <iostream>

double calibrate_gyroscope(){
    double gyro_x_sum = 0;
    int num_samples = 200;  // Number of samples for averaging
    for (int i = 0; i<num_samples; i++){
        double gx = gyro_x();  // Read gyroscope data
        gyro_x_sum += gx;  // Accumulate gyro z readings
    }
    double gyro_x_bias = gyro_x_sum / num_samples;  // Calculate bias for gyro z
	std::cout << gyro_x_bias;
    return gyro_x_bias;
}

void estimate_orientation(double zbias){
    double last_time = seconds();  // Store the initial time
    //std::cout << last_time;
    double orientation = 0;  // Initialize the orientation to 0
    for(int i = 0; i < 1500; i++){
        //gyro_calibrate();
        //float gx = gyro_x();
        //float gy = gyro_y();
        double gz = gyro_x() - zbias; // Read gyroscope data
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

void go_straight(double speed, double duration_sec){
    double xbias = calibrate_gyroscope();
    msleep(1000);

    double start_time = seconds();
    double last_time = start_time;
    double orientation = 0;
    double Kp = 0.005;

    while(seconds() - start_time < duration_sec){
        double current_time = seconds();
        double dt = current_time - last_time;
        last_time = current_time;

        double gx = gyro_x() - xbias;
        orientation += gx * dt;

        double error = -orientation;
        double correction = Kp * error;

        int left = speed - correction;
        int right = speed + correction;

        motor(0, left);
        motor(3, left);
        motor(1, right);
        motor(2, right);

        msleep(10);
    }

    ao();
}

int main(){
    std::cout << "Driving straight...\n";
    go_straight(50, 15);  // use seconds
    msleep(500);
    return 0;
}
