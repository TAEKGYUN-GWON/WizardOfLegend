#pragma once
#include "Scene.h"
#include <commdlg.h> //OPENFILENAME을 위한 헤더

#define SET_TILE_WIDTH 60
#define SET_TILE_HEIGHT 60

#define SET_TILE_NUM_X 4
#define SET_TILE_NUM_Y 6

class Tile;

struct current
{
    Vector2 imgSize;
    string imgKey;
    Attribute attribute;
};

class Maptool : public Scene
{
private:
    int mapMax_x;
    int mapMax_y;
    Object* _sample;
    vector<Tile*> _vTiles;
    current cur;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void Save();
    void Load();

    void SetUp();
    void SetMap();
    void ClickSetTile();
    void RemoveObject();
};
