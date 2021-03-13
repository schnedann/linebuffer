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
  $$PWD/../../../the_framework/algorithms/countbitsset.cpp \
  $$PWD/../../../the_framework/algorithms/minmax.cpp \
  $$PWD/../../../the_framework/core/error_mgnt.cpp \
  $$PWD/../../../the_framework/enviroment/endianness_detect.cpp \
  $$PWD/../../../the_framework/i18n/i18n_strings.cpp \
  $$PWD/../../../the_framework/math/flowpoint_util.cpp \
  $$PWD/../../../the_framework/math/math_discrete.cpp \
  $$PWD/../../../the_framework/math/ovf_save.cpp \
  $$PWD/../../../the_framework/targets/unittest/main.cpp \
  $$PWD/../../../the_framework/unittest/utest_bitmacros.cpp \
  $$PWD/../../../the_framework/unittest/utest_bitreverse.cpp \
  $$PWD/../../../the_framework/unittest/utest_compiler.cpp \
  $$PWD/../../../the_framework/unittest/utest_dbllnkdlst.cpp \
  $$PWD/../../../the_framework/unittest/utest_fields.cpp \
  $$PWD/../../../the_framework/unittest/utest_helpers.cpp \
  $$PWD/../../../the_framework/unittest/utest_i18n.cpp \
  $$PWD/../../../the_framework/unittest/utest_linebuffer.cpp \
  $$PWD/../../../the_framework/unittest/utest_linear_equation.cpp \
  $$PWD/../../../the_framework/unittest/utest_log_base2.cpp \
  $$PWD/../../../the_framework/unittest/utest_math_discrete.cpp \
  $$PWD/../../../the_framework/unittest/utest_meta.cpp \
  $$PWD/../../../the_framework/utility/Stringhelper.cpp \
  $$PWD/../../../the_framework/utility/linebuffer.cpp \
  $$PWD/../../../the_framework/utility/utility_fkt.cpp

HEADERS += \
  $$PWD/../../../the_framework/algorithms/bitreverse.h \
  $$PWD/../../../the_framework/algorithms/countbitsset.h \
  $$PWD/../../../the_framework/algorithms/log_base2.h \
  $$PWD/../../../the_framework/algorithms/minmax.h \
  $$PWD/../../../the_framework/core/array_fun.h \
  $$PWD/../../../the_framework/core/bitmacros.h \
  $$PWD/../../../the_framework/core/compile_guards.h \
  $$PWD/../../../the_framework/core/dtypes.h \
  $$PWD/../../../the_framework/core/error_mgnt.h \
  $$PWD/../../../the_framework/core/iterators.h \
  $$PWD/../../../the_framework/core/meta.h \
  $$PWD/../../../the_framework/dstruct/dbllnkdlst.h \
  $$PWD/../../../the_framework/dstruct/fields.h \
  $$PWD/../../../the_framework/dstruct/node_definitions.h \
  $$PWD/../../../the_framework/enviroment/cpp_detect.h \
  $$PWD/../../../the_framework/enviroment/endianness_detect.h \
  $$PWD/../../../the_framework/enviroment/env_detect.h \
  $$PWD/../../../the_framework/enviroment/gccversion.h \
  $$PWD/../../../the_framework/enviroment/posix_detect.h \
  $$PWD/../../../the_framework/i18n/i18n_strings.h \
  $$PWD/../../../the_framework/math/bitreverse.h \
  $$PWD/../../../the_framework/math/control_pid.h \
  $$PWD/../../../the_framework/math/flowpoint_util.h \
  $$PWD/../../../the_framework/math/linear_equation.h \
  $$PWD/../../../the_framework/math/math_config.h \
  $$PWD/../../../the_framework/math/math_discrete.h \
  $$PWD/../../../the_framework/math/ovf_save.h \
  $$PWD/../../../the_framework/math/simple_hash_fct.h \
  $$PWD/../../../the_framework/targets/unittest/global_config.h \
  $$PWD/../../../the_framework/utility/Stringhelper.h \
  $$PWD/../../../the_framework/utility/debug_hlp.h \
  $$PWD/../../../the_framework/utility/linebuffer.h \
  $$PWD/../../../the_framework/utility/utility_fkt.h \
  $$PWD/../../../external/Catch2/single_include/catch2/catch.hpp

INCLUDEPATH += \
  $$PWD/../../../the_framework/algorithms \
  $$PWD/../../../the_framework/core \
  $$PWD/../../../the_framework/dstruct \
  $$PWD/../../../the_framework/enviroment \
  $$PWD/../../../the_framework/i18n \
  $$PWD/../../../the_framework/math \
  $$PWD/../../../the_framework/targets/unittest \
  $$PWD/../../../the_framework/utility \
  $$PWD/../../../external/Catch2/single_include/catch2

DISTFILES += \
  $$PWD/../../../the_framework/unittest/testlist.txt
