#!/bin/bash

ARCHS="rv32ic rv32im rv32i"
TESTS="tests/kernel/stack/stack_api tests/kernel/mutex/mutex tests/kernel/context tests/kernel/critical tests/kernel/fifo/fifo_api tests/kernel/mbox/mbox_usage tests/kernel/mem_pool/mem_pool_threadsafe tests/kernel/sleep tests/kernel/timer/timer_api"

origin=$(pwd)

rm -rf regressionBuild/*
mkdir regressionBuild

for arch in $ARCHS; do
    
    tmp="/CONFIG_RISCV_ARCH=/c\CONFIG_RISCV_ARCH="\"
    tmp=$tmp$arch
    tmp=$tmp\"
    
    sed -i $tmp vexriscv_cpp_regression_defconfig

    for test in $TESTS; do
        cd ../../../$test
        rm -rf build
        mkdir build
        cd build
        cmake -DBOARD=vexriscv_cpp_regression ..
        make -j8
        riscv64-unknown-elf-objdump -S -d zephyr/zephyr.elf  > zephyr/zephyr.asm
        cd $origin
        cp ../../../$test/build/zephyr/zephyr.hex regressionBuild/${test//\//_}_$arch.hex
        cp ../../../$test/build/zephyr/zephyr.asm regressionBuild/${test//\//_}_$arch.asm
    done
done


zip regressionBuild/asm.zip regressionBuild/*.asm
rm -rf regressionBuild/*.asm

