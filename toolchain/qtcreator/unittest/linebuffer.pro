TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG   += -Wall -Wextra -std=c++2a -ffunction-sections
#QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -Ofast -fexpensive-optimizations -mtune=native -march=native -flto -funroll-loops -frename-registers  -Wformat -Wformat-security -fpic -shared -fasynchronous-unwind-tables -D_GLIBCXX_ASSERTIONS -fstack-clash-protection -fstack-protector-all -fcf-protection -pipe -msse3
QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -O3 -mtune=znver2 -march=native

#QMAKE_CXXFLAGS += -pthread

QMAKE_LFLAGS_DEBUG   += -Wl,-z,now -Wl,-z,relro
QMAKE_LFLAGS_RELEASE += -Wl,-z,now -Wl,-z,relro

QMAKE_LFLAGS += -Wl,-Map=signslots.map

SOURCES += \
  $$PWD/../../../src/utility/linebuffer.cpp \
  $$PWD/../../../src/targets/unittest/main.cpp \
  $$PWD/../../../src/unittest/utest_dbllnkdlst.cpp \
  $$PWD/../../../src/unittest/utest_fields.cpp \
  $$PWD/../../../src/unittest/utest_linebuffer.cpp

HEADERS += \
  $$PWD/../../../src/core/compile_guards.h \
  $$PWD/../../../src/core/dtypes.h \
  $$PWD/../../../src/core/iterators.h \
  $$PWD/../../../src/dstruct/dbllnkdlst.h \
  $$PWD/../../../src/dstruct/fields.h \
  $$PWD/../../../src/dstruct/node_definitions.h \
  $$PWD/../../../src/utility/linebuffer.h \
  $$PWD/../../../external/Catch2/single_include/catch2/catch.hpp

INCLUDEPATH += \
  $$PWD/../../../src/core \
  $$PWD/../../../src/dstruct \
  $$PWD/../../../src/utility \
  $$PWD/../../../external/Catch2/single_include/catch2
