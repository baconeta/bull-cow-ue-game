// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("If you don't know how to play, too bad.\nThere are no instructions yet."));
    PrintLine(TEXT("Please guess the 5 letter word:")); // TODO change 5 to magic number 
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (Input == HiddenWord) {
        PrintLine(TEXT("Congratulations,\nyou guessed the hidden word - well done"));
    }
    else {        
        PrintLine(Input);
        PrintLine(TEXT("That word is incorrect. Sorry."));
    }

    // check if isogram
    // check length of word
    // remove a life

    // check lives > 0
    // if yes, guess again
    // show lives remaining
    // if no, show game over and hidden word
}

void UBullCowCartridge::InitGame() {
    HiddenWord = TEXT("marsh"); // Set the hidden word
    LivesRemaining = 5; // Set the lives
}