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
  $$PWD/../../../src/the_framework/algorithms/crc/crc_calc.cpp \
  $$PWD/../../../src/the_framework/math/math_discrete.cpp \
  $$PWD/../../../src/targets/gen_hdl_crc/main.cpp \
  $$PWD/../../../src/targets/gen_hdl_crc/hdlgenerate.cpp \
  $$PWD/../../../src/the_framework/utility/gendata.cpp \
  $$PWD/../../../src/the_framework/utility/Stringhelper.cpp \
  $$PWD/../../../src/the_framework/utility/utility_fct.cpp

HEADERS += \
  $$PWD/../../../src/targets/gen_hdl_crc/global_config.h \
  $$PWD/../../../src/targets/gen_hdl_crc/hdlgenerate.h \
  $$PWD/../../../src/the_framework/algorithms/bitreverse.h \
  $$PWD/../../../src/the_framework/algorithms/crc/crc_calc.h \
  $$PWD/../../../src/the_framework/core/bitmacros.h \
  $$PWD/../../../src/the_framework/core/compile_guards.h \
  $$PWD/../../../src/the_framework/core/dtypes.h \
  $$PWD/../../../src/the_framework/core/paramodifiers.h \
  $$PWD/../../../src/the_framework/math/math_discrete.h \
  $$PWD/../../../src/the_framework/utility/debug_hlp.h \
  $$PWD/../../../src/the_framework/utility/gendata.h \
  $$PWD/../../../src/the_framework/utility/Stringhelper.h \
  $$PWD/../../../src/the_framework/utility/utility_fct.h

INCLUDEPATH += \
  $$PWD/../../../src/targets/gen_hdl_crc \
  $$PWD/../../../src/the_framework/algorithms \
  $$PWD/../../../src/the_framework/algorithms/crc \
  $$PWD/../../../src/the_framework/core \
  $$PWD/../../../src/the_framework/math \
  $$PWD/../../../src/the_framework/utility

LIBS += -lpthread
