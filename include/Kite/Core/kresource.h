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
#ifndef KRESOURCE_H
#define KRESOURCE_H

#include "Kite/core/kcoredef.h"
#include "Kite/core/kcoretypes.h"
#include "Kite/core/knoncopyable.h"
#include "Kite/core/kistream.h"
#include <cstring>

namespace Kite{
	class KITE_FUNC_EXPORT KResource : KNonCopyable{
	friend class KResourceManager;
	public:
		KResource(const std::string &Name, KResourceTypes Type):
			_ktype(Type),
			_kname(Name),
			_kref(0)
		{}

		virtual ~KResource(){};

		//! Read the resource from input stream.
		/*!
		\param Stream Input stream.

		\return True if loading was successful
		*/
		virtual bool loadStream(KIStream &Stream, U32 Flag = 0) = 0;

		inline U32 getReferencesCount() const { return _kref; }

		inline const std::string &getResourceName() const { return _kname; }

		inline KResourceTypes getResourceType() const { return _ktype; }

	private:
		// internal use by resource manager
		inline void setResourceName(const std::string &Name) { _kname = Name; }
		inline void incRef() { ++_kref; }
		inline void decRef() { _kref > 0 ? --_kref : _kref; }

		U32 _kref;
		KResourceTypes _ktype;
		std::string _kname;
	};
}

#endif // KRESOURCE_H