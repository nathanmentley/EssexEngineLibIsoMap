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

#include <EssexEngineLibIsoMap/MapCharacterDef.h>

EssexEngine::Libs::IsoMap::MapCharacterDef::MapCharacterDef(std::string _filenamebody, std::string _filenamehead, std::string _filenameweapon) {
    filenamebody = _filenamebody;
    filenamehead = _filenamehead;
    filenameweapon = _filenameweapon;
}

EssexEngine::Libs::IsoMap::MapCharacterDef::~MapCharacterDef() {
}

std::string EssexEngine::Libs::IsoMap::MapCharacterDef::GetFilenameBody() {
    return filenamebody;
}

std::string EssexEngine::Libs::IsoMap::MapCharacterDef::GetFilenameHead() {
    return filenamehead;
}

std::string EssexEngine::Libs::IsoMap::MapCharacterDef::GetFilenameWeapon() {
    return filenameweapon;
}

