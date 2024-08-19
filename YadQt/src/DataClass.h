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

		QString						title;
		QString						body;
		QString						defaultText;
		int							width=100;
		int							height=100;
		int							boxType=-1;

		QMessageBox::StandardButtons	buttons=QMessageBox::NoButton;
		QCommandLineParser			parser;

		void							setButtons(void);
		void							getBoxType(void);
		
};

#endif