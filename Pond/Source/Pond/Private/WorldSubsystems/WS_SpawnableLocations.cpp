// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldSubsystems/WS_SpawnableLocations.h"
#include "MyJsonFileUtilities.h"

UWS_SpawnableLocations::UWS_SpawnableLocations()
{

}

void UWS_SpawnableLocations::Initialize(FSubsystemCollectionBase& Collection)
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
        return;
    }
    for(auto Row : JsonObject->GetArrayField("rows")){
        FSpawnableLocationDescription SpawnableLocationDescription;
        SpawnableLocationDescription.id = Row->AsObject()->GetStringField("id");
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
    }
    //ORGANIZE Data using tags
    //NEVER USE FOREACH WITH SET INSERT
    for(int i = 0; i < SpawnableLocations.Num(); i++){
        unsigned long long Hash;
        for(auto tag : SpawnableLocations[i].tags){

            if(MemHash.Find(tag) == nullptr){
                Hash = HashFunction(tag);
                MemHash.Add(tag, Hash);
            }
            else{
                Hash = MemHash[tag];
            }

            if(SetMap.Find(Hash) == nullptr){
                SetMap.Add(Hash, TSet<FSpawnableLocationDescription*>());
            }
            SetMap[Hash].Add(&(SpawnableLocations[i]));
        }
    }
}

void UWS_SpawnableLocations::Deinitialize()
{
    Super::Deinitialize();
}

TSet<FSpawnableLocationDescription *> UWS_SpawnableLocations::Query(FString QueryStr)
{
    TArray<FString> Token;
    QueryStr.ParseIntoArray(Token, TEXT("."));
    Token.Sort();
    FString Total;
    for(auto Elem : Token)
        Total += Elem;
    unsigned long long Hash = HashFunction(Total);
    if(MemHash.Find(Total) != nullptr){
        return SetMap[Hash];
    }
    else{
        for(int i = 0; i < Token.Num(); i++){
            if(MemHash.Find(Token[i]) == nullptr){
                return TSet<FSpawnableLocationDescription*>();
            }
        }
        TSet<FSpawnableLocationDescription*> Temp = SetMap[MemHash[Token[0]]];
        for(int i = 1; i < Token.Num(); i++){
            Temp.Union(SetMap[MemHash[Token[i]]]);
        }
        SetMap.Add(Hash, Temp);
        return SetMap[Hash];
    }
}

unsigned long long UWS_SpawnableLocations::HashFunction(FString str)
{
    unsigned long long sum = 0;
    char* strCharArr = TCHAR_TO_ANSI(*str);
    unsigned long long i = 0;
    unsigned long long g = 1;
    while(strCharArr[i] != '\0')
    {
        unsigned long long temp = (unsigned long long)(strCharArr[i]) * g;
        temp  = temp % Capacity;
        sum += temp;
        i++;
        g *= 31;
    }
    sum = sum % Capacity;
    return sum;
}