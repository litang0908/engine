// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/impeller/tessellator/circle_tessellator.h"

#include "flutter/fml/logging.h"

namespace impeller {

int CircleTessellator::kPrecomputedDivisions[kPrecomputedDivisionCount] = {
    // clang-format off
     1,  2,  3,  4,  4,  4,  5,  5,  5,  6,  6,  6,  7,  7,  7,  7,
     8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9, 10, 10, 10, 10, 10,
    10, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 13,
    13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18,
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19,
    19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23,
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
    33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
    34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35,
    35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38,
    38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
    38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
    39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41,
    41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
    41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
    42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43,
    43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
    43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
    45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
    45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
    46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49,
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51,
    51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
    51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52,
    52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
    52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53,
    53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53,
    53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
    55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
    55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57,
    // clang-format on
};

size_t CircleTessellator::ComputeQuadrantDivisions(Scalar pixel_radius) {
  if (pixel_radius <= 0.0) {
    return 1;
  }
  int radius_index = ceil(pixel_radius);
  if (radius_index < kPrecomputedDivisionCount) {
    return kPrecomputedDivisions[radius_index];
  }

  // For a circle with N divisions per quadrant, the maximum deviation of
  // the polgyon approximation from the true circle will be at the center
  // of the base of each triangular pie slice. We can compute that distance
  // by finding the midpoint of the line of the first slice and compare
  // its distance from the center of the circle to the radius. We will aim
  // to have the length of that bisector to be within |kCircleTolerance|
  // from the radius in pixels.
  //
  // Each vertex will appear at an angle of:
  //   theta(i) = (kPi / 2) * (i / N)  // for i in [0..N]
  // with each point falling at:
  //   point(i) = r * (cos(theta), sin(theta))
  // If we consider the unit circle to simplify the calculations below then
  // we need to scale the tolerance from its absolute quantity into a unit
  // circle fraction:
  //   k = tolerance / radius
  // Using this scaled tolerance below to avoid multiplying by the radius
  // throughout all of the math, we have:
  //   first point = (1, 0)   // theta(0) == 0
  //   theta = kPi / 2 / N    // theta(1)
  //   second point = (cos(theta), sin(theta)) = (c, s)
  //   midpoint = (first + second) * 0.5 = ((1 + c)/2, s/2)
  //   |midpoint| = sqrt((1 + c)*(1 + c)/4 + s*s/4)
  //     = sqrt((1 + c + c + c*c + s*s) / 4)
  //     = sqrt((1 + 2c + 1) / 4)
  //     = sqrt((2 + 2c) / 4)
  //     = sqrt((1 + c) / 2)
  //     = cos(theta / 2)     // using half-angle cosine formula
  //   error = 1 - |midpoint| = 1 - cos(theta / 2)
  //   cos(theta/2) = 1 - error
  //   theta/2 = acos(1 - error)
  //   kPi / 2 / N / 2 = acos(1 - error)
  //   kPi / 4 / acos(1 - error) = N
  // Since we need error <= k, we want divisions >= N, so we use:
  //   N = ceil(kPi / 4 / acos(1 - k))
  //
  // Math is confirmed in https://math.stackexchange.com/a/4132095
  // (keeping in mind that we are computing quarter circle divisions here)
  // which also points out a performance optimization that is accurate
  // to within an over-estimation of 1 division would be:
  //   N = ceil(kPi / 4 / sqrt(2 * k))
  // Since we have precomputed the divisions for radii up to 1024, we can
  // afford to be more accurate using the acos formula here for larger radii.
  double k = kCircleTolerance / pixel_radius;
  return ceil(kPiOver4 / std::acos(1 - k));
}

const std::vector<Trig>& CircleTessellator::GetTrigsForDivisions(
    std::shared_ptr<Tessellator>& tessellator,
    size_t divisions) {
  std::vector<Trig>& trigs = (divisions < Tessellator::kCachedTrigCount)
                                 ? tessellator->precomputed_trigs_[divisions]
                                 : temp_trigs_;

  if (trigs.empty()) {
    // Either not cached yet, or we are usig the temp vector...
    trigs.reserve(divisions + 1);

    double angle_scale = kPiOver2 / divisions;

    trigs.emplace_back(1.0, 0.0);
    for (size_t i = 1; i < divisions; i++) {
      trigs.emplace_back(Radians(i * angle_scale));
    }
    trigs.emplace_back(0.0, 1.0);

    FML_DCHECK(trigs.size() == divisions + 1);
  }

  return trigs;
}

void CircleTessellator::GenerateCircleTriangleStrip(
    const TessellatedPointProc& proc,
    const Point& center,
    Scalar radius) const {
  // Quadrant 1 connecting with Quadrant 4:
  for (auto& trig : trigs_) {
    auto offset = trig * radius;
    proc({center.x - offset.x, center.y + offset.y});
    proc({center.x - offset.x, center.y - offset.y});
  }

  // The second half of the circle should be iterated in reverse, but
  // we can instead iterate forward and swap the x/y values of the
  // offset as the angles should be symmetric and thus should generate
  // symmetrically reversed trig vectors.
  // Quadrant 2 connecting with Quadrant 2:
  for (auto& trig : trigs_) {
    auto offset = trig * radius;
    proc({center.x + offset.y, center.y + offset.x});
    proc({center.x + offset.y, center.y - offset.x});
  }
}

void CircleTessellator::GenerateStrokedCircleTriangleStrip(
    const TessellatedPointProc& proc,
    const Point& center,
    Scalar outer_radius,
    Scalar inner_radius) const {
  // Zig-zag back and forth between points on the outer circle and the
  // inner circle. Both circles are evaluated at the same number of
  // quadrant divisions so the points for a given division should match
  // 1 for 1 other than their applied radius.

  // Quadrant 1:
  for (auto& trig : trigs_) {
    auto outer = trig * outer_radius;
    auto inner = trig * inner_radius;
    proc({center.x - outer.x, center.y - outer.y});
    proc({center.x - inner.x, center.y - inner.y});
  }

  // The even quadrants of the circle should be iterated in reverse, but
  // we can instead iterate forward and swap the x/y values of the
  // offset as the angles should be symmetric and thus should generate
  // symmetrically reversed trig vectors.
  // Quadrant 2:
  for (auto& trig : trigs_) {
    auto outer = trig * outer_radius;
    auto inner = trig * inner_radius;
    proc({center.x + outer.y, center.y - outer.x});
    proc({center.x + inner.y, center.y - inner.x});
  }

  // Quadrant 3:
  for (auto& trig : trigs_) {
    auto outer = trig * outer_radius;
    auto inner = trig * inner_radius;
    proc({center.x + outer.x, center.y + outer.y});
    proc({center.x + inner.x, center.y + inner.y});
  }

  // Quadrant 4:
  for (auto& trig : trigs_) {
    auto outer = trig * outer_radius;
    auto inner = trig * inner_radius;
    proc({center.x - outer.y, center.y + outer.x});
    proc({center.x - inner.y, center.y + inner.x});
  }
}

void CircleTessellator::GenerateRoundCapLineTriangleStrip(
    const TessellatedPointProc& proc,
    const Point& p0,
    const Point& p1,
    Scalar radius) const {
  auto along = p1 - p0;
  auto length = along.GetLength();
  if (length < kEhCloseEnough) {
    return GenerateCircleTriangleStrip(proc, p0, radius);
  }
  along *= radius / length;
  auto across = Point(-along.y, along.x);

  for (auto& trig : trigs_) {
    auto relative_across = across * trig.cos;
    auto relative_along = along * trig.sin;
    proc({p0 + relative_across - relative_along});
    proc({p1 + relative_across + relative_along});
  }
  // The second half of the round caps should be iterated in reverse, but
  // we can instead iterate forward and swap the sin/cos values as they
  // should be symmetric.
  for (auto& trig : trigs_) {
    auto relative_across = across * trig.sin;
    auto relative_along = along * trig.cos;
    proc({p0 - relative_across - relative_along});
    proc({p1 - relative_across + relative_along});
  }
}

}  // namespace impeller
