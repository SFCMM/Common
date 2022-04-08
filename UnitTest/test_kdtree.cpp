#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(kdtree, HandlesZeroInput) {
  KDTree<Debug_Level::debug, 2> testKD;
  triangle<2>                   a;
  a.m_vertices[0] = VectorD<2>({0, 0});
  a.m_vertices[1] = VectorD<2>({1, 1});
  a.m_vertices[2] = VectorD<2>({1, 0});
  a.m_max         = VectorD<2>({1, 1});
  a.m_min         = VectorD<2>({0, 0});

  std::vector<triangle<2>> triangles;
  triangles.emplace_back(a);

  BoundingBoxCT<2> bb;

  testKD.buildTree(triangles, bb);

  std::vector<GInt> nodeList;
  VectorD<2>        point({0.5, 0.5});
  testKD.retrieveNodes(point, nodeList);

  ASSERT_EQ(nodeList.size(), 1);


  KDTree<Debug_Level::debug, 2> testKD2;
  triangle<2>                   b;
  triangle<2>                   c;
  triangle<2>                   d;
  b.m_vertices[0] = VectorD<2>({0, 0});
  b.m_vertices[1] = VectorD<2>({1, 1});
  b.m_vertices[2] = VectorD<2>({1, 0});
  b.m_max         = VectorD<2>({1, 1});
  b.m_min         = VectorD<2>({0, 0});

  c.m_vertices[0] = VectorD<2>({0, 1});
  c.m_vertices[1] = VectorD<2>({1, 2});
  c.m_vertices[2] = VectorD<2>({2, 0});
  c.m_max         = VectorD<2>({2, 2});
  c.m_min         = VectorD<2>({0, 0});

  d.m_vertices[0] = VectorD<2>({2, 1});
  d.m_vertices[1] = VectorD<2>({1, 2});
  d.m_vertices[2] = VectorD<2>({1, 1});
  d.m_max         = VectorD<2>({2, 2});
  d.m_min         = VectorD<2>({1, 1});

  std::vector<triangle<2>> triangles2;
  triangles2.emplace_back(b);
  triangles2.emplace_back(c);
  triangles2.emplace_back(d);

  BoundingBoxCT<2> bb2;

  testKD2.buildTree(triangles2, bb2);

  std::vector<GInt> nodeList2;
  VectorD<2>        point2({1.5, 1.5});
  testKD2.retrieveNodes(point2, nodeList2);

  //todo: the test is pointless
  ASSERT_EQ(nodeList2.size(), 1);
  ASSERT_EQ(testKD2.get_root(), 0);
  std::cout << "nodeList " << nodeList2[0] << std::endl;
}