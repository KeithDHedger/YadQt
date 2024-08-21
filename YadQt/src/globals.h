
#ifndef _GLOBALS_
#define _GLOBALS_

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QSettings>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QDebug>
#include <QIcon>
#include <QtWidgets>

#include <vector>

#define MARGINS 4

class DataClass;

#include "LFSTKUtilityClass.h"
#include "DataClass.h"
#include "InfoBoxClass.h"
#include "InputDialogsClass.h"
#include "FormsClass.h"
#include "ListBoxClass.h"
#include "FilesClass.h"
#include "OrphanDialogClass.h"

enum {ABOUT=0,ABOUTQT,WHAT,INFO,WARN,FATAL,GETTEXT,GETITEM,GETFORM,GETLIST,SHOWTEXTFILE,SHOWIMAGEFILE,GETCOLOUR};


#endif
