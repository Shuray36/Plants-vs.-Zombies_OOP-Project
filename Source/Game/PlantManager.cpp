#include "stdafx.h"
#include "PlantManager.h"

void PlantManager::setSunmanager(shared_ptr<SunManager> sm)
{
    sun_manager = sm;
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
        plants.back()->SetTopLeft(
            BoardLeft +BLOCK_WIDTH*static_cast<int>(coordinate.x),
            BoardTop +BLOCK_HEIGHT*static_cast<int>(coordinate.y));
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
    case PlantType::BEAN_PLANT: break;
    case PlantType::NUT_PLANT: 
        {
            auto nut=make_shared<Nut>();
            nut->Init();
            p=nut;
        }
        break;
    case PlantType::DOUBLE_BEAN: break;
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
    return plants.size();
}
