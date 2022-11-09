#include <iostream>

#include "sln_device.hpp"


int main(int argc, char *argv[]) {

    sln::Device device;

    while(!device.should_close()) {
        device.poll_events();
    }

    return 0;
}
