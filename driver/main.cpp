#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../math_ops/math_ops.h"
#include "../modulation/modulation.h"

int main() {
  // Test BPSK modulation
  std::cout << "Testing BPSK modulation..." << std::endl;
  Modulator bpskModulator(Modulator::ModulationScheme::BPSK);
  std::bitset<8> bpskInput("11001010");
  auto bpskOutput = bpskModulator.modulate(bpskInput);
  std::cout << "8 bit input, BPSK Output: ";
  for (const auto& symbol : bpskOutput) {
    std::cout << symbol << " ";
  }
  std::cout << std::endl;

  // Test QPSK modulation
  std::cout << "Testing QPSK modulation..." << std::endl;
  Modulator qpskModulator(Modulator::ModulationScheme::QPSK);
  std::bitset<8> qpskInput("11001010");
  auto qpskOutput = qpskModulator.modulate(qpskInput);
  std::cout << "8 bit input, QPSK Output: ";
  for (const auto& symbol : qpskOutput) {
    std::cout << symbol << " ";
  }
  std::cout << std::endl;

  // Test QAM16 modulation
  std::cout << "Testing QAM16 modulation..." << std::endl;
  Modulator qam16Modulator(Modulator::ModulationScheme::QAM16);
  std::bitset<8> qam16Input("11001010");
  auto qam16Output = qam16Modulator.modulate(qam16Input);
  std::cout << "8 bit input, QAM16 Output: ";
  for (const auto& symbol : qam16Output) {
    std::cout << symbol << " ";
  }
  std::cout << std::endl;

  // Test QAM64 modulation
  std::cout << "Testing QAM64 modulation..." << std::endl;
  Modulator qam64Modulator(Modulator::ModulationScheme::QAM64);
  std::bitset<12> qam64Input("110010101011");
  auto qam64Output = qam64Modulator.modulate(qam64Input);
  std::cout << "12 bit input, QAM64 Output: ";
  for (const auto& symbol : qam64Output) {
    std::cout << symbol << " ";
  }
  std::cout << std::endl;

  // Test QAM256 modulation
  std::cout << "Testing QAM256 modulation..." << std::endl;
  Modulator qam256Modulator(Modulator::ModulationScheme::QAM256);
  std::bitset<16> qam256Input("1100101010110011");
  auto qam256Output = qam256Modulator.modulate(qam256Input);
  std::cout << "16 bit input, QAM256 Output: ";
  for (const auto& symbol : qam256Output) {
    std::cout << symbol << " ";
  }
  std::cout << std::endl;

  // Test convolution operation
  std::cout << "Testing convolution operation..." << std::endl;
  const std::vector<float> x = {1.1, 2.3, 3.6, 9.4, 8.8};
  const std::vector<float> h = {4.3, 5.2, 6.5};
  const auto convolutionOutput = math_ops::convolution(x, h);
  std::cout << "Convolution Output: ";
  for (const auto& value : convolutionOutput) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "All tests completed successfully." << std::endl;
  return 0;
}
