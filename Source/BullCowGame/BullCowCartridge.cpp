// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuest(Input);
    }



}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len()*2;
    bGameOver = false;

    PrintLine(TEXT("Welcome to the game!"));
    PrintLine(FString::Printf(TEXT("You have %i lives."), Lives ));
    PrintLine(FString::Printf(TEXT("The lenght of the word is: %i"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
    PrintLine(TEXT("The first charecter of the word is %c"), HiddenWord[0]);
    PrintLine(TEXT("The last charecter of the word is %c"), HiddenWord[HiddenWord.Len()-1]);
    PrintLine(TEXT("------------------------------------------"));
    PrintLine(TEXT("Guess the word: "));

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("PRESS ENTER TO PLAY AGAIN"));
}

void UBullCowCartridge::ProcessGuest(const FString& Guess)
{
    
    ClearScreen();
    PrintLine(TEXT("Welcome to the game!"));
    PrintLine(FString::Printf(TEXT("You have %i lives."), Lives ));
    PrintLine(FString::Printf(TEXT("The lenght of the word is: %i"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
    PrintLine(TEXT("The first charecter of the word is %c"), HiddenWord[0]);
    PrintLine(TEXT("The last charecter of the word is %c"), HiddenWord[HiddenWord.Len()-1]);
    PrintLine(TEXT("------------------------------------------"));

    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
    }
    else
    {

        PrintLine(FString::Printf(TEXT("You've lost a life --> %i left"), --Lives));

        if (Lives == 0)
        {
            ClearScreen();
            PrintLine(TEXT("You lost!"));
            EndGame();
            return;
        }
    }
    PrintLine(TEXT("Guess the word: "));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    { 
        for (int32 j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])return false;
        }
    }
    return true;
}

const TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordsList) const
{
    TArray <FString> ValidWords;
    for(FString Word: WordsList)
    {
        if( Word.Len()>=4 && Word.Len()<=8 && !IsIsogram(Word) )
           ValidWords.Emplace(Word);
    }
    return ValidWords;
}
