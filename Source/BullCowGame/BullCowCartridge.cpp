// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("If you don't know how to play, too bad.\nThere are no instructions yet."));
    PrintLine(TEXT("Please input something into the window."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString HiddenWord = TEXT("marsh");
    ClearScreen();
    PrintLine(Input);
}