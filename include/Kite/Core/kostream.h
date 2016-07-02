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
#ifndef KOSTREAM_H
#define KOSTREAM_H

#include "Kite/core/kcoredef.h"
#include "Kite/core/kcoretypes.h"
#include "Kite/meta/kmetadef.h"
#include <string>
#include "kostream.khgen.h"

KMETA
namespace Kite {
	KM_CLASS(ABSTRACT, OSTREAM)
	class KITE_FUNC_EXPORT KOStream {
		KMETA_KOSTREAM_BODY();
	public:
		virtual ~KOStream() {}

		KM_FUN()
		virtual bool open(const std::string &Address, IOMode Type) = 0;

		virtual SIZE write(const void *Data, SIZE DataSize) = 0;

		KM_FUN()
		virtual bool isOpen() = 0;

		KM_FUN()
		virtual I32 close() = 0;

		KM_FUN()
		virtual const std::string &getFileName() = 0;

		KM_FUN()
		virtual const std::string &getPath() = 0;

		KM_FUN()
		virtual const std::string &getFullPath() = 0;

		KM_FUN()
		virtual IOMode getIOMode() = 0;

		/// will be implemented by KHParser
		/// usage: access base class in lua
		virtual KOStream *getBase() = 0;

		/// will be implemented by KHParser
		virtual inline std::string getType() const = 0;

		/// will be implemented by KHParser
		virtual inline U32 getHashType() const = 0;
	};
}

#endif // KOSTREAM_H