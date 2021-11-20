// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // debugging code only
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
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() {
    bGameOver = false;
    HiddenWord = TEXT("marsh");
    LivesRemaining = HiddenWord.Len();
    
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("If you don't know how to play, too bad.\nThere are no instructions yet."));
    PrintLine(TEXT("Please guess the %i letter word:"), HiddenWord.Len());
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to restart."));
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if (Guess == HiddenWord)  
    {
        PrintLine(TEXT("Congratulations,\nYou guessed the hidden word - well done"));
        EndGame();
        return;
    }
          
    if (Guess.Len() != HiddenWord.Len()) 
    {
        PrintLine(TEXT("The hidden word is %i characters long,\nTry again."), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("That guess is not an isogram!"));
        PrintLine(TEXT("Isograms contain just one of each letter."));
        return;
    }

    PrintLine(TEXT("That word is incorrect. Sorry."));
    --LivesRemaining;
    
    if (LivesRemaining <= 0)
    {
        PrintLine(TEXT("You lose! The word was %s."), *HiddenWord);
        EndGame();
    }

    //Show the player the bulls and cows

    PrintLine(TEXT("You have %i lives remaining"), LivesRemaining);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    // check if any letters match another in the same word
    for (int32 i = 0; i < Word.Len(); ++i)
    {
        for (int32 j=i+1; j<Word.Len(); ++j)
        {
            if (Word[i] == Word[j])     
            {
                return false;
            }
        }
    }
    // if no letters match, the word is an isogram
    return true;
}