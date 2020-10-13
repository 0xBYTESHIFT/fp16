#include <iostream>
#include <cassert>
#include "half.hpp"

int main(int, char**) {
    using half_float::half;
    using namespace half_float::literal;

    auto f0 = 2.f;
    auto f1 = 3.f;
    half h0(f0);
    half h1(f1);

    assert((half)f0+(half)f1 == (float)(h0+h1));
    assert((half)f0-(half)f1 == (float)(h0-h1));
    assert((half)f0*(half)f1 == (float)(h0*h1));
    assert((half)f0/(half)f1 == (float)(h0/h1));

    auto is_scalar = std::is_scalar<half>::value;
    auto is_fp = std::is_floating_point<half>::value;
    auto is_int = std::is_integral<half>::value;
    auto is_arithmetic = std::is_arithmetic<half>::value;
    std::cout << "is_scalar:" << is_scalar << "\n";
    std::cout << "is_floating_point:" << is_fp << "\n";
    std::cout << "is_integral:" << is_int << "\n";
    std::cout << "is_arithmetic:" << is_arithmetic << "\n";

    assert(is_scalar);
    assert(is_fp);
    assert(!is_int);
    assert(is_arithmetic);
}