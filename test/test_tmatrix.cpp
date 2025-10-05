#include "tmatrix.h"

#include <gtest.h>
#include <sstream>
#include <utility>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  for (size_t i = 0; i < m.size(); ++i)
    for (size_t j = 0; j < m.size(); ++j)
      m[i][j] = static_cast<int>(i * 10 + j);

  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  TDynamicMatrix<int> m1(m);
  m1[0][0] = 999;
  EXPECT_EQ(1, m[0][0]);
  EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 42;
  EXPECT_EQ(42, m[1][2]);
  const TDynamicMatrix<int>& cm = m;
  EXPECT_EQ(42, cm[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_THROW(m[0].at(static_cast<size_t>(-1)), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_THROW(m[0].at(m.size()), std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(2u, m.size());
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[0][1]);
  EXPECT_EQ(3, m[1][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1; a[0][1]=2;
  a[1][0]=3; a[1][1]=4;
  b = a;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> a(3), b(2);
  b[0][0] = 7; b[0][1] = 8;
  b[1][0] = 9; b[1][1] = 10;

  a = b;
  EXPECT_EQ(2u, a.size());
  EXPECT_EQ(7, a[0][0]);
  EXPECT_EQ(10, a[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> src(2), dst(4);
  src[0][0] = 11; src[0][1] = 22;
  src[1][0] = 33; src[1][1] = 44;
  ASSERT_NO_THROW(dst = src);
  EXPECT_EQ(2u, dst.size());
  EXPECT_EQ(src, dst);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1; a[0][1]=2;
  a[1][0]=3; a[1][1]=4;
  b[0][0]=1; b[0][1]=2;
  b[1][0]=3; b[1][1]=4;
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 5; a[0][1] = 6;
  a[1][0] = 7; a[1][1] = 8;
  EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=1; a[0][1]=2; a[1][0]=3; a[1][1]=4;
  b[0][0]=10; b[0][1]=20; b[1][0]=30; b[1][1]=40;
  TDynamicMatrix<int> c = a + b;
  EXPECT_EQ(11, c[0][0]);
  EXPECT_EQ(22, c[0][1]);
  EXPECT_EQ(33, c[1][0]);
  EXPECT_EQ(44, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_ANY_THROW( (void)(a + b) );
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0]=7; a[0][1]=8; a[1][0]=9; a[1][1]=10;
  b[0][0]=1; b[0][1]=2; b[1][0]=3; b[1][1]=4;
  TDynamicMatrix<int> c = a - b;
  EXPECT_EQ(6, c[0][0]);
  EXPECT_EQ(6, c[0][1]);
  EXPECT_EQ(6, c[1][0]);
  EXPECT_EQ(6, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(4);
  EXPECT_ANY_THROW( (void)(a - b) );
}


TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  TDynamicMatrix<int> r = m * 10;
  EXPECT_EQ(10, r[0][0]);
  EXPECT_EQ(20, r[0][1]);
  EXPECT_EQ(30, r[1][0]);
  EXPECT_EQ(40, r[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  TDynamicVector<int> v(2);
  v[0] = 5; v[1] = 6;
  TDynamicVector<int> res = m * v;
  // res = [1*5 + 2*6, 3*5 + 4*6] = [17, 39]
  EXPECT_EQ(17, res[0]);
  EXPECT_EQ(39, res[1]);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  // a = [1 2; 3 4], b = [2 0; 1 2]
  a[0][0]=1; a[0][1]=2; a[1][0]=3; a[1][1]=4;
  b[0][0]=2; b[0][1]=0; b[1][0]=1; b[1][1]=2;
  TDynamicMatrix<int> c = a * b;
  // c = a*b = [1*2+2*1, 1*0+2*2; 3*2+4*1, 3*0+4*2] = [4,4;10,8]
  EXPECT_EQ(4, c[0][0]);
  EXPECT_EQ(4, c[0][1]);
  EXPECT_EQ(10, c[1][0]);
  EXPECT_EQ(8, c[1][1]);
}

TEST(TDynamicMatrix, stream_input_output_roundtrip)
{
  TDynamicMatrix<int> m(2);
  m[0][0]=1; m[0][1]=2; m[1][0]=3; m[1][1]=4;
  std::stringstream ss;
  ss << m;
  TDynamicMatrix<int> r(2);
  ss >> r;
  EXPECT_EQ(m, r);
}
