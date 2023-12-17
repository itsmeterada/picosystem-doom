rm -rf rp2040-build
mkdir rp2040-build
cd rp2040-build

cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DPICO_BOARD=vgaboard -DPICO_SDK_PATH=$PICO_SDK_PATH -DPICO_EXTRAS_PATH=$PICO_EXTRAS_PATH ..
