#
#
AC_INIT([YadQt],[1.0.1],[PROJ],[YadQt])

AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX

AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_CXX

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE(qt5,AS_HELP_STRING([--enable-qt5],[Build for Qt5]),
    [enable_qt5=$enableval],
    [enable_qt5="no"])

	if test "$enable_qt5" = "no"; then
		QTWIDGETS_MODULES="Qt6Widgets >= 6.6.0"
		PKG_CHECK_MODULES(QTWIDGETS, $QTWIDGETS_MODULES)
		AC_DEFINE([_USEQT6_], [], [Build Qt6])
		AC_MSG_NOTICE([Using Qt6])
	else
		QTWIDGETS_MODULES="Qt5Widgets >= 5.15.0"
		PKG_CHECK_MODULES(QTWIDGETS, $QTWIDGETS_MODULES)
		AC_MSG_NOTICE([Using Qt5])
	fi

AC_SUBST(QTWIDGETS_CFLAGS)
AC_SUBST(QTWIDGETS_LIBS)

AC_CONFIG_FILES(Makefile YadQt/app/Makefile)
AC_OUTPUT

