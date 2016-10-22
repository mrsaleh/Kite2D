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
#ifndef KORTHOMAPCOM_H
#define KORTHOMAPCOM_H

#include "Kite/core/kcoredef.h"
#include "Kite/core/kcomponent.h"
#include "Kite/meta/kmetadef.h"
#include "Kite/graphic/kgraphicstructs.h"
#include "Kite/graphic/korthogonalmap.h"
#include "Kite/math/kmathstructs.h"
#include <vector>
#include "krenderable.h"
#include "korthomapcom.khgen.h"

KMETA
namespace Kite {
	KM_CLASS(COMPONENT)
	class KITE_FUNC_EXPORT KOrthoMapCom : public KComponent, public KRenderable {
		friend class KRenderSys;
		friend class KGCullingSys;
		KM_INFO(KI_NAME = "OrthogonalMapView");
		KMETA_KORTHOMAPCOM_BODY();
	public:
		KOrthoMapCom(const std::string &Name = "");

		void attached(KEntity *Owner) override;

		void deattached(KEntity *Owner) override;

		RecieveTypes onMessage(KMessage *Message, MessageScope Scope) override;

		KM_PRO_SET(KP_NAME = "map")
		void setMap(const KStringID &ResName);

		KM_PRO_GET(KP_NAME = "map", KP_TYPE = KStringID, KP_CM = "name of the orthogonal map resource", KP_RES = RTypes::OrthogonalMap)
		inline const KStringID &getMap() const { return _kmapName; }

		KM_PRO_SET(KP_NAME = "cullingArea")
		void setCullingArea(const KRectF32 &Area);

		KM_PRO_GET(KP_NAME = "cullingArea", KP_TYPE = KRectF32, KP_CM = "object visibility")
		inline const KRectF32 &getCullingArea() const { return _kcullArea; }

		KM_PRO_SET(KP_NAME = "shaderProgram")
		void setShader(const KStringID &ShaderProgram);

		KM_PRO_GET(KP_NAME = "shaderProgram", KP_TYPE = KStringID, KP_CM = "name of the shader program", KP_RES = RTypes::ShaderProgram)
		inline const KStringID &getShader() const { return _kshprogName; }

		KM_PRO_SET(KP_NAME = "textureGroup")
		void setAtlasTextureArraye(const KStringID &TextureArrayName);

		KM_PRO_GET(KP_NAME = "textureGroup", KP_TYPE = KStringID, KP_CM = "name of the atlas texture group",
				   KP_RES = RTypes::TextureGroup)
		inline const KStringID &getAtlasTextureArray() const { return _ktextureArrayName; }

		KM_PRO_SET(KP_NAME = "visible")
		inline void setVisible(bool Visible) { _kisVisible = Visible; }

		KM_PRO_GET(KP_NAME = "visible", KP_TYPE = bool, KP_CM = "object visibility")
		inline bool isVisible() const override { return _kisVisible; }

		KM_FUN()
		inline bool isCullingAreaInside() const { return _kcullIsValid; }

		KM_FUN()
		void getBoundingRect(KRectF32 &Output) const override;

		bool updateRes() override;

	protected:
		/// render system interface
		inline const std::vector<KGLVertex> *getVertex() const override { return &_kverts; }
		inline const U32 getIndexSize() const override { return _kisize; }
		inline const std::vector<KPointSprite> *getPoint() const override { return nullptr; }
		inline GLPrimitive getGeoType() const override { return GLPrimitive::TRIANGLES; }
		inline bool isIndexed() const override { return true; }
		inline bool isPoint() const override { return false; }
		inline KShaderProgram *getShaderProg() const override { return _kshprog; }
		inline KAtlasTextureArray *getATextureArray() const override { return _katarray; }

	private:
		// calculate and update vertex
		void queryVerts();

		KM_VAR() U16 _ktindex;
		KM_VAR() bool _kisVisible;
		KM_VAR() KStringID _kmapName;
		KM_VAR() KRectF32 _kcullArea;
		KM_VAR() bool _kcullIsValid;
		KM_VAR() KStringID _kshprogName;
		KM_VAR() KStringID _ktexture;
		KM_VAR() KStringID _ktextureArrayName;

		std::vector<KGLVertex> _kverts;
		U32 _kisize;

		KOrthogonalMap *_kmap;
		KShaderProgram *_kshprog;
		KAtlasTextureArray *_katarray;
		bool _kquery;
	};
}

#endif // KORTHOMAPCOM_H