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
#ifndef KKLISTENER_H
#define KKLISTENER_H

#include "Kite/core/kcoredef.h"
#include "Kite/ecs/kecstypes.h"
#include "Kite/ecs/kmessage.h"
#include "Kite/meta/kmetadef.h"
#include "klistener.khgen.h"

KMETA
namespace Kite {
	KM_CLASS(SCRIPTABLE)
	class KITE_FUNC_EXPORT KListener {
		KMETA_KLISTENER_BODY();
	public:
		KListener();
		virtual ~KListener();

		virtual RecieveTypes onMessage(KMessage *Message, MessageScope Scope) = 0;

		KM_PRO_GET(KP_NAME = "Enable", KP_TYPE = bool, KP_CM = "enable/disable recieving message")
		inline bool getEnableRecieveMsg() const { return _kenable; }

		KM_PRO_SET(KP_NAME = "Enable")
		inline void setEnableRecieveMsg(bool Value) { _kenable = Value; }

	private:
		bool _kenable;
	};
}


#endif // KKLISTENER_H