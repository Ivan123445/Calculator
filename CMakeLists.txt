cmake_minimum_required(VERSION 3.25)
project(C7_SmartCalc_v1_0_1 C)

set(CMAKE_C_STANDARD 11)

set(CALCULATE_H src/calculate/s21_calculate.h)
set(CALCULATE_C src/calculate/convert_to_rpn.c
                src/calculate/parse_str.c)

set(UTILS_H src/utils/s21_utils.h)
set(UTILS_C src/utils/stack.c)

add_executable(C7_SmartCalc_v1_0_1
        src/s21_smartcalc.h

        ${CALCULATE_H}
        ${CALCULATE_C}

        ${UTILS_H}
        ${UTILS_C}
        )
