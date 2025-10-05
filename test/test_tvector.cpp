#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> v1(v);

  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 10; v[1] = 20; v[2] = 30;

  TDynamicVector<int> v1(v);
  v1[0] = 999;

  EXPECT_EQ(10, v[0]);
  EXPECT_NE(v[0], v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(3);
  EXPECT_THROW(v.at(static_cast<size_t>(-1)), std::out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(3);
  EXPECT_THROW(v.at(v.size()), std::out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(3u, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2 = v1;
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(5), v2(2);
  v2[0] = 7; v2[1] = 8;

  v1 = v2;
  EXPECT_EQ(2u, v1.size());
  EXPECT_EQ(7, v1[0]);
  EXPECT_EQ(8, v1[1]);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> src(2), dst(5);
  src[0] = 11; src[1] = 22;
  ASSERT_NO_THROW(dst = src);
  EXPECT_EQ(2u, dst.size());
  EXPECT_EQ(src, dst);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> a(3), b(3);
  a[0]=1; a[1]=2; a[2]=3;
  b[0]=1; b[1]=2; b[2]=3;
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> a(2);
  a[0] = 5; a[1] = 6;
  EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  v[0]=1; v[1]=2; v[2]=3;
  TDynamicVector<int> res = v + 5;
  EXPECT_EQ(6, res[0]);
  EXPECT_EQ(7, res[1]);
  EXPECT_EQ(8, res[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<double> v(3);
  v[0]=1.5; v[1]=2.5; v[2]=3.5;
  TDynamicVector<double> res = v - 1.0;
  EXPECT_DOUBLE_EQ(0.5, res[0]);
  EXPECT_DOUBLE_EQ(1.5, res[1]);
  EXPECT_DOUBLE_EQ(2.5, res[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<double> v(3);
  v[0]=1.0; v[1]=2.0; v[2]=3.0;
  TDynamicVector<double> res = v * 2.0;
  EXPECT_DOUBLE_EQ(2.0, res[0]);
  EXPECT_DOUBLE_EQ(4.0, res[1]);
  EXPECT_DOUBLE_EQ(6.0, res[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0]=1; a[1]=2; a[2]=3;
  b[0]=4; b[1]=5; b[2]=6;
  TDynamicVector<int> c = a + b;
  EXPECT_EQ(5, c[0]);
  EXPECT_EQ(7, c[1]);
  EXPECT_EQ(9, c[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(2);
  a[0]=1; a[1]=2; a[2]=3;
  b[0]=10; b[1]=20;
  EXPECT_ANY_THROW( a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0]=7; a[1]=8; a[2]=9;
  b[0]=1; b[1]=2; b[2]=3;
  TDynamicVector<int> c = a - b;
  EXPECT_EQ(6, c[0]);
  EXPECT_EQ(6, c[1]);
  EXPECT_EQ(6, c[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_ANY_THROW( (void)(a - b) );
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0]=1; a[1]=2; a[2]=3;
  b[0]=4; b[1]=5; b[2]=6;
  int dot = a * b;
  EXPECT_EQ(32, dot);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(2);
  EXPECT_ANY_THROW(a * b);
}

TEST(TDynamicVector, can_construct_from_raw_array_and_is_independent_copy)
{
  int arr[] = { 5, 6, 7, 8 };
  TDynamicVector<int> v(arr, 4);
  arr[0] = 999;
  EXPECT_EQ(5, v[0]);
  EXPECT_EQ(6, v[1]);
  EXPECT_EQ(7, v[2]);
  EXPECT_EQ(8, v[3]);
}

TEST(TDynamicVector, move_constructor_transfers_ownership)
{
  TDynamicVector<int> src(3);
  src[0] = 1; src[1] = 2; src[2] = 3;
  TDynamicVector<int> copy_before(src);
  TDynamicVector<int> moved(std::move(src));
  EXPECT_EQ(copy_before, moved);
  EXPECT_EQ(0u, src.size());
}

TEST(TDynamicVector, move_assignment_transfers_ownership)
{
  TDynamicVector<int> src(4);
  src[0]=10; src[1]=11; src[2]=12; src[3]=13;
  TDynamicVector<int> dst(2);
  dst[0]=1; dst[1]=2;
  dst = std::move(src);
  EXPECT_EQ(4u, dst.size());
  EXPECT_EQ(10, dst[0]);
  EXPECT_EQ(11, dst[1]);
  EXPECT_EQ(12, dst[2]);
  EXPECT_EQ(13, dst[3]);
  EXPECT_EQ(0u, src.size());
}

TEST(TDynamicVector, friend_swap_exchanges_contents_and_sizes)
{
  TDynamicVector<int> a(2);
  a[0]=1; a[1]=2;
  TDynamicVector<int> b(3);
  b[0]=10; b[1]=20; b[2]=30;
  swap(a, b);
  EXPECT_EQ(3u, a.size());
  EXPECT_EQ(2u, b.size());
  EXPECT_EQ(10, a[0]); EXPECT_EQ(20, a[1]); EXPECT_EQ(30, a[2]);
  EXPECT_EQ(1, b[0]);  EXPECT_EQ(2, b[1]);
}

TEST(TDynamicVector, stream_input_output_roundtrip)
{
  TDynamicVector<int> v(3);
  v[0]=42; v[1]=43; v[2]=44;
  std::stringstream ss;
  ss << v;
  TDynamicVector<int> w(3);
  ss >> w;
  EXPECT_EQ(v, w);
}

TEST(TDynamicVector, float_equality_within_epsilon)
{
  TDynamicVector<float> a(3), b(3);
  a[0] = 1.00000f; a[1] = 2.00000f; a[2] = 3.00000f;
  b[0] = 1.000004f; b[1] = 1.999996f; b[2] = 3.0000005f;
  EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, float_inequality_outside_epsilon)
{
  TDynamicVector<float> a(2), b(2);
  a[0] = 1.0f; a[1] = 2.0f;
  b[0] = 1.0f + 1e-4f;
  b[1] = 2.0f;
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, const_indexing_returns_value)
{
  TDynamicVector<int> v(2);
  v[0] = 7; v[1] = 8;
  const TDynamicVector<int>& cv = v;
  EXPECT_EQ(7, cv[0]);
  EXPECT_EQ(8, cv[1]);
}