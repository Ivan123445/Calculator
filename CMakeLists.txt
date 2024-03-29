cmake_minimum_required(VERSION 3.25)
project(C7_SmartCalc_v1_0_1 C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -rdynamic")

set(CALCULATE_H src/calculate/s21_calculate.h)
set(CALCULATE_C src/calculate/convert_to_rpn.c
                src/calculate/parse_str.c
                src/calculate/calc_rpn.c
                src/calculate/calculate_coordinates.c
                src/calculate/create_coordinate_file.c)

set(GUI_C   src/gui/calc.glade
            src/gui/main_window.c
        src/gui/deposit_calc_window.c
        )

set(UTILS_H src/utils/s21_utils.h)
set(UTILS_C src/utils/stack.c
            src/utils/utils.c)

set(TEST_C src/test/test.c
            src/test/test_parse_str.c
            src/test/test_convert_to_rpn.c
            src/test/test_calc_rpn.c
            src/test/test_calculate_coordinates.c
            src/test/test_create_coordinate_file.c)

add_executable(C7_SmartCalc_v1_0_1
        src/s21_smartcalc.h

        ${CALCULATE_H}
        ${CALCULATE_C}

        ${GUI_C}

        ${UTILS_H}
        ${UTILS_C}

#        ${TEST_C}
        )

add_executable(calculation_test
        src/s21_smartcalc.h

        ${CALCULATE_H}
        ${CALCULATE_C}

#        ${GUI_C}

        ${UTILS_H}
        ${UTILS_C}

        ${TEST_C}
        )


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

target_link_libraries(C7_SmartCalc_v1_0_1 ${GTK3_LIBRARIES} check subunit m)
target_link_libraries(calculation_test ${GTK3_LIBRARIES} check subunit m)

add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})