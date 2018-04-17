/*********************************************************************************************************************/
/*!
    @file     IO.h
    @author   sbmrgd

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2018, sbmrgd
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    This entire game is based on a tutorial by Javier L�pez L�pez
    Link: http://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/
*/
/*********************************************************************************************************************/
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
// ------ Includes -----


// ------ Enums -----

enum color { BLACK1, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, ORANGE, PURPLE, WHITE1, GREY, GREY2, COLOR_MAX}; // Colors



const unsigned char paletteLinez[48] = {
0x00,0x00,0x00, //000000
0xFF,0x00,0x00, //FF0000
0x00,0xFF,0x00, //00FF00
0x00,0x00,0xFF, //0000FF

0x00,0xFF,0xFF, //00FFFF
0xFF,0x00,0xFF, //FF00FF
0xFF,0xFF,0x00, //FFFF00
0xFF,0xA5,0x00, //FFA500

0x80,0x00,0x80, //800080
0xFF,0xFF,0xFF, //FFFFFF
0x2F,0x4F,0x4F, //2F4F4F
0x4F,0x4F,0x4F, //4F4F4F

0xD2,0xAA,0x99, //d2aa99
0x6D,0xC2,0xCA, //6dc2ca
0xDA,0xD4,0x5E, //dad45e
0xDE,0xEE,0xD6  //deeed6
};
// --------------------------------------------------------------------------------
//									 IO
// --------------------------------------------------------------------------------


#endif // IO_H_INCLUDED
