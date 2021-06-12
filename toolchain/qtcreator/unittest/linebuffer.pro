TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG   += -Wall -Wextra -std=c++17 -ffunction-sections
#QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -Ofast -fexpensive-optimizations -mtune=native -march=native -flto -funroll-loops -frename-registers  -Wformat -Wformat-security -fpic -shared -fasynchronous-unwind-tables -D_GLIBCXX_ASSERTIONS -fstack-clash-protection -fstack-protector-all -fcf-protection -pipe -msse3
QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -O3 -mtune=znver2 -march=native

#QMAKE_CXXFLAGS += -pthread

QMAKE_LFLAGS_DEBUG   += -Wl,-z,now -Wl,-z,relro
QMAKE_LFLAGS_RELEASE += -Wl,-z,now -Wl,-z,relro

QMAKE_LFLAGS += -Wl,-Map=signslots.map

SOURCES += \
  $$PWD/../../../src/the_framework/algorithms/countbitsset.cpp \
  $$PWD/../../../src/the_framework/algorithms/large_mul.cpp \
  $$PWD/../../../src/the_framework/core/error_mgnt.cpp \
  $$PWD/../../../src/the_framework/enviroment/endianness_detect.cpp \
 #$$PWD/../../../src/the_framework/i18n/i18n_strings.cpp \
  $$PWD/../../../src/the_framework/math/flowpoint_util.cpp \
  $$PWD/../../../src/the_framework/math/log2.cpp \
  $$PWD/../../../src/the_framework/math/math_discrete.cpp \
  $$PWD/../../../src/targets/unittest/main.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_bitmacros.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_bitreverse.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_compiler.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_countbitsset.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_dbllnkdlst.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_dtypes.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_fields.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_helpers.cpp \
 #$$PWD/../../../src/the_framework/unittest/utest_i18n.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_large_mul.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_large_mul_v2.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_linebuffer.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_linear_equation.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_log2.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_math_discrete.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_meta.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_minmax.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_ovf_save.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_utility_fct.cpp \
  $$PWD/../../../src/the_framework/utility/linebuffer.cpp \
  $$PWD/../../../src/the_framework/utility/Stringhelper.cpp \
  $$PWD/../../../src/the_framework/utility/utility_fct.cpp \
  $$PWD/../../../src/the_framework/algorithms/crc/base_crc.cpp \
  $$PWD/../../../src/the_framework/algorithms/crc/para_crc.cpp \
  $$PWD/../../../src/the_framework/algorithms/crc/para_crc_sets.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_fifo_fixed_size.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_median_filter.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_moving_average.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_fastcopy.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_ringbuffer.cpp \
  $$PWD/../../../src/the_framework/core/scope_guard.cpp \
  $$PWD/../../../src/the_framework/core/signslots.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_dis_sll.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_dividebyshift.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_signslots.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_statemachine.cpp \
  $$PWD/../../../src/the_framework/unittest/utest_variable_guard.cpp \
  $$PWD/../../../src/the_framework/utility/gendata.cpp \
  $$PWD/../../../src/the_framework/core/mutual_lock.cpp

