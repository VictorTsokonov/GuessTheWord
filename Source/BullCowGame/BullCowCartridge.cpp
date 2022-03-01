// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
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
    // Welcome the player
    HiddenWord = TEXT("ugabuga");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to the game!"));
    PrintLine(FString::Printf(TEXT("You have %i lives."), Lives ));
    

    PrintLine(FString::Printf(TEXT("It's lenght is: %i"), HiddenWord.Len()));
    PrintLine(TEXT("Your guess:"));

    PrintLine(TEXT("The first charecter of the word is %c"), HiddenWord[0]);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("PRESS ENTER TO PLAY AGAIN"));
}

void UBullCowCartridge::ProcessGuest(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
    }
    else
    {
        if (IsIsogram(Guess))
        {
            PrintLine(TEXT("The word is isogram"));
        }
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("The word is not isogram"));
        }
        PrintLine(FString::Printf(TEXT("You've lost a life --> %i left"), --Lives));
        if (Lives == 0)
        {
            ClearScreen();
            PrintLine(TEXT("You lost!"));
            EndGame();
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int i = 0; i < Word.Len(); i++)
    {
        for (int j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])return false;
        }
    }
    return true;
}