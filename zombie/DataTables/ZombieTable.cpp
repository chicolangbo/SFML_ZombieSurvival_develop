#include "stdafx.h"
#include "ZombieTable.h"
#include "rapidcsv.h"

bool ZombieTable::Load()
{
	std::string filename = "tables/ZombieTable.csv";

	rapidcsv::Document doc(filename); // 맨 첫번째 행은 안 불러옴
	//std::vector<std::string> ids = doc.GetRow<std::string>(0); // 해당 열에 들어가 있는 애들이 형변환 됨
	std::vector<int> zombieId = doc.GetColumn<int>(0);
	std::vector<std::string> zombieTexture = doc.GetColumn<std::string>(1);
	std::vector<float> zombieSpeed = doc.GetColumn<float>(2);
	std::vector<int> zombieMaxHp = doc.GetColumn<int>(3);
	std::vector<int> zombieDamage = doc.GetColumn<int>(4);
	std::vector<float> zombieAttackRate = doc.GetColumn<float>(5);

	//std::vector<ZombieInfo> zombieInfoVec;

	for(int i = 0; i< zombieId.size(); ++i)
	{
		ZombieInfo values;
		values.zombieType = (Zombie::Types)zombieId[i];
		values.textureId = zombieTexture[i];
		values.speed = zombieSpeed[i];
		values.maxHp = zombieMaxHp[i];
		values.damage = zombieDamage[i];
		values.attackRate = zombieAttackRate[i];

		// test code
		//std::cout << (int)zombieId[i] << " " << zombieTexture[i] << " " << zombieSpeed[i] << " " << zombieMaxHp[i] << " " << zombieDamage[i] << " " << zombieAttackRate[i];

		//zombieInfoVec.push_back(values);

		table.insert({ (Zombie::Types)zombieId[i], values });
	}

	return true;
}

void ZombieTable::Release()
{
	table.clear();
}

const ZombieInfo& ZombieTable::Get(Zombie::Types id)
{
	auto find = table.find(id);
	//if (find == table.end()) 예외 throw or 포인터로 변경
	//{
	//	return;
	//}
	return find->second;
}
