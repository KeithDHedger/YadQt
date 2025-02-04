
#ifndef _GLOBALS_
#define _GLOBALS_

#include <QApplication>
#include <QWidget>
#include <QSettings>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QDebug>
#include <QIcon>
#include <QtWidgets>
#include <QColor>
#include <QSystemTrayIcon>
#include <QProxyStyle>

#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MARGINS 4

#include "config.h"

class DataClass;

#include "LFSTKUtilityClass.h"
#include "prefsClass.h"
#include "DataClass.h"
#include "InfoBoxClass.h"
#include "InputDialogsClass.h"
#include "FormsClass.h"
#include "ListBoxClass.h"
#include "FilesClass.h"
#include "OrphanDialogClass.h"

enum {ABOUT=0,ABOUTQT,QUERY,INFO,WARN,FATAL,GETINPUT,GETITEM,GETFORM,GETLIST,SHOWTEXTFILE,SHOWIMAGEFILE,GETCOLOUR,GETFONT,GETTEXT,TAILBOX,NOTEPAD,RICHTEXT,OPENFILE,SAVEFILE,PREFSDIALOG,TABBEDPREFSDIALOG,TRAYMENU,YADQTHELP};

#endif
