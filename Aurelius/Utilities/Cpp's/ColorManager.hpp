//
//  ColorManager.hpp
//  Aurelius
//
//  Created by Haakon Svane on 17/07/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include "Constants.hpp"
#include "Identifications.hpp"
#include <ostream>

// Colors used for the sprites. Last color is used for Keying.
constexpr Uint8 KeyColors[8] = { 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0xFF };


enum COLORS //Prefixes: l = light, d = dark, s = shadow
{
    DEFAULT,
    
    RED,  YELLOW,  PINK,  GREEN,  PURPLE,  ORANGE,  BLUE,  GRAY, WHITE, BLACK,
    lRED, lYELLOW, lPINK, lGREEN, lPURPLE, lORANGE, lBLUE, lGRAY,
    dRED, dYELLOW, dPINK, dGREEN, dPURPLE, dORANGE, dBLUE, dGRAY,
    
    SKIN_1, sSKIN_1,
    SKIN_2, sSKIN_2,
    SKIN_3, sSKIN_3,
    SKIN_4, sSKIN_4,
    SKIN_OUTLINE,
    
    
    dGRASS, GRASS, lGRASS, llGRASS,
    dWATER, WATER, lWATER,
    dSAND, SAND, lSAND,
    dWOOD, WOOD, lWOOD
};

struct Color{
    Color();
    Color(Uint8 r, Uint8 g, Uint8 b);
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color(const Color& other);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    
    bool operator == (const Color& other) const;
};

const std::unordered_map<COLORS, Color> COLOR_MAP{
    
    { DEFAULT,      {0x91, 0x1C, 0x6D} },
    
    { RED,          {0xDE, 0x29, 0x31} },
    { lRED,         {0xF6, 0x5A, 0x59} },
    { dRED,         {0xA4, 0x20, 0x29} },
    
    { YELLOW,       {0xFE, 0xC5, 0x00} },
    { lYELLOW,      {0xFE, 0xDE, 0x00} },
    { dYELLOW,      {0x83, 0x5A, 0x00} },
    
    { PINK,         {0xB0, 0x40, 0x70} },
    { lPINK,        {0xF8, 0xA0, 0xC0} },
    { dPINK,        {0x90, 0x28, 0x60} },
    
    { GREEN,        {0x00, 0x7B, 0x31} },
    { lGREEN,       {0x5A, 0xCD, 0x73} },
    { dGREEN,       {0x00, 0x29, 0x08} },
    
    { PURPLE,       {0x83, 0x4A, 0x9C} },
    { lPURPLE,      {0xBD, 0x83, 0xD5} },
    { dPURPLE,      {0x4A, 0x29, 0x62} },
    
    { ORANGE,       {0xF6, 0x83, 0x10} },
    { lORANGE,      {0xF6, 0xA4, 0x10} },
    { dORANGE,      {0xCD, 0x52, 0x10} },
    
    { BLUE,         {0x39, 0x52, 0x9C} },
    { lBLUE,        {0x62, 0x8B, 0xE6} },
    { dBLUE,        {0x10, 0x29, 0x6A} },
    
    { GRAY,         {0x7F, 0x7F, 0x7F} },
    { lGRAY,        {0xB1, 0xB1, 0xAF} },
    { dGRAY,        {0x41, 0x39, 0x31} },
    
    { WHITE,        {0xFE, 0xFE, 0xFE} },
    { BLACK,        {0x01, 0x01, 0x01} },
    
    { SKIN_1,       {0xFD, 0xE7, 0xCC} },
    { sSKIN_1,      {0xEE, 0xB4, 0x83} },
    
    { SKIN_2,       {0xF6, 0xD5, 0xA4} },
    { sSKIN_2,      {0xDE, 0x94, 0x62} },
    
    { SKIN_3,       {0xEF, 0xD0, 0x74} },
    { sSKIN_3,      {0xEE, 0xB4, 0x7B} },
    
    { SKIN_4,       {0xBD, 0x7B, 0x41} },
    { sSKIN_4,      {0x9C, 0x5A, 0x29} },
    
    { SKIN_OUTLINE, {0x4A, 0x29, 0x18} },
    
    { dGRASS,       {0x28, 0x50, 0x2e} },
    { GRASS,        {0x60, 0x80, 0x38} },
    { lGRASS,       {0x6E, 0xB2, 0x57} },
    { llGRASS,      {0x7E, 0xC2, 0x67} },
    
    { dWATER,       {0x00, 0x00, 0x00} },
    { WATER,        {0x38, 0x80, 0x78} },
    { lWATER,       {0x58, 0xA0, 0x98} },
    
    { dSAND,        {0xaf, 0xa4, 0x4d} },
    { SAND,         {0xcf, 0xc8, 0x91} },
    { lSAND,        {0xe6, 0xe2, 0xc6} },
    
    { dWOOD,        {0x49, 0x32, 0x20} },
    { WOOD,         {0x80, 0x58, 0x38} },
    { lWOOD,        {0xb4, 0x7e, 0x53} }
};





class ColorPalette{
public:
    ColorPalette();
    ColorPalette(const ColorPalette& other);
    void operator =(const ColorPalette& other);
    void insert(Uint8 index, COLORS c);
    void remove(Uint8 index);
    Uint32 get_color(const Uint8 index) const;
private:
    Color colors[CONSTANTS::BIT_DEPTH_ART];
};

std::ostream& operator<<(std::ostream&, const ColorPalette&);
std::ostream& operator<<(std::ostream&, const Color&);


template <>
struct std::hash<Color>{
    std::size_t operator()(const Color& c) const;
};


namespace ColorFunctions {
Uint32 Color_to_Uint32(const Color c);
Color Uint32_to_Color(const Uint32 c);
}
