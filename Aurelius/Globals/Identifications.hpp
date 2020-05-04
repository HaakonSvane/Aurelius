//
//  Identifications.hpp
//  Aurelius
//
//  Created by Haakon Svane on 13/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <unordered_map>
#include "Vector2D.hpp"


namespace ID
{
enum PERIPHERALS {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Æ, Ø, Å,
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, æ, ø, å,
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SPACE, EXCL, QUOT, HASH,
    DOLLAR, PERC, AMPR, PLUS, MINUS, COLON, SCOLON, EQUAL, POINT, COMMA, SLASH, FSLASH, LPAR, RPAR,
    
    
};


enum class RENDER_LAYER{
    NONE, BACKGROUND, TILE, WORLD_OBJECT, UI
};
    
enum class SPRITES_ID {
    
    NONE,
    
//      MOBS
    PLAYER,
    
//      BLOCKS
    GRASS, WATER, STONE, SAND,
    
//      SCENERY
    FLOWER, TREE,
    
//      PERIPHERALS
    s8_LETTERS_SYMBOLS, s16_LETTERS_SYMBOLS, CONTAINER_FRAME,
    
//      EFFECTS
    MEDIUM_SHADOW, BIG_SHADOW
};


// TODO: CHECK PERFORMANCE ON INLINED FUNCTION
inline std::string ID_to_string(const SPRITES_ID id){
    switch(id){
        case SPRITES_ID::PLAYER: return "[Player]"; break;
        case SPRITES_ID::GRASS: return "[Grass block]"; break;
        case SPRITES_ID::WATER: return "[Water block]"; break;
        case SPRITES_ID::STONE: return "[Stone block]"; break;
        case SPRITES_ID::SAND: return "[Sand block]"; break;
        case SPRITES_ID::FLOWER: return "[Flower block]"; break;
        case SPRITES_ID::TREE: return "[Tree]"; break;
        case SPRITES_ID::s8_LETTERS_SYMBOLS: return "[8bit Letters/symbols]"; break;
        case SPRITES_ID::s16_LETTERS_SYMBOLS: return "[16 bit Letters/symbols]"; break;
        case SPRITES_ID::CONTAINER_FRAME: return "[Container frame]"; break;
        case SPRITES_ID::MEDIUM_SHADOW: return "[Medium Shadow]"; break;
        case SPRITES_ID::BIG_SHADOW: return "[Big Shadow]"; break;
        default: return "[DEFAULT]"; break;
    }
    
}

enum class TYPES {
    MOBS, BLOCKS, SCENERY, PERIPHERALS, EFFECTS
};

const std::unordered_map<SPRITES_ID, TYPES> SPRITE_TYPES{
    {SPRITES_ID::PLAYER, TYPES::MOBS},
    
    {SPRITES_ID::GRASS, TYPES::BLOCKS}, {SPRITES_ID::WATER, TYPES::BLOCKS}, {SPRITES_ID::STONE, TYPES::BLOCKS}, {SPRITES_ID::SAND, TYPES::BLOCKS},
    
    {SPRITES_ID::FLOWER, TYPES::SCENERY}, {SPRITES_ID::TREE, TYPES::SCENERY},
    
    {SPRITES_ID::s8_LETTERS_SYMBOLS, TYPES::PERIPHERALS}, {SPRITES_ID::s16_LETTERS_SYMBOLS, TYPES::PERIPHERALS}, {SPRITES_ID::CONTAINER_FRAME, TYPES::PERIPHERALS},
    
    {SPRITES_ID::MEDIUM_SHADOW, TYPES::EFFECTS}, {SPRITES_ID::BIG_SHADOW, TYPES::EFFECTS}
};

const std::unordered_map<SPRITES_ID, Vector2D<int>> SPRITESHEET_LOC{
    {SPRITES_ID::PLAYER,                {1,     62}  },
    
    {SPRITES_ID::GRASS,                 {1,     42}  },
    {SPRITES_ID::WATER,                 {21,    58}  },
    {SPRITES_ID::STONE,                 {16,    42}  },
    {SPRITES_ID::SAND,                  {11,    52}  },
    {SPRITES_ID::FLOWER,                {12,    44}  },
    
    {SPRITES_ID::TREE,                  {1,     112} },
    
    {SPRITES_ID::s8_LETTERS_SYMBOLS,    {1,     86}  },
    {SPRITES_ID::s16_LETTERS_SYMBOLS,   {1,     85}  },
    {SPRITES_ID::CONTAINER_FRAME,       {641,   676} },
    
    {SPRITES_ID::MEDIUM_SHADOW,         {1,     34}  },
    {SPRITES_ID::BIG_SHADOW,            {65,    164} }
};



enum Controllers{
    KEYBOARD_MOUSE, GAME_CONTROLLER
};

enum Keys{
    KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ATTACK,
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
};

const std::unordered_map<SDL_Keycode, Keys> KEYBOARD_MAP{
    {SDLK_w, KEY_UP}, {SDLK_s, KEY_DOWN}, {SDLK_a, KEY_LEFT}, {SDLK_d, KEY_RIGHT},
    {SDLK_SPACE, KEY_ATTACK},
    {SDLK_1, KEY_1}, {SDLK_2, KEY_2}, {SDLK_3, KEY_3}, {SDLK_4, KEY_4}, {SDLK_5, KEY_5},
    {SDLK_6, KEY_6}, {SDLK_7, KEY_7}, {SDLK_8, KEY_8}, {SDLK_9, KEY_9}, {SDLK_0, KEY_0},
};

enum Move_dirs{
    MOVE_UP, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_NONE
};

enum class Anim_Modes
{
    /*
     *
     *    ANIM_UP:      Animator iterates upwards (in value) and resets to first frame at the last frame
     *    ANIM_DOWN:    Animator iterates downwards (in value) and resets to the last frame at the first frame.
     *    ANIM_OSC:     Animator oscillates between first frame and last frame starting at the first
     *    ANIM_FOIL:    Animator oscillates between 0 and a number k such that k_(n+1) = k_(n) + 1 until it reaches last frame, where it resets to first state. Example:                         0-1-0-2-0-3-0-1-0-2... /7410
     *
     *    ANIM_RAND:    Animator selects the next frame randomly based on a uniform probability distribution
     *
     */
    
