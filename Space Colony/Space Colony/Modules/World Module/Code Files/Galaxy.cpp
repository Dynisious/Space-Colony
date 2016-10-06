#include "..\Headers\Galaxy.h"
#include <cmath>

World_Module::Galaxy::Galaxy()
	: Galaxy(StarMap()) {}

World_Module::Galaxy::Galaxy(const Galaxy & orig)
	: Galaxy(orig.clusters) {}

World_Module::Galaxy::Galaxy(const StarMap & clstrs)
	: clusters(clstrs) {}

void World_Module::Galaxy::newCluster(const Galactic::StarCluster & cluster) {
	coordinate center(0), coord(0);
	__int32 distance(0);
	StarMap::const_iterator iter, end(clusters.end());
	do {
		center.fill(0), coord.fill(0);
		distance = 0;
		for (iter = clusters.begin(); iter != end; iter++)
			//Accumulate all coordinates.
			center += iter->first;
		center /= clusters.size();
		//Get the average of all the coordinates.
		for (iter = clusters.begin(); iter != end; iter++) {
			const double newDist((iter->first - center).magnituid());
			//Get the distance from the center to this coordinate.
			if (newDist > distance)
				//This new distance is greater than the last.
				distance = newDist;
		}
		distance = distance - (std::rand() / distance);
		//The distance will be between 0 and the maximum distance from the center.
		coord[0] = std::rand() % 100 - 50;
		coord[1] = std::rand() % 100 - 50;
		//Random coordinates to provide a direction.
		coord = center + (coord.unit() * distance);
		//The new coordinate is the distance from the center in a random direction.
	} while (clusters.count(coord) != 0);
	//Ensure that the new coordinate does not overlap.
	clusters[coord] = cluster;
}

World_Module::Galaxy & World_Module::Galaxy::operator=(const Galaxy & right) {
	clusters = right.clusters;
	return *this;
}

bool World_Module::Galaxy::operator==(const Galaxy & right) const {
	return (this == &right)
		|| (clusters == right.clusters);
}

bool World_Module::Galaxy::operator!=(const Galaxy & right) const {
	return !operator==(right);
}
