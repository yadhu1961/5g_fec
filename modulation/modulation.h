#pragma once

#include <bitset>
#include <complex>
#include <vector>

// Modulator class definition
class Modulator {
 public:
  // Enum for modulation schemes
  enum class ModulationScheme { BPSK, QPSK, QAM16, QAM64, QAM256 };

  // Constructor
  explicit Modulator(ModulationScheme scheme);

  template <size_t N>
  std::vector<std::complex<float>> modulate(const std::bitset<N>& inputBits);

 private:
  // Modulation scheme used by the modulator
  ModulationScheme modulationScheme;

  // Precomputed constants
  static constexpr float BPSK_HIGH = 1.0f;
  static constexpr float BPSK_LOW = -1.0f;
  static constexpr float QPSK_SCALE = 0.7071067811865475f;   // 1.0 / sqrt(2.0)
  static constexpr float QAM16_SCALE = 0.6324555320336759f;  // 2.0 / sqrt(10.0)
  static constexpr float QAM16_OFFSET = 1.5f;
  static constexpr float SQRT_2 = 1.4142135623730951f;    // sqrt(2.0)
  static constexpr float SQRT_10 = 3.1622776601683795f;   // sqrt(10.0)
  static constexpr float SQRT_42 = 6.48074069840786f;     // sqrt(42.0)
  static constexpr float SQRT_170 = 13.038404810405298f;  // sqrt(170.0)

  // Modulation functions for different schemes
  template <size_t N>
  std::vector<std::complex<float>> modulateBPSK(
      const std::bitset<N>& inputBits);

  template <size_t N>
  std::vector<std::complex<float>> modulateQPSK(
      const std::bitset<N>& inputBits);

  template <size_t N>
  std::vector<std::complex<float>> modulateQAM16(
      const std::bitset<N>& inputBits);

  template <size_t N>
  std::vector<std::complex<float>> modulateQAM64(
      const std::bitset<N>& inputBits);

  template <size_t N>
  std::vector<std::complex<float>> modulateQAM256(
      const std::bitset<N>& inputBits);
};