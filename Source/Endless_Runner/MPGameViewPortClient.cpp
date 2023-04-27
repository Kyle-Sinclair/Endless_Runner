// Fill out your copyright notice in the Description page of Project Settings.


#include "MPGameViewPortClient.h"

bool UMPGameViewPortClient::InputKey(const FInputKeyEventArgs& inputArgs)
{
    //UE_LOG(LogTemp, Warning, TEXT("Processing input events"));

    if (IgnoreInput() || inputArgs.Key.IsMouseButton()) {
        return Super::InputKey(inputArgs);
    }
    
    else
    {
        // Propagate keyboard events to all players
        UEngine* const Engine = GetOuterUEngine();
        int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
        //UE_LOG(LogTemp, Warning, TEXT("Number of players to propagate events to is %i"), NumPlayers);

        bool bRetVal = false;
        for (int32 i = 0; i < NumPlayers; i++)
        {
            bRetVal = Super::InputKey(inputArgs);
        }

        return bRetVal;
    }
}
