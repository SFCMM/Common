#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Integration, HandlesZeroInput){
  std::function<GDouble(GDouble)> linear = [](const GDouble x){return 1;};

  std::function<GDouble(GDouble)> square = [](const GDouble x){return x;};

  std::function<GDouble(GDouble)> log = [](const GDouble x){return 1.0/x;};

  std::function<GDouble(GDouble)> exp_p1 = [](const GDouble x){return gcem::exp(x)+1;};


  static constexpr integration::range              range_01 = {0, 1};
  static constexpr integration::range              range_011 = {0.1, 1};
  static constexpr integration::range              range_02 = {0, 2};

  static constexpr GDouble ana_lin_range_01 = range_01.b - range_01.a; // 1-0 -> 1
  static constexpr GDouble ana_lin_range_02 = range_02.b - range_02.a; // 2-0 -> 2
  static constexpr GDouble ana_sq_range_01 = gcem::pow(range_01.b,2) - gcem::pow(range_01.a, 2); //1^2 - 0^2 = 1
  static constexpr GDouble ana_sq_range_02 = gcem::pow(range_02.b,2) - gcem::pow(range_02.a, 2); //2^2 - 0^2 = 4
  static constexpr GDouble ana_log_range_011 = gcem::log(range_011.b) - gcem::log(range_011.a); // 0--2.30259 -> 2.30259
  static constexpr GDouble ana_expp1_range_01 = range_01.b + gcem::exp(range_01.b) - (gcem::exp(range_01.a) + range_01.a); // 2.7183

  const double eps = std::numeric_limits<double>::epsilon();

  ASSERT_EQ(integration::midpoint(range_01, linear), 1);
  ASSERT_EQ(integration::trapezoidal(range_01, linear), 1);
  ASSERT_EQ(integration::simpson(range_01, linear), 1);
  ASSERT_EQ(integration::midpoint(range_01, square), 0.5);
  ASSERT_EQ(integration::trapezoidal(range_01, square), 0.5);
  ASSERT_EQ(integration::simpson(range_01, square), 0.5);

  ASSERT_EQ(integration::midpoint(range_02, linear), 2);
  ASSERT_EQ(integration::trapezoidal(range_02, linear), 2);
  ASSERT_EQ(integration::simpson(range_02, linear), 2);
  ASSERT_EQ(integration::midpoint(range_02, square), 2);
  ASSERT_EQ(integration::trapezoidal(range_02, square), 2);
  ASSERT_EQ(integration::simpson(range_02, square), 2);

  ASSERT_TRUE(approx(integration::midpoint(range_011, log), 1.63636, 1E-5));
  ASSERT_EQ(integration::trapezoidal(range_011, log), 4.95);
  ASSERT_TRUE(approx(integration::simpson(range_011, log), 2.74091, 1E-5));

  ASSERT_TRUE(approx(integration::midpoint(range_01, exp_p1), 2.64872, 1E-5));
  ASSERT_TRUE(approx(integration::trapezoidal(range_01, exp_p1), 2.85914, 1E-5));
  ASSERT_TRUE(approx(integration::simpson(range_01, exp_p1), 2.71886, 1E-5));
}
