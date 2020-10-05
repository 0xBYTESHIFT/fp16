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
}