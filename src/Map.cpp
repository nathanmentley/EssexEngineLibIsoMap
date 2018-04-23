/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineLibIsoMap/Map.h>

EssexEngine::Libs::IsoMap::Map::Map(WeakPointer<Context> _gameContext, WeakPointer<Daemons::Json::IJsonDocument> _gameDocument, WeakPointer<Daemons::Json::IJsonDocument> _mapDocument) {
    gameContext = _gameContext;
    
    mapData = WeakPointer<MapData>(new MapData(_gameContext, _gameDocument, _mapDocument));
    
    InitMap();
    
    zoom = 1;
    currentScreenX = 0;
    currentScreenY = 0;
}

EssexEngine::Libs::IsoMap::Map::~Map() {}

void EssexEngine::Libs::IsoMap::Map::Render(WeakPointer<Daemons::Window::IRenderContext> target) {
    RunMapScripts("render_loop");
    
    //Setup Character
    GetCharacter()->SetZoom(zoom);
    GetCharacter()->SetScreenPosition(
        GetScreenX(target, GetCharacter()->GetX(), GetCharacter()->GetY()),
        GetScreenY(target, GetCharacter()->GetX(), GetCharacter()->GetY())
    );
    
    //Setup and Render Map
    MapTileRTree::BoundingBox bound;
    bound.edges[0].first  = GetScreenX() - 25;
    bound.edges[0].second = GetScreenX() + 25;
    bound.edges[1].first  = GetScreenY() - 25;
    bound.edges[1].second = GetScreenY() + 25;
    
    MapTileRTreeVisitor closeByTiles = mapData->GetTiles(bound);
    
    for (auto tileInfo : closeByTiles.data) {
        WeakPointer<MapTile> tile = mapData->GetTile(tileInfo.id);
        WeakPointer<Daemons::Gfx::Entity> entity = tile->GetEntity();
        
        RStarBoundingBox<2> tileLocation = tileInfo.box;
        double x = tileLocation.edges[0].first;
        double y = tileLocation.edges[1].first;
        
        int screenx = GetScreenX(target, x, y);
        int screeny = GetScreenY(target, x, y);
        
        entity->SetPosition(screenx, screeny);
        entity->SetScale(zoom, zoom);
        
        gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderEntity(target, entity);
    }
    
    //Setup and Render Doodads
    DoodadRTree::BoundingBox doodadBounds;
    doodadBounds.edges[0].first  = GetScreenX() - 25;
    doodadBounds.edges[0].second = GetScreenX() + 25;
    doodadBounds.edges[1].first  = GetScreenY() - 25;
    doodadBounds.edges[1].second = GetScreenY() + 25;
    
    DoodadRTreeVisitor closeByDoodads = mapData->GetDoodads(doodadBounds);
    
    for (auto doodadWrapper : closeByDoodads.data) {
        WeakPointer<MapDoodad> doodad = doodadWrapper.doodad;
        double x = doodad->GetX();
        double y = doodad->GetY();
        
        doodad->SetScreenPosition(GetScreenX(target, x, y), GetScreenY(target, x, y));
        doodad->SetZoom(zoom);
        doodad->Render(gameContext, target);
    }
    
    //Setup and Render Characters
    CharacterRTree::BoundingBox characterBounds;
    characterBounds.edges[0].first  = GetScreenX() - 25;
    characterBounds.edges[0].second = GetScreenX() + 25;
    characterBounds.edges[1].first  = GetScreenY() - 25;
    characterBounds.edges[1].second = GetScreenY() + 25;
    
    CharacterRTreeVisitor closeByCharacters = mapData->GetCharacters(characterBounds);
    
    for (auto characterInfo : closeByCharacters.data) {
        WeakPointer<MapCharacter> character = characterInfo.character;
        double x = character->GetX();
        double y = character->GetY();
        
        character->SetScreenPosition(GetScreenX(target, x, y), GetScreenY(target, x, y));
        character->SetZoom(zoom);
        character->Render(gameContext, target);
    }
}

void EssexEngine::Libs::IsoMap::Map::Update() {
    RunMapScripts("logic_loop");
    
    DoodadRTreeVisitor allDoodads = mapData->GetDoodads();
    for (auto doodadWrapper : allDoodads.data) {
        WeakPointer<MapDoodad> doodad = doodadWrapper.doodad;
        doodad->Update();
    }
    CharacterRTreeVisitor allCharacters = mapData->GetCharacters();
    for (auto characterInfo : allCharacters.data) {
        WeakPointer<MapCharacter> character = characterInfo.character;
        character->Update();
        
        if(!character->IsDead()) {
            if(character->GetQueuedAction().size() > 0) {
                if(!character->GetQueuedAction().front()->GetIsRunning()) {
                    character->GetQueuedAction().front()->Start();
                }
            
                ProcessAction(character, character->GetQueuedAction().front());
                if(CheckActionCompleteStatus(character, character->GetQueuedAction().front()) || character->GetQueuedAction().front()->GetIsCancelled()) {
                    character->GetQueuedAction().pop();
                }
            } else {
                character->SetAnimation(Stance);
                
                if(character != mapData->GetCharacter().Cast<MapCharacter>()) {
                    bool action = false;
                    CharacterRTree::BoundingBox bound;
                    bound.edges[0].first  = character->GetX() - character->GetAttackRange();
                    bound.edges[0].second = character->GetX() + character->GetAttackRange();
                    bound.edges[1].first  = character->GetY() - character->GetAttackRange();
                    bound.edges[1].second = character->GetY() + character->GetAttackRange();
                
                    for (auto closeCharacterInfo : mapData->GetCharacters(bound).data) {
                        WeakPointer<MapCharacter> closeCharacter = closeCharacterInfo.character;
                    
                        if(closeCharacter->GetTeam() != character->GetTeam()) {
                            action = true;
                            character->QueueAction(WeakPointer<MapCharacterAction>(new MapCharacterAction(MapCharacterActionTypes::Attack, closeCharacter.Cast<MapObject>())));
                            break;
                        }
                    }
                    
                    if(!action) {
                        CharacterRTree::BoundingBox bound2;
                        bound2.edges[0].first  = character->GetX() - character->GetSightRange();
                        bound2.edges[0].second = character->GetX() + character->GetSightRange();
                        bound2.edges[1].first  = character->GetY() - character->GetSightRange();
                        bound2.edges[1].second = character->GetY() + character->GetSightRange();
                        
                        for (auto closeCharacterInfo : mapData->GetCharacters(bound2).data) {
                            WeakPointer<MapCharacter> closeCharacter = closeCharacterInfo.character;
                            
                            if(closeCharacter->GetTeam() != character->GetTeam()) {
                                character->QueueAction(WeakPointer<MapCharacterAction>(new MapCharacterAction(MapCharacterActionTypes::MoveTo, closeCharacter.Cast<MapObject>())));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


void EssexEngine::Libs::IsoMap::Map::InitMap() {
    RunMapScripts("init");
}


void EssexEngine::Libs::IsoMap::Map::ProcessAction(WeakPointer<MapCharacter> character, WeakPointer<MapCharacterAction> action) {
    switch(action->GetType()) {
        case MoveNorth:
            mapData->MoveCharacter(character, North);
            break;
        case MoveSouth:
            mapData->MoveCharacter(character, South);
            break;
        case MoveEast:
            mapData->MoveCharacter(character, East);
            break;
        case MoveWest:
            mapData->MoveCharacter(character, West);
            break;
        case MoveNorthEast:
            mapData->MoveCharacter(character, NorthEast);
            break;
        case MoveNorthWest:
            mapData->MoveCharacter(character, NorthWest);
            break;
        case MoveSouthEast:
            mapData->MoveCharacter(character, SouthEast);
            break;
        case MoveSouthWest:
            mapData->MoveCharacter(character, SouthWest);
            break;
        case MoveTo:
            ProcessPath(character, action->GetTarget()->GetX(), action->GetTarget()->GetY());
            break;
        case Attack:
            character->SetAnimation(MeleeSwing);
            break;
    }
}
bool EssexEngine::Libs::IsoMap::Map::CheckActionCompleteStatus(WeakPointer<MapCharacter> character, WeakPointer<MapCharacterAction> action) {
    if(action->GetType() == MoveTo) {
        if(floor(character->GetX()) != floor(action->GetTarget()->GetX()) || floor(character->GetY()) != floor(action->GetTarget()->GetY())) {
            return false;
        }
    } else if (action->GetType() == Attack) {
        if(action->GetTarget().HasValue()) {
            WeakPointer<MapCharacter> otherCharacter = action->GetTarget().Cast<MapCharacter>();
            
            if(!otherCharacter->IsDead() && !(character->GetAttackRange() < GetDistence(character.Cast<MapObject>(), otherCharacter.Cast<MapObject>()))) {
                return false;
            }
        }
    }
    
    return true;
}

void EssexEngine::Libs::IsoMap::Map::ZoomIn(){
    if(zoom <= 5) {
        zoom += .1;
    }
}
void EssexEngine::Libs::IsoMap::Map::ZoomOut(){
    if(zoom > .2){
        zoom -= .1;
    }
}

EssexEngine::WeakPointer<EssexEngine::Libs::IsoMap::MapPlayerCharacter> EssexEngine::Libs::IsoMap::Map::GetCharacter() {
    return mapData->GetCharacter();
}

void EssexEngine::Libs::IsoMap::Map::ProcessPath(WeakPointer<MapCharacter> character, int x, int y) {
    
}

double EssexEngine::Libs::IsoMap::Map::GetDistence(WeakPointer<MapObject> obj1, WeakPointer<MapObject> obj2) {
    double dx = obj2->GetX() - obj1->GetX();
    double dy = obj2->GetY() - obj1->GetY();
    
    return sqrt((double) dx*dx + dy*dy);
}

void EssexEngine::Libs::IsoMap::Map::RunMapScripts(std::string scriptCode) {
    std::vector<std::string>* scripts = mapData->GetScripts(scriptCode);
    
    if(scripts != 0) {
        for (auto script = scripts->begin(); script != scripts->end(); ++script)
        {
            gameContext->GetDaemon<Daemons::Script::ScriptDaemon>()->ExecuteScript(*script);
        }
    }
}

int EssexEngine::Libs::IsoMap::Map::GetScreenX(WeakPointer<Daemons::Window::IRenderContext> target, double x, double y) {
    int centerScreenX = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenWidth(target) / 2);
    
    double offsetX = (GetScreenX() - x);
    double offsetY = (GetScreenY() - y);
    
    return centerScreenX + ((offsetX - offsetY) * (MapTile::TILE_WIDTH / 2) * zoom);
}

int EssexEngine::Libs::IsoMap::Map::GetScreenY(WeakPointer<Daemons::Window::IRenderContext> target, double x, double y) {
    int centerScreenY = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenHeight(target) / 2);
    
    double offsetX = (GetScreenX() - x);
    double offsetY = (GetScreenY() - y);
    
    return centerScreenY + ((offsetX + offsetY) * (MapTile::TILE_HEIGHT / 2) * zoom);
}

double EssexEngine::Libs::IsoMap::Map::GetX(WeakPointer<Daemons::Window::IRenderContext> target, int screenX, int screenY) {
    int centerScreenX = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenWidth(target) / 2);
    int centerScreenY = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenHeight(target) / 2);
    
    int tempX = (screenX - centerScreenX);
    int tempY = (screenY - centerScreenY);

    int offsetX = GetScreenX() * MapTile::TILE_WIDTH * zoom;
    int offsetY = GetScreenY() * MapTile::TILE_HEIGHT * zoom;
    
    return ((offsetX - tempX) * MapTile::TILE_WIDTH/2) - ((offsetY - tempY) * MapTile::TILE_HEIGHT);
}

double EssexEngine::Libs::IsoMap::Map::GetY(WeakPointer<Daemons::Window::IRenderContext> target, int screenX, int screenY) {
    int centerScreenX = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenWidth(target) / 2);
    int centerScreenY = (gameContext->GetDaemon<Daemons::Window::WindowDaemon>()->GetScreenHeight(target) / 2);
    
    int tempX = (screenX - centerScreenX);
    int tempY = (screenY - centerScreenY);
    
    int offsetX = GetScreenX() * MapTile::TILE_WIDTH * zoom;
    int offsetY = GetScreenY() * MapTile::TILE_HEIGHT * zoom;
    
    return (((offsetX - tempX) * MapTile::TILE_WIDTH/2) + ((offsetY - tempY) * MapTile::TILE_HEIGHT)) / 2;
}

void EssexEngine::Libs::IsoMap::Map::SetScreenX(double x) {
    currentScreenX = x;
}

void EssexEngine::Libs::IsoMap::Map::SetScreenY(double y) {
    currentScreenY = y;
}

double EssexEngine::Libs::IsoMap::Map::GetScreenX() {
    return currentScreenX;
}

double EssexEngine::Libs::IsoMap::Map::GetScreenY() {
    return currentScreenY;
}
