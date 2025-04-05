#include "modulation.h"

#include <cassert>
#include <cmath>
#include <iostream>

// Define a custom assert macro
#define ASSERT_WITH_MSG(condition, message)                        \
  do {                                                             \
    if (!(condition)) {                                            \
      std::cerr << "Assertion failed: " << (message) << std::endl; \
      std::abort();                                                \
    }                                                              \
  } while (false)

Modulator::Modulator(ModulationScheme scheme) : modulationScheme(scheme) {}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulate(
    const std::bitset<N> &inputBits) {
  if (modulationScheme == ModulationScheme::BPSK) {
    return modulateBPSK(inputBits);
  } else if (modulationScheme == ModulationScheme::QPSK) {
    ASSERT_WITH_MSG(N % 2 == 0, "Input size must be even for QPSK modulation.");
    return modulateQPSK(inputBits);
  } else if (modulationScheme == ModulationScheme::QAM16) {
    ASSERT_WITH_MSG(N % 4 == 0,
                    "Input size must be a multiple of 4 for QAM16 modulation.");
    return modulateQAM16(inputBits);
  } else if (modulationScheme == ModulationScheme::QAM64) {
    ASSERT_WITH_MSG(N % 6 == 0,
                    "Input size must be a multiple of 6 for QAM64 modulation.");
    return modulateQAM64(inputBits);
  } else if (modulationScheme == ModulationScheme::QAM256) {
    ASSERT_WITH_MSG(
        N % 8 == 0,
        "Input size must be a multiple of 8 for QAM256 modulation.");
    return modulateQAM256(inputBits);
  } else {
    // Handle unsupported modulation schemes
    std::cout << "Error: Unsupported modulation scheme." << std::endl;
    return {};  // Return an empty array for unsupported schemes
  }
}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulateBPSK(
    const std::bitset<N> &inputBits) {
  std::vector<std::complex<float>> symbols(N);
  for (size_t i = 0; i < N; ++i) {
    symbols[i] = std::complex<float>(
        inputBits[i] ? Modulator::BPSK_HIGH : Modulator::BPSK_LOW, 0.0f);
  }
  return symbols;
}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulateQPSK(
    const std::bitset<N> &inputBits) {
  std::vector<std::complex<float>> symbols(N / 2);
  for (size_t i = 0; i < N; i += 2) {
    float real = (inputBits[i] ? Modulator::BPSK_HIGH : Modulator::BPSK_LOW) *
                 Modulator::QPSK_SCALE;
    float imag =
        (inputBits[i + 1] ? Modulator::BPSK_HIGH : Modulator::BPSK_LOW) *
        Modulator::QPSK_SCALE;
    symbols[i / 2] = std::complex<float>(real, imag);
  }
  return symbols;
}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulateQAM16(
    const std::bitset<N> &inputBits) {
  std::vector<std::complex<float>> symbols(N / 4);
  for (size_t i = 0; i < N; i += 4) {
    int realPart = (inputBits[i] << 1) | inputBits[i + 1];
    int imagPart = (inputBits[i + 2] << 1) | inputBits[i + 3];
    float real = ((realPart == 0 || realPart == 3) ? -1.0f : 1.0f) *
                 Modulator::QAM16_SCALE * ((realPart & 1) ? 1.0f : 3.0f);
    float imag = ((imagPart == 0 || imagPart == 3) ? -1.0f : 1.0f) *
                 Modulator::QAM16_SCALE * ((imagPart & 1) ? 1.0f : 3.0f);
    symbols[i / 4] = std::complex<float>(real, imag);
  }
  return symbols;
}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulateQAM64(
    const std::bitset<N> &inputBits) {
  static constexpr float QAM64_SCALE =
      4.0f / Modulator::SQRT_42;  // Use precomputed value
  std::vector<std::complex<float>> symbols(N / 6);
  for (size_t i = 0; i < N; i += 6) {
    int realPart =
        (inputBits[i] << 2) | (inputBits[i + 1] << 1) | inputBits[i + 2];
    int imagPart =
        (inputBits[i + 3] << 2) | (inputBits[i + 4] << 1) | inputBits[i + 5];
    float real = ((realPart < 4 || realPart > 7) ? -1.0f : 1.0f) * QAM64_SCALE *
                 ((realPart & 3) == 0   ? 7.0f
                  : (realPart & 3) == 1 ? 5.0f
                  : (realPart & 3) == 2 ? 3.0f
                                        : 1.0f);
    float imag = ((imagPart < 4 || imagPart > 7) ? -1.0f : 1.0f) * QAM64_SCALE *
                 ((imagPart & 3) == 0   ? 7.0f
                  : (imagPart & 3) == 1 ? 5.0f
                  : (imagPart & 3) == 2 ? 3.0f
                                        : 1.0f);
    symbols[i / 6] = std::complex<float>(real, imag);
  }
  return symbols;
}

template <size_t N>
std::vector<std::complex<float>> Modulator::modulateQAM256(
    const std::bitset<N> &inputBits) {
  static constexpr float QAM256_SCALE =
      8.0f / Modulator::SQRT_170;  // Use precomputed value
  std::vector<std::complex<float>> symbols(N / 8);
  for (size_t i = 0; i < N; i += 8) {
    int realPart = (inputBits[i] << 3) | (inputBits[i + 1] << 2) |
                   (inputBits[i + 2] << 1) | inputBits[i + 3];
    int imagPart = (inputBits[i + 4] << 3) | (inputBits[i + 5] << 2) |
                   (inputBits[i + 6] << 1) | inputBits[i + 7];
    float real = ((realPart < 8 || realPart > 15) ? -1.0f : 1.0f) *
                 QAM256_SCALE *
                 ((realPart & 7) == 0   ? 15.0f
                  : (realPart & 7) == 1 ? 13.0f
                  : (realPart & 7) == 2 ? 11.0f
                  : (realPart & 7) == 3 ? 9.0f
                  : (realPart & 7) == 4 ? 7.0f
                  : (realPart & 7) == 5 ? 5.0f
                  : (realPart & 7) == 6 ? 3.0f
                                        : 1.0f);
    float imag = ((imagPart < 8 || imagPart > 15) ? -1.0f : 1.0f) *
                 QAM256_SCALE *
                 ((imagPart & 7) == 0   ? 15.0f
                  : (imagPart & 7) == 1 ? 13.0f
                  : (imagPart & 7) == 2 ? 11.0f
                  : (imagPart & 7) == 3 ? 9.0f
                  : (imagPart & 7) == 4 ? 7.0f
                  : (imagPart & 7) == 5 ? 5.0f
                  : (imagPart & 7) == 6 ? 3.0f
                                        : 1.0f);
    symbols[i / 8] = std::complex<float>(real, imag);
  }
  return symbols;
}

template std::vector<std::complex<float>> Modulator::modulate<12>(
    const std::bitset<12> &);
template std::vector<std::complex<float>> Modulator::modulate<16>(
    const std::bitset<16> &);
template std::vector<std::complex<float>> Modulator::modulate<8>(
    const std::bitset<8> &inputBits);
