#include <iostream>
#include <cassert>
#include "table.hpp"
#include "half/half.hpp"

template<class T>
auto to_string(const T& val){
    std::stringstream ss;
    ss.precision(10);
    ss << val;
    return ss.str();
};

template<class T>
auto gen_row(const std::string &name, cli_table &t){
    auto dig = std::numeric_limits<T>::digits;
    auto dig10 = std::numeric_limits<T>::digits10;
    auto max_dig10 = std::numeric_limits<T>::max_digits10;
    auto min_exp = std::numeric_limits<T>::min_exponent;
    auto max_exp = std::numeric_limits<T>::max_exponent;
    t.add_row<cli_table::row>({name,
        to_string(std::numeric_limits<T>::min()),
        to_string(std::numeric_limits<T>::max()),
        to_string(std::numeric_limits<T>::lowest()),
        to_string(std::numeric_limits<T>::epsilon()),
        to_string(min_exp),
        to_string(max_exp),
        to_string(std::numeric_limits<T>::denorm_min()),
        to_string(dig),
        to_string(dig10),
        to_string(max_dig10)
    });
}

int main(int, char**) {
    using half_float::half;
    using namespace half_float::literal;

    auto f0 = 2.f;
    auto f1 = 3.f;
    half h0 = f0;
    half h1 = f1;

    assert((half)f0+(half)f1 == (float)(h0+h1));
    assert((half)f0-(half)f1 == (float)(h0-h1));
    assert((half)f0*(half)f1 == (float)(h0*h1));
    assert((half)f0/(half)f1 == (float)(h0/h1));

    auto is_scalar = std::is_scalar<half>::value;
    auto is_fp = std::is_floating_point<half>::value;
    auto is_int = std::is_integral<half>::value;
    auto is_arithmetic = std::is_arithmetic<half>::value;
    auto is_signed = std::is_signed<half>::value;
    std::cout << "is_scalar:" << is_scalar << "\n";
    std::cout << "is_floating_point:" << is_fp << "\n";
    std::cout << "is_integral:" << is_int << "\n";
    std::cout << "is_arithmetic:" << is_arithmetic << "\n";
    std::cout << "is_signed:" << is_signed << "\n";
    std::cout << "\n";

    cli_table t;
    using row = std::vector<std::string>; 
    t.add_row<row>({"name", "min", "max", "lowest",
        "eps", "min_exp", "max_exp",
        "denorm_min", "dig", "dig10", "max_dig10"});
    gen_row<half>("half", t);
    gen_row<float>("float", t);
    gen_row<double>("double", t);
    std::cout << t << std::endl;

    /*
    assert(is_scalar);
    assert(is_fp);
    assert(!is_int);
    assert(is_arithmetic);
    assert(is_signed);
    */
}