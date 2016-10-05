#pragma once

#include "Ship Types.h"
#include "ShipStats.h"
#include <unordered_map>

namespace Combat_Module {

	namespace Ship_Types {

		/*
		A ShipTemplate is a collection of stats defining a Ship type with an
		identifying ID which can represent it's type in the game.*/
		class ShipTemplate : public ShipStats {
		public:
			/*
			An ID used to represent this ShipTemplate within the game.*/
			typedef __int32 ShipTemplateID;

			ShipTemplate();
			ShipTemplate(const ShipTemplate& orig);
			ShipTemplate(ShipTemplateID d);
			ShipTemplate(ShipTemplateID d, const ShipStats& stats);

			ShipTemplateID get_id() const;

			/*
			The ID representing this ShipTemplate in the game.*/
			__declspec(property(get = get_id)) ShipTemplateID _ID;

			ShipTemplate& operator=(const ShipTemplate& right);
			bool operator==(const ShipTemplate& right) const;
			bool operator!=(const ShipTemplate& right) const;

			explicit operator ShipStats&();
			explicit operator const ShipStats&() const;

		private:
			ShipTemplateID id;

		};

		/*
		True if the ShipTemplate was loaded as a new Template.*/
		bool ShipTemplate_load(const ShipTemplate& tmp);
		/*
		Returns TRUE if the passed ID is a loaded ShipTemplate and places the
		value into "res".*/
		bool ShipTemplate_getTemplate(ShipTemplate::ShipTemplateID ID, ShipTemplate& res);
		/*
		Returns TRUE if the passed ID was a loaded ShipTemplate. "res" holds
		the unloaded ShipTemplate.*/
		bool ShipTemplate_unload(ShipTemplate::ShipTemplateID ID, ShipTemplate* const res = nullptr);
		/*
		Returns TRUE if the passed ID is a loaded ShipTemplate.*/
		bool ShipTemplate_isLoaded(const ShipTemplate& tmp);

	}

}
