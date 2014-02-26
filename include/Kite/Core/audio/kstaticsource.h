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
#ifndef KSTATICSOURCE_H
#define KSTATICSOURCE_H

#include "Kite/system/ksystemdef.h"
#include "Kite/audio/ksoundsource.h"
#include "Kite/audio/ksoundbuffer.h"

namespace Kite{
    class KITE_FUNC_EXPORT KStaticSource : public KSoundSource{
    public:
        void play();
        void pause();
        void stop();

        /// default false
        void setLoop(bool Loop);
        bool getLoop();

        /// attach a buffer to the source
        void attachBuffer(const KSoundBuffer &Buffer);

        /// deattach buffer
        void deattachBuffer();

        /// set play offset
        void setPlayOffset(U32 Second);
    };
}

#endif // KSTATICSOURCE_H
