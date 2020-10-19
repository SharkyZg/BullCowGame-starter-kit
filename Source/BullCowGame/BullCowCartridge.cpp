// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <map>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ProcessGuess(Input);
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

void UBullCowCartridge::ProcessGuess(FString Guess)
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

        if (Guess.Len() != hidden_word.Len())
        {
            PrintLine(TEXT("Number of letters in guess does not match %i"), hidden_word.Len());
            return;
        }

        // Checking PlayerGuess

        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("Please enter an isogram."));
            return;
        }

        if (hidden_word == Guess)
        {
            PrintLine(TEXT("Guessed !!! Congrats you have won !"));
            EndGame();
        }
        else
        {
            number_of_lives--;
            PrintLine(TEXT("Fail!, you have %i lives left"), number_of_lives);
        };
    }

    // Check User input
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    std::map<char, int> counter;
    for (char const &c : Word)
    {
        counter[c]++;
        if (counter[c] > 1)
            return false;
    }
    return true;
}