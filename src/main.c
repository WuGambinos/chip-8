/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *          
 *    Description:  
 *          Date:   8/1/2021
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lajuan Station 
 *    
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/emu.h"
#include "../include/raylib.h"


int main(int argc, char **argv) {

    
    argc = argc;

    //Rom Menu
    bool isMenu = true;

    //Store Strings for Debugging
    char string[100];

    //Store roms
    char roms[8][100];

    //Selector for rom starting at 0
    int rom = 0;

    //Open File
    FILE *f = fopen(argv[1], "rb");

    // Halt Program if file not found 
    if(f == NULL)
    {
        printf("Error: Couldn't open rom\n");
        exit(1);
    }

    //Get File size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //Create Chip
    Chip8* chip = InitChip8();

    //Load Program
    loadProgram(chip, f ,fsize);


//RAYLIB

//(820, 320)
InitWindow (800, 320, "Chip8 Virtual Machine");
SetTargetFPS(120);

    while(!WindowShouldClose()) {

        if(isMenu) {
            if(IsKeyPressed(KEY_ENTER)) {
                isMenu = false;
            }

        }

        
        BeginDrawing();

        if(isMenu) {
            ClearBackground(WHITE);
            DrawText("Hello World", GetScreenWidth()/2, GetScreenHeight()/2, 20, RED);
            //DrawRectangleLines(GetScreenWidth()/2, GetScreenHeight()/2, GetScreenWidth(), GetScreenHeight(), BLUE);
            

        }

        else {

            ClearBackground (BLUE);

            emulateCycle(chip);
            checkKeys(chip);
                    
            // If the draw flag is set update the screen
            if (chip -> drawFlag == 1)
            { 
                drawGraphics(chip);
            }

            DrawText("Hello World", 700, 25, 15, WHITE);
            sprintf(string, "PC: %X", chip -> pc);
            DrawText(string, 700, 40, 10, WHITE);

            sprintf(string, "SP: %X", chip -> sp);
            DrawText(string, 700, 55,10, WHITE);

            for(int i = 0; i < 0xF; i++)
            {
                sprintf(string, "V[%X] = %X", i, chip -> V[i]);
                DrawText(string, 700, 70 + (i * 10), 10, WHITE);
            }
        }


        EndDrawing();
    }
    CloseWindow();
    




    return 0;
}