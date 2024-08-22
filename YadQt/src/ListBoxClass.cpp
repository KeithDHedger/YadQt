/*
 *
 * ©K. D. Hedger. Mon 19 Aug 14:04:11 BST 2024 keithdhedger@gmail.com

 * This file (ListBoxClass.cpp) is part of YadQt.

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

#include "ListBoxClass.h"

ListBoxClass::ListBoxClass(QApplication *app,DataClass *data)
{
	this->data=data;
}

ListBoxClass::~ListBoxClass()
{
}

unsigned ListBoxClass::getList(void)
{
	QDialog					*theDialog;
	QWidget					*hbox;
	QVBoxLayout				*docvlayout=new QVBoxLayout;
	QHBoxLayout				*hlayout;
	QPushButton				*cancelbutton=new QPushButton("&Cancel");
	QPushButton				*okbutton=new QPushButton("&Apply");
	QStringList				items;
	QListWidget				*listwidget;
	int						res=0;

	theDialog=new QDialog();

	QObject::connect(cancelbutton,&QPushButton::clicked,[this,theDialog]()
		{
			theDialog->reject();
		});
	QObject::connect(okbutton,&QPushButton::clicked,[this,theDialog]()
		{
			theDialog->accept();
		});

	std::vector<std::string> names=LFSTK_UtilityClass::LFSTK_strTok(this->data->defaultText.toStdString(),this->data->ipsep.toStdString());
	for(long unsigned int j=0;j<names.size();j++)
		items<<names.at(j).c_str();

	listwidget=new QListWidget(nullptr);
	if(this->data->parser.isSet("multiple"))
		listwidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

	listwidget->addItems(items);
	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);
	docvlayout->addWidget(listwidget);

	hbox=new QWidget;
	hlayout=new QHBoxLayout;
	hlayout->setContentsMargins(0,0,0,0);
	hbox->setLayout(hlayout);
	hlayout->addWidget(cancelbutton);
	hlayout->addStretch(0);
	hlayout->addWidget(okbutton);

	docvlayout->addWidget(hbox);

	theDialog->setLayout(docvlayout);
	theDialog->setWindowTitle(this->data->title);


	if(this->data->customSize==true)
		theDialog->resize(QSize(this->data->width,this->data->height));

	res=theDialog->exec();
	if(res==1)
		{
			QString	textstrings;
			QList	l=listwidget->selectedItems();

			for(int j=0;j<l.size()-1;j++)
				textstrings+=l.at(j)->text()+data->opsep;
			textstrings+=l.at(l.size()-1)->text();

			QTextStream(stdout) <<textstrings<< Qt::endl;
			return(QMessageBox::Apply);		
		}

	return(QMessageBox::Cancel);
}

