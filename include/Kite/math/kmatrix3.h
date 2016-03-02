/*
    Kite2D Game Framework.
    Copyright (C) 2010-2015  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/
#ifndef KMATRIX3_H
#define KMATRIX3_H

#include "Kite/core/kcoredef.h"

namespace Kite{
    class KMatrix3{
    public:
		KMatrix3(F32 E00 = 1.0f, F32 E01 = 0.0f, F32 E02 = 0.0f,
				 F32 E10 = 0.0f, F32 E11 = 1.0f, F32 E12 = 0.0f,
				 F32 E20 = 0.0f, F32 E21 = 0.0f, F32 E22 = 1.0f);

        inline const F32 *getArray() const {return _kmatrix;}

		inline float KMatrix3::operator[](int index) const { return _kmatrix[index]; }

		inline float& KMatrix3::operator[](int index) { return _kmatrix[index]; }

		KMatrix3 operator+(const KMatrix3 &right) const;

		KMatrix3 operator-(const KMatrix3 &right) const;

		KMatrix3 &operator+=(const KMatrix3 &right);

		KMatrix3 &operator-=(const KMatrix3 &right);

		KMatrix3 operator*(const KMatrix3& right) const;

		KMatrix3& KMatrix3::operator*=(const KMatrix3& right);

		bool KMatrix3::operator==(const KMatrix3& right) const;

		bool KMatrix3::operator!=(const KMatrix3& right) const;

		KMatrix3 operator-(const KMatrix3& right);
    private:
        F32 _kmatrix[9];
    };
}

#endif // KMATRIX3_H
