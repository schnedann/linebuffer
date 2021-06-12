TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS_DEBUG   += -Wall -Wextra
QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -std=c++17 -O0

QMAKE_CFLAGS_RELEASE   += -Wall -Wextra
QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -Ofast -fexpensive-optimizations -mtune=native -march=native -flto -funroll-loops -frename-registers -fvisibility=hidden -fvisibility-inlines-hidden

SOURCES += \
        $$PWD/../../../src/targets/fat32ctrl/main.cpp \
        $$PWD/../../../src/the_framework/fileio/file_fkt.cpp \
        $$PWD/../../../src/the_framework/core/error_mgnt.cpp \
        $$PWD/../../../src/the_framework/enviroment/endianness_detect.cpp \
        $$PWD/../../../src/the_framework/utility/Stringhelper.cpp \
        $$PWD/../../../src/the_framework/utility/utility_fct.cpp \
        $$PWD/../../../src/the_framework/math/math_discrete.cpp
        #$$PWD/../../../src/the_framework/math/ovf_save.cpp

HEADERS += \
  $$PWD/../../../src/the_framework/core/bitmacros.h \
  $$PWD/../../../src/the_framework/core/compile_guards.h \
  $$PWD/../../../src/the_framework/core/dtypes.h \
  $$PWD/../../../src/the_framework/core/meta.h \
  $$PWD/../../../src/the_framework/fileio/file_fkt.h \
  $$PWD/../../../src/the_framework/core/error_mgnt.h \
  $$PWD/../../../src/the_framework/core/iterators.h \
  $$PWD/../../../src/the_framework/enviroment/posix_detect.h \
  $$PWD/../../../src/the_framework/enviroment/cpp_detect.h \
  $$PWD/../../../src/the_framework/enviroment/endianness_detect.h \
  $$PWD/../../../src/the_framework/enviroment/env_detect.h \
  $$PWD/../../../src/the_framework/enviroment/gccversion.h \
  $$PWD/../../../src/the_framework/utility/Stringhelper.h \
  $$PWD/../../../src/the_framework/utility/debug_hlp.h \
  $$PWD/../../../src/the_framework/utility/utility_fct.h \
  $$PWD/../../../src/the_framework/math/math_discrete.h \
  $$PWD/../../../src/the_framework/math/ovf_save.h \
  $$PWD/../../../src/targets/fat32ctrl/global_config.h \
  $$PWD/../../../src/the_framework/algorithms/bitreverse.h \
  $$PWD/../../../src/the_framework/dstruct/fields.h

INCLUDEPATH += $$PWD/../../../src/the_framework/algorithms
INCLUDEPATH += $$PWD/../../../src/the_framework/core
INCLUDEPATH += $$PWD/../../../src/the_framework/dstruct
INCLUDEPATH += $$PWD/../../../src/the_framework/enviroment
INCLUDEPATH += $$PWD/../../../src/the_framework/fileio
INCLUDEPATH += $$PWD/../../../src/the_framework/math
INCLUDEPATH += $$PWD/../../../src/targets/fat32ctrl
INCLUDEPATH += $$PWD/../../../src/the_framework/utility

LIBS += -lpthread
