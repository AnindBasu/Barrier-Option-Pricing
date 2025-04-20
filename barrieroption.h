#ifndef BARRIER_OPTION_H
#define BARRIER_OPTION_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>  // For std::vector

// BarrierOption class definition
class barrieroption {
private:
    double S0;       // Initial stock price
    double K;        // Strike price
    double sigma;    // Volatility
    double r;        // Risk-free rate
    double t;        // Time to maturity
    double b;        // Barrier value
    int n_steps;     // Number of time steps
    int num_exp;     // Number of experiments
    std::vector<double> payoffs;  // Vector to store payoffs from each experiment

public:
    // Constructor to initialize the option parameters
    barrieroption(double S0_, double K_, double sigma_, double r_, double t_, double b_, int n_steps_, int num_exp_);

    // Function to generate a single Gaussian random number using Box-Muller method
    double get_one_gaussian_by_box_muller();

    // Function to simulate the option and calculate its price
    void simulate();

    // Function to calculate and return the standard deviation of payoffs
    double calculate_stddev();

    // General utility functions for mean and standard deviation
    static double get_vector_mean(const std::vector<double>& this_vec);
    static double get_vector_stddev(const std::vector<double>& this_vec);
};

#endif // BARRIER_OPTION_H
