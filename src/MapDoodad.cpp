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

#include <EssexEngineLibIsoMap/MapDoodad.h>

EssexEngine::Libs::IsoMap::MapDoodad::MapDoodad(WeakPointer<Context> gameContext, std::string texture, int x, int y, int w, int h)
:MapObject() {
    entities = std::vector<UniquePointer<Daemons::Gfx::Entity>>();
    currentAnimationFrame = 0;
    
    UniquePointer<Daemons::Gfx::Entity> entity = gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetEntity(
        gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetSprite(
            gameContext->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(texture),
            x,
            y,
            w,
            h
        )
    );

    entities.push_back(std::move(entity));
}

EssexEngine::Libs::IsoMap::MapDoodad::~MapDoodad() {}

void EssexEngine::Libs::IsoMap::MapDoodad::Render(WeakPointer<Context> gameContext) {
    WeakPointer<Daemons::Gfx::Entity> entity = entities.at(currentAnimationFrame).ToWeakPointer();

    entity->SetPosition(GetScreenX(), GetScreenY());
    entity->SetScale(GetZoom(), GetZoom());
    gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderEntity(entity);
}

void EssexEngine::Libs::IsoMap::MapDoodad::Update() {
}
