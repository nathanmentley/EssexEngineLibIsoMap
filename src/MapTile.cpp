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

#include <EssexEngineLibIsoMap/MapTile.h>

EssexEngine::Libs::IsoMap::MapTile::MapTile(UniquePointer<Daemons::Gfx::Entity> _entity, bool _blocking) :
    entity(std::move(_entity)), blocking(_blocking) {}

EssexEngine::Libs::IsoMap::MapTile::~MapTile()
{
}

EssexEngine::WeakPointer<EssexEngine::Daemons::Gfx::Entity> EssexEngine::Libs::IsoMap::MapTile::GetEntity() {
    return entity.ToWeakPointer();
}

bool EssexEngine::Libs::IsoMap::MapTile::IsBlocking() {
    return blocking;
}
