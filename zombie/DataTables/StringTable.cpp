#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

bool StringTable::Load()
{
	// 언어별로 순회
	std::vector<std::string> filenames;
	filenames.push_back("tables/StringTable_Kor.csv");
	filenames.push_back("tables/StringTable_Eng.csv");
	filenames.push_back("tables/StringTable_Jap.csv");

	for (int i = 0; i<tables.size(); ++i)
	{
		rapidcsv::Document doc(filenames[i]);
		std::vector<std::string> ids = doc.GetColumn<std::string>(0); // 해당 열에 들어가 있는 애들이 형변환 됨
		std::vector<std::string> values = doc.GetColumn<std::string>(1);

		for (int j = 0; j < ids.size(); ++j)
		{
			 std::cout << ids[j] << " " << values[j] << std::endl;
			tables[i].insert({ids[j], values[j]});
		}
	}

	return true;
}

void StringTable::Release()
{
	for (auto table : tables)
	{
		table.clear();
	}
	//tables.clear();
}

const std::string& StringTable::Get(const std::string& id, Languages lang) const
{
	auto& table = tables[(int)lang];

	auto find = table.find(id);
	if (find == table.end())
	{
		return "ERR: Undefined";
	}
	return find->second;
}
