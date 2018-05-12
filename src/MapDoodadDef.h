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
    class MapDoodadDef
    {
    public:
        MapDoodadDef(std::string _filename, int _x, int _y, int _w, int _h);
        ~MapDoodadDef();
        
        std::string GetFilename();
        int GetX();
        int GetY();
        int GetW();
        int GetH();
    protected:
    private:
        std::string filename;
        int x;
        int y;
        int w;
        int h;
    };
}}};
