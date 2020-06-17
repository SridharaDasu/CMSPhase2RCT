#ifndef __APXLINKDATA_H__
#define __APXLINKDATA_H__

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iomanip>

class APxLinkData final {
public:

	struct LinkValue {
		uint16_t user;
		uint64_t data;

		bool operator ==(const LinkValue &b) const;
		bool operator !=(const LinkValue &b) const { return !(*this == b); };
	};

	APxLinkData(size_t links);

	void add(size_t cycle, size_t link, const LinkValue value);

	bool get(size_t cycle, size_t link, LinkValue& value) const;

	void write(const std::string filename) const;

	void read(const std::string filename);

	void print() const;

	inline size_t getLinks() const { return this->links; };
	inline size_t getCycles() const { return this->max_cycles; };

	bool operator ==(const APxLinkData &b) const;
	inline bool operator !=(const APxLinkData &b) const { return !(*this == b); };

private:
	size_t links;
	size_t max_cycles;

	typedef std::map<size_t, LinkValue> CycleDataMap;
	typedef std::map<size_t, CycleDataMap> LinkDataMap;
	LinkDataMap data;
};

#endif
