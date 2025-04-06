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
auto convolution(std::vector<float>& x, std::vector<float>& h) {
  const uint8_t output_size = x.size() + h.size() - 1;
  std::vector<float> output(output_size, 0);
  for (uint8_t n = 0; n < output_size; ++n) {
    for (uint8_t k = 0; k <= n; ++k) {
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
