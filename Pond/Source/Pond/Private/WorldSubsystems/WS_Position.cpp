// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_Position.h"

UWS_Position::UWS_Position()
{

}

void UWS_Position::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    //READ From JsonFile
    FString JsonString;
    FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectDir() + "EUW/" + FilePath));
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    FJsonSerializer::Deserialize(Reader, JsonObject);
    if(!JsonObject.IsValid()){
        UE_LOG(LogTemp, Warning, TEXT("UMyJsonFileUtilities::LoadJsonFromFilePath: Invalid FilePath input"));
    }
    else{
        int InternalIdVal = 0;
        for(auto Row : JsonObject->GetArrayField("rows")){
            FSpawnableLocationDescription SpawnableLocationDescription;
            SpawnableLocationDescription.id = "InternalId_" + FString::FromInt(InternalIdVal);
            SpawnableLocationDescription.position = FVector(
                Row->AsObject()->GetObjectField("position")->GetNumberField("x"),
                Row->AsObject()->GetObjectField("position")->GetNumberField("y"),
                Row->AsObject()->GetObjectField("position")->GetNumberField("z")
            );
            TArray<TSharedPtr<FJsonValue>> _tags = Row->AsObject()->GetArrayField("tags");
            for(auto Tag : _tags){
                SpawnableLocationDescription.tags.Add(Tag->AsString());
            }
            SpawnableLocationDescription.tags.Sort();
            SpawnableLocations.Add(SpawnableLocationDescription);
            InternalIdVal++;
        }
    }
    //Initialize IdToVector
    for(FSpawnableLocationDescription Location : SpawnableLocations){
        IdToVector.Add(Location.id, Location.position);
    }
    //Initialize LocationsByTag
    for(FSpawnableLocationDescription Location : SpawnableLocations){
        for(FString tag : Location.tags){
            if(LocationsByTag.Find(tag) == nullptr)
                LocationsByTag.Add(tag, TSet<FString>());
            LocationsByTag[tag].Add(Location.id);
        }
    }
}

void UWS_Position::Deinitialize()
{
    Super::Deinitialize();
}

void UWS_Position::Query(TSet<FVector>& Output, FString QueryStr)
{
    TArray<FString> Tokens;
    QueryStr.ParseIntoArray(Tokens, TEXT(" "));
    TArray<FString> Stack;
    TArray<TSet<FString>> Save;
    for(int i = 0; i < Tokens.Num(); i++){
        if(Tokens[i].Equals(")")){
            FString Var1 = Stack.Pop();
            TSet<FString> Var1Set;
            if(Var1.Mid(0, 2).Equals("S_"))
                Var1Set = Save[FCString::Atoi(*(Var1.Right(2)))];
            else
                Var1Set = LocationsByTag[Var1];

            FString Operator;
            while(!Stack.Top().Equals("(")){
                if(Stack.Top().Equals("&") || Stack.Top().Equals("|")){
                    Operator = Stack.Pop();
                }
                else{
                    FString Var2 = Stack.Pop();
                    TSet<FString> Var2Set;
                    if(Var2.Mid(0, 2).Equals("S_"))
                        Var2Set = Save[FCString::Atoi(*(Var2.Right(2)))];
                    else
                        Var2Set = LocationsByTag[Var2];
                    
                    if(Operator.Equals("&"))
                        Var1Set = Var1Set.Intersect(Var2Set);
                    else if(Operator.Equals("|"))
                        Var1Set = Var1Set.Union(Var2Set);
                    Operator = "";
                }
            }
            Stack.Pop();
            Stack.Push("S_" + FString::FromInt(Save.Num()));
            Save.Add(Var1Set);
        }
        else{
            Stack.Push(Tokens[i]);
        }
    }

    TSet<FString> Result = Save.Top();
    for(auto Elem : Result){
        Output.Add(IdToVector[Elem]);
    }
}