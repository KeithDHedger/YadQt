/*
 *
 * ©K. D. Hedger. Fri  1 Nov 13:52:11 GMT 2024 keithdhedger@gmail.com

 * This file (this->dialogPrefsClass.cpp) is part of Classes-DEV.

 * Classes-DEV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Classes-DEV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Classes-DEV.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "prefsClass.h"

/**
* this->dialogPrefsClass class destroy.
*/
prefsClass::~prefsClass()
{
	for(int j=0;j<this->dialogPrefs.comboBoxCnt;j++)
		delete this->dialogPrefs.comboBoxes[j];
				
	for(int j=0;j<this->dialogPrefs.editBoxCnt;j++)
		delete this->dialogPrefs.editBoxes[j];

	for(int j=0;j<this->dialogPrefs.checkBoxCnt;j++)
		delete this->dialogPrefs.checkBoxes[j];

	for(int j=0;j<this->dialogPrefs.colourBoxCnt;j++)
		delete this->dialogPrefs.colourBoxes[j];

	for(int j=0;j<this->dialogPrefs.fontBoxCnt;j++)
		delete this->dialogPrefs.fontBoxes[j];

	for(int j=0;j<this->dialogPrefs.fileBoxCnt;j++)
		delete this->dialogPrefs.fileBoxes[j];

	delete this->dialogPrefs.theDialog;
}

/**
* this->dialogPrefsClass.
*/
prefsClass::prefsClass()
{
	this->bb=new QDialogButtonBox(QDialogButtonBox::NoButton);
}

QString prefsClass::bestFontColour(QString colour)
{
	QColor	cc(colour);
    int		r=0,g=0,b=0;

	r=cc.red();
	g=cc.green();
	b=cc.blue();

	if((r+r+r+b+g+g+g+g)>>3>128)
		return("black");
	else
		return("white");
}

unsigned long prefsClass::hashFromKey(QString key)
{
	unsigned long hash=0;

	for(int i=0;i<key.length();i++)
		hash=31*hash+key.at(i).toLatin1();

	return(hash);
}

void prefsClass::setPrefValue(QString name,QVariant val)
{
	this->prefsData[this->hashFromKey(name)]=val;
}

QVariant prefsClass::getPrefValue(QString name)
{
	return(this->prefsData.value(this->hashFromKey(name)));
}

void prefsClass::writePrefs(void)
{
	QSettings	defaults;

	for(int j=0;j<this->prefsData.size();j++)
		{
			defaults.setValue(this->prefsNames.at(j),this->prefsData.value(this->hashFromKey(this->prefsNames.at(j))));
		}
}

void prefsClass::readPrefs(void)
{
	QSettings	defaults;

	for(int j=0;j<this->prefsData.size();j++)
		{
			this->prefsData[this->hashFromKey(this->prefsNames.at(j))]=defaults.value(this->prefsNames.at(j),this->prefsData.value(this->hashFromKey(this->prefsNames.at(j))));
		}
}

void prefsClass::setPrefs(QStringList items)
{
	int			j=0;
	QSettings	defaults;

	this->prefsNames=items;
	this->prefsData.clear();

	while(j<items.size())
		{
			this->prefsData[this->hashFromKey(items.at(j))]=QVariant(0);
			j++;
		}
}

void prefsClass::printCurrentPrefs()
{
	if(this->dialogPrefs.valid==true)
		{
			QSettings	prefs;
			QString		opsep=this->opSep;

			for(int j=0;j<this->dialogPrefs.comboBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.comboBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.comboBoxes[j]->currentText()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.comboBoxesPrefsName[j],this->dialogPrefs.comboBoxes[j]->currentText());
				}
			for(int j=0;j<this->dialogPrefs.editBoxCnt;j++)
				{
					prefs.setValue(this->dialogPrefs.editBoxesPrefsName[j],this->dialogPrefs.editBoxes[j]->text());
					QTextStream(stdout)<<QString(this->dialogPrefs.editBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.editBoxes[j]->text()<<"'"<<opsep;
				}
			for(int j=0;j<this->dialogPrefs.checkBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.checkBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.checkBoxes[j]->isChecked()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.checkBoxesPrefsName[j],this->dialogPrefs.checkBoxes[j]->isChecked());
				}
			for(int j=0;j<this->dialogPrefs.colourBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.colourBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.colourBoxes[j]->text()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.colourBoxesPrefsName[j],this->dialogPrefs.colourBoxes[j]->text());
				}
			for(int j=0;j<this->dialogPrefs.fontBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.fontBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.fontBoxes[j]->text()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.fontBoxesPrefsName[j],this->dialogPrefs.fontBoxes[j]->text());
				}
			for(int j=0;j<this->dialogPrefs.fileBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.fileBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.fileBoxes[j]->text()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.fileBoxesPrefsName[j],this->dialogPrefs.fileBoxes[j]->text());
				}
			for(int j=0;j<this->dialogPrefs.spinBoxCnt;j++)
				{
					QTextStream(stdout)<<QString(this->dialogPrefs.spinBoxesPrefsName[j]).replace("/","_")<<"='"<<this->dialogPrefs.spinBoxes[j]->text()<<"'"<<opsep;
					prefs.setValue(this->dialogPrefs.spinBoxesPrefsName[j],this->dialogPrefs.spinBoxes[j]->text());
				}
		}
}

