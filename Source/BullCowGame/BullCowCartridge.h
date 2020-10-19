// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(FString Guess);
	bool IsIsogram(FString Word) const;
	int32 CreateRandNumber(int32 NumberOfWords) const;
	TArray<FString> GetValidWords(TArray<FString> WordList) const;


	// Your declarations go below!
private:
	FString hidden_word;
	int32 number_of_lives;
	bool bGameOver;
	TArray<FString> ValidWords;
};
