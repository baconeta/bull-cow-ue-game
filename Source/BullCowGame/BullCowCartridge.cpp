// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else 
    {   
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    HiddenWord = SetupValidWordsList(Words)[FMath::RandRange(0, SetupValidWordsList(Words).Num() - 1)];
    LivesRemaining = HiddenWord.Len();

    // debugging code only
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);
    
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("If you don't know how to play, too bad.\nThere are no instructions yet."));
    PrintLine(TEXT("Please guess the %i letter word:"), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to restart."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
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

    // show the player the bulls and cows

    PrintLine(TEXT("You have %i lives remaining"), LivesRemaining);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // Check if any letters match another in the same word
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])     
            {
                return false;
            }
        }
    }
    // If no letters match, the word is an isogram
    return true;
}

TArray<FString> UBullCowCartridge::SetupValidWordsList(const TArray<FString>& ListOfWords) const 
{
    TArray<FString> ValidWords;
    for (FString Word : ListOfWords) {
            if (Word.Len() >= 4 && Word.Len() <= 8) 
            {
                if (IsIsogram(Word))
                {
                    ValidWords.Emplace(Word);
                }
            }
        }
    return ValidWords;
}