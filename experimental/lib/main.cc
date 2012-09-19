#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "boost/scoped_ptr.hpp"
#include "discretizations.h"
#include "experiment.h"
#include "glog/logging.h"
#include "jpeg_codec.h"
#include "util.h"

namespace cryptogram {

// Generates the random values to fill @entries based on random choices of the
// values in @values.
void GenerateRandomRgbArray(
    const int* values,
    const int num_values,
    const int num_rgb_pixels,
    unsigned char* entries) {
  CHECK_NOTNULL(entries);
  CHECK_NOTNULL(values);

  for (int i = 0; i < num_rgb_pixels; i++) {
    size_t val_index = rand() % num_values;
    int value = values[val_index];
    entries[(3 * i)] = value;
    entries[(3 * i) + 1] = value;
    entries[(3 * i) + 2] = value;
  }
}

class RgbImageMatrix {
 public:
  struct Pixel {
    Pixel(Byte red, Byte green, Byte blue);
    
    Byte red;
    Byte green;
    Byte blue;
  };

  
 private:
  int width_;
  int height_;

  // GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RgbImageMatrix);
};

} // namespace cryptogram

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "Initializng the random number generator.";
  srand(0);

  const int values[] = { 64, 172 };
  const int num_values = 3;
  const int num_rgb_pixels = 8 * 8;
  const int num_bytes = num_rgb_pixels * 3;

  unsigned char array[num_bytes];
  bzero(array, num_bytes);
  
  for (int trial = 0; trial < 1000000; trial++) {
    if (trial % 100000 == 0) {
      printf("Trial: %d\n", trial);
    }
    cryptogram::GenerateRandomRgbArray(values, num_values, num_rgb_pixels, array);

    std::vector<unsigned char> output;

    int width = 8;
    int height = 8;
    int quality = 72;
    bool result = gfx::JPEGCodec::Encode(array,
                                         gfx::JPEGCodec::FORMAT_RGB,
                                         width,
                                         height,
                                         width * cryptogram::kBytesPerWidthEntry,
                                         quality,
                                         &output);

    // if (result) {
    //   std::ofstream out_file("test.jpg", std::ios::out | std::ios::binary);
    //   for (const unsigned char val : output) {
    //     out_file << val;
    //   }
    //   out_file.close();
    // }

    // cryptogram::Experiment experiment;

    // std::ifstream in_file("test.jpg", std::ios::binary);
    // in_file.seekg (0, std::ios::end);
    // int length = in_file.tellg();
    // in_file.seekg (0, std::ios::beg);
    // std::cout << length << std::endl;
    // boost::scoped_ptr<char> buffer(new char[length]);
    // in_file.read(buffer.get(), length);
    // in_file.close();

    const int length = output.size();
    unsigned char uchars[length];
    // for (int i = 0; i < length; i++) {
    //   uchars[i] = buffer.get()[i];
    // }
    cryptogram::UcharVectorToArray(output, length, uchars);
  
    output.clear();
    result = gfx::JPEGCodec::Decode(uchars,
                                    length,
                                    gfx::JPEGCodec::FORMAT_RGB,
                                    &output,
                                    &width,
                                    &height);
  }
  // if (result) {
  //   for (const unsigned char val : output) {
  //     printf("%d ", val);
  //   }
  // }

  return 0;
}