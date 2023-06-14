#pragma once
#include <vector>

#include "../Library/gameutil.h"

class CardManager
{
    std::vector<pair<game_framework::CMovingBitmap,int>> cards;
    vector<int> price;
    vector<vector<string>> path;
    vector<pair<int,int>> cardPosition;
public:
    CardManager(){
        path.push_back({"Plants_vs_Zombies_Image/card/sunflower_card/sunflower_card.bmp" , "Plants_vs_Zombies_Image/card/sunflower_card/sunflower_gray_card.bmp" });
        cardPosition={{240,0}};
        price = {50};
    }
    void LoadCard()
    {
        for(int i = 0;i<(int)path.size();i++)
        {
            game_framework::CMovingBitmap card;
            card.LoadBitmapByString(path[i], RGB(255, 255, 255));
            card.SetTopLeft(cardPosition[i].first, cardPosition[i].second);
            cards.push_back({card,price[i]});
        }
    }
    void show(int money){
        for(auto& c: cards)
        {
            if(money>=c.second)
            {
                c.first.ShowBitmap();
            }
        }
    }
    int GetItem(int x,int y){
        int item =0;
        for(auto& c: cards)
        {
            if(game_framework::CMovingBitmap::IsCardClick(x,y,c.first))
            {
                return item;
            }
            item++;
        }
        return -1;
    }
};
