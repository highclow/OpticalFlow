#include <cblas.h>
#include "image.h"
#include "gtest/gtest.h"

namespace test {

// Tests the default c'tor.
TEST(Image, DefaultConstructor) {
  const DImage im;
  EXPECT_EQ(nullptr, im.data());
}

// Tests the c'tor with dimension.
TEST(Image, ConstructorDimension) {
  size_t width = 3;
  size_t height = 4;
  size_t channels = 5;
  const DImage im(width, height, channels);
  EXPECT_EQ(12, im.pixels());
  EXPECT_EQ(60, im.elements());
  for (size_t i=0; i!=im.elements(); ++i) {
      EXPECT_EQ(0., im[i]);
  }
}

// Tests the c'tor with values.
TEST(Image, ConstructorValue) {
  size_t width = 3;
  size_t height = 4;
  size_t channels = 5;
  double value = 0.3;
  const DImage im(value, width, height, channels);
  EXPECT_EQ(12, im.pixels());
  EXPECT_EQ(60, im.elements());
  for (size_t i=0; i!=im.elements(); ++i) {
      EXPECT_EQ(0.3, im[i]);
  }
}

// Tests the c'tor with values.
TEST(Image, ConstructorCopy) {
  int wsize = 3;
  double sigma = 0.5;
  DImage im;
  im.generate2DGaussian(wsize, sigma);
  EXPECT_EQ(49, im.pixels());
  EXPECT_EQ(49, im.elements());
  const DImage im2(im);
  EXPECT_EQ(49, im2.pixels());
  EXPECT_EQ(49, im2.elements());
  for (size_t i=0; i!=im.elements(); ++i) {
      EXPECT_EQ(im[i], im2[i]);
  }
  double sum = cblas_dasum(im.elements(), im.data(), 1);
  EXPECT_NEAR(sum, 1.0, 1e-5);
}


// Tests the clear method.
TEST(Image, Clear) {
  size_t width = 3;
  size_t height = 4;
  size_t channels = 5;
  double value = 0.3;
  DImage im(value, width, height, channels);
  im.clear();
  EXPECT_EQ(nullptr, im.data());
}


}  // namespace
