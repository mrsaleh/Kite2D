/* 
 Kite2D Game Framework.
 Copyright (C) 2010-2014  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or 
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KGRAPHICDEF_H
#define KGRAPHICDEF_H

namespace Kite{

/// Hardware color macros
#define ARGB(a,r,g,b)	((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + DWORD(b))

/// buffer offest
#define KBUFFER_OFFSET(i) ((void*)(i))

/// vertex attribute index
#define KVATTRIB_XY 0
#define KVATTRIB_UV 1
#define KVATTRIB_RGBA 2

/// convert opengl (buttom-left) float coordinate to window (top-left) integer coordinate
/// default center = top-right
#define KCGL_TO_WIN_X(x, w)         (((float)x + 1) * (w / 2))
#define KCGL_TO_WIN_Y(y, h)         (h - (((float)y + 1) * (h / 2)))

/// convert window (top-left) integer coordinate to opengl (buttom-left) float coordinate
/// default center = top-right
#define KCWIN_TO_GL_X(x, w)         ((x - ((float)w / 2)) * (1 / ((float)w / 2)))
#define KCWIN_TO_GL_Y(y, h)         ((y - ((float)h / 2)) * (1 / ((float)h / 2)) * -1)

/// convert (buttom-left) integer coordinate to (buttom-left) opengl float coordinate
/// default center = top-right
#define KCINT_TO_F_POS(xy, wh)      ((xy - ((float)wh / 2)) * (1 / ((float)wh / 2)))

/// convert integer base size to float (opengl -1 to 0) base size
/// e.g s = 10, b = 40 , result = 0.5
#define KCINT_TO_F_SIZE(s, b)       ((2 / (float)b) * s)

/// convert mouse position (y) from microsoft windows to opengl
#define KCYMOUSE(y, h)			(h - y)

}
#endif // KGRAPHICDEF_H
