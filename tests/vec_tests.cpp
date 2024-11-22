#include <gtest/gtest.h>
#include <rnm/rnm.hpp>

using namespace rnm;

TEST(VecTest, AdditionOperator) {
    vec3<float> v1{1.0f, 2.0f, 3.0f};
    vec3<float> v2{4.0f, 5.0f, 6.0f};
    vec3<float> result = v1 + v2;
    
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(VecTest, SubtractionOperator) {
    vec3<float> v1{6.0f, 7.0f, 8.0f};
    vec3<float> v2{1.0f, 2.0f, 3.0f};
    vec3<float> result = v1 - v2;
    
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
    EXPECT_FLOAT_EQ(result.z, 5.0f);
}

TEST(VecTest, ScalarMultiplication) {
    vec3<float> v{1.0f, 2.0f, 3.0f};
    float scalar = 2.0f;
    vec3<float> result = v * scalar;
    
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(VecTest, ScalarDivision) {
    vec3<float> v{10.0f, 20.0f, 30.0f};
    float scalar = 2.0f;
    vec3<float> result = v / scalar;
    
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 10.0f);
    EXPECT_FLOAT_EQ(result.z, 15.0f);
}

TEST(VecTest, NegationOperator) {
    vec3<float> v{1.0f, -2.0f, 3.0f};
    vec3<float> result = -v;
    
    EXPECT_FLOAT_EQ(result.x, -1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, -3.0f);
}

TEST(VecTest, DotProduct) {
    vec3<float> v1{1.0f, 2.0f, 3.0f};
    vec3<float> v2{4.0f, -5.0f, 6.0f};
    float result = dot(v1, v2);
    
    EXPECT_FLOAT_EQ(result, 12.0f);  // 1*4 + 2*(-5) + 3*6 = 4 - 10 + 18 = 12
}

TEST(VecTest, CrossProduct) {
    vec3<float> v1{1.0f, 2.0f, 3.0f};
    vec3<float> v2{4.0f, -5.0f, 6.0f};
    vec3<float> result = cross(v1, v2);
     
    EXPECT_FLOAT_EQ(result.x, 27.f);
    EXPECT_FLOAT_EQ(result.y, 6.f);
    EXPECT_FLOAT_EQ(result.z, -13.f);
}


TEST(VecTest, LengthSquared) {
    vec3<float> v{1.0f, 2.0f, 3.0f};
    float result = length_sqr(v);
    
    EXPECT_FLOAT_EQ(result, 14.0f);  // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
}

TEST(VecTest, Length) {
    vec3<float> v{1.0f, 2.0f, 3.0f};
    float result = length(v);
    
    EXPECT_FLOAT_EQ(result, std::sqrt(14.0f));  // sqrt(1 + 4 + 9)
}

TEST(VecTest, Normalized) {
    vec3<float> v{1.0f, 2.0f, 3.0f};
    vec3<float> result = normalized(v);
    
    float length_val = length(v);
    EXPECT_FLOAT_EQ(result.x, v.x / length_val);
    EXPECT_FLOAT_EQ(result.y, v.y / length_val);
    EXPECT_FLOAT_EQ(result.z, v.z / length_val);
}

TEST(VecTest, Lerp) {
    vec3<float> v1{0.0f, 0.0f, 0.0f};
    vec3<float> v2{1.0f, 1.0f, 1.0f};
    float t = 0.5f;
    
    vec3<float> result = lerp(v1, v2, t);
    
    EXPECT_FLOAT_EQ(result.x, 0.5f);
    EXPECT_FLOAT_EQ(result.y, 0.5f);
    EXPECT_FLOAT_EQ(result.z, 0.5f);
}

TEST(VecTest, PerpendicularRight) {
    vec2<float> v{1.0f, 0.0f};
    vec2<float> result = perpendicular_right(v);
    
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, -1.0f);
}

TEST(VecTest, PerpendicularLeft) {
    vec2<float> v{1.0f, 0.0f};
    vec2<float> result = perpendicular_left(v);
    
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 1.0f);
}
