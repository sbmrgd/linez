/*********************************************************************************************************************/
/*!
    @file     Game.cpp
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
#include "Game.h"


/*
======================================
Init
======================================
*/
Game::Game(Board *pBoard, Pieces *pPieces, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
    Pokitto::Display::clear();
	// Game initialization
	InitGame();
}


/*
======================================
Get a random int between to integers

Parameters:
>> pA: First number
>> pB: Second number
======================================
*/
int Game::GetRand(int pA, int pB)
{
	return rand() % (pB - pA + 1) + pA;
}


/*
======================================
Initial parameters of the game
======================================
*/
void Game::InitGame()
{
	// Init random numbers
	srand((unsigned int)Pokitto::core.getTime());

	// First piece
	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);
	DetermineVerticalPosGhost();

	//  Next piece
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BOARD_WIDTH + 4;
	mNextPosY = 5;
}


/*
======================================
Create a random piece
======================================
*/
void Game::CreateNewPiece()
{
	// The new piece
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);
	DetermineVerticalPosGhost();
	// Random next piece
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

/*
==================================================
Determine the vertical position of the ghost piece
==================================================
*/
void Game::DetermineVerticalPosGhost()
{
    mPosY_ghost = mPosY;
    while (mBoard->IsPossibleMovement(mPosX, mPosY_ghost, mPiece, mRotation)){
				mPosY_ghost++;
			}
	mPosY_ghost--;
}

/*
======================================
Draw piece

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
>> pPiece:	Piece to draw
>> pRotation:	1 of the 4 possible rotations
======================================
*/
void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	color mColor;				// Color of the block

	// Obtain the position in pixel in the screen of the block we want to draw
	int mPixelsX = mBoard->GetXPosInPixels(pX);
	int mPixelsY = mBoard->GetYPosInPixels(pY);

	switch (pPiece)
	{
	case 0: mColor = YELLOW; break;
	case 1: mColor = CYAN; break;
	case 2: mColor = ORANGE; break;
	case 3: mColor = BLUE; break;
	case 4: mColor = RED; break;
	case 5: mColor = GREEN; break;
	case 6: mColor = PURPLE; break;
	default: mColor = BLUE;
	}
	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Get the type of the block and draw it with the correct color

			if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0)
            {
                Pokitto::Core::display.setColor(mColor);
                Pokitto::Core::display.fillRectangle(mPixelsX + i * BLOCK_SIZE,
				mPixelsY + j * BLOCK_SIZE,
				BLOCK_SIZE-1, BLOCK_SIZE-2);
            }

		}
	}
}


/*
======================================
Draw piece

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
>> pPiece:	Piece to draw
>> pRotation:	1 of the 4 possible rotations
======================================
*/
void Game::DrawPiece_Ghost(int pX, int pY, int pPiece, int pRotation)
{
	color mColor;				// Color of the block

	// Obtain the position in pixel in the screen of the block we want to draw
	int mPixelsX = mBoard->GetXPosInPixels(pX);
	int mPixelsY = mBoard->GetYPosInPixels(pY);

	 mColor = GREY2;

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Get the type of the block and draw it with the correct color

			if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0)
			{
			    Pokitto::Core::display.setColor(mColor);
                Pokitto::Core::display.drawRectangle(mPixelsX + i * BLOCK_SIZE,
				mPixelsY + j * BLOCK_SIZE,
				BLOCK_SIZE-2, BLOCK_SIZE-2);
			}

		}
	}
}


/*
======================================
Draw board

Draw the two lines that delimit the board
======================================
*/
void Game::DrawBoard()
{
	// Calculate the limits of the board in pixels
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	// Check that the vertical margin is not to small
	//assert (mY > MIN_VERTICAL_MARGIN);

	// Rectangles that delimits the board
	Pokitto::Core::display.setColor(WHITE1);
    Pokitto::Core::display.fillRectangle(mX1 - BOARD_LINE_WIDTH, mY, BOARD_LINE_WIDTH, mScreenHeight - 1-mY);
    Pokitto::Core::display.fillRectangle(mX2, mY, BOARD_LINE_WIDTH, mScreenHeight - 1-mY);

	// Rectangles that delimit the next piece
	Pokitto::Core::display.fillRectangle(mX2, mBoard->GetYPosInPixels(mNextPosY + 2),mBoard->GetXPosInPixels(mNextPosX - 1) + 2-mX2, BOARD_LINE_WIDTH);
	Pokitto::Core::display.fillRectangle(mBoard->GetXPosInPixels(mNextPosX - 1) - 2, mBoard->GetYPosInPixels(mNextPosY - 1) - 2, mBoard->GetXPosInPixels(mNextPosX + 5)-mBoard->GetXPosInPixels(mNextPosX - 1) + 4, mBoard->GetYPosInPixels(mNextPosY + 5)-mBoard->GetYPosInPixels(mNextPosY - 1) + 4);
	Pokitto::Core::display.setColor(BLACK1);
	Pokitto::Core::display.fillRectangle(mBoard->GetXPosInPixels(mNextPosX - 1) + 2, mBoard->GetYPosInPixels(mNextPosY - 1) + 2, mBoard->GetXPosInPixels(mNextPosX + 5)-mBoard->GetXPosInPixels(mNextPosX - 1) - 4, mBoard->GetYPosInPixels(mNextPosY + 5)-mBoard->GetYPosInPixels(mNextPosY - 1) - 4);

	// Check that the horizontal margin is not to small
	//assert (mX1 > MIN_HORIZONTAL_MARGIN);

	// Drawing the blocks that are already stored in the board
	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeBlock(i, j)) {
                Pokitto::Core::display.setColor(mBoard->GetColor(i,j));
                Pokitto::Core::display.fillRectangle(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE, BLOCK_SIZE - 1, BLOCK_SIZE - 2);
			}


		}
	}

}


/*
======================================
Draw Level

Draw current level Info
======================================
*/
void Game::DrawLevel(int level)
{
	Pokitto::Core::display.setCursor(5,8);
	Pokitto::Core::display.setColor(ORANGE);
	Pokitto::Core::display.println("Level");
	Pokitto::Core::display.setCursor(5+16-4*((int)log10(level)),1+13);
	Pokitto::Core::display.println(level);
}

/*
======================================
Draw Number of lines

Draw total number of lines
======================================
*/
void Game::DrawNrofLines(int lines)
{
	Pokitto::Core::display.setCursor(5,1+19);
	Pokitto::Core::display.setColor(ORANGE);
	Pokitto::Core::display.println("Lines");
	Pokitto::Core::display.setCursor(5+16-4*((int)log10(lines)),1+25);
	Pokitto::Core::display.println(lines);
}

/*
======================================
Draw Score

======================================
*/
void Game::DrawScore(int score)
{
	Pokitto::Core::display.setCursor(5,1+31);
	Pokitto::Core::display.setColor(ORANGE);
	Pokitto::Core::display.println("Score");
	Pokitto::Core::display.setCursor(5+16-4*((int)log10(score)),1+37);
	Pokitto::Core::display.println(score);
}



/*
======================================
Draw scene

Draw all the objects of the scene
======================================
*/
void Game::DrawScene(int level, int nroflines, int score)
{
	DrawLevel(level); //Draw level info
	DrawNrofLines(nroflines); //Draw number of lines info
	DrawScore(score); //Draw score
	DrawBoard();													// Draw the delimitation lines and blocks stored in the board
	DrawPiece_Ghost(mPosX, mPosY_ghost, mPiece, mRotation);
	DrawPiece(mPosX, mPosY, mPiece, mRotation);					// Draw the playing piece
	DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);	// Draw the next piece

}
