#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Integration, HandlesZeroInput) {
  using namespace integration;

  static constexpr double eps = std::numeric_limits<double>::epsilon();

  std::function<GDouble(GDouble)> linear = [](const GDouble /*x*/) { return 1; };

  std::function<GDouble(GDouble)> square = [](const GDouble x) { return x; };

  std::function<GDouble(GDouble)> log = [](const GDouble x) { return 1.0 / x; };

  std::function<GDouble(GDouble)> exp_p1 = [](const GDouble x) { return gcem::exp(x) + 1; };

  std::function<GDouble(GDouble)> poly2 = [](const GDouble x) { return x*x + 3 * x - 2; };

  std::function<GDouble(GDouble)> poly3 = [](const GDouble x) { return x*x*x - 3 * x * x + 20 * x - 101; };

  std::function<GDouble(GDouble)> nonlin = [](const GDouble x) { return gcem::sin(x)/x; };



  static constexpr range range_01  = {0, 1};
  static constexpr range range_011 = {0.1, 1};
  static constexpr range range_02  = {0, 2};
  static constexpr range range_010  = {eps, 10};

  static constexpr GDouble ana_lin_range_01 = range_01.b - range_01.a;                                         // 1-0 -> 1
  static constexpr GDouble ana_lin_range_02 = range_02.b - range_02.a;                                         // 2-0 -> 2
  static constexpr GDouble ana_sq_range_01  = gcem::pow(range_01.b, 2) / 2.0 - gcem::pow(range_01.a, 2) / 2.0; // 1^2/2 - 0^2/2 = 0.5
  static constexpr GDouble ana_sq_range_02  = gcem::pow(range_02.b, 2) / 2.0 - gcem::pow(range_02.a, 2) / 2.0; // 2^2/2 - 0^2/2
                                                                                                               // = 2
  static constexpr GDouble ana_log_range_011  = gcem::log(range_011.b) - gcem::log(range_011.a);               // 0--2.30259 -> 2.30259
  static constexpr GDouble ana_expp1_range_01 = range_01.b + gcem::exp(range_01.b) - (gcem::exp(range_01.a) + range_01.a); // 2.7183

  static constexpr GDouble ana_poly2_range_01 = - 1.0/6.0;
  static constexpr GDouble ana_poly3_range_010 = 1490;
  static constexpr GDouble ana_nonlin_range_010 = 1.65835;



  ASSERT_EQ(gcem::abs(midpoint(range_01, linear) - ana_lin_range_01), 0);
  ASSERT_EQ(gcem::abs(multi_midpoint(range_01, linear) - ana_lin_range_01), 0);
  ASSERT_EQ(gcem::abs(multi_midpoint(range_01, linear, 3) - ana_lin_range_01), 0);
  ASSERT_EQ(gcem::abs(trapezoidal(range_01, linear) - ana_lin_range_01), 0);
  ASSERT_EQ(gcem::abs(simpson(range_01, linear) - ana_lin_range_01), 0);

  ASSERT_LT(gcem::abs(midpoint(range_01, square) - ana_sq_range_01), eps);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, square) - ana_sq_range_01), eps);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, square, 10) - ana_sq_range_01), eps);
  ASSERT_LT(gcem::abs(trapezoidal(range_01, square) - ana_sq_range_01), eps);
  ASSERT_LT(gcem::abs(simpson(range_01, square) - ana_sq_range_01), eps);

  ASSERT_LT(gcem::abs(midpoint(range_02, linear) - ana_lin_range_02), eps);
  ASSERT_LT(gcem::abs(multi_midpoint(range_02, linear) - ana_lin_range_02), eps);
  ASSERT_LT(gcem::abs(trapezoidal(range_02, linear) - ana_lin_range_02), eps);
  ASSERT_LT(gcem::abs(simpson(range_02, linear) - ana_lin_range_02), eps);

  ASSERT_LT(gcem::abs(midpoint(range_02, square) - ana_sq_range_02), eps);
  ASSERT_LT(gcem::abs(multi_midpoint(range_02, square) - ana_sq_range_02), eps);
  ASSERT_LT(gcem::abs(trapezoidal(range_02, square) - ana_sq_range_02), eps);
  ASSERT_LT(gcem::abs(simpson(range_02, square) - ana_sq_range_02), eps);

  ASSERT_LT(gcem::abs(midpoint(range_011, log) - ana_log_range_011), 0.666222);
  ASSERT_LT(gcem::abs(multi_midpoint(range_011, log) - ana_log_range_011), 0.337326);
  ASSERT_LT(gcem::abs(multi_midpoint(range_011, log, 10) - ana_log_range_011), 0.0298449);
  ASSERT_LT(gcem::abs(multi_midpoint(range_011, log, 1000) - ana_log_range_011), 4E-6);
  ASSERT_LT(gcem::abs(trapezoidal(range_011, log) - ana_log_range_011), 2.64742);
  ASSERT_LT(gcem::abs(simpson(range_011, log) - ana_log_range_011), 0.438325);

  ASSERT_LT(gcem::abs(midpoint(range_01, exp_p1) - ana_expp1_range_01)
                , 0.14086);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, exp_p1) - ana_expp1_range_01), 0.0177692);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, exp_p1, 10) - ana_expp1_range_01), 0.000715743);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, exp_p1, 100) - ana_expp1_range_01), 7.2E-6);
  ASSERT_LT(gcem::abs(trapezoidal(range_01, exp_p1) - ana_expp1_range_01), 0.14086);
  ASSERT_LT(gcem::abs(simpson(range_01, exp_p1) - ana_expp1_range_01), 0.000579324);

  ASSERT_LT(gcem::abs(multi_midpoint(range_01, poly2) - ana_poly2_range_01), 0.0208334);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, poly2,10) - ana_poly2_range_01), 0.000833334);
  ASSERT_LT(gcem::abs(multi_midpoint(range_01, poly2, 100) - ana_poly2_range_01), 8.33334e-06);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, poly3) - ana_poly3_range_010), 251);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, poly3, 10) - ana_poly3_range_010), 11);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, poly3, 100) - ana_poly3_range_010), 0.2);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, nonlin) - ana_nonlin_range_010), 0.163929);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, nonlin, 10) - ana_nonlin_range_010), 0.003345);
  ASSERT_LT(gcem::abs(multi_midpoint(range_010, nonlin, 100) - ana_nonlin_range_010), 3.02965e-05);

  ASSERT_LT(gcem::abs(multi_trapezoidal(range_01, poly2) - ana_poly2_range_01), 0.0416667);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_01, poly2,10) - ana_poly2_range_01), 0.00166668);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_01, poly2, 100) - ana_poly2_range_01), 1.66668e-05);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, poly3) - ana_poly3_range_010), 501);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, poly3, 10) - ana_poly3_range_010), 21);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, poly3, 100) - ana_poly3_range_010), 0.3);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, nonlin) - ana_nonlin_range_010),  2.75328);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, nonlin, 10) - ana_nonlin_range_010), 0.50664);
  ASSERT_LT(gcem::abs(multi_trapezoidal(range_010, nonlin, 100) - ana_nonlin_range_010), 0.050068);

  ASSERT_LT(gcem::abs(multi_simpson(range_01, poly2) - ana_poly2_range_01), eps);
  ASSERT_LT(gcem::abs(multi_simpson(range_01, poly2,10) - ana_poly2_range_01), eps);
  ASSERT_LT(gcem::abs(multi_simpson(range_01, poly2, 100) - ana_poly2_range_01), eps);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, poly3) - ana_poly3_range_010), 2.27374e-13);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, poly3, 10) - ana_poly3_range_010), eps);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, poly3, 100) - ana_poly3_range_010), 6.82122e-13);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, nonlin) - ana_nonlin_range_010),  0.808476);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, nonlin, 10) - ana_nonlin_range_010), 0.166648);
  ASSERT_LT(gcem::abs(multi_simpson(range_010, nonlin, 100) - ana_nonlin_range_010), 0.0166691);

}
