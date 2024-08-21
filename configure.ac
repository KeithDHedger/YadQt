#
#
AC_INIT([YadQt],[0.1.0],[PROJ],[YadQt])

AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX

AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_CXX

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE(qt6,AS_HELP_STRING([--enable-qt6],[Build for Qt6]),
    [enable_qt6=$enableval],
    [enable_qt6="no"])

	if test "$enable_qt6" = "yes"; then
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

