#include "stdafx.h"
#include "PlantManager.h"

#include "Bean.h"
#include "double_bean.h"

void PlantManager::setSunmanager(shared_ptr<SunManager> sm)
{
    sun_manager = sm;
}
void PlantManager::setPbmanager(shared_ptr<PbManager> sm)
{
    pb_manager = sm;
}

void PlantManager::Update()
{
    int index=0;
    vector<int> removeIndex;
    for(auto& p:plants)
    {
        p->Update();
        if(!p->GetActive())
        {
            removeIndex.insert(removeIndex.begin(),index);
        }
        index+=1;
    }
    for(auto& p:removeIndex)
    {
        plants.erase(plants.begin()+p);
    }
}

void PlantManager::Show()
{
    for(auto& p:plants)
    {
        p->Show();
    }
}

void PlantManager::OnMouseMove(Vector2 point)
{
    if(!plants.empty() && !plants.back()->GetIsPlace())
    {
        plants.back()->SetPositionByCenter(point);
    }
}

void PlantManager::OnLButtonDown(Vector2 coordinate)
{
    if(!plants.empty() && !plants.back()->GetIsPlace())
    {
        plants.back()->SetCoordinate(coordinate);
        plants.back()->SetPosition(
        {
            static_cast<float>( BoardLeft +BLOCK_WIDTH*static_cast<int>(coordinate.x)),
            static_cast<float>(BoardTop +BLOCK_HEIGHT*static_cast<int>(coordinate.y))
        });
        plants.back()->SetIsPlace(true);
    }
}

void PlantManager::MakePlant(PlantType type, Vector2 position)
{
    if(!plants.empty()&&!plants.back()->GetIsPlace())
    {
        return;
    }
    //todo
    std::shared_ptr<Plant> p;
    switch (type)
    {
    case PlantType::SUN_FLOWER:
        {
            auto s=make_shared<Sunflower>();
            s->Init();
            s->setSunmanager(sun_manager);
            s->SetAttackCounter(3000);
            p=s;
        }
        break;
    case PlantType::BEAN_PLANT:
        {
            auto bean=make_shared<Bean>();
            bean->Init();
            bean->SetAttackCounter(1500);
            bean->SetPbManager(pb_manager);
            p=bean;
        }
        break;
    case PlantType::NUT_PLANT: 
        {
            auto nut=make_shared<Nut>();
            nut->Init();
            p=nut;
        }
        break;
    case PlantType::DOUBLE_BEAN:
        {
            
            auto bean=make_shared<Double_bean>();
            bean->Init();
            bean->SetAttackCounter(1500);
            bean->SetPbManager(pb_manager);
            p=bean;
        }
        break;
	case PlantType::CHILI_PLANT:
		{
			auto chili = make_shared<Chili>();
			chili->Init();
			chili->SetAttackCounter(1500);
			p = chili;
		}
		break;
    default: ;
    }
    p->SetPositionByCenter(position);
    plants.push_back(p);
}

void PlantManager::clear_plant()
{
    plants.clear();
}

int PlantManager::plant_size()
{
    return (int)plants.size();
}
