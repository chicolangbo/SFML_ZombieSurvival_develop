#pragma once
#include "DataTable.h"
#include "Singleton.h"

class DataTableMgr : public Singleton<DataTableMgr>
{
protected:
	std::unordered_map<DataTable::Ids, DataTable*> tables;

	DataTableMgr(const DataTableMgr& other) = delete;
	bool operator==(const DataTableMgr& other) const = delete;

public:
	DataTableMgr() = default;
	
	virtual ~DataTableMgr() { ReleaseAll(); }

	void LoadAll();
	void ReleaseAll();

	template <typename T>
	T* Get(DataTable::Ids id) const;
};

template<typename T>
inline T* DataTableMgr::Get(DataTable::Ids id) const
{
	auto find = tables.find(id);
	if (find == tables.end()) // 못 찾은 경우
	{
		return nullptr;
	}
	return dynamic_cast<T*>(find->second); // 못 찾은 경우 nullptr 반환해주는 dynamic_cast
}

#define DATATABLE_MGR (DataTableMgr::Instance())