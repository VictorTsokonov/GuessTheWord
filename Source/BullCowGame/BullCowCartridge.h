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
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuest(const FString& Guess); // Compare the user Input to the HiddenWord, then decrement Lives if the guess is wrong.
	bool IsIsogram(const FString& Word) const; // Checks if the word has repeating letters
	const TArray<FString> GetValidWords(const TArray<FString> &WordsList) const;


	// Your declarations go below!
private:
	bool bGameOver;
	int32 Lives;
	FString HiddenWord;
	TArray <FString> Isograms;
};
