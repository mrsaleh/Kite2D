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
#ifndef KGLWINDOW_H
#define KGLWINDOW_H

#include <string>
#include "Kite/core/system/ksystemdef.h"
#include "Kite/core/system/kcoreinstance.h"
#include "Kite/Core/math/kmathstructs.h"
#include "Kite/core/window/kwindowtypes.h"
#include "Kite/core/window/kwindowstructs.h"

namespace Kite{
    class KITE_FUNC_EXPORT KGLWindow : public KCoreInstance{
    public:
        // window will be created after open() call
        KGLWindow();
        KGLWindow(KWindowState &WindowState);
        ~KGLWindow();

        bool update();
        void display(); // swap buffer

        void open();
        void open(KWindowState &WindowState);
        void close();

        bool isOpen() const;
        //static bool isAnyCreatedContext();

        /// manipulate window settings
        void setTitle(const std::string &Title);
        void setSize(U32 Width, U32 Height);
        void setPosition(U32 XPosition, U32 YPosition);
        void setShowCursor(bool Enable);
        //bool setFullscreen(bool Enable);

        inline KWindowHandle getWindowHandle() const {return (KWindowHandle)_kwindow;}
        inline const KWindowState &getWindowState() const {return _kwinstate;}
        KVector2I32 getFrameBufferSize();

        /// window callbacks
        void registerCallback(void *Callback, KWindowCallbackTypes CallbackType);
        void unregisterCallback(KWindowCallbackTypes CallbackType);

		//! Get size of resource in memory
		/*!
		\return Size of resource in bytes
		*/
		U64 getInstanceSize() const;

    private:
        void *_kwindow;
        KWindowState _kwinstate;
    };
}

#endif // KGLWINDOW_H
