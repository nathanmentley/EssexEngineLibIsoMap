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

#include <EssexEngineLibIsoMap/MapPlayerCharacter.h>

EssexEngine::Libs::IsoMap::MapPlayerCharacter::MapPlayerCharacter(WeakPointer<Context> gameContext, std::string bodyTexture, std::string headTexture, std::string weaponTexture)
:MapCharacter(gameContext, bodyTexture, headTexture, weaponTexture) {
    SetTeam(0);
}

EssexEngine::Libs::IsoMap::MapPlayerCharacter::~MapPlayerCharacter() {
}
