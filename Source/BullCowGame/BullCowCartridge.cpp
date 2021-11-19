// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine("Welcome to the Bull Cow Game!");
    PrintLine("If you don't know how to play, too bad.\nThere are no instructions yet.");
    PrintLine("Please input something into the window.");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
}