


#include "Subsystem/GameOwnerSubsystem.h"
#include "Subsystem/GamePoolSubsystem.h"
#include "Library/GameOwnerLibrary.h"
#include "Owner/GameOwner.h"
#include "Requests/Request.h"
void UGameOwnerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    OnInitialize();
}
void UGameOwnerSubsystem::Deinitialize() {
    OnDeinitialize();
}
void UGameOwnerSubsystem::Tick(float DeltaTime) {
    for(UGameOwner * GameOwner : GameOwners){
        GameOwner->TickRequest(DeltaTime);
    }
}
UGameOwner* UGameOwnerSubsystem::SpawnGameOwner() {
    UGamePoolSubsystem* GanePoolSubsystem = (UGamePoolSubsystem*)UGameOwnerLibrary::GetGameSubsystem(UGamePoolSubsystem::StaticClass());
    UGameOwner* GameOwner = (UGameOwner*)GanePoolSubsystem->Spawn(UGameOwner::StaticClass());
    GameOwners.Add(GameOwner);
    return GameOwner;
}
URequest* UGameOwnerSubsystem::SpawnRequest(FName Name) {
    URequest* Request = nullptr;
    if(InterfaceSpawnRequest.IsBound()){
        Request = InterfaceSpawnRequest.Execute(Name);
    }
    return Request;
}
