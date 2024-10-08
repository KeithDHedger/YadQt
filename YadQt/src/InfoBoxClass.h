/*
 *
 * ©K. D. Hedger. Sat 17 Aug 12:29:57 BST 2024 keithdhedger@gmail.com

 * This file (InfoBoxClass.h) is part of YadQt.

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

#ifndef _INFOBOXCLASS_
#define _INFOBOXCLASS_

#include "globals.h"

class InfoBoxClass
{
	public:
		InfoBoxClass(QApplication *app,DataClass *data);
		~InfoBoxClass();

		void			showDialog(void);

	private:
		DataClass	*data;
};

#endif
