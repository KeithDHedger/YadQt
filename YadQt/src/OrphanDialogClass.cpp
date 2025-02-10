/*
 *
 * ©K. D. Hedger. Tue 20 Aug 20:21:24 BST 2024 keithdhedger@gmail.com

 * This file (OrphanDialogClass.cpp) is part of YadQt.

 * YadQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * YadQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with YadQt.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "OrphanDialogClass.h"

OrphanDialogClass::OrphanDialogClass(QApplication *app,DataClass *data)
{
	this->data=data;
	this->app=app;
}

OrphanDialogClass::~OrphanDialogClass()
{
}

void OrphanDialogClass::getColour(void)
{
	QColor	initcol(this->data->defaultText);
	QColor	colour;

	if(this->data->defaultText.length()>7)
		colour=QColorDialog::getColor(initcol,nullptr,this->data->title,QColorDialog::ShowAlphaChannel);
	else
		colour=QColorDialog::getColor(initcol,nullptr,this->data->title);

	if(colour.isValid()==true)
		{
			if(this->data->defaultText.length()>7)
				QTextStream(stdout) <<colour.name(QColor::HexArgb)<< Qt::endl;
			else
				QTextStream(stdout) <<colour.name()<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::getFont(void)
{
	bool		ok;
	QFont	tfont;
	QFont	font;

	tfont.fromString(this->data->defaultText);
	font=QFontDialog::getFont(&ok,tfont,nullptr,this->data->title);
	if(ok==true)
		{
			QTextStream(stdout) <<font.toString()<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::tailBox(void)
{
	QPlainTextEdit	*thetext;
	QVBoxLayout		*docvlayout=new QVBoxLayout;
	QString			boxtext="";
	QTextBlock		block;
	QTextCursor		cursor;
	int				available_bytes=-1;
	QTextStream		datastream(stdin);
	QString			datain="";

	this->data->theDialog=new QDialog();
	thetext=new QPlainTextEdit(nullptr);
	thetext->setReadOnly(true);

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);
	docvlayout->addWidget(this->data->bb);
	this->data->theDialog->setLayout(docvlayout);

	this->data->theDialog->setWindowTitle(this->data->title);

	if(this->data->customSize==true)
		this->data->theDialog->resize(this->data->adjustBoxSize(640,480));

	this->data->theDialog->show();
	this->data->retval=-1;

	fcntl(0,F_SETFL,fcntl(0, F_GETFL) | O_NONBLOCK);
	while(this->data->retval<0)
		{
			this->app->processEvents();
			if(this->data->theDialog->isVisible()==false)
				this->data->retval=0;

			usleep(10000);
			ioctl(0,FIONREAD,&available_bytes);
			if(available_bytes>0)
				{
    					datain=datastream.readAll();
    					if(datain.isEmpty()==false)
						{
							boxtext+=QString(datain);
							thetext->setPlainText(boxtext);
							block=thetext->document()->lastBlock();
							cursor=thetext->textCursor();
							cursor.setPosition(block.position());
							thetext->setTextCursor(cursor);
						}    				
				}
		}
}

void OrphanDialogClass::prefsDialog(bool istabbed)
{
	prefsClass	*newprefs=new prefsClass();
	QStringList  prefsdata;;
	QSize		sze;

	prefsdata=this->data->defaultText.split(this->data->ipsep);
	newprefs->paged=istabbed;
	newprefs->opSep=this->data->opsep;
	newprefs->bb->setStandardButtons(this->data->dbutton);

	if(this->data->customSize==true)
		newprefs->createDialog(this->data->title,prefsdata,this->data->adjustBoxSize(-1,-1));
	else
		newprefs->createDialog(this->data->title,prefsdata);

	if(newprefs->dialogPrefs.valid==true)
		{
			for(int j=0;j<newprefs->dialogPrefs.comboBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.comboBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.comboBoxes[j]->currentText()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.editBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.editBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.editBoxes[j]->text()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.checkBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.checkBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.checkBoxes[j]->isChecked()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.colourBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.colourBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.colourBoxes[j]->text()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.fontBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.fontBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.fontBoxes[j]->text()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.fileBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.fileBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.fileBoxes[j]->text()<<"'"<<newprefs->opSep;
			for(int j=0;j<newprefs->dialogPrefs.spinBoxCnt;j++)
				QTextStream(stdout)<<QString(newprefs->dialogPrefs.spinBoxesPrefsName[j]).replace("/","_")<<"='"<<newprefs->dialogPrefs.spinBoxes[j]->text()<<"'"<<newprefs->opSep;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
	delete newprefs;
}

void OrphanDialogClass::openFile(void)
{
	QString filename=QFileDialog::getOpenFileName(nullptr,"Open File",this->data->defaultText);
	if(filename.isEmpty()==false)
		{
			QTextStream(stdout) <<filename<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::saveFile(void)
{
	QString filename=QFileDialog::getSaveFileName(nullptr,"Save File",this->data->defaultText);
	if(filename.isEmpty()==false)
		{
			QTextStream(stdout) <<filename<< Qt::endl;
			this->data->retButton=QMessageBox::Ok;
			this->data->retval=0;
		}
	else
		{
			this->data->retButton=QMessageBox::Cancel;
			this->data->retval=1;
		}
}

void OrphanDialogClass::notePad(void)
{
	QPlainTextEdit	*thetext;
	QVBoxLayout		*docvlayout=new QVBoxLayout;

	this->data->theDialog=new QDialog();
	thetext=new QPlainTextEdit(nullptr);

	QFile file(this->data->defaultText);
	file.open(QFile::ReadOnly | QFile::Text);
	thetext->setPlainText(file.readAll());
	file.close();

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(thetext);

	this->data->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Save|(unsigned int)QDialogButtonBox::Discard);
	this->data->bb->setStandardButtons(this->data->dbutton);
	docvlayout->addWidget(this->data->bb);
	this->data->theDialog->setLayout(docvlayout);

	if(this->data->parser.isSet("title")==false)
		this->data->title=QFileInfo(this->data->defaultText).fileName();

	this->data->theDialog->setWindowTitle(this->data->title);	
	this->data->theDialog->resize(this->data->adjustBoxSize(640,480));

	this->data->theDialog->exec();
	if(this->data->retval==0)
		{
			if(file.open(QIODevice::ReadWrite))
				{
					QTextStream(&file) << thetext->toPlainText() << Qt::endl;
					file.close();
				}
		}
}

void OrphanDialogClass::loadData(QString uri)
{
	QByteArray		qb;
//	QTextCodec		*codec;
	QString			str;
	QMimeDatabase	db1;
	QFile			file(uri);
	QString			realpath=QFileInfo(file).canonicalFilePath();

	if(db1.mimeTypeForFile(realpath).name().compare("text/markdown")==0)
		{
			QUrl baseUrl=QUrl::fromLocalFile(realpath).adjusted(QUrl::RemoveFilename);
			this->baseurl=baseUrl;
			this->thedoc->setSource(QUrl::fromLocalFile(realpath),QTextDocument::MarkdownResource);	
		}
	else if(db1.mimeTypeForFile(realpath).name().compare("text/html")==0)
		{
			QUrl baseUrl=QUrl::fromLocalFile(realpath).adjusted(QUrl::RemoveFilename);
			this->baseurl=baseUrl;
			this->thedoc->document()->setBaseUrl(baseUrl);
			this->thedoc->setSource(QUrl::fromLocalFile(realpath),QTextDocument::HtmlResource);
		}
	else if(db1.mimeTypeForFile(realpath).name().startsWith("image/")==true)
		{
			thedoc->document()->clear();
			QUrl baseUrl=QUrl::fromLocalFile(realpath).adjusted(QUrl::RemoveFilename);
			this->baseurl=baseUrl;
			this->thedoc->document()->setBaseUrl(baseUrl);
			thedoc->append(QString("<img src=\"%1\" />").arg(realpath));
		}
	else
		{
			QFile file(realpath);
			file.open(QFile::ReadOnly | QFile::Text);
			thedoc->document()->setPlainText(file.readAll());
			file.close();;
		}
}

void OrphanDialogClass::richText(void)
{
	QVBoxLayout		*docvlayout=new QVBoxLayout;
	QByteArray		qb;
	QString			str;
	QMimeDatabase	db1;
	QHBoxLayout		*hlayout;
	QWidget			*hbox;

	this->data->theDialog=new QDialog();
	this->thedoc=new QTextBrowser(nullptr);
	
	this->thedoc->setAcceptRichText(true);
	this->thedoc->setOpenExternalLinks(true);
	QObject::connect(thedoc,&QTextBrowser::anchorClicked,[this](const QUrl &link)
		{
			QFile f1(link.toString(QUrl::RemoveScheme));
			if(f1.exists()==true)
				this->loadData(link.toLocalFile());
		});
	this->loadData(this->data->defaultText);

	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(this->thedoc);

	QPushButton *pb=new QPushButton(QIcon::fromTheme("go-previous"),"Back");
	QObject::connect(pb,&QPushButton::clicked,[this]()
		{
			this->thedoc->backward();
		});

	QPushButton *ph=new QPushButton(QIcon::fromTheme("go-home"),"Home");
	QObject::connect(ph,&QPushButton::clicked,[this]()
		{
			this->thedoc->home();
		});

	QPushButton *pf=new QPushButton(QIcon::fromTheme("go-next"),"Forward");
	QObject::connect(pf,&QPushButton::clicked,[this]()
		{
			this->thedoc->forward();
		});
	QPushButton *prf=new QPushButton(QIcon::fromTheme("view-refresh"),"Refresh");
	QObject::connect(prf,&QPushButton::clicked,[this]()
		{
			this->thedoc->reload();
		});

	QPushButton *ok=new QPushButton(QIcon::fromTheme("stock_close"),"OK");
	QObject::connect(ok,&QPushButton::clicked,[this]()
		{
			this->data->theDialog->hide();
			this->data->retval=0;
			this->data->retButton=QMessageBox::Ok;
		});

	hbox=new QWidget;
	hlayout=new QHBoxLayout;
	hlayout->setContentsMargins(0,0,0,0);
	hbox->setLayout(hlayout);
	hlayout->addWidget(ph,0,Qt::AlignLeft);
	hlayout->addWidget(pb,0,Qt::AlignLeft);
	hlayout->addWidget(pf,0,Qt::AlignLeft);
	hlayout->addWidget(prf,0,Qt::AlignLeft);
	hlayout->addWidget(ok,1,Qt::AlignRight);
	docvlayout->addWidget(hbox);

	this->data->theDialog->setLayout(docvlayout);

	if(this->data->parser.isSet("title")==false)
		this->data->title=QFileInfo(this->data->defaultText).fileName();

	this->data->theDialog->setWindowTitle(this->data->title);
	this->data->theDialog->resize(this->data->adjustBoxSize(640,480));

	this->data->theDialog->show();
	this->data->retval=-1;

	while(this->data->retval!=0)
		{
			this->app->processEvents();
			if(this->data->theDialog->isVisible()==false)
				this->data->retval=0;
			pb->setEnabled(this->thedoc->isBackwardAvailable());
			pf->setEnabled(this->thedoc->isForwardAvailable());
		}
}

void OrphanDialogClass::trayMenu(void)
{
	QStringList		items;
    QSystemTrayIcon	*trayIcon=new QSystemTrayIcon(nullptr);
    QMenu			*trayIconContextMenu=new QMenu(nullptr);
	QAction			*anAction;
    QAction			*quitAction;
    QAction			*restartAction;
	bool				flag=false;

	ProxyStyle *mainThemeProxy=new ProxyStyle();
	mainThemeProxy->setParent(this->app);
	this->app->setStyle(mainThemeProxy);

	trayIcon->setToolTip(data->title);

	if((this->data->dataFromStdIn==false) && (QFile::exists(this->data->defaultText)))
		{
			QFile file(this->data->defaultText);
			file.open(QFile::ReadOnly | QFile::Text);
			this->data->defaultText=file.readAll().trimmed();
			file.close();
			flag=true;
		}

	items=this->data->defaultText.split(this->data->ipsep,Qt::KeepEmptyParts,Qt::CaseInsensitive);
	if((items.count() % 3) !=0)//TODO//
		{
			qDebug()<<"Wrong number of arguments, MUST be NAME|ICON|PATH/TO/EXECUTABLE. exiting ...";
			this->data->retval=1;
			return;
		}

	for(int j=0;j<items.count();j+=3)
		{
			anAction=new QAction(QIcon::fromTheme(items.at(j+1).trimmed()),items.at(j),nullptr);
			anAction->setData(items.at(j+2));
			QObject::connect(anAction, &QAction::triggered,[=] ()
				{
					if(anAction->data().toString().length()==0)
						{
							qDebug()<<"No executable supplied ...";
							return;
						}
					QStringList	comargs=QProcess::splitCommand(anAction->data().toString());
					QString		prog=comargs.at(0);
					if(this->data->timeOut!=0)
						trayIcon->showMessage(anAction->text(),QString("Launching %1 ...").arg(prog),anAction->icon(),this->data->timeOut);
					comargs.removeFirst();
					QProcess::startDetached(prog,comargs);
				});
			trayIconContextMenu->addAction(anAction);
		}

	trayIconContextMenu->addSeparator();

	if((flag==true) && (this->data->allowRestart==true))
		{
		    restartAction=new QAction("Restart",nullptr);
			QObject::connect(restartAction, &QAction::triggered,[=] ()
				{
					QStringList	comargs=this->app->arguments();
					QString		prog=comargs.at(0);
					comargs.removeFirst();
					this->app->quit();
					QProcess::startDetached(prog,comargs);
				});
			trayIconContextMenu->addAction(restartAction);
		}

    quitAction=new QAction("Quit",nullptr);
    QObject::connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
	trayIconContextMenu->addAction(quitAction);

	trayIcon->setContextMenu(trayIconContextMenu);
	trayIcon->setIcon(QIcon::fromTheme(this->data->theIcon));	

	if(this->data->body.compare(PACKAGE_NAME)!=0)
		{
			QObject::connect(trayIcon, &QSystemTrayIcon::activated,[=] (QSystemTrayIcon::ActivationReason reason)
				{
					if(reason==QSystemTrayIcon::Trigger)
						{
							int tout=this->data->timeOut;
							if(tout==0)
								tout=1500;
							trayIcon->showMessage(this->data->title,this->data->body,QIcon::fromTheme(this->data->theIcon),tout);
						}
				});
		}

    trayIcon->show();
	this->app->exec();

	delete trayIcon;
	delete trayIconContextMenu;
}

void OrphanDialogClass::yadQtHelp(void)
{
	this->data->title="Yad~Qt Help";
	this->data->width=830;
	this->data->height=640;
	this->data->defaultText=DATADIR "/help/yadqt.html";
	this->richText();
}