HEADERS += \
  $$PWD/../../../external/Catch2/single_include/catch2/catch.hpp \
  $$PWD/../../../src/the_framework/algorithms/bitreverse.h \
  $$PWD/../../../src/the_framework/algorithms/countbitsset.h \
  $$PWD/../../../src/the_framework/algorithms/crc/base_crc.h \
  $$PWD/../../../src/the_framework/algorithms/crc/para_crc.h \
  $$PWD/../../../src/the_framework/algorithms/crc/para_crc_sets.h \
  $$PWD/../../../src/the_framework/algorithms/fastcopy.h \
  $$PWD/../../../src/the_framework/algorithms/large_mul.h \
  $$PWD/../../../src/the_framework/algorithms/large_mul_v2.h \
  $$PWD/../../../src/the_framework/algorithms/minmax.h \
  $$PWD/../../../src/the_framework/algorithms/median_filter.h \
  $$PWD/../../../src/the_framework/algorithms/moving_average.h \
  $$PWD/../../../src/the_framework/core/array_fun.h \
  $$PWD/../../../src/the_framework/core/bitmacros.h \
  $$PWD/../../../src/the_framework/core/compile_guards.h \
  $$PWD/../../../src/the_framework/core/dtypes.h \
  $$PWD/../../../src/the_framework/core/error_mgnt.h \
  $$PWD/../../../src/the_framework/core/iterators.h \
  $$PWD/../../../src/the_framework/core/meta.h \
  $$PWD/../../../src/the_framework/core/statemachine.h \
  $$PWD/../../../src/the_framework/core/scope_guard.h \
  $$PWD/../../../src/the_framework/core/signslots.h \
  $$PWD/../../../src/the_framework/core/variable_guard.h \
  $$PWD/../../../src/the_framework/dstruct/dbllnkdlst.h \
  $$PWD/../../../src/the_framework/dstruct/dis_sll.h \
  $$PWD/../../../src/the_framework/dstruct/fields.h \
  $$PWD/../../../src/the_framework/dstruct/fifo_fixed_size.h \
  $$PWD/../../../src/the_framework/dstruct/node_definitions.h \
  $$PWD/../../../src/the_framework/dstruct/ringbuffer.h \
  $$PWD/../../../src/the_framework/dstruct/ringbuffer_ll.h \
  $$PWD/../../../src/the_framework/enviroment/cpp_detect.h \
  $$PWD/../../../src/the_framework/enviroment/endianness_detect.h \
  $$PWD/../../../src/the_framework/enviroment/env_detect.h \
  $$PWD/../../../src/the_framework/enviroment/gccversion.h \
  $$PWD/../../../src/the_framework/enviroment/posix_detect.h \
 #$$PWD/../../../src/the_framework/i18n/i18n_strings.h \
  $$PWD/../../../src/the_framework/math/alternate_divide.h \
  $$PWD/../../../src/the_framework/math/bitreverse.h \
  $$PWD/../../../src/the_framework/math/control_pid.h \
  $$PWD/../../../src/the_framework/math/flowpoint_util.h \
  $$PWD/../../../src/the_framework/math/linear_equation.h \
  $$PWD/../../../src/the_framework/math/log2.h \
  $$PWD/../../../src/the_framework/math/math_config.h \
  $$PWD/../../../src/the_framework/math/math_discrete.h \
  $$PWD/../../../src/the_framework/math/ovf_save.h \
  $$PWD/../../../src/the_framework/math/simple_hash_fct.h \
  $$PWD/../../../src/targets/unittest/global_config.h \
  $$PWD/../../../src/the_framework/utility/ansiconsolecolor.h \
  $$PWD/../../../src/the_framework/utility/debug_hlp.h \
  $$PWD/../../../src/the_framework/utility/gendata.h \
  $$PWD/../../../src/the_framework/utility/stopwatch.h \
  $$PWD/../../../src/the_framework/utility/Stringhelper.h \
  $$PWD/../../../src/the_framework/utility/linebuffer.h \
  $$PWD/../../../src/the_framework/utility/utility_fct.h \
  ../../../src/the_framework/core/mutual_lock.h \
  ../../../src/the_framework/core/swtimer.h

INCLUDEPATH += \
  $$PWD/../../../src/the_framework/algorithms \
  $$PWD/../../../src/the_framework/core \
  $$PWD/../../../src/the_framework/dstruct \
  $$PWD/../../../src/the_framework/enviroment \
 #$$PWD/../../../src/the_framework/i18n \
  $$PWD/../../../src/the_framework/math \
  $$PWD/../../../src/targets/unittest \
  $$PWD/../../../src/the_framework/utility \
  $$PWD/../../../external/Catch2/single_include/catch2

DISTFILES += \
  $$PWD/../../../src/the_framework/unittest/testlist.txt \
  ../../../.gitignore

LIBS += -lpthread
