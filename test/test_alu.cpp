#include "test_alu.hpp"

#include <gtest/gtest.h>
#include <verilated.h>

#include <climits>
#include <random>

void ValuForTest::exec(const int &_inst, const int &_a, const int &_b) {
    inst = _inst;
    a = _a;
    b = _b;
    eval();
}

class TestAlu : public ::testing::Test {
   protected:
    TestAlu()
        : engine(seed_gen()), dist_int(INT_MIN, INT_MAX), dist_5bit(0, 31) {}
    ValuForTest *dut;

    std::random_device seed_gen;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> dist_int;
    std::uniform_int_distribution<unsigned char> dist_5bit;

    int inst;
    int a;
    int b;

    void SetUp() override { dut = new ValuForTest(); }

    void TearDown() override {
        dut->final();
        delete dut;
    }
};

namespace {

const unsigned N = 1000000;

TEST_F(TestAlu, ADD) {
    inst = 0b000;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a + b);
    }
}

TEST_F(TestAlu, SLL) {
    inst = 0b001;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_5bit(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a << b);
    }
}

TEST_F(TestAlu, SLT) {
    inst = 0b010;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a < b);
    }
}

TEST_F(TestAlu, SLTU) {
    inst = 0b011;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, (unsigned)a < (unsigned)b);
    }
}

TEST_F(TestAlu, XOR) {
    inst = 0b100;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a ^ b);
    }
}

TEST_F(TestAlu, SRL) {
    inst = 0b101;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_5bit(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, (unsigned)a >> b);
    }
}

TEST_F(TestAlu, OR) {
    inst = 0b110;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a | b);
    }
}

TEST_F(TestAlu, AND) {
    inst = 0b111;
    for (unsigned i = 0; i < N; ++i) {
        a = dist_int(engine);
        b = dist_int(engine);
        dut->exec(inst, a, b);
        ASSERT_EQ(dut->rslt, a & b);
    }
}

}  // namespace