    ANIM_UP, ANIM_DOWN, ANIM_OSC, ANIM_FOIL, ANIM_RAND
    
};


const std::unordered_map<int8_t, PERIPHERALS> ASCII_CODES{
    {65, A},        {66, B},        {67, C},        {68, D},        {69, E},        {70, F},        {71, G},
    {72, H},        {73, I},        {74, J},        {75, K},        {76, L},        {77, M},        {78, N},
    {79, O},        {80, P},        {81, Q},        {82, R},        {83, S},        {84, T},        {85, U},
    {86, V},        {87, W},        {88, X},        {89, Y},        {90, Z},        {-58, Æ},       {-40, Ø},
    {-59, Å},       {97, a},        {98, b},        {99, c},        {100, d},       {101, e},       {102, f},
    {103, g},       {104, h},       {105, i},       {106, j},       {107, k},       {108, l},       {109, m},
    {110, n},       {111, o},       {112, p},       {113, q},       {114, r},       {115, s},       {116, t},
    {117, u},       {118, v},       {119, w},       {120, x},       {121, y},       {122, z},       {-26, æ},
    {-8, ø},        {-27, Å},       {48, ZERO},     {49, ONE},      {50, TWO},      {51, THREE},    {52, FOUR},
    {53, FIVE},     {54, SIX},      {55, SEVEN},    {56, EIGHT},    {57, NINE},     {32, SPACE},    {33, EXCL},
    {34, QUOT},     {35, HASH},     {36, DOLLAR},   {37, PERC},     {38, AMPR},     {43, PLUS},     {45, MINUS},
    {58, COLON},    {59, SCOLON},   {61, EQUAL},    {46, POINT},    {44, COMMA},    {47, SLASH},    {92, FSLASH},
    {40, LPAR},     {41, RPAR},
    
};
}
