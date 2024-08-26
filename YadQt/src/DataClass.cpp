/*
 *
 * ©K. D. Hedger. Sat 17 Aug 16:43:17 BST 2024 keithdhedger@gmail.com

 * This file (DataClass.cpp) is part of YadQt.

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

#include "DataClass.h"

DataClass::~DataClass()
{
}

DataClass::DataClass()
{
	this->bb=new QDialogButtonBox(QDialogButtonBox::NoButton);
	QObject::connect(this->bb,&QDialogButtonBox::clicked,[this](QAbstractButton *button)
		{
			this->retButton=QMessageBox::StandardButton(this->bb->standardButton(button));
			this->setReturnVals();
			this->theDialog->done(this->retval);
		});
}

void DataClass::setDButtons(void)
{
	if(this->parser.isSet("buttons"))
		{
			QString					d;
			std::vector<std::string> names=LFSTK_UtilityClass::LFSTK_strTok(this->parser.value("buttons").toStdString(),std::string("|"));

			for(long unsigned int j=0;j<names.size();j++)
				{
					d=names.at(j).c_str();

					if(d.compare("ok",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Ok|(unsigned int)this->dbutton);
					if(d.compare("cancel",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Cancel|(unsigned int)this->dbutton);
					if(d.compare("open",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Open|(unsigned int)this->dbutton);
					if(d.compare("Save",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Save|(unsigned int)this->dbutton);
					if(d.compare("Close",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Close|(unsigned int)this->dbutton);
					if(d.compare("Discard",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Discard|(unsigned int)this->dbutton);
					if(d.compare("Apply",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Apply|(unsigned int)this->dbutton);
					if(d.compare("Reset",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Reset|(unsigned int)this->dbutton);
					if(d.compare("RestoreDefaults",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::RestoreDefaults|(unsigned int)this->dbutton);
					if(d.compare("Help",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Help|(unsigned int)this->dbutton);
					if(d.compare("SaveAll",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::SaveAll|(unsigned int)this->dbutton);
					if(d.compare("Yes",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Yes|(unsigned int)this->dbutton);
					if(d.compare("YesToAll",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::YesToAll|(unsigned int)this->dbutton);
					if(d.compare("No",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::No|(unsigned int)this->dbutton);
					if(d.compare("NoToAll",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::NoToAll|(unsigned int)this->dbutton);
					if(d.compare("Abort",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Abort|(unsigned int)this->dbutton);
					if(d.compare("Retry",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Retry|(unsigned int)this->dbutton);
					if(d.compare("Ignore",Qt::CaseInsensitive)==0)
						this->dbutton=(QDialogButtonBox::StandardButton)((unsigned int)QDialogButtonBox::Ignore|(unsigned int)this->dbutton);
				}
			this->bb->setStandardButtons(this->dbutton);
		}
}

void DataClass::getBoxType()
{
	QString	str=this->parser.value("type");
//info boxes
	if(str.compare("about",Qt::CaseInsensitive)==0)
		this->boxType=ABOUT;
	if(str.compare("aboutqt",Qt::CaseInsensitive)==0)
		this->boxType=ABOUTQT;
	if(str.compare("query",Qt::CaseInsensitive)==0)
		this->boxType=QUERY;
	if(str.compare("info",Qt::CaseInsensitive)==0)
		this->boxType=INFO;
	if(str.compare("warn",Qt::CaseInsensitive)==0)
		this->boxType=WARN;
	if(str.compare("fatal",Qt::CaseInsensitive)==0)
		this->boxType=FATAL;

//input boxes
	if(str.compare("input",Qt::CaseInsensitive)==0)
		this->boxType=GETINPUT;
	if(str.compare("getitem",Qt::CaseInsensitive)==0)
		this->boxType=GETITEM;

//forms
	if(str.compare("form",Qt::CaseInsensitive)==0)
		this->boxType=GETFORM;

//list
	if(str.compare("list",Qt::CaseInsensitive)==0)
		this->boxType=GETLIST;
//files
	if(str.compare("textfile",Qt::CaseInsensitive)==0)
		this->boxType=SHOWTEXTFILE;
	if(str.compare("imagefile",Qt::CaseInsensitive)==0)
		this->boxType=SHOWIMAGEFILE;

//orphans
	if(str.compare("colour",Qt::CaseInsensitive)==0)
		this->boxType=GETCOLOUR;
	if(str.compare("font",Qt::CaseInsensitive)==0)
		this->boxType=GETFONT;
	if(str.compare("text",Qt::CaseInsensitive)==0)
		this->boxType=GETTEXT;
	if(str.compare("tailbox",Qt::CaseInsensitive)==0)
		this->boxType=TAILBOX;
}

void DataClass::setReturnVals(void)
{
	switch(this->retButton)
		{
			case QMessageBox::Ok:
			case QMessageBox::Open:
			case QMessageBox::Save:
			case QMessageBox::Close:
			case QMessageBox::Apply:
			case QMessageBox::Reset:
			case QMessageBox::RestoreDefaults:
			case QMessageBox::Help:
			case QMessageBox::SaveAll:
			case QMessageBox::Yes:
			case QMessageBox::YesToAll:
			case QMessageBox::Retry:
				this->retval=0;
				break;
			case QMessageBox::Ignore:
			case QMessageBox::Cancel:
			case QMessageBox::No:
			case QMessageBox::NoToAll:
			case QMessageBox::Abort:
				this->retval=1;
				break;
			default:
				this->retval=1;
				break;
		}
}
