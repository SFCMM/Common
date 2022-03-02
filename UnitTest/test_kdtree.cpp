#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(kdtree, HandlesZeroInput) {
  KDTree<Debug_Level::debug, 2> testKD;
  triangle<2> a;
  a.m_vertices[0] =VectorD<2>({0, 0});
  a.m_vertices[1] =VectorD<2>({1, 1});
  a.m_vertices[2] =VectorD<2>({1, 0});
  a.m_max = VectorD<2>({1,1});
  a.m_min = VectorD<2>({0,0});

  std::vector<triangle<2>> triangles;
  triangles.emplace_back(a);

  BoundingBoxCT<2> bb;

  testKD.buildTree(triangles, bb);

  std::vector<GInt> nodeList;
  VectorD<2> point({0.5, 0.5});
  testKD.retrieveNodes(point, nodeList);

  ASSERT_EQ(nodeList.size(), 1);

  std::cout << nodeList.size() << std::endl;
  std::cout << nodeList[0] << std::endl;
}