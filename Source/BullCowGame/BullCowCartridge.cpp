// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        SetupGame();
    }
    else
    {
        if (number_of_lives == 0)
        {
            PrintLine(TEXT("Game over, no more lives left"));
            EndGame();
            return;
        }

        if (Input.Len() != hidden_word.Len())
        {
            PrintLine(TEXT("Number of letters in guess does not match %i"), hidden_word.Len());
            return;
        }

        // Checking PlayerGuess

        if (hidden_word == Input)
        {
            PrintLine(TEXT("Guessed !!! Congrats you have won ! \nPress enter to play again."));
            EndGame();
        }
        else
        {
            number_of_lives--;
            PrintLine(TEXT("Fail!, you have %i lives left"), number_of_lives);
        };
    }
    // Check if Isogram

    // Check User input
}

void UBullCowCartridge::SetupGame()
{
    hidden_word = TEXT("cakes");
    number_of_lives = hidden_word.Len();
    bGameOver = false;
    ClearScreen();
    PrintLine(TEXT("Hey ho let's go"));
    PrintLine(TEXT("Guess the %i letter word!"), hidden_word.Len());
    PrintLine(TEXT("You have %i lives."), hidden_word.Len()); 
    PrintLine(TEXT("Type in guess and press enter"));
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("Press enter to restart"));
    bGameOver = true;
}