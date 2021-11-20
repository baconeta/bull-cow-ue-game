// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word)
        {
            return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word);
        });

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
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    LivesRemaining = HiddenWord.Len() * 2;
    
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
        PrintLine(TEXT("Congratulations,\nYou guessed the hidden word - well done."));
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
        return;
    }

    // Show the player the bulls and cows

    FBullCowCount Count = GetBullCows(Guess);

    PrintLine(TEXT("You have %i bulls, and %i cows."), Count.Bulls, Count.Cows);

    PrintLine(TEXT("You have %i lives remaining"), LivesRemaining);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 ComparisonIndex = 0; ComparisonIndex < HiddenWord.Len(); ComparisonIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[ComparisonIndex])
            {
                Count.Cows++;
                break;
            }
        }       
    }
    return Count;
}