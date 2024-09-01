// Fill out your copyright notice in the Description page of Project Settings.
#include "BFL/MyJsonFileUtilities.h"
#include "JsonObjectConverter.h"

void UMyJsonFileUtilities::LoadJsonFromFilePath(TArray<FSpawnableLocationDescription> &Output, FString FilePath)
{
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
        Output.Add(SpawnableLocationDescription);
    }
}
 
void UMyJsonFileUtilities::SaveJsonToFilePath(TArray<FSpawnableLocationDescription> Input, FString FilePath)
{
    TSharedPtr<FJsonObject> JsonObject_Rows = MakeShareable(new FJsonObject());
    TArray<TSharedPtr<FJsonValue>> JsonValue;
    for(auto Elem : Input)
    {
        TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Elem);
        TSharedPtr<FJsonValueObject> JsonValueObject = MakeShareable(new FJsonValueObject(JsonObject));
        JsonValue.Add(JsonValueObject);
    }
    JsonObject_Rows->SetArrayField("rows", JsonValue);

    FString JsonString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject_Rows.ToSharedRef(), Writer);

    FFileHelper::SaveStringToFile(JsonString, *(FPaths::ProjectDir() + "EUW/" +  FilePath));
}