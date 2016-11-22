#include "stdafx.h"
#include "CppUnitTest.h"
#include "TypeCounter.h"
#include "ConstructType.h"
#include "ResourceType.h"
#include "ShipType.h"
#include "Fleet.h"
#include "World Module\Headers\Galactic\Planetary\Construct.h"
#include "World Module\Headers\Galactic\Planet.h"
#include "World Module\Headers\Galactic\SolarSystem.h"
#include "World Module\Headers\Galactic\StarSector.h"
#include "World Module\Headers\Galaxy.h"

using namespace Space_Colony;
using namespace Space_Colony::World_Module;
using namespace Space_Colony::World_Module::Galactic;
using namespace Space_Colony::World_Module::Galactic::Planetary;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SpaceColony_tests {
	TEST_CLASS(Space_Colony_tests) {
public:

	TEST_METHOD(TypeCounter_tests) {
		TypeCounter z0, cntr1, cntr2, neg, pos;
		for (__int32 i(0); i < 5; ++i) {
			z0.setCounter(i, 0);
			neg.setCounter(i, -1);
			pos.setCounter(i, 1);
			cntr1.setCounter(i, i);
			cntr2.setCounter(i, i * 2);
		}

		Assert::IsTrue(pos.isPos(), L"\"isPos\" failed.");

		Assert::IsTrue(neg.isNeg(), L"\"isNeg\" failed.");

		Assert::IsTrue(cntr1.size() == 4, L"\"size\" failed.");

		Assert::IsTrue(z0.empty(), L"\"empty\" failed.");

		Assert::IsTrue(z0 == z0, L"\"== op\" failed.");

		Assert::IsTrue(z0 != cntr1, L"\"!= op\" failed.");

		Assert::IsTrue(z0 == (cntr1 - cntr1), L"\"+ op\" failed.");

		Assert::IsTrue(cntr2 == (cntr1 + cntr1), L"\"+ op\" failed.");

		Assert::IsTrue(cntr1.getCounter(3) == 3, L"\"getCounter\" failed.");

		cntr1.incCounter(1, 1);
		Assert::IsTrue(cntr1.getCounter(1) == cntr2.getCounter(1), L"\"incCounter\" failed.");

	}

	TEST_METHOD(Fleet_tests) {
		ShipType shpTyp1(
			CombatStats(0, 0, 0, 0, 0, 0, 0),
			ShipType::WorldStats(TypeCounter(0), 1, 1, 1, 1, "Temp ShipType")
		), shpTyp2(shpTyp1), shpTyp3(shpTyp1);
		ShipTypeVector shipTypes({ shpTyp1, shpTyp2, shpTyp3 });

		ResourceType rsrcTyp1(1, 1), rsrcTyp2(rsrcTyp1), rsrcTyp3(rsrcTyp1);
		ResourceTypeVector resourceTypes({ rsrcTyp1, rsrcTyp2, rsrcTyp3 });

		TypeCounter ships({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});
		TypeCounter cargo({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});
		Fleet flt(Game_Factions::player, "Temp Fleet", 15, ships, cargo);

		Assert::IsTrue(flt.getShips() == ships, L"\"getShips\" failed.");

		Assert::IsTrue(flt.getShipMass(shipTypes) == 15, L"\"getShipMass\" failed.");

		try {
			flt.setShips(ships / 5, shipTypes, resourceTypes) == ships;
			Assert::Fail(L"\"setShips\" failed.");
		} catch (...) {
			Assert::IsTrue(flt.getShips() == ships, L"\"setShips\" failed.");
		}

		try {
			Assert::IsTrue(flt.setShips(0, 6, shipTypes, resourceTypes) == 5, L"\"setShips\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setShips\" failed.");
		}

		try {
			Assert::IsTrue(flt.setShips(0, 5, shipTypes, resourceTypes) == 6, L"\"setShips\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setShips\" failed.");
		}

		Assert::IsTrue(flt.getCargo() == cargo, L"\"getCargo\" failed.");

		Assert::IsTrue(flt.getCargoMass(resourceTypes) == 15, L"\"getCargoMass\" failed.");

		Assert::IsTrue(flt.getCargoVolume(resourceTypes) == 15, L"\"getCargoVolume\" failed.");

		Assert::IsTrue(flt.getCargoCapacity(shipTypes) == 15, L"\"getCargoCapacity\" failed.");

		try {
			flt.setCargo(cargo * 5, shipTypes, resourceTypes) == cargo;
			Assert::Fail(L"\"setCargo\" failed.");
		} catch (...) {
			Assert::IsTrue(flt.getCargo() == cargo, L"\"setCargo\" failed.");
		}

		try {
			Assert::IsTrue(flt.setCargo(0, 4, shipTypes, resourceTypes) == 5, L"\"setCargo\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setCargo\" failed.");
		}

		try {
			Assert::IsTrue(flt.setCargo(0, 5, shipTypes, resourceTypes) == 4, L"\"setCargo\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setCargo\" failed.");
		}

		Assert::IsTrue(flt.getFuel() == 15, L"\"getFuel\" failed.");

		Assert::IsTrue(flt.getFuelCapacity(shipTypes) == 15, L"\"getFuelCapacity\" failed.");

		Assert::IsTrue(flt.getFuelEfficiency(shipTypes) == 1, L"\"getFuelEfficiency\" failed.");

		try {
			Assert::IsTrue(flt.setFuel(30, shipTypes) == 15, L"\"setFuel\" failed.");
			Assert::Fail(L"\"setFuel\" failed.");
		} catch (...) {
			Assert::IsTrue(flt.getFuel() == 15, L"\"setFuel\" failed.");
		}

		try {
			Assert::IsTrue(flt.incFuel(-1, shipTypes) == 15, L"\"setFuel\" failed.");
			Assert::IsTrue(flt.getFuel() == 14, L"\"setFuel\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setFuel\" failed.");
		}

		try {
			Assert::IsTrue(flt.incFuel(1, shipTypes) == 14, L"\"setFuel\" failed.");
			Assert::IsTrue(flt.getFuel() == 15, L"\"setFuel\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setFuel\" failed.");
		}

	}

	TEST_METHOD(Planet_tests) {
		ResourceType rsrcTyp(1, 1);
		ResourceTypeVector resourceTypes({ rsrcTyp, rsrcTyp, rsrcTyp });
		TypeCounter resources({
			std::pair<__int32,__int32>(0, 25),
			std::pair<__int32,__int32>(1, 25)
		}), naturalCapacity({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		});

		ConstructType cnstrctTyp(
			TypeCounter({
			std::pair<__int32,__int32>(0, 1),
			std::pair<__int32,__int32>(1, 1)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}), "Unnamed ConstructType", {});
		ConstructTypeVector constructTypes({ cnstrctTyp, cnstrctTyp, cnstrctTyp });

		Planet::ConstructVector sites({
			Construct(0, true),
			Construct(1, true),
			Construct(2, true)
		});
		Planet::ConstructList satellites({
			sites[0]
		});

		Planet planet(Game_Factions::player, "Temp Planet", resources, naturalCapacity, 1);
		planet = Planet(Game_Factions::player, "Temp Planet", resources, naturalCapacity, sites, satellites);

		Assert::IsTrue(planet.getResources() == resources, L"\"getResources\" failed.");

		Assert::IsTrue(planet.getResourceCapacity(constructTypes) == resources, L"\"getResources\" failed.");

		try {
			Assert::IsTrue(planet.setResources(resources * 2, constructTypes) == resources, L"\"setResources\" failed.");
			Assert::Fail(L"\"setResources\" failed.");
		} catch (...) {
			Assert::IsTrue(planet.getResources() == resources, L"\"setResources\" failed.");
		}

		try {
			Assert::IsTrue(planet.setResource(0, 0, constructTypes) == 25, L"\"setResource\" failed.");
			Assert::IsTrue(planet.getResources().getCounter(0) == 0, L"\"setResource\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setResource\" failed.");
		}

		try {
			Assert::IsTrue(planet.setResource(0, 25, constructTypes) == 0, L"\"setResource\" failed.");
			Assert::IsTrue(planet.getResources().getCounter(0) == 25, L"\"setResource\" failed.");
		} catch (...) {
			Assert::Fail(L"\"setResource\" failed.");
		}

		Assert::IsTrue(planet.getSites() == sites, L"\"getSites\" failed.");

		Assert::IsTrue(planet.getSite(0) == sites[0], L"\"getSite\" failed.");

		Assert::IsTrue(planet.isFilled(0), L"\"isFilled\" failed.");

		planet.emptySite(0);
		Assert::IsFalse(planet.isFilled(0), L"\"isFilled \ emptySite\" failed.");

		planet.getSite(0) = sites[0];
		Assert::IsTrue(planet.getSatellites() == satellites, L"\"getSatellites\" failed.");

		planet.addSatellite(sites[1]);
		Assert::IsTrue(planet.getSatellites().size() == 2, L"\"addSatellite\" failed.");

		Assert::IsTrue(planet.setSatellites(satellites, constructTypes).size() == 2, L"\"setSatellite\" failed.");

		planet.addSatellite(sites[1]);
		planet.removeSatellite(sites[1], constructTypes);
		Assert::IsTrue(planet.getSatellites().size() == 1, L"\"removeSatellite\" failed.");

		Assert::IsFalse(planet.isSuperConstruct(), L"\"isSuperConstruct\" failed.");

		planet.getSite(1) = sites[0];
		planet.getSite(2) = sites[0];
		Assert::IsTrue(planet.isSuperConstruct(), L"\"isSuperConstruct\" failed.");

		planet.setSites(sites, constructTypes);
		Assert::IsTrue(planet.getSites() == sites, L"\"setSites\" failed.");

	}

	TEST_METHOD(SolarSystem_tests) {
		ResourceType rsrcTyp(1, 1);
		ResourceTypeVector resourceTypes({ rsrcTyp, rsrcTyp, rsrcTyp });
		TypeCounter resources({
			std::pair<__int32,__int32>(0, 25),
			std::pair<__int32,__int32>(1, 25)
		}), naturalCapacity({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		});

		ConstructType cnstrctTyp(
			TypeCounter({
			std::pair<__int32,__int32>(0, 1),
			std::pair<__int32,__int32>(1, 1)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}), "Unnamed ConstructType", {}
		);
		ConstructTypeVector constructTypes({ cnstrctTyp, cnstrctTyp, cnstrctTyp });

		Planet::ConstructVector sites({
			Construct(0, true),
			Construct(1, true),
			Construct(2, true)
		});
		Planet::ConstructList satellites({
			sites[0]
		});

		Planet plnt(Game_Factions::player, "Temp Planet", resources, naturalCapacity, sites, satellites);
		SolarSystem::PlanetVector planets({ plnt,plnt,plnt });

		ShipType shpTyp1(
			CombatStats(0, 0, 0, 0, 0, 0, 0),
			ShipType::WorldStats(TypeCounter(0), 1, 1, 1, 1, "Temp ShipType")
		), shpTyp2(shpTyp1), shpTyp3(shpTyp1);
		ShipTypeVector shipTypes({ shpTyp1, shpTyp2, shpTyp3 });

		TypeCounter ships({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});
		TypeCounter cargo({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});

		Fleet flt(Game_Factions::player, "Temp Fleet", 15, ships, cargo);
		FleetVector fleets({ flt, flt, flt });

		SolarSystem system("Temp SolarSystem", 1, planets, { 0, 1, 2 });

		Assert::IsTrue(system.getFaction(fleets) == Game_Factions::player, L"\"getFaction\" failed.");

		Assert::IsTrue(system.getResource(0) == 75, L"\"getResource\" failed.");

		Assert::IsTrue(system.getResources().getCounter(0) == system.getResource(0), L"\"getResources\" failed.");

		system.moveFleet(0, system, system);
		Assert::IsTrue(system.getFleets().size() == 3, L"\"moveFleet\" failed.");

	}

	TEST_METHOD(StarSector_tests) {
		ResourceType rsrcTyp(1, 1);
		ResourceTypeVector resourceTypes({ rsrcTyp, rsrcTyp, rsrcTyp });
		TypeCounter resources({
			std::pair<__int32,__int32>(0, 25),
			std::pair<__int32,__int32>(1, 25)
		}), naturalCapacity({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		});

		ConstructType cnstrctTyp(
			TypeCounter({
			std::pair<__int32,__int32>(0, 1),
			std::pair<__int32,__int32>(1, 1)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}),
			TypeCounter({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5)
		}), "Unnamed ConstructType", {}
		);
		ConstructTypeVector constructTypes({ cnstrctTyp, cnstrctTyp, cnstrctTyp });

		Planet::ConstructVector sites({
			Construct(0, true),
			Construct(1, true),
			Construct(2, true)
		});
		Planet::ConstructList satellites({
			sites[0]
		});

		Planet plnt(Game_Factions::player, "Temp Planet", resources, naturalCapacity, sites, satellites);
		SolarSystem::PlanetVector planets({ plnt,plnt,plnt });

		ShipType shpTyp1(
			CombatStats(0, 0, 0, 0, 0, 0, 0),
			ShipType::WorldStats(TypeCounter(0), 1, 1, 1, 1, "Temp ShipType")
		), shpTyp2(shpTyp1), shpTyp3(shpTyp1);
		ShipTypeVector shipTypes({ shpTyp1, shpTyp2, shpTyp3 });

		TypeCounter ships({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});
		TypeCounter cargo({
			std::pair<__int32,__int32>(0, 5),
			std::pair<__int32,__int32>(1, 5),
			std::pair<__int32,__int32>(2, 5)
		});

		Fleet flt(Game_Factions::player, "Temp Fleet", 15, ships, cargo);
		FleetVector fleets({ flt, flt, flt });

		SolarSystem sys("Temp SolarSystem", 1, planets, { 0, 1, 2 });
		StarSector::SystemVector systems({ sys, sys, sys });

		StarSector sector("Temp StarSector", systems);

		Assert::IsTrue(sector.getFaction(fleets) == Game_Factions::player, L"\"getFaction\" failed.");

		Assert::IsTrue(sector.getResource(0) == 225, L"\"getResource\" failed.");

		Assert::IsTrue(sector.getResources().getCounter(0) == sector.getResource(0), L"\"getResources\" failed.");

	}

	};

}