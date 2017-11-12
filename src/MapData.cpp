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

#include <EssexEngineLibIsoMap/MapData.h>

EssexEngine::Libs::IsoMap::MapData::MapData(WeakPointer<Context> _gameContext, WeakPointer<Daemons::Json::IJsonDocument> _gameDocument, WeakPointer<Daemons::Json::IJsonDocument> _mapDocument) {
    gameContext = _gameContext;
    
    tiles = std::map<int, std::unique_ptr<MapTile>>();
    
    doodadDefs = std::map<int, std::unique_ptr<MapDoodadDef>>();
    characterDefs = std::map<int, std::unique_ptr<MapCharacterDef>>();
    
    map = MapTileRTree();
    doodads = DoodadRTree();
    characters = CharacterRTree();
    
    scripts = std::map<std::string, std::vector<std::string>>();
    
    //Load Map File
    gameDocument = _gameDocument;
    mapDocument = _mapDocument;
    
    LoadTiles();
    LoadDoodadDefs();
    LoadCharacterDefs();
    
    LoadMapTiles();
    LoadDoodads();
    LoadNPCs();
    LoadPlayer();
    LoadScripts();
}

EssexEngine::Libs::IsoMap::MapData::~MapData() {
}

EssexEngine::WeakPointer<EssexEngine::Libs::IsoMap::MapTile> EssexEngine::Libs::IsoMap::MapData::GetTile(int id) {
    return EssexEngine::WeakPointer<MapTile>(tiles[id].get());
}

EssexEngine::Libs::IsoMap::MapTileRTreeVisitor EssexEngine::Libs::IsoMap::MapData::GetTiles(MapTileRTree::BoundingBox bounds) {
    return map.Query(MapTileRTree::AcceptOverlapping(bounds), MapTileRTreeVisitor());
}

EssexEngine::Libs::IsoMap::DoodadRTreeVisitor EssexEngine::Libs::IsoMap::MapData::GetDoodads(DoodadRTree::BoundingBox bounds) {
    return doodads.Query(DoodadRTree::AcceptOverlapping(bounds), DoodadRTreeVisitor());
}

EssexEngine::Libs::IsoMap::CharacterRTreeVisitor EssexEngine::Libs::IsoMap::MapData::GetCharacters(CharacterRTree::BoundingBox bounds) {
    return characters.Query(CharacterRTree::AcceptOverlapping(bounds), CharacterRTreeVisitor());
}

EssexEngine::Libs::IsoMap::DoodadRTreeVisitor EssexEngine::Libs::IsoMap::MapData::GetDoodads() {
    return doodads.Query(DoodadRTree::AcceptAny(), DoodadRTreeVisitor());
}

EssexEngine::Libs::IsoMap::CharacterRTreeVisitor EssexEngine::Libs::IsoMap::MapData::GetCharacters() {
    return characters.Query(CharacterRTree::AcceptAny(), CharacterRTreeVisitor());
}

void EssexEngine::Libs::IsoMap::MapData::AddCharacter(WeakPointer<MapCharacter> characeter, CharacterRTree::BoundingBox box) {
    characters.Insert(characeter, box);
}

bool EssexEngine::Libs::IsoMap::MapData::DetectCollision(WeakPointer<MapCharacter> character, CharacterDirections direction, double &newX, double &newY) {
    newX = character->GetX();
    newY = character->GetY();
    double speed = character->GetSpeed();
    
    MapTileRTree::BoundingBox bound;
    DoodadRTree::BoundingBox doodadBound;
    CharacterRTree::BoundingBox charBound;
    
    switch(direction) {
        case North:
            bound.edges[0].first  = floor(newX);
            bound.edges[0].second = ceil(newX + speed);
            bound.edges[1].first  = floor(newY);
            bound.edges[1].second = ceil(newY + speed);
            doodadBound.edges[0].first  = floor(newX);
            doodadBound.edges[0].second = ceil(newX + speed);
            doodadBound.edges[1].first  = floor(newY);
            doodadBound.edges[1].second = ceil(newY + speed);
            charBound.edges[0].first  = floor(newX);
            charBound.edges[0].second = ceil(newX + speed);
            charBound.edges[1].first  = floor(newY);
            charBound.edges[1].second = ceil(newY + speed);
            
            newX += speed;
            newY += speed;
            break;
        case South:
            bound.edges[0].first  = floor(newX - speed);
            bound.edges[0].second = ceil(newX);
            bound.edges[1].first  = floor(newY - speed);
            bound.edges[1].second = ceil(newY);
            doodadBound.edges[0].first  = floor(newX - speed);
            doodadBound.edges[0].second = ceil(newX);
            doodadBound.edges[1].first  = floor(newY - speed);
            doodadBound.edges[1].second = ceil(newY);
            charBound.edges[0].first  = floor(newX - speed);
            charBound.edges[0].second = ceil(newX);
            charBound.edges[1].first  = floor(newY - speed);
            charBound.edges[1].second = ceil(newY);
            
            newX -= speed;
            newY -= speed;
            break;
        case East:
            bound.edges[0].first  = floor(newX - speed);
            bound.edges[0].second = ceil(newX);
            bound.edges[1].first  = floor(newY);
            bound.edges[1].second = ceil(newY + speed);
            doodadBound.edges[0].first  = floor(newX - speed);
            doodadBound.edges[0].second = ceil(newX);
            doodadBound.edges[1].first  = floor(newY);
            doodadBound.edges[1].second = ceil(newY + speed);
            charBound.edges[0].first  = floor(newX - speed);
            charBound.edges[0].second = ceil(newX);
            charBound.edges[1].first  = floor(newY);
            charBound.edges[1].second = ceil(newY + speed);
            
            newX -= speed;
            newY += speed;
            break;
        case West:
            bound.edges[0].first  = floor(newX);
            bound.edges[0].second = ceil(newX + speed);
            bound.edges[1].first  = floor(newY - speed);
            bound.edges[1].second = ceil(newY);
            doodadBound.edges[0].first  = floor(newX);
            doodadBound.edges[0].second = ceil(newX + speed);
            doodadBound.edges[1].first  = floor(newY - speed);
            doodadBound.edges[1].second = ceil(newY);
            charBound.edges[0].first  = floor(newX);
            charBound.edges[0].second = ceil(newX + speed);
            charBound.edges[1].first  = floor(newY - speed);
            charBound.edges[1].second = ceil(newY);
            
            newX += speed;
            newY -= speed;
            break;
        case NorthEast:
            bound.edges[0].first  = floor(newX);
            bound.edges[0].second = ceil(newX + speed);
            bound.edges[1].first  = floor(newY);
            bound.edges[1].second = ceil(newY + speed);
            doodadBound.edges[0].first  = floor(newX);
            doodadBound.edges[0].second = ceil(newX + speed);
            doodadBound.edges[1].first  = floor(newY);
            doodadBound.edges[1].second = ceil(newY + speed);
            charBound.edges[0].first  = floor(newX);
            charBound.edges[0].second = ceil(newX + speed);
            charBound.edges[1].first  = floor(newY);
            charBound.edges[1].second = ceil(newY + speed);
            
            newY += speed;
            break;
        case NorthWest:
            bound.edges[0].first  = floor(newX);
            bound.edges[0].second = ceil(newX + speed);
            bound.edges[1].first  = floor(newY);
            bound.edges[1].second = ceil(newY + speed);
            doodadBound.edges[0].first  = floor(newX);
            doodadBound.edges[0].second = ceil(newX + speed);
            doodadBound.edges[1].first  = floor(newY);
            doodadBound.edges[1].second = ceil(newY + speed);
            charBound.edges[0].first  = floor(newX);
            charBound.edges[0].second = ceil(newX + speed);
            charBound.edges[1].first  = floor(newY);
            charBound.edges[1].second = ceil(newY + speed);
            
            newX += speed;
            break;
        case SouthWest:
            bound.edges[0].first  = floor(newX - speed);
            bound.edges[0].second = ceil(newX);
            bound.edges[1].first  = floor(newY - speed);
            bound.edges[1].second = ceil(newY);
            doodadBound.edges[0].first  = floor(newX - speed);
            doodadBound.edges[0].second = ceil(newX);
            doodadBound.edges[1].first  = floor(newY - speed);
            doodadBound.edges[1].second = ceil(newY);
            charBound.edges[0].first  = floor(newX - speed);
            charBound.edges[0].second = ceil(newX);
            charBound.edges[1].first  = floor(newY - speed);
            charBound.edges[1].second = ceil(newY);
            
            newY -= speed;
            break;
        case SouthEast:
            bound.edges[0].first  = floor(newX - speed);
            bound.edges[0].second = ceil(newX);
            bound.edges[1].first  = floor(newY - speed);
            bound.edges[1].second = ceil(newY);
            doodadBound.edges[0].first  = floor(newX - speed);
            doodadBound.edges[0].second = ceil(newX);
            doodadBound.edges[1].first  = floor(newY - speed);
            doodadBound.edges[1].second = ceil(newY);
            charBound.edges[0].first  = floor(newX - speed);
            charBound.edges[0].second = ceil(newX);
            charBound.edges[1].first  = floor(newY - speed);
            charBound.edges[1].second = ceil(newY);
            
            newX -= speed;
            break;
    }
    
    //check map
    MapTileRTreeVisitor tilesBetween = map.Query(MapTileRTree::AcceptEnclosing(bound), MapTileRTreeVisitor());
    for (auto tileInfo : tilesBetween.data) {
        if(tiles[tileInfo.id]->IsBlocking()) {
            return true;
        }
    }
    
    //check doodads
    DoodadRTreeVisitor doodadsBetween = doodads.Query(DoodadRTree::AcceptEnclosing(doodadBound), DoodadRTreeVisitor());
    for (auto doodadInfo : doodadsBetween.data) {
        if(doodadInfo.doodad) {
            return true;
        }
    }
    
    //check players (skip self)
    CharacterRTreeVisitor charactersBetween = characters.Query(CharacterRTree::AcceptEnclosing(charBound), CharacterRTreeVisitor());
    for (auto charInfo : charactersBetween.data) {
        if(charInfo.character != character) {
            return true;
        }
    }
    
    return false;
}

bool EssexEngine::Libs::IsoMap::MapData::MoveCharacter(WeakPointer<MapCharacter> character, CharacterDirections direction) {
    double newX;
    double newY;
    
    if(!DetectCollision(character, direction, newX, newY)) {
        character->SetDirection(direction);
        character->SetAnimation(Running);
        
        characters.RemoveItem(character);
        CharacterRTree::BoundingBox charBound;
        charBound.edges[0].first  = newX;
        charBound.edges[0].second = newX + 1;
        charBound.edges[1].first  = newY;
        charBound.edges[1].second = newY + 1;
        characters.Insert(character, charBound);
        character->SetPosition(newX, newY);
    
        return true;
    }
    return false;
}

EssexEngine::WeakPointer<EssexEngine::Libs::IsoMap::MapPlayerCharacter> EssexEngine::Libs::IsoMap::MapData::GetCharacter() {
    return WeakPointer<MapPlayerCharacter>(player.get());
}


int EssexEngine::Libs::IsoMap::MapData::GetMapWidth() {
    return gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(
        mapDocument, "width"
    );
}

int EssexEngine::Libs::IsoMap::MapData::GetMapHeight() {
    return gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(
        mapDocument, "height"
    );
}

std::vector<std::string>* EssexEngine::Libs::IsoMap::MapData::GetScripts(std::string scriptCode) {
    std::map<std::string, std::vector<std::string> >::iterator it = scripts.find(scriptCode);
    if(it != scripts.end())
    {
        //element exists
        return &scripts[scriptCode];
    }
    
    return 0;
}

void EssexEngine::Libs::IsoMap::MapData::LoadTiles() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> tilesInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(gameDocument, "tiles");
    
    int counter = 0;
    
    for(auto& tile : tilesInFile) {
        auto tileInFile = WeakPointer<Daemons::Json::IJsonNode>(tile.get());

        std::string filename = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(tileInFile, "filename");
        
        int spritex = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(tileInFile, "spritexposition");
        int spritey = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(tileInFile, "spriteyposition");
        bool blocking = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetBoolFromNode(tileInFile, "blocking");
        
        tiles[counter++] = std::unique_ptr<MapTile>(
            new MapTile(
                gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetEntity(
                    gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetSprite(
                        gameContext->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(filename),
                        spritex,
                        spritey,
                        MapTile::TILE_WIDTH,
                        MapTile::TILE_HEIGHT
                    )
                ),
                blocking
            )
        );
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadDoodadDefs() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> doodadsInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(gameDocument, "doodads");
    
    int counter = 0;
    for(auto& doodad : doodadsInFile) {
        auto doodadInFile = WeakPointer<Daemons::Json::IJsonNode>(doodad.get());

        std::string filename = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(doodadInFile, "filename");
        int spritex = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "spritexposition");
        int spritey = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "spriteyposition");
        int spritewidth = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "spritewidth");
        int spriteheight = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "spriteheight");
        
        doodadDefs[counter++] = std::unique_ptr<MapDoodadDef>(
            new MapDoodadDef(
                filename,
                spritex,
                spritey,
                spritewidth,
                spriteheight
            )
        );
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadCharacterDefs() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> charactersInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(gameDocument, "characters");
    
    int counter = 0;
    for(auto& character: charactersInFile) {
        auto characterInFile = WeakPointer<Daemons::Json::IJsonNode>(character.get());

        std::string filenamebody = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(characterInFile, "filenamebody");
        std::string filenamehead = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(characterInFile, "filenamehead");
        std::string filenameweapon = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(characterInFile, "filenameweapon");
        
        characterDefs[counter++] = std::unique_ptr<MapCharacterDef>(
            new MapCharacterDef(filenamebody, filenamehead, filenameweapon)
        );
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadMapTiles() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> maptilesInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(mapDocument, "maptiles");
    
    for(auto& maptile : maptilesInFile) {
        auto maptileInFile = WeakPointer<Daemons::Json::IJsonNode>(maptile.get());

        int x = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(maptileInFile, "x");
        int y = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(maptileInFile, "y");
        int tile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(maptileInFile, "tile");
        
        MapTileRTree::BoundingBox bb;
        bb.edges[0].first  = x;
        bb.edges[0].second = x+1;
        bb.edges[1].first  = y;
        bb.edges[1].second = y+1;
        
        map.Insert(tile, bb);
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadDoodads() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> doodadsInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(mapDocument, "doodads");
    
    for(auto& doodad : doodadsInFile) {
        auto doodadInFile = WeakPointer<Daemons::Json::IJsonNode>(doodad.get());

        int doodadsId = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "doodad");
        
        std::string filename = doodadDefs[doodadsId]->GetFilename();
        
        int spritex = doodadDefs[doodadsId]->GetX();
        int spritey = doodadDefs[doodadsId]->GetY();
        int spritew = doodadDefs[doodadsId]->GetW();
        int spriteh = doodadDefs[doodadsId]->GetH();
        
        int x = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "x");
        int y = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "y");
        int w = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "w");
        int h = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(doodadInFile, "h");
        
        DoodadRTree::BoundingBox bbdoodad;
        bbdoodad.edges[0].first  = x;
        bbdoodad.edges[0].second = x+w;
        bbdoodad.edges[1].first  = y;
        bbdoodad.edges[1].second = y+h;
        
        MapDoodad* doodadObj = new MapDoodad(gameContext, filename, spritex, spritey, spriteh, spritew);
        doodadObj->SetPosition(x, y);
        doodads.Insert(
            doodadObj,
            bbdoodad
        );
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadNPCs() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> npcsInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(mapDocument, "npcs");
    
    for(auto& npc : npcsInFile) {
        auto npcInFile = WeakPointer<Daemons::Json::IJsonNode>(npc.get());

        int characterId = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(npcInFile, "character");
        
        std::string filenamebody = characterDefs[characterId]->GetFilenameBody();
        std::string filenamehead = characterDefs[characterId]->GetFilenameHead();
        std::string filenameweapon = characterDefs[characterId]->GetFilenameWeapon();
        
        int x = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(npcInFile, "x");
        int y = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(npcInFile, "y");
        int w = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(npcInFile, "w");
        int h = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(npcInFile, "h");
        
        CharacterRTree::BoundingBox bbchar;
        bbchar.edges[0].first  = x;
        bbchar.edges[0].second = x+w;
        bbchar.edges[1].first  = y;
        bbchar.edges[1].second = y+h;
        
        MapNPCCharacter* npcObj = new MapNPCCharacter(
            gameContext,
            filenamebody,
            filenamehead,
            filenameweapon
        );
        npcObj->SetPosition(x, y);
        AddCharacter(npcObj, bbchar);
    }
}

void EssexEngine::Libs::IsoMap::MapData::LoadPlayer() {
    std::unique_ptr<Daemons::Json::IJsonNode> playerNode = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNode(mapDocument, "player");
    auto playerInFile = WeakPointer<Daemons::Json::IJsonNode>(playerNode.get());

    int characterId = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(playerInFile, "character");
    
    int x = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(playerInFile, "x");
    int y = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(playerInFile, "y");
    int w = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(playerInFile, "w");
    int h = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetIntFromNode(playerInFile, "h");
    
    std::string filenamebody = characterDefs[characterId]->GetFilenameBody();
    std::string filenamehead = characterDefs[characterId]->GetFilenameHead();
    std::string filenameweapon = characterDefs[characterId]->GetFilenameWeapon();
    
    player = std::unique_ptr<MapPlayerCharacter>(
        new MapPlayerCharacter(
            gameContext,
            filenamebody,
            filenamehead,
            filenameweapon
        )
    );
    player->SetPosition(x, y);
    
    CharacterRTree::BoundingBox bbplayer;
    bbplayer.edges[0].first  = x;
    bbplayer.edges[0].second = x+w;
    bbplayer.edges[1].first  = y;
    bbplayer.edges[1].second = y+h;
    
    AddCharacter(WeakPointer<MapPlayerCharacter>(player.get()).Cast<MapCharacter>(), bbplayer);
}

void EssexEngine::Libs::IsoMap::MapData::LoadScripts() {
    std::list<std::unique_ptr<Daemons::Json::IJsonNode>> scriptsInFile = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonNodeArray(mapDocument, "scripts");
    
    for(auto& script : scriptsInFile) {
        auto scriptInFile = WeakPointer<Daemons::Json::IJsonNode>(script.get());
        
        std::string type = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(scriptInFile, "type");
        std::string logic = gameContext->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(scriptInFile, "logic");
        
        std::map<std::string, std::vector<std::string> >::iterator it = scripts.find(type);
        if(it == scripts.end())
        {
            //element doesn't exists
            scripts[type] = std::vector<std::string>();
        }
        
        scripts[type].push_back(logic);
    }
}
