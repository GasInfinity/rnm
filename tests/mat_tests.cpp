#include <gtest/gtest.h>
#include <rnm/rnm.hpp>

using namespace rnm;

TEST(MatTest, AdditionOperator) {
    mat2<float> m1{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> m2{{5.0f, 6.0f}, {7.0f, 8.0f}};
    mat2<float> result = m1 + m2;

    EXPECT_FLOAT_EQ((result[0, 0]), 6.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 8.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 10.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 12.0f); // Second row, second column
}

TEST(MatTest, SubtractionOperator) {
    mat2<float> m1{{5.0f, 6.0f}, {7.0f, 8.0f}};
    mat2<float> m2{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> result = m1 - m2;

    EXPECT_FLOAT_EQ((result[0, 0]), 4.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 4.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 4.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 4.0f); // Second row, second column
}

TEST(MatTest, ScalarMultiplication) {
    mat2<float> m{{1.0f, 2.0f}, {3.0f, 4.0f}};
    float scalar = 2.0f;
    mat2<float> result = m * scalar;

    EXPECT_FLOAT_EQ((result[0, 0]), 2.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 4.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 6.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 8.0f); // Second row, second column
}

TEST(MatTest, ScalarDivision) {
    mat2<float> m{{2.0f, 4.0f}, {6.0f, 8.0f}};
    float scalar = 2.0f;
    mat2<float> result = m / scalar;

    EXPECT_FLOAT_EQ((result[0, 0]), 1.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 2.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 3.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 4.0f); // Second row, second column
}

TEST(MatTest, MatrixMultiplication) {
    mat2<float> m1{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> m2{{5.0f, 6.0f}, {7.0f, 8.0f}};
    mat2<float> result = m1 * m2;

    EXPECT_FLOAT_EQ((result[0, 0]), 19.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 22.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 43.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 50.0f); // Second row, second column
}

TEST(MatTest, Adjugate) {
    mat2<float> m{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> result = adjugate(m);

    EXPECT_FLOAT_EQ((result[0, 0]), 4.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), -3.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), -2.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 1.0f);  // Second row, second column
}

TEST(MatTest, Inverse) {
    mat2<float> m{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> result = inverse(m);

    EXPECT_FLOAT_EQ((result[0, 0]), -2.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 1.0f);  // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 1.5f);  // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), -0.5f); // Second row, second column
}

TEST(MatTest, Minor) {
    mat3<float> m{{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    mat2<float> result = minor<0, 0>(m);

    EXPECT_FLOAT_EQ((result[0, 0]), 5.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 6.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 8.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 9.0f); // Second row, second column
}

TEST(MatTest, Determinant) {
    mat3<float> m{{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    float result = determinant(m);

    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(MatTest, Transpose) {
    mat2<float> m{{1.0f, 2.0f}, {3.0f, 4.0f}};
    mat2<float> result = transpose(m);

    EXPECT_FLOAT_EQ((result[0, 0]), 1.0f); // First row, first column
    EXPECT_FLOAT_EQ((result[0, 1]), 3.0f); // First row, second column
    EXPECT_FLOAT_EQ((result[1, 0]), 2.0f); // Second row, first column
    EXPECT_FLOAT_EQ((result[1, 1]), 4.0f); // Second row, second column
}

// Test for matrix multiplication with matrix * vector
TEST(MatTest, MatrixVectorMultiplication) {
    mat2<float> m{{1.0f, 2.0f}, {3.0f, 4.0f}};
    vec2<float> v{5.0f, 6.0f};
    vec2<float> result = m * v;

    EXPECT_FLOAT_EQ((result[0]), 17.0f); // First element of result vector
    EXPECT_FLOAT_EQ((result[1]), 39.0f); // Second element of result vector
}

// Test for matrix multiplication with vector * matrix
TEST(MatTest, VectorMatrixMultiplication) {
    vec2<float> v{1.0f, 2.0f};
    mat2<float> m{{3.0f, 4.0f}, {5.0f, 6.0f}};
    vec2<float> result = v * m;

    EXPECT_FLOAT_EQ((result[0]), 13.0f); // First element of result vector
    EXPECT_FLOAT_EQ((result[1]), 16.0f); // Second element of result vector
}
