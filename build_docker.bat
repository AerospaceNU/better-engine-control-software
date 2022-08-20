docker pull wpilib/raspbian-cross-ubuntu:10-18.04

docker run -v %cd%:/work wpilib/raspbian-cross-ubuntu:10-18.04 bash -c "cd work && cmake -B build-pi -DIS_CROSS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=CMake/arm-pi-gnueabihf.toolchain.cmake && cmake --build build-pi --target ecs_pi -- -j 8"
