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
#include "src/Kite/core/system/win32/mutex.h"

namespace Kite{
namespace Internal{

    Mutex::Mutex(){
        InitializeCriticalSection(&_ksysmutex);
    }

    Mutex::~Mutex(){
        DeleteCriticalSection(&_ksysmutex);
    }

    void Mutex::lock(){
        EnterCriticalSection(&_ksysmutex);
    }

    void Mutex::unlock(){
        LeaveCriticalSection(&_ksysmutex);
    }

}
}