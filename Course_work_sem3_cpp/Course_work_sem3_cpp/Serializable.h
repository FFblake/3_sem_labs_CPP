#pragma once
#include<iostream>

class Serializable abstract
{
public:
	virtual ~Serializable() = default;

	virtual void Save(std::ostream& output) const = 0;
	virtual void Load(std::istream& input) = 0;

protected:
	static void Write(std::ostream& output, const std::string& value) {
		output << value.size() << " " << value << " ";
	}
	static void Read(std::istream& input, std::string& value)
	{
		int stringsize;
		input >> stringsize;
		SkipOneChar(input);
		value.resize(stringsize);
		if (!input.read(value.data(), stringsize)) throw std::runtime_error("reading buffer failed!");
		SkipOneChar(input);
	}
	static void Write(std::ostream& output, const int& value) {
		output << value << " ";
	}
	static void Read(std::istream& input, int& value)
	{		
		input >> value;
		SkipOneChar(input);

	}
	template <typename TMap>
	static void Write(std::ostream& output, const typename TMap& map) {
		Write(output, (int) map.size());
		for (auto it2 = map.begin(); it2 != map.end(); ++it2) {
			Write(output, it2->first);
			it2->second.Save(output);
		}
	}
	template <typename TMap>
	static void Read(std::istream& input, typename TMap& map) {
		int mapsize;
		Read(input, mapsize);
		for (int i = 0; i < mapsize; i++) {
			typename TMap::key_type key;
			Read(input, key);
			typename TMap::mapped_type object;
			object.Load(input);
			map.insert({ key, object });
		}
	}
private:
	static void SkipOneChar(std::istream& input)
	{
		input.seekg(1,std::ios_base::cur );
	}
};