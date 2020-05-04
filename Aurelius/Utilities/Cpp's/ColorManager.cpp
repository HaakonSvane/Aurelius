//
//  ColorManager.cpp
//  Aurelius
//
//  Created by Haakon Svane on 17/07/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#include "ColorManager.hpp"


Color::Color():
    Color{COLOR_MAP.at(COLORS::DEFAULT)}
{}

Color::Color(const Color& other){
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b):
    Color{r, g, b, 0xFF}
{}

bool Color::operator==(const Color& other) const{
    if (r == other.r && g == other.g && b == other.b && a == other.a){
        return true;
    }else{
        return false;
    }
}

ColorPalette::ColorPalette(){
    for(int i = 0; i < CONSTANTS::BIT_DEPTH_ART; i++){
        colors[i] = COLOR_MAP.at(DEFAULT);
    }
}

ColorPalette::ColorPalette(const ColorPalette& other){
    operator=(other);
}

void ColorPalette::operator=(const ColorPalette& other){
    for(int i = 0; i < CONSTANTS::BIT_DEPTH_ART; i++){
        colors[i] = other.colors[i];
    }
}

void ColorPalette::insert(Uint8 index, COLORS c){
    colors[index] = COLOR_MAP.at(c);
}

void ColorPalette::remove(Uint8 index){
    colors[index] = COLOR_MAP.at(COLORS::DEFAULT);
}

Uint32 ColorPalette::get_color(const Uint8 index) const
{
    if (index < 0 || index > CONSTANTS::BIT_DEPTH_ART) throw std::invalid_argument("Input index is not valid");
    Color c = colors[index];
    return static_cast<Uint32>((c.r << 24) + (c.g << 16) + (c.b << 8) + (0xFF << 0));
}

std::ostream& operator<<(std::ostream& os, const Color& c)
{
    os << "R: " << std::hex << c.r << "\tG" << std::hex << c.g << "\tB: " << std::hex << c.b << "\tA: " << std::hex << c.a << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const ColorPalette& cp)
{
    os << "Index:\tHex:\n";
    for (int i = 0; i <= CONSTANTS::BIT_DEPTH_ART; i++){
        os << i << "\t\t" << std::hex << cp.get_color(i) << "\n";
    }
    return os;
}

std::size_t std::hash<Color>::operator()(const Color &c) const{
    std::size_t r = std::hash<Uint8>{}(c.r);
    std::size_t g = std::hash<Uint8>{}(c.g);
    std::size_t b = std::hash<Uint8>{}(c.b);
    std::size_t a = std::hash<Uint8>{}(c.a);
    return ((r^(g<<1)>>1)^((b<<1))>>1)^(a<<1);
}


namespace ColorFunctions {
Uint32 Color_to_Uint32(const Color c){
    return static_cast<Uint32>((c.r << 24) + (c.g << 16) + (c.b << 8) + (c.a << 0));
}
Color Uint32_to_Color(const Uint32 c){
    Uint32 mask = 0xFF;
    const Uint8 r = (c&(mask<<24)) >> 24;
    const Uint8 g = (c&(mask<<16)) >> 16;
    const Uint8 b = (c&(mask<<8)) >> 8;
    const Uint8 a = c&mask;
    return Color{r, g, b, a};
}

}
