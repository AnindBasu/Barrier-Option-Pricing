
# Down-and-In Barrier Call Option Pricing

This project implements a **C++ Monte Carlo simulation** to approximate the theoretical price of a **down-and-in barrier call option**—a type of exotic financial derivative. The simulation assumes standard market dynamics and uses object-oriented programming principles to structure and perform the pricing.

## 📌 Overview

A *down-and-in* barrier call option is activated only if the underlying asset price drops below a predefined barrier level during its lifetime. The pricing requires simulating many possible future asset paths using geometric Brownian motion.

## 💡 Features

- C++ class-based simulation framework.
- Uses the **Box-Muller** method for generating Gaussian noise.
- Euler discretization of asset paths under geometric Brownian motion.
- Support for configurable parameters like volatility, interest rate, barrier levels, etc.
- Calculates both the expected discounted payoff and standard deviation.

## 📊 Model Assumptions

- Risk-free rate `r` and volatility `σ` are constant.
- Underlying follows a Geometric Brownian Motion:
  ```
  S_{t+Δt} = S_t + S_t × (rΔt + σ√Δt Z),   where Z ~ N(0, 1)
  ```
- Monte Carlo settings:
  - Number of experiments: `100,000`
  - Steps per experiment: `10,000`

## 🧪 Sample Results

| Barrier Level | Discounted Price | Standard Deviation |
|---------------|------------------|---------------------|
| 95            | 2.71             | 7.96                |
| 97            | 3.79             | 9.56                |
| 99            | 5.30             | 11.47               |

As the barrier increases toward the initial stock price, the likelihood of the option activating increases, resulting in higher prices.

## 🧱 Code Structure

### `barrieroption` Class

- Attributes:
  - `S0`, `K`, `sigma`, `r`, `t`, `b`
  - `n_steps`, `num_exp`
- Methods:
  - `get_one_gaussian_by_box_muller()`
  - `simulate()`
  - `calculate_stddev()`

### Main Program

Instantiates `barrieroption` objects with different barrier values and prints the option prices.

## 🛠️ Compilation & Usage

```bash
g++ -std=c++11 -o barrier_option barrier_option.cpp
./barrier_option
```

## 📁 Files

- `barrier_option.cpp`: Main source code implementing the simulation.



--
