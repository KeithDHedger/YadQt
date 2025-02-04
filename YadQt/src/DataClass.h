/*
 *
 * ©K. D. Hedger. Sat 17 Aug 16:43:30 BST 2024 keithdhedger@gmail.com

 * This file (DataClass.h) is part of YadQt.

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

#ifndef _DATACLASS_
#define _DATACLASS_

#include "globals.h"

class DataClass
{
	public:
		DataClass();
		~DataClass();

		QCommandLineParser				parser;
		QString							title=PACKAGE_NAME;
		QString							body="Information";
		QString							defaultText;
		QDialog							*theDialog;
		QDialogButtonBox					*bb;
		QString							opsep="|";
		QString							ipsep="|";
		QMessageBox::StandardButton		retButton=QMessageBox::NoButton;
		QDialogButtonBox::StandardButton	dbutton=QDialogButtonBox::NoButton;
		int								width=-1;
		int								height=-1;
		bool								customSize=false;
		int								boxType=-1;
		int								retval=0;
		QString							theIcon="system-run";

		void								setDButtons(void);
		void								getBoxType(void);
		void								setReturnVals(void);
		QSize							adjustBoxSize(int defw,int defy);
};

#endif
