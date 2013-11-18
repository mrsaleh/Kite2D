/*    
    Kite2D Game Framework.
    Copyright (C) 2010-2013  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "include/Kite/system/kmutex.h"

#if defined(KITE_PLATFORM_WINDOWS)

    #include "src/Kite/system/win32/kmuteximpl.h"

#elif defined(KITE_PLATFORM_LINUX)


#elif defined(KITE_PLATFORM_MACOS)


#endif

namespace Kite{

    KMutex::KMutex(){
        m_impl = new Internal::KMutexImpl();
    }

    KMutex::~KMutex(){
        delete m_impl;
    }

    void KMutex::lock(){
        m_impl->lock();
    }

    void KMutex::unlock(){
        m_impl->unlock();
    }

}
