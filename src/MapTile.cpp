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

EssexEngine::Libs::IsoMap::MapTile::MapTile(SharedPointer<Daemons::Gfx::ISprite> _sprite, bool _blocking)
{
    blocking = _blocking;
    sprite = _sprite;
}

EssexEngine::Libs::IsoMap::MapTile::~MapTile()
{
}

EssexEngine::WeakPointer<EssexEngine::Daemons::Gfx::ISprite> EssexEngine::Libs::IsoMap::MapTile::GetSprite() {
    return sprite.GetWeakPointer();
}

bool EssexEngine::Libs::IsoMap::MapTile::IsBlocking() {
    return blocking;
}
