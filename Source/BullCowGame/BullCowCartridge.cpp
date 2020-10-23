// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <map>
#include <ctime>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    TArray<FString> Words;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    ValidWords = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    int32 random_number = CreateRandNumber(ValidWords.Num());
    hidden_word = ValidWords[random_number];
    number_of_lives = hidden_word.Len();
    bGameOver = false;
    ClearScreen();
    PrintLine(TEXT("Hey ho let's go"));
    PrintLine(TEXT("Number of possible words is %i"), ValidWords.Num());
    PrintLine(TEXT("Random word number is %i"), random_number);
    PrintLine(TEXT("Hidden word is %s"), *hidden_word);
    PrintLine(TEXT("Guess the %i letter word!"), hidden_word.Len());
    PrintLine(TEXT("You have %i lives."), hidden_word.Len());
    PrintLine(TEXT("Type in guess and press enter"));
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("Press enter to restart"));
    bGameOver = true;
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
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

            GetBullCows(Guess);

            PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
            PrintLine(TEXT("Fail, you have %i lives left"), number_of_lives);
        };
    }

    // Check User input
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
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

int32 UBullCowCartridge::CreateRandNumber(const int32 NumberOfWords) const
{
    srand((unsigned)time(0));
    int32 randomNumber = (rand() % (NumberOfWords - 1)) + 1;
    return randomNumber;
};

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> Words;
    for (FString const &Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
            Words.Emplace(Word);
    }
    return Words;
}

void UBullCowCartridge::GetBullCows(const FString &Guess)
{
    Count.Bulls = 0;
    Count.Cows = 0;
    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == hidden_word[i])
        {
            Count.Bulls++;
            continue;
        }
        for (char const &c : hidden_word)
        {
            if (Guess[i] == c)
            {
                Count.Cows++;
                break;
            }
        }
    }
}