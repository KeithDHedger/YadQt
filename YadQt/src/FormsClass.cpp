/*
 *
 * ©K. D. Hedger. Mon 19 Aug 12:27:16 BST 2024 keithdhedger@gmail.com

 * This file (FormsClass.cpp) is part of YadQt.

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

#include "FormsClass.h"

FormsClass::FormsClass(QApplication *app,DataClass *data)
{
	this->data=data;
}

FormsClass::~FormsClass()
{
}

formReturnStruct FormsClass::formsDialog(QStringList items)
{
	formReturnStruct	prefs;
	QWidget					*hbox;
	QHBoxLayout				*hlayout;
	QVBoxLayout				*docvlayout=new QVBoxLayout;

	prefs.theDialog=new QDialog();

	this->data->theDialog=prefs.theDialog;//TODO//
	for(int j=0;j<items.size();j++)
		{
			hbox=new QWidget;
			hlayout=new QHBoxLayout;
			hlayout->setContentsMargins(0,0,0,0);
			hbox->setLayout(hlayout);
			hlayout->addWidget(new QLabel(items.at(j)),0,Qt::AlignLeft);
			prefs.boxes[j]=new QLineEdit(nullptr);

			hlayout->addWidget(prefs.boxes[j],1,Qt::AlignRight);
			docvlayout->addWidget(hbox);
		}

	docvlayout->addWidget(this->data->bb);
	docvlayout->setContentsMargins(MARGINS,MARGINS,MARGINS,MARGINS);

	prefs.theDialog->setLayout(docvlayout);
	prefs.theDialog->setWindowTitle(this->data->title);

	if(this->data->customSize==true)
		prefs.theDialog->resize(this->data->adjustBoxSize(256,-1));
	return(prefs);
}

void FormsClass::getForm(void)
{
	int						res=0;
	QStringList				items;
	QStringList				textstrings;
	formReturnStruct	form;

	std::vector<std::string> names=LFSTK_UtilityClass::LFSTK_strTok(this->data->body.toStdString(),std::string("|"));//TODO//
	for(long unsigned int j=0;j<names.size();j++)
		items<<names.at(j).c_str();

	form=this->formsDialog(items);

	std::vector<std::string> text=LFSTK_UtilityClass::LFSTK_strTok(this->data->defaultText.toStdString(),this->data->ipsep.toStdString());//TODO//
	for(long unsigned int j=0;j<text.size();j++)
		{
			textstrings<<text.at(j).c_str();
			form.boxes[j]->setText(text.at(j).c_str());
		}

	res=form.theDialog->exec();
	if(this->data->retval==0)
		{
			QString op="";
			for(int j=0;j<form.boxes.size()-1;j++)
				op+=form.boxes[j]->text()+data->opsep;
			op+=form.boxes[form.boxes.size()-1]->text();

			QTextStream(stdout) <<op<< Qt::endl;
		}
}

