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

#include <EssexEngineLibIsoMap/MapCharacterAction.h>

EssexEngine::Libs::IsoMap::MapCharacterAction::MapCharacterAction(MapCharacterActionTypes _type, WeakPointer<MapObject> _target)
{
    type = _type;
    target = _target;
    isRunning = false;
    isCancelled = false;
}

EssexEngine::Libs::IsoMap::MapCharacterAction::~MapCharacterAction()
{
}

bool EssexEngine::Libs::IsoMap::MapCharacterAction::GetIsRunning() {
    return isRunning;
}

void EssexEngine::Libs::IsoMap::MapCharacterAction::Start() {
    isRunning = true;
}

bool EssexEngine::Libs::IsoMap::MapCharacterAction::GetIsCancelled() {
    return isCancelled;
}

void EssexEngine::Libs::IsoMap::MapCharacterAction::Cancel() {
    isCancelled = true;
}

EssexEngine::Libs::IsoMap::MapCharacterActionTypes EssexEngine::Libs::IsoMap::MapCharacterAction::GetType() {
    return type;
}

EssexEngine::WeakPointer<EssexEngine::Libs::IsoMap::MapObject> EssexEngine::Libs::IsoMap::MapCharacterAction::GetTarget() {
    return target;
}
