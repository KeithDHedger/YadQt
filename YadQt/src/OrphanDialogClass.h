/*
 *
 * ©K. D. Hedger. Tue 20 Aug 20:21:31 BST 2024 keithdhedger@gmail.com

 * This file (OrphanDialogClass.h) is part of YadQt.

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

#ifndef _ORPHANDIALOGCLASS_
#define _ORPHANDIALOGCLASS_

#include "globals.h"

class ProxyStyle : public QProxyStyle
{
	public:
		int styleHint(StyleHint hint,const QStyleOption *option=nullptr,const QWidget *widget=nullptr,QStyleHintReturn *returnData=nullptr) const override
			{
				if(hint==QStyle::SH_Menu_Scrollable)
					return(int(true));

				return(QProxyStyle::styleHint(hint,option,widget,returnData));
			};
};

class OrphanDialogClass
{
	public:
		OrphanDialogClass(QApplication *app,DataClass *data);
		~OrphanDialogClass();

		void		getColour(void);
		void		getFont(void);
		void		tailBox(void);
		void		notePad(void);
		void		richText(void);
		void		openFile(void);
		void		openFolder(void);
		void		saveFile(void);
		void		prefsDialog(bool istabbed=false);
		void		trayMenu(void);
		void		yadQtHelp(void);

	private:
		void		loadData(QString uri);
		void		loadDataFromStdin(void);
		void		loadTrayMenu(void);

		DataClass		*data;
		QApplication		*app;
		QTextBrowser		*thedoc;
		QUrl				baseurl;
		QSystemTrayIcon	*trayIcon=NULL;
		QString			menuData;
		QMenu			*trayIconContextMenu=NULL;
		QMenu			*trayIconMenu=NULL;
		QAction			*lastTrayMenuAction=NULL;
		QScreen			*onScreen=NULL;
};

#endif
