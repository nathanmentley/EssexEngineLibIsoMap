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
#pragma once

#include <string>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapCharacterDef
    {
    public:
        MapCharacterDef(std::string _filenamebody, std::string _filenamehead, std::string _filenameweapon);
        ~MapCharacterDef();
        
        std::string GetFilenameBody();
        std::string GetFilenameHead();
        std::string GetFilenameWeapon();
    protected:
    private:
        std::string filenamebody;
        std::string filenamehead;
        std::string filenameweapon;
    };
}}};
