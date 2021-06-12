TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG   += -Wall -Wextra -std=c++20
#QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -Ofast -fexpensive-optimizations -mtune=native -march=native -flto -funroll-loops -frename-registers  -Wformat -Wformat-security -fpic -shared -fasynchronous-unwind-tables -D_GLIBCXX_ASSERTIONS -fstack-clash-protection -fstack-protector-all -fcf-protection -pipe -msse3
QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++20 -O3 -mtune=znver2 -march=native

QMAKE_LFLAGS_DEBUG   += -Wl,-z,now -Wl,-z,relro
QMAKE_LFLAGS_RELEASE += -Wl,-z,now -Wl,-z,relro

QMAKE_LFLAGS += -Wl,-Map=CountbitSet.map

SOURCES += \
    $$PWD/../../../src/targets/filetwiddeling/main.cpp \
    $$PWD/../../../src/the_framework/fileio/file_fkt.cpp \
    $$PWD/../../../src/the_framework/core/error_mgnt.cpp \
    $$PWD/../../../src/the_framework/enviroment/endianness_detect.cpp \
    $$PWD/../../../src/the_framework/utility/Stringhelper.cpp \
    $$PWD/../../../src/the_framework/math/math_discrete.cpp

HEADERS += \
    $$PWD/../../../src/the_framework/core/dtypes.h \
    $$PWD/../../../src/the_framework/core/error_mgnt.h \
    $$PWD/../../../src/the_framework/core/iterators.h \
    $$PWD/../../../src/the_framework/dstruct/fields.h \
    $$PWD/../../../src/the_framework/enviroment/posix_detect.h \
    $$PWD/../../../src/the_framework/enviroment/cpp_detect.h \
    $$PWD/../../../src/the_framework/enviroment/endianness_detect.h \
    $$PWD/../../../src/the_framework/enviroment/env_detect.h \
    $$PWD/../../../src/the_framework/enviroment/gccversion.h \
    $$PWD/../../../src/the_framework/fileio/file_fkt.h \
    $$PWD/../../../src/the_framework/math/math_discrete.h \
    $$PWD/../../../src/the_framework/utility/ansiconsolecolor.h \
    $$PWD/../../../src/the_framework/utility/debug_hlp.h \
    $$PWD/../../../src/the_framework/utility/Stringhelper.h \
    $$PWD/../../../src/targets/filetwiddeling/global_config.h

INCLUDEPATH += \
    $$PWD/../../../src/the_framework/core \
    $$PWD/../../../src/the_framework/dstruct \
    $$PWD/../../../src/the_framework/enviroment \
    $$PWD/../../../src/the_framework/fileio \
    $$PWD/../../../src/the_framework/math \
    $$PWD/../../../src/the_framework/utility \
    $$PWD/../../../src/targets/filetwiddeling

