/*
 *
 * ©K. D. Hedger. Tue 20 Aug 12:07:05 BST 2024 keithdhedger@gmail.com

 * This file (FilesClass.h) is part of YadQt.

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

#ifndef _FILESCLASS_
#define _FILESCLASS_

#include "globals.h"

class FilesClass
{
	public:
		FilesClass(QApplication *app,DataClass *data);
		~FilesClass();

		unsigned		showTextFile(void);
	private:
		DataClass	*data;
};
#endif
