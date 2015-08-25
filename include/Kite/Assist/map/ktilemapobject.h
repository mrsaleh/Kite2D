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
#ifndef KTILE_H
#define KTILE_H

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/Core/graphic/kgraphicstructs.h"

namespace Kite {
	class KITE_FUNC_EXPORT KTileMapObject {
		friend class KTileMap;
	public:
		KTileMapObject(I32 ObjectFlag = -1, U32 Layer = 0) :
			_kflag(ObjectFlag),
			_ktID(-1),
			_klayer(Layer)
		{}

		virtual ~KTileMapObject() {}

		// ID of tile in the map
		inline I32 getTileID() const { return _ktID; }

		inline I32 getTileFlag() const { return _kflag; }

		inline void setLayer(U32 Layer) { _klayer = Layer; }
		inline U32 getLayer() const { return _klayer; }

		// get next object in the tile list
		inline KTileMapObject *getNextObject() const { return (KTileMapObject *)_klink.next; }

		virtual const KVector2F32 *getTilePosition() const = 0;

	protected:
		// custom flag
		inline void setTileFlag(I32 Flag) { _kflag = Flag; }

	private:
		I32 _kflag;
		I32 _ktID;
		U32 _klayer;
		Internal::KLinkedPoint _klink;
	};
}


#endif // KTILE_H