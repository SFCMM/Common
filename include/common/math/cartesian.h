#ifndef GRIDGENERATOR_CARTESIAN_H
#define GRIDGENERATOR_CARTESIAN_H

#include <gcem.hpp>

namespace cartesian {

/// The direction opposite to the given dir.
/// \param dir Direction for which to obtain opposite direction.
/// \return The opposite direction to dir.
static constexpr inline auto oppositeDir(const GInt dir) -> GInt {
  return 2 * (dir / 2) + 1 - (dir % 2);
  // 0 = 1 ok
  // 1 = 0 ok
  // 2 = 3 ok
  //...
  // 5 = 4 ok
  // 6 = 7 ok
  // 7 = 6 ok
}
/// Return maximum number of children per cell
/// \tparam NDIM Number of dimension of the Cartesian grid
/// \return The maximum number of children for a NDIM Cartesian mesh
template <GInt NDIM>
static constexpr inline auto maxNoChildren() -> GInt {
  return gcem::pow(2, NDIM);
}

/// Return maximum number of Neighbors per cell
/// \tparam NDIM Number of dimensions of the Cartesian grid
/// \return The maximum number of same level neighbors at the given NDIM.
template <GInt NDIM>
static constexpr inline auto maxNoNghbrs() -> GInt {
  return 2 * NDIM;
}


// todo: replace with constant expression function
/// Given the childId gives the "direction" of this child relative to the center of a cell.
static constexpr std::array<std::array<GDouble, MAX_DIM>, cartesian::maxNoChildren<MAX_DIM>()> childDir = {{
    //-> 2D
    // -x,-y, -z
    {{-1, -1, -1, -1}}, // 0
    //+x, -y, -z
    {{1, -1, -1, -1}}, // 1
    //-x, +y, -z
    {{-1, 1, -1, -1}}, // 2
    //+x, -y, -z
    {{1, 1, -1, -1}}, // 3
    //<- 2D

    //-> 3D (+z)
    {{-1, -1, 1, -1}}, // 4
    {{1, -1, 1, -1}},  // 5
    {{-1, 1, 1, -1}},  // 6
    {{1, 1, 1, -1}},   // 7
    //<- 3D (+z)

    //-> 4D
    {{-1, -1, -1, 1}}, // 8
    {{1, -1, -1, 1}},  // 9
    {{-1, 1, -1, 1}},  // 10
    {{1, 1, -1, 1}},   // 11
    {{-1, -1, 1, 1}},  // 12
    {{1, -1, 1, 1}},   // 13
    {{-1, 1, 1, 1}},   // 14
    {{1, 1, 1, 1}}     // 15
                       //<- 4D
}};

// todo: replace with constant expression function
/// Given the childId gives the neighboring childIds(and existence ==-1 -> doesnot exist)
static constexpr std::array<std::array<GDouble, cartesian::maxNoNghbrs<MAX_DIM>()>, cartesian::maxNoChildren<MAX_DIM>()> nghbrInside = {{
    //-x +x -y +y -z +z -zz +zz
    {{-1, 1, -1, 2, -1, 4, -1, 8}},  // 0
    {{0, -1, -1, 3, -1, 5, -1, 9}},  // 1
    {{-1, 3, 0, -1, -1, 6, -1, 10}}, // 2
    {{2, -1, 1, -1, -1, 7, -1, 11}}, // 3
    {{-1, 5, -1, 6, 0, -1, -1, 12}}, // 4
    {{4, -1, -1, 7, 1, -1, -1, 13}}, // 5
    {{-1, 7, 4, -1, 2, -1, -1, 14}}, // 6
    {{6, -1, 5, -1, 3, -1, -1, 15}}, // 7


    // upper table +8 and last dir = -1
    {{-1, 9, -1, 10, -1, 12, 0, -1}},  // 8
    {{8, -1, -1, 11, -1, 13, 1, -1}},  // 9
    {{-1, 11, 8, -1, -1, 14, 2, -1}},  // 10
    {{10, -1, 9, -1, -1, 15, 3, -1}},  // 11
    {{-1, 13, -1, 14, 8, -1, 4, -1}},  // 12
    {{12, -1, -1, 15, 9, -1, 5, -1}},  // 13
    {{-1, 15, 12, -1, 10, -1, 6, -1}}, // 14
    {{14, -1, 13, -1, 11, -1, 7, -1}}  // 15
}};

// todo: replace with constant expression function
/// Given the childId obtain the possible neighbors in a neighboring cell that doesnot have the same parent
static constexpr std::array<std::array<GDouble, cartesian::maxNoNghbrs<MAX_DIM>()>, cartesian::maxNoChildren<MAX_DIM>()>
    nghbrParentChildId = {{
        //-x +x -y +y -z +z -zz +zz
        {{1, -1, 2, -1, 4, -1, 8, -1}},  // 0
        {{-1, 0, 3, -1, 5, -1, 9, -1}},  // 1
        {{3, -1, -1, 0, 6, -1, 10, -1}}, // 2
        {{-1, 2, -1, 1, 7, -1, 11, -1}}, // 3
        {{5, -1, 6, -1, -1, 0, 12, -1}}, // 4
        {{-1, 4, 7, -1, -1, 1, 13, -1}}, // 5
        {{7, -1, -1, 4, -1, 2, 14, -1}}, // 6
        {{-1, 6, -1, 5, -1, 3, 15, -1}}, // 7


        // upper table +8 and last dir = -1
        {{9, -1, 10, -1, 12, -1, -1, 0}},  // 8
        {{-1, 8, 11, -1, 13, -1, -1, 1}},  // 9
        {{11, -1, -1, 8, 14, -1, -1, 2}},  // 10
        {{-1, 10, -1, 9, 15, -1, -1, 3}},  // 11
        {{13, -1, 14, -1, -1, 8, -1, 4}},  // 12
        {{-1, 12, 15, -1, -1, 9, -1, 5}},  // 13
        {{15, -1, -1, 12, -1, 10, -1, 6}}, // 14
        {{-1, 14, -1, 13, -1, 11, -1, 7}}  // 15
    }};
} // namespace cartesian
#endif // GRIDGENERATOR_CARTESIAN_H