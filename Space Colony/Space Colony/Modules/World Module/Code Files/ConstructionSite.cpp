#include "..\Headers\Star System\ConstructionSite.h"

using namespace World_Module::Star_System;

ConstructionSite::Site::Site() {}

ConstructionSite::Site::~Site() {}

ConstructionSite::ConstructionSite()
	: ConstructionSite(state_empty) {}

ConstructionSite::ConstructionSite(const ConstructionSite& orig) {
	operator=(orig);
}

World_Module::Star_System::ConstructionSite::ConstructionSite(const ConstructionSite_state st)
	: state(st) {
	if (st == state_city)
		site.city = City();
	else if (st == state_construct)
		site.construct = Construct();
}

ConstructionSite::ConstructionSite(const City& filledSite) {
	site.city = filledSite;
	state = state_city;
}

ConstructionSite::ConstructionSite(const Construct& filledSite) {
	site.construct = filledSite;
	state = state_construct;
}

ConstructionSite::~ConstructionSite() {
	if (state == state_city)
		site.city.~City();
	else if (state == state_construct)
		site.construct.~Construct();
}

void ConstructionSite::deconstruct() {
	state = state_empty;
}

ConstructionSite::ConstructionSite_state ConstructionSite::get_state() const {
	return state;
}

ConstructionSite::Site & ConstructionSite::get_site() {
	return site;
}

const ConstructionSite::Site & ConstructionSite::get_site() const {
	return site;
}

ConstructionSite& ConstructionSite::operator=(const ConstructionSite& right) {
	state = right.state;
	if (right.state == state_city)
		site.city = right;
	else if (right.state == state_construct)
		site.construct = right;
	return *this;
}

ConstructionSite& ConstructionSite::operator=(const City& right) {
	state = state_city;
	site.city = right;
	return *this;
}

ConstructionSite& ConstructionSite::operator=(const Construct& right) {
	state = state_construct;
	site.construct = right;
	return *this;
}

bool ConstructionSite::operator==(const ConstructionSite& right) const {
	if (state != right.state)
		return false;
	if (state == state_city)
		return site.city == right;
	else if (state == state_construct)
		return site.construct == right;
}

bool ConstructionSite::operator==(const City& right) const {
	return state == state_city
		&& site.city == right;
}

bool ConstructionSite::operator==(const Construct& right) const {
	return state == state_construct
		&& site.construct == right;
}

bool ConstructionSite::operator!=(const ConstructionSite& right) const {
	if (state != right.state)
		return true;
	if (state == state_city)
		return site.city != right;
	else if (state == state_construct)
		return site.construct != right;
}

bool ConstructionSite::operator!=(const City& right) const {
	return state != state_city
		|| site.city != right;
}

bool ConstructionSite::operator!=(const Construct& right) const {
	return state != state_construct
		|| site.construct != right;
}

ConstructionSite::operator const City&() const {
	if (state != state_city)
		throw ConstructionSite_StateException();
	return site.city;
}

ConstructionSite::operator const Construct&() const {
	if (state != state_construct)
		throw ConstructionSite_StateException();
	return site.construct;
}

ConstructionSite::operator City&() {
	if (state != state_city)
		throw ConstructionSite_StateException();
	return site.city;
}

ConstructionSite::operator Construct&() {
	if (state != state_construct)
		throw ConstructionSite_StateException();
	return site.construct;
}

ConstructionSite_StateException::ConstructionSite_StateException()
	: exception("The attempted retrieval of the type for this site does not match with the sites state.") {}

ConstructionSite_StateException::ConstructionSite_StateException(const ConstructionSite_StateException & orig)
	: exception(orig) {}

ConstructionSite_StateException::ConstructionSite_StateException(const char * Message)
	: exception(Message) {}
