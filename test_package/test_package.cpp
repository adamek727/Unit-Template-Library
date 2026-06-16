#include <utl/utl.hpp>

int main() {
    auto distance = utl::Velocity<double>(30.0) * utl::Time<double>(5.0);
    return distance.m() == 150.0 ? 0 : 1;
}
