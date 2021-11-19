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
        if (Input == HiddenWord) 
        {
        PrintLine(TEXT("Congratulations,\nYou guessed the hidden word - well done"));
        }
        else
        {        
            PrintLine(Input);
            if (Input.Len() != HiddenWord.Len()) {
                PrintLine(TEXT("The hidden word is %i characters long,\nTry again."), HiddenWord.Len()); // TODO change magic number
            }
            else
            {
                --LivesRemaining;
                if (LivesRemaining > 0)
                {
                    PrintLine(TEXT("That word is incorrect. Sorry."));
                    PrintLine(TEXT("You have %i lives remaining"), LivesRemaining);
                }
                else
                {
                    EndGame();
                }
            }
        }
    }

    // check if isogram
    
    // remove a life

    // check lives > 0
    // if yes, guess again
    // show lives remaining
    // if no, show game over and hidden word
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
    PrintLine(TEXT("You lose! The word was %s."), *HiddenWord);
    PrintLine(TEXT("Press enter to restart."));
}