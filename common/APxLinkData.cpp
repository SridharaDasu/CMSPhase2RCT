#include "APxLinkData.hh"
#include <sstream>

using namespace std;

bool APxLinkData::LinkValue::operator ==(const LinkValue &b) const {
	if (this->user != b.user || this->data != b.data) return false;

	return true;
}

APxLinkData::APxLinkData(size_t links) {
	this->links = links;
	this->max_cycles = 0;
}

void APxLinkData::add(size_t cycle, size_t link, const LinkValue value) {
	if (link > this->links) throw runtime_error("Link out-of-range");

	CycleDataMap &v = this->data[cycle];
	//std::map<size_t, LinkValue> &v = this->data[cycle];
	v[link] = value;

	if (cycle >= this->max_cycles)
		this->max_cycles = cycle+1;
}

bool APxLinkData::get(size_t cycle, size_t link, LinkValue& value) const {

	LinkDataMap::const_iterator it1 = this->data.find(cycle);
	if (it1 == this->data.end()) return false;

	CycleDataMap::const_iterator it2 = it1->second.find(link);
	if (it2 == it1->second.end()) return false;

	value = it2->second;
	return true;
}

void APxLinkData::write(const string filename) const {
	ofstream of;
	of.open(filename.c_str());
	if (!of) throw runtime_error("Cannot open output file: " + filename);

	of << "# Automatically generated" << endl;
	of << endl;

	of << "# CLK ";
	for (size_t k = 0; k < this->links; k++) {
		of << "Link " << setw(2) << k << "                  ";
	}
	of << endl;

	for (LinkDataMap::const_iterator it1 = this->data.begin(); it1 != this->data.end(); it1++) {
		of << dec << setfill(' ') << setw(4) << it1->first << "  ";

		for (size_t k = 0; k < this->links; k++) {
			CycleDataMap::const_iterator it2 = it1->second.find(k);
			if (it2 == it1->second.end()) {
				of << "-    -                   ";
			} else {
				of << "0x" << hex << setfill('0') << setw(2) << it2->second.user << " 0x" << setw(16) << it2->second.data << "  ";
			}
		}

		of << endl;
	}

	of.close();
}

void APxLinkData::read(const std::string filename) {
	ifstream rs(filename.c_str());
	if (!rs) throw runtime_error("Cannot open input file: " + filename);

	for (string line; getline(rs, line);) {
		if (line.length() <= 1 || line[0] == '#') continue;

		int cycle;

		istringstream ss(line);
		ss >> cycle;

		for (size_t i = 0; i < this->links; i++) {
			string user, data;
			ss >> user;
			ss >> data;

			if (user[0] == '-' && data[0] == '-') continue;

			LinkValue word;
			word.user = std::stoi(user, nullptr, 0);
			word.data = std::stoull(data, nullptr, 0);

			this->add(cycle, i, word);
		}
	}

	rs.close();
}

void APxLinkData::print() const {
	for (LinkDataMap::const_iterator it1 = this->data.begin(); it1 != this->data.end(); it1++) {
		cout << dec << setfill(' ') << setw(4) << it1->first << "  ";

		for (size_t k = 0; k < this->links; k++) {
			CycleDataMap::const_iterator it2 = it1->second.find(k);
			if (it2 == it1->second.end()) {
				cout << "-    -                   ";
			} else {
				cout << "0x" << hex << setfill('0') << setw(2) << it2->second.user << " 0x" << setw(16) << it2->second.data << "  ";
			}
		}

		cout << endl;
	}
}

bool APxLinkData::operator ==(const APxLinkData &b) const {
	for (size_t i = 0; i < this->max_cycles; i++) {
		for (size_t k = 0; i < this->links; k++) {
			LinkValue v1, v2;

			bool r1 = this->get(i, k, v1);
			bool r2 = b.get(i, k, v2); // hack: remove const

			if (r1 != r2) return false;
			if ((r1 && r2) && (v1 != v2)) return false;
		}
	}

	return true;
}
