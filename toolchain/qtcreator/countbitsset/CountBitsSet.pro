TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG   += -Wall -Wextra -std=c++17
#QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -Ofast -fexpensive-optimizations -mtune=native -march=native -flto -funroll-loops -frename-registers  -Wformat -Wformat-security -fpic -shared -fasynchronous-unwind-tables -D_GLIBCXX_ASSERTIONS -fstack-clash-protection -fstack-protector-all -fcf-protection -pipe -msse3
QMAKE_CXXFLAGS_RELEASE += -Wall -Wextra -std=c++17 -O3 -mtune=znver2 -march=native

QMAKE_LFLAGS_DEBUG   += -Wl,-z,now -Wl,-z,relro
QMAKE_LFLAGS_RELEASE += -Wl,-z,now -Wl,-z,relro

QMAKE_LFLAGS += -Wl,-Map=CountbitSet.map

SOURCES += \
    $$PWD/../../../src/targets/countbitsset/main.cpp \
    $$PWD/../../../src/the_framework/algorithms/countbitsset.cpp \
    $$PWD/../../../src/the_framework/utility/Stringhelper.cpp

HEADERS += \
    $$PWD/../../../src/targets/countbitsset/global_config.h \
    $$PWD/../../../src/the_framework/algorithms/countbitsset.h \
    $$PWD/../../../src/the_framework/algorithms/minmax.h \
    $$PWD/../../../src/the_framework/core/compile_guards.h \
    $$PWD/../../../src/the_framework/core/dtypes.h \
    $$PWD/../../../src/the_framework/core/bitmacros.h \
    $$PWD/../../../src/the_framework/core/compile_guards.h \
    $$PWD/../../../src/the_framework/core/linear_equation.h \
    $$PWD/../../../src/the_framework/enviroment/gccversion.h \
    $$PWD/../../../src/the_framework/math/bitreverse.h \
    $$PWD/../../../src/the_framework/utility/Stringhelper.h \
    $$PWD/../../../external/GSL/include/gsl/gsl \
    $$PWD/../../../external/GSL/include/gsl/gsl_algorithm \
    $$PWD/../../../external/GSL/include/gsl/gsl_assert \
    $$PWD/../../../external/GSL/include/gsl/gsl_byte \
    $$PWD/../../../external/GSL/include/gsl/gsl_util \
    $$PWD/../../../external/GSL/include/gsl/multi_span \
    $$PWD/../../../external/GSL/include/gsl/pointers \
    $$PWD/../../../external/GSL/include/gsl/span \
    $$PWD/../../../external/GSL/include/gsl/span_ext \
    $$PWD/../../../external/GSL/include/gsl/string_span


INCLUDEPATH += \
    $$PWD/../../../src/the_framework/algorithms \
    $$PWD/../../../src/the_framework/core \
    $$PWD/../../../src/the_framework/enviroment \
    $$PWD/../../../src/the_framework/math \
    $$PWD/../../../src/the_framework/utility \
    $$PWD/../../../src/targets/countbitsset \
    $$PWD/../../../external/GSL/include \
    $$PWD/../../../external/GSL/include/gsl

OTHER_FILES += \
    $$PWD/../../../doc/countbitsset/results.txt
