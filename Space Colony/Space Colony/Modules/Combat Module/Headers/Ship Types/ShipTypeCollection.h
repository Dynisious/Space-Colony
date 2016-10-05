#pragma once

#include "Ship Types.h"
#include "ShipTemplate.h"
#include <unordered_map>

namespace Combat_Module {

	namespace Ship_Types {

		/*
		A collection of ShipTemplates where each id will only appear once.*/
		class ShipTypeCollection {
		public:
			/*
			A map of ShipTemplateIDs and ShipTemplates.*/
			typedef std::unordered_map<ShipTemplate::ShipTemplateID, ShipTemplate> TemplateMap;
			typedef std::pair<TemplateMap::const_iterator, bool> ModifyType;
			typedef TemplateMap::const_iterator const_iterator;

			ShipTypeCollection();
			ShipTypeCollection(const ShipTypeCollection& orig);
			ShipTypeCollection(const TemplateMap& tmplts);

			const_iterator begin() const;
			const_iterator end() const;
			/*
			Adds the template if it does not already exist.*/
			ModifyType addTemplate(const ShipTemplate& tmp);
			/*
			Returns the template attached to the passed ID should it exist.*/
			ModifyType getTemplate(ShipTemplate::ShipTemplateID id) const;
			/*
			Removes the template for the passed ID.*/
			bool removeTemplate(ShipTemplate::ShipTemplateID id);
			/*
			True if there is a mapping for the passed ID.*/
			bool contains(const ShipTemplate::ShipTemplateID& id) const;
			/*
			Returns the number of templates in this collection.*/
			__int32 size() const;

			ShipTypeCollection& operator=(const ShipTypeCollection& right);
			bool operator==(const ShipTypeCollection& right) const;
			bool operator!=(const ShipTypeCollection& right) const;
			ModifyType operator[](ShipTemplate::ShipTemplateID id) const;

		private:
			TemplateMap templates;

		};

	}

}