void prefsClass::createDialog(QString title,QStringList items,QSize sze)
{
	QWidget					*hbox=NULL;
	QVBoxLayout				*docvlayout=NULL;
	QVBoxLayout				*mainvlayout=new QVBoxLayout;
	QHBoxLayout				*hlayout=NULL;
	QString					prefsentry;
	QSettings				defaults;
	int						j=0;
	QString					labelstr;
	QFrame					f;
	QTabWidget				*tabbar=NULL;

	f.setFrameStyle(QFrame::HLine|QFrame::Plain);
	this->dialogPrefs.theDialog=new QDialog();
	this->dialogPrefs.theDialog->setWindowTitle(title);
	this->dialogPrefs.theDialog->setGeometry(defaults.value(QString("%1_%2").arg(qApp->applicationName()).arg("prefsgeometry"),QRect(100,100,320,128)).toRect());

	QSize tsze(this->dialogPrefs.theDialog->size());
	if(sze.width()!=-1)
		tsze.setWidth(sze.width());
	if(sze.height()!=-1)
		tsze.setHeight(sze.height());

	this->dialogPrefs.theDialog->resize(tsze);

	if(this->paged==true)
		{
			tabbar=new QTabWidget(nullptr);
			
			mainvlayout->setContentsMargins(0,0,0,0);
			mainvlayout->addWidget(tabbar);
			this->dialogPrefs.theDialog->setLayout(mainvlayout);
	}
	else
		{
			docvlayout=new QVBoxLayout;
			this->dialogPrefs.theDialog->setLayout(mainvlayout);
			mainvlayout->addLayout(docvlayout);
		}

	j=0;
	while(j<items.size())
		{
			//new page
			if((this->paged==true) && (items.at(j).compare("page")==0))
				{
					QWidget	*vbox;
					hbox=new QWidget;
					if(docvlayout!=NULL)
						docvlayout->addWidget(hbox,1);
					docvlayout=new QVBoxLayout;
					j++;
					labelstr=items.at(j).trimmed();
					vbox=new QWidget;
					vbox->setLayout(docvlayout);
					tabbar->addTab(vbox,QIcon(""),labelstr);
				}

			//edits
			if(items.at(j).compare("edit")==0)
				{
					hbox=new QWidget;
					hlayout=new QHBoxLayout;
					hlayout->setContentsMargins(0,0,0,0);
					hbox->setLayout(hlayout);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					hlayout->addWidget(new QLabel(labelstr),1);
					prefsentry.replace(" ","_");
					this->dialogPrefs.editBoxesPrefsName[this->dialogPrefs.editBoxCnt]=prefsentry.toLower();
					j++;
					this->dialogPrefs.editBoxes[this->dialogPrefs.editBoxCnt]=new QLineEdit(defaults.value(this->dialogPrefs.editBoxesPrefsName[this->dialogPrefs.editBoxCnt],items.at(j)).toString());
					hlayout->addWidget(this->dialogPrefs.editBoxes[this->dialogPrefs.editBoxCnt],RITESTRETCH);
					docvlayout->addWidget(hbox,0);
					this->dialogPrefs.editBoxes[this->dialogPrefs.editBoxCnt]->setCursorPosition(0);
					this->dialogPrefs.editBoxCnt++;
				}

			//spin boxes
			if(items.at(j).compare("spinner")==0)
				{
					hbox=new QWidget;
					hlayout=new QHBoxLayout;
					hlayout->setContentsMargins(0,0,0,0);
					hbox->setLayout(hlayout);
					j++;
					labelstr=items.at(j);
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]=new QDoubleSpinBox();
					prefsentry.replace(" ","_");
					this->dialogPrefs.spinBoxesPrefsName[this->dialogPrefs.spinBoxCnt]=prefsentry.toLower();
					j++;
					this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setMinimum(items.at(j++).toDouble());
					this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setMaximum(items.at(j++).toDouble());
					this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setValue(defaults.value(this->dialogPrefs.spinBoxesPrefsName[this->dialogPrefs.spinBoxCnt],items.at(j++)).toDouble());	
					this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setSingleStep(items.at(j).toDouble());
					if(items.at(j).lastIndexOf('.')!=-1)
						this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setDecimals(items.at(j).length()-items.at(j).lastIndexOf('.')-1);
					else
						this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt]->setDecimals(0);

					hlayout->addWidget(this->dialogPrefs.spinBoxes[this->dialogPrefs.spinBoxCnt],RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.spinBoxCnt++;
				}

			//combo
			if(items.at(j).compare("combostart")==0)
				{
					hbox=new QWidget;
					hlayout=new QHBoxLayout;
					hlayout->setContentsMargins(0,0,0,0);
					hbox->setLayout(hlayout);
					j++;
					labelstr=items.at(j);
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.comboBoxes[this->dialogPrefs.comboBoxCnt]=new QComboBox();
					prefsentry.replace(" ","_");
					this->dialogPrefs.comboBoxesPrefsName[this->dialogPrefs.comboBoxCnt]=prefsentry.toLower();
					j++;
					QString defstr=items.at(j).trimmed();
					j++;
					while(items.at(j).compare("comboend")!=0)
						{
							this->dialogPrefs.comboBoxes[this->dialogPrefs.comboBoxCnt]->addItem(items.at(j));
							j++;
						}
					this->dialogPrefs.comboBoxes[this->dialogPrefs.comboBoxCnt]->setCurrentText(defstr);
					this->dialogPrefs.comboBoxes[this->dialogPrefs.comboBoxCnt]->setCurrentText(defaults.value(this->dialogPrefs.comboBoxesPrefsName[this->dialogPrefs.comboBoxCnt],items.at(j)).toString());
					hlayout->addWidget(this->dialogPrefs.comboBoxes[this->dialogPrefs.comboBoxCnt],RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.comboBoxCnt++;
				}

			//checkboxes
			if(items.at(j).compare("check")==0)
				{
					hbox=new QWidget;
					hlayout=new QHBoxLayout;
					hlayout->setContentsMargins(0,0,0,0);
					hbox->setLayout(hlayout);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					prefsentry.replace(" ","_");
					this->dialogPrefs.checkBoxesPrefsName[this->dialogPrefs.checkBoxCnt]=prefsentry.toLower();
					this->dialogPrefs.checkBoxes[this->dialogPrefs.checkBoxCnt]=new QCheckBox(labelstr);
					j++;
					this->dialogPrefs.checkBoxes[this->dialogPrefs.checkBoxCnt]->setChecked(defaults.value(this->dialogPrefs.checkBoxesPrefsName[this->dialogPrefs.checkBoxCnt],items.at(j)).toBool());
					hlayout->addWidget(this->dialogPrefs.checkBoxes[this->dialogPrefs.checkBoxCnt],1);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.checkBoxCnt++;
				}

			//colours
			if(items.at(j).compare("colour")==0)
				{
					hbox=new QWidget;
					QWidget *hbox2=new QWidget;
					hlayout=new QHBoxLayout;
					QHBoxLayout *hlayout2=new QHBoxLayout;
					QPushButton *pb=NULL;
					hlayout->setContentsMargins(0,0,0,0);
					hlayout->setSpacing(0);
					hlayout2->setContentsMargins(3,0,0,0);
					hlayout2->setSpacing(0);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					prefsentry.replace(" ","_");
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.colourBoxesPrefsName[this->dialogPrefs.colourBoxCnt]=prefsentry.toLower();
					j++;
					pb=new QPushButton(QIcon::fromTheme("preferences-desktop-theme"),"");
					pb->setMaximumWidth(24);
					hlayout2->addWidget(pb,1);
					this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]=new QLineEdit(defaults.value(this->dialogPrefs.colourBoxesPrefsName[this->dialogPrefs.colourBoxCnt],items.at(j)).toString());	
					this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]->setStyleSheet(QString("background: %1;\ncolor: %2;").arg(this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]->text()).arg(this->bestFontColour(this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]->text())));
					this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]->update();
					QObject::connect(pb,&QPushButton::clicked,[this,pb,cbnum=this->dialogPrefs.colourBoxCnt]()
						{
							QColor colour;
							
							colour=QColorDialog::getColor(this->dialogPrefs.colourBoxes[cbnum]->text(),nullptr,"Select Colour",QColorDialog::ShowAlphaChannel);
							if(colour.isValid()==true)
								{
									QString s;
									s=QString("background: %1;\ncolor: %2;").arg(colour.name(QColor::HexArgb)).arg(this->bestFontColour(colour.name(QColor::HexArgb)));
									this->dialogPrefs.colourBoxes[cbnum]->setStyleSheet(s);//ding ding ding
									this->dialogPrefs.colourBoxes[cbnum]->update();
									this->dialogPrefs.colourBoxes[cbnum]->setText(colour.name(QColor::HexArgb));
									this->dialogPrefs.colourBoxes[cbnum]->setCursorPosition(0);
								}
						});
					hlayout2->addWidget(this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt],2);
					hbox2->setLayout(hlayout2);
					hbox->setLayout(hlayout);
					hlayout->addWidget(hbox2,RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.colourBoxes[this->dialogPrefs.colourBoxCnt]->setCursorPosition(0);
					this->dialogPrefs.colourBoxCnt++;
				}

			//font
			if(items.at(j).compare("font")==0)
				{
					QWidget		*hbox2=new QWidget;
					QHBoxLayout	*hlayout2=new QHBoxLayout;
					QPushButton	*pb=NULL;
					QFont		font;

					hlayout=new QHBoxLayout;
					hbox=new QWidget;
					hlayout->setContentsMargins(0,0,0,0);
					hlayout->setSpacing(0);
					hlayout2->setContentsMargins(3,0,0,0);
					hlayout2->setSpacing(0);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					prefsentry.replace(" ","_");
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.fontBoxesPrefsName[this->dialogPrefs.fontBoxCnt]=prefsentry.toLower();
					j++;
					pb=new QPushButton(QIcon::fromTheme("preferences-desktop-font"),"");
					pb->setMaximumWidth(24);
					hlayout2->addWidget(pb,1);
					this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt]=new QLineEdit(defaults.value(this->dialogPrefs.fontBoxesPrefsName[this->dialogPrefs.fontBoxCnt],items.at(j)).toString());	
					font.fromString(this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt]->text());
					this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt]->setFont(font);
					this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt]->update();
					QObject::connect(pb,&QPushButton::clicked,[this,pb,fbnum=this->dialogPrefs.fontBoxCnt]()
						{
							bool		ok=false;
							QFont	tfont;
							QFont	font;

							tfont.fromString(this->dialogPrefs.fontBoxes[fbnum]->text());
							font=QFontDialog::getFont(&ok,tfont,nullptr,"Seleect Font");
							if(ok==true)
								{
									this->dialogPrefs.fontBoxes[fbnum]->setText(font.toString());
									this->dialogPrefs.fontBoxes[fbnum]->setCursorPosition(0);
									this->dialogPrefs.fontBoxes[fbnum]->setFont(font);
									this->dialogPrefs.fontBoxes[fbnum]->update();
								}
						});
					hlayout2->addWidget(this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt],2);
					hbox2->setLayout(hlayout2);
					hbox->setLayout(hlayout);
					hlayout->addWidget(hbox2,RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.fontBoxes[this->dialogPrefs.fontBoxCnt]->setCursorPosition(0);
					this->dialogPrefs.fontBoxCnt++;
				}

			//files
			if(items.at(j).compare("file")==0)
				{
					QWidget		*hbox2=new QWidget;
					QHBoxLayout	*hlayout2=new QHBoxLayout;
					QPushButton	*pb=NULL;

					hlayout=new QHBoxLayout;
					hbox=new QWidget;
					hlayout->setContentsMargins(0,0,0,0);
					hlayout->setSpacing(0);
					hlayout2->setContentsMargins(3,0,0,0);
					hlayout2->setSpacing(0);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					prefsentry.replace(" ","_");
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.fileBoxesPrefsName[this->dialogPrefs.fileBoxCnt]=prefsentry.toLower();
					j++;
					pb=new QPushButton(QIcon::fromTheme("text-x-generic"),"");
					pb->setMaximumWidth(24);
					hlayout2->addWidget(pb,1);
					this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt]=new QLineEdit(defaults.value(this->dialogPrefs.fileBoxesPrefsName[this->dialogPrefs.fileBoxCnt],items.at(j)).toString());	
					QObject::connect(pb,&QPushButton::clicked,[this,pb,filenum=this->dialogPrefs.fileBoxCnt]()
						{
							QString filename=QFileDialog::getOpenFileName(nullptr,"Select File",this->dialogPrefs.fileBoxes[filenum]->text());
							if(filename.isEmpty()==false)
								{
									this->dialogPrefs.fileBoxes[filenum]->setText(filename);
									this->dialogPrefs.fileBoxes[filenum]->setCursorPosition(0);
								}
						});
					hlayout2->addWidget(this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt],2);
					hbox2->setLayout(hlayout2);
					hbox->setLayout(hlayout);
					hlayout->addWidget(hbox2,RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt]->setCursorPosition(0);
					this->dialogPrefs.fileBoxCnt++;
				}

			//folders
			if(items.at(j).compare("folder")==0)
				{
					QWidget		*hbox2=new QWidget;
					QHBoxLayout	*hlayout2=new QHBoxLayout;
					QPushButton	*pb=NULL;

					hlayout=new QHBoxLayout;
					hbox=new QWidget;
					hlayout->setContentsMargins(0,0,0,0);
					hlayout->setSpacing(0);
					hlayout2->setContentsMargins(3,0,0,0);
					hlayout2->setSpacing(0);
					j++;
					labelstr=items.at(j).trimmed();
					prefsentry=labelstr;
					labelstr=labelstr.mid(labelstr.lastIndexOf("/")+1,-1);
					prefsentry.replace(" ","_");
					hlayout->addWidget(new QLabel(labelstr),1);
					this->dialogPrefs.fileBoxesPrefsName[this->dialogPrefs.fileBoxCnt]=prefsentry.toLower();
					j++;
					pb=new QPushButton(QIcon::fromTheme("folder"),"");

					pb->setMaximumWidth(24);
					hlayout2->addWidget(pb,1);
					this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt]=new QLineEdit(defaults.value(this->dialogPrefs.fileBoxesPrefsName[this->dialogPrefs.fileBoxCnt],items.at(j)).toString());	
					QObject::connect(pb,&QPushButton::clicked,[this,pb,foldnum=this->dialogPrefs.fileBoxCnt]()
						{
							QString foldername=QFileDialog::getExistingDirectory(nullptr,"Select Folder",this->dialogPrefs.fileBoxes[foldnum]->text(),QFileDialog::ShowDirsOnly);
							if(foldername.isEmpty()==false)
								{
									this->dialogPrefs.fileBoxes[foldnum]->setText(foldername);
									this->dialogPrefs.fileBoxes[foldnum]->setCursorPosition(0);
								}
						});
					hlayout2->addWidget(this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt],2);
					hbox2->setLayout(hlayout2);
					hbox->setLayout(hlayout);
					hlayout->addWidget(hbox2,RITESTRETCH);
					docvlayout->addWidget(hbox);
					this->dialogPrefs.fileBoxes[this->dialogPrefs.fileBoxCnt]->setCursorPosition(0);
					this->dialogPrefs.fileBoxCnt++;
				}
			j++;
		}

	if(this->paged==true)
		{
			hbox=new QWidget;
			docvlayout->addWidget(hbox,1);
		}

	//QDialogButtonBox bb(QDialogButtonBox::Ok|QDialogButtonBox::Apply|QDialogButtonBox::Cancel);
	//QDialogButtonBox bb();
	QObject::connect(this->bb,&QDialogButtonBox::clicked,[this](QAbstractButton *button)
		{
		qDebug()<<">>>>>>>";
			switch(this->bb->standardButton(button))
				{
					case QDialogButtonBox::Ok:
						{
							QSettings	defaults;
							QRect		rf,rg;

							rg=this->dialogPrefs.theDialog->geometry();
							rf=this->dialogPrefs.theDialog->frameGeometry();
							rf.setHeight(rf.height()-(rf.height()-rg.height()));
							rf.setWidth(rf.width()-(rf.width()-rg.width()));
							defaults.setValue(QString("%1_%2").arg(qApp->applicationName()).arg("prefsgeometry"),rf);
							this->dialogPrefs.theDialog->accept();
							this->dialogPrefs.valid=true;
						}
						break;

					case QDialogButtonBox::Apply:
						{
							this->dialogPrefs.valid=true;
							this->printCurrentPrefs();
						}			
						break;

					case QDialogButtonBox::Cancel:
						this->dialogPrefs.theDialog->reject();
						this->dialogPrefs.valid=false;
						break;
					default:
						break;
				}
		});

	if(this->paged==false)
		{
			mainvlayout->addWidget(&f);
			mainvlayout->addWidget(this->bb);
		}
	else
		{
			mainvlayout->addWidget(this->bb);
			mainvlayout->addSpacing(8);
		}

	int res=this->dialogPrefs.theDialog->exec();
	if(res==1)
		this->printCurrentPrefs();
}
