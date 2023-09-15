docker pull wpilib/raspbian-cross-ubuntu:bullseye-22.04

docker run -v ${PWD}:/work wpilib/raspbian-cross-ubuntu:bullseye-22.04 bash -c "cd work && cmake -B build-pi -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=CMake/arm-pi-gnueabihf.toolchain.cmake && cmake --build build-pi --target ecs_pi -- -j 8"
