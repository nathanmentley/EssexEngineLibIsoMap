/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineLibIsoMap/MapNPCCharacter.h>

EssexEngine::Libs::IsoMap::MapNPCCharacter::MapNPCCharacter(WeakPointer<Context> gameContext, WeakPointer<Daemons::Window::IRenderContext> target, std::string bodyTexture, std::string headTexture, std::string weaponTexture)
:MapCharacter(gameContext, target, bodyTexture, headTexture, weaponTexture) {
}

EssexEngine::Libs::IsoMap::MapNPCCharacter::~MapNPCCharacter() {
}
