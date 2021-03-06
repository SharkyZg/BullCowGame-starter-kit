// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString &Guess);
	bool IsIsogram(const FString &Word) const;
	int32 CreateRandNumber(const int32 NumberOfWords) const;
	TArray<FString> GetValidWords(const TArray<FString> &WordList) const;
	void GetBullCows(const FString &Guess);

	// Your declarations go below!
private:
	FString hidden_word;
	int32 number_of_lives;
	bool bGameOver;
	TArray<FString> ValidWords;
	FBullCowCount Count;
};
