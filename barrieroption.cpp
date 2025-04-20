#include "barrieroption.h"  


// Constructor to initialize all parameters
barrieroption::barrieroption(double S0_, double K_, double sigma_, double r_,
                             double t_, double b_, int n_steps_, int num_exp_)
    : S0(S0_), K(K_), sigma(sigma_), r(r_), t(t_), b(b_),
      n_steps(n_steps_), num_exp(num_exp_) {}

// Function to generate one Gaussian random number using Box-Muller method
double barrieroption::get_one_gaussian_by_box_muller() {
    double result, x, y, size_squared;

    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1.0;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1.0;
        size_squared = x * x + y * y;
    } while (size_squared >= 1.0 || size_squared == 0.0); // Avoid division by zero

    result = x * sqrt(-2.0 * log(size_squared) / size_squared);
    return result;
}

// Function to simulate the option price
void barrieroption::simulate() {
    double dt = t / n_steps;
    payoffs.clear(); // Clear the payoffs vector for a new simulation

    // Print parameter values
    std::cout << "Simulation Parameters:\n";
    std::cout << "S0 (Initial Stock Price): " << S0 << "\n";
    std::cout << "K (Strike Price): " << K << "\n";
    std::cout << "sigma (Volatility): " << sigma << "\n";
    std::cout << "r (Risk-Free Rate): " << r << "\n";
    std::cout << "t (Time to Maturity): " << t << "\n";
    std::cout << "b (Barrier): " << b << "\n";
    std::cout << "n_steps (Number of Steps): " << n_steps << "\n";
    std::cout << "num_exp (Number of Experiments): " << num_exp << "\n";
    std::cout << "dt (Time Increment): " << dt << "\n\n";

    double PAYOFF = 0.0;

    // Simulate paths for num_exp experiments
    for (int exp_num = 1; exp_num <= num_exp; ++exp_num) {
        double S = S0;
        bool ACTIVATED = false;

        // Simulate the price path
        for (int step = 1; step <= n_steps; ++step) {
            double y = get_one_gaussian_by_box_muller();
            double dS = S * (r * dt + sigma * sqrt(dt) * y);
            S += dS;
            if (S <= b) {
                ACTIVATED = true;
            }
        }

        // Calculate the payoff if the option is activated
        double payoff = 0.0;
        if (ACTIVATED && S > K) {
            payoff = S - K;
        }
        payoffs.push_back(payoff);
        PAYOFF += payoff;
    }

    // Calculate average payoff and discount to present value
    double average_payoff = get_vector_mean(payoffs);
    double current_value = average_payoff * exp(-r * t);

    // Print results
    std::cout << "Results:\n";
    std::cout << "Average Payoff (Undiscounted): " << average_payoff << "\n";
    std::cout << "Current Value of Payoff (Discounted): " << current_value << "\n";
    std::cout << "Standard Deviation of Current Value of Payoff (Discounted): "
              << calculate_stddev() * exp(-r * t) << "\n";
    std::cout << "------------------------------------------\n";
}

// Function to calculate and return the standard deviation of payoffs
double barrieroption::calculate_stddev() {
    return get_vector_stddev(payoffs);
}

// General function for mean of a vector
double barrieroption::get_vector_mean(const std::vector<double>& this_vec) {
    double sum = 0.0;
    size_t this_size = this_vec.size();

    for (size_t i = 0; i < this_size; ++i) {
        sum += this_vec[i];
    }
    return sum / static_cast<double>(this_size);
}

// General function for standard deviation of a vector
double barrieroption::get_vector_stddev(const std::vector<double>& this_vec) {
    double mean = get_vector_mean(this_vec);
    double sum = 0.0;
    size_t this_size = this_vec.size();

    for (size_t i = 0; i < this_size; ++i) {
        sum += pow(this_vec[i] - mean, 2);
    }
    return sqrt(sum / static_cast<double>(this_size - 1));
}

int main() {
    // Test with different barrier values
    barrieroption option1(100.0, 110.0, 0.25, 0.05, 0.75, 95.0, 10000, 100000);
    option1.simulate();

    barrieroption option2(100.0, 110.0, 0.25, 0.05, 0.75, 97.0, 10000, 100000);
    option2.simulate();

    barrieroption option3(100.0, 110.0, 0.25, 0.05, 0.75, 99.0, 10000, 100000);
    option3.simulate();

    return 0;
}