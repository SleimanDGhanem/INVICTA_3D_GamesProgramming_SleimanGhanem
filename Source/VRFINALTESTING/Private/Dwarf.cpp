// Fill out your copyright notice in the Description page of Project Settings.


#include "Dwarf.h"
#include "Engine/Engine.h"
#include "Http.h"
#include "Json.h"
#include <String>





// Sets default values
ADwarf::ADwarf()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADwarf::BeginPlay()
{
	Super::BeginPlay();
	char BearerToken[] = "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";
	std::string AuthorizationHeader = "Bearer " + std::string(BearerToken);
	
	TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	RequestObject->SetStringField("model", "gpt-3.5-turbo");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hello, Unreal C++!"));
	//Add a system messgae
	TArray<TSharedPtr<FJsonValue>> MessagesArray;

	// Add a "system" message
	TSharedPtr<FJsonObject> SystemMessage = MakeShareable(new FJsonObject());
	SystemMessage->SetStringField("role", "system");
	SystemMessage->SetStringField("content", "You are a pirate");
	MessagesArray.Add(MakeShareable(new FJsonValueObject(SystemMessage)));

	// Add a "user" message
	TSharedPtr<FJsonObject> UserMessage1 = MakeShareable(new FJsonObject());
	UserMessage1->SetStringField("role", "user");
	UserMessage1->SetStringField("content", "How do I make a chocolate cake?");
	MessagesArray.Add(MakeShareable(new FJsonValueObject(UserMessage1)));

	// Add the messages array to the RequestObject
	RequestObject->SetArrayField("messages", MessagesArray);

	FString RequestBody; 

	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObject, Writer);



	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ADwarf::OnResponseReceived);
	Request->SetURL("https://api.openai.com/v1/chat/completions");
	Request->SetVerb("POST");
	Request->SetHeader("Authorization", AuthorizationHeader.c_str());
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();


	
}

// Called every frame
void ADwarf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADwarf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void ADwarf::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully && Response.IsValid())
    {
        // Get the content of the response as an FString
        FString ResponseContent = Response->GetContentAsString();

        // Create a JSON reader to parse the string
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);

        TSharedPtr<FJsonObject> JsonObject;
        // Deserialize the JSON string into a JSON object
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            // Access the "choices" field
            if (JsonObject->HasField("choices"))
            {
                TArray<TSharedPtr<FJsonValue>> ChoicesArray = JsonObject->GetArrayField("choices");
                if (ChoicesArray.Num() > 0)
                {
                    // Access the "message" object in the first element of "choices"
                    TSharedPtr<FJsonObject> ChoiceObject = ChoicesArray[0]->AsObject();
                    if (ChoiceObject.IsValid() && ChoiceObject->HasField("message"))
                    {
                        TSharedPtr<FJsonObject> MessageObject = ChoiceObject->GetObjectField("message");
                        if (MessageObject.IsValid() && MessageObject->HasField("content"))
                        {
                            // Get the "content" field from the "message" object
                            FString Content = MessageObject->GetStringField("content");
                            UE_LOG(LogTemp, Display, TEXT("Message Content: %s"), *Content);

                            if (GEngine)
                            {
                                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Content);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request failed."));
    }
}
    



