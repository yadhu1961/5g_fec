#pragma once

#include <cstdint>
#include <vector>

namespace math_ops {

/**
 * @brief Performs convolution of two vectors using the bitwise OR operation.
 * @param x The input signal sequence.
 * @param h The impulse response of the filter.
 * @return The resulting vector after convolution.
 */
auto convolution(const std::vector<float>& x, const std::vector<float>& h) {
  // Calculate the size of the output vector based on the lengths of x and h.
  const size_t output_size{x.size() + h.size() - 1};
  // Initialize the output vector with zeros.
  std::vector<float> output(output_size, 0);

  for (size_t n = 0; n < output_size; ++n) {
    // here k<= n is needed to consider index 0 as well.
    for (size_t k = 0; k <= n; ++k) {
      const float x_k = k < x.size() ? x[k] : 0;
      const float h_n_k = (n - k) < h.size() ? h[n - k] : 0;
      const bool isMulNeeded = (x_k != 0 && h_n_k != 0);
      // optimization to avoid unnecessary multiplications
      output[n] += isMulNeeded ? x_k * h_n_k : 0;
    }
  }

  return output;
}

// TODO add implementation for FFT with complexity O(n log n)

}  // namespace math_ops
