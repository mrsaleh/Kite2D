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
#ifndef KMESSENGER_H
#define KMESSENGER_H

#include "Kite/core/kcoredef.h"
#include "Kite/core/knoncopyable.h"
#include "Kite/core/kcoretypes.h"
#include "Kite/core/kcorestructs.h"
#include "Kite/core/klistener.h"
#include "Kite/core/kmessage.h"
#include "Kite/meta/kmetadef.h"
#include <unordered_map>

KMETA
namespace Kite {
	KMETA_CLASS(SCRIPTABLE)
	class KITE_FUNC_EXPORT KMessenger{
	public:
		KMETA_CONSTRUCTURE()
		KMessenger();

		virtual ~KMessenger();

		KMETA_FUNCTION()
		void subscribe(KListener &Listener, const std::string &Type);

		/// dont need compute hash code of string by this function
		/// so it's a bit faster than subscribe by string
		KMETA_FUNCTION()
		void subscribeByHash(KListener &Listener, U32 Hash);

		KMETA_FUNCTION()
		void unsubscribe(KListener &Listener, const std::string &Type);

		/// dont need compute hash code of string by this function
		/// so it's a bit faster than unsubscribe by string
		KMETA_FUNCTION()
		void unsubscribeByHash(KListener &Listener, U32 Hash);

	protected:
		/// post message by its type (immediately)
		/// return number of objects that recieved message
		KMETA_FUNCTION()
		U32 postMessage(KMessage &Message, KMessageScopeTypes Scope);

	private:
		std::unordered_multimap<U32, KListener *> _khndlMap;
	};
}

#endif // KMESSENGER_H