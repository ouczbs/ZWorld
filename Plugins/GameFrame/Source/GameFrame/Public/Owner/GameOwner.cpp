


#include "GameOwner.h"
#include "Requests/Request.h"
#include "Library/GameOwnerLibrary.h"
#include "Subsystem/GameOwnerSubsystem.h"

URequest* UGameOwner::FindOrAddRequest(FName Name) {
    if (!AllRequests.Contains(Name)) {
        UGameOwnerSubsystem* GameOwnerSubsystem = (UGameOwnerSubsystem*)UGameOwnerLibrary::GetGameSubsystem(UGameOwnerSubsystem::StaticClass());
        URequest* Request = GameOwnerSubsystem->SpawnRequest(Name);
        if (!Request) {
            return Request;
        }
        Request->InitRequest(this , Name);
        if(!Request->IsOnly){
            return Request;
        }
        AllRequests.Add(Name , Request);
    }
    return AllRequests.FindRef(Name);
}

void UGameOwner::RemoveRequest(URequest* Request){
    if(!Request->IsPersistence){
        AllRequests.Remove(Request->GetName());
    }
}
/*
Pending | Active | Blocked --> Active | Blocked | Entry
*/
bool UGameOwner::PushRequest(URequest* Request){
    if(Request->GetState() == ERequestState::Entry){
        Request->MarkState(ERequestState::Pending);
        ActiveRequests.Add(Request);
        return true;
    }
    return false;
}
void UGameOwner::TickRequest(float DeltaTime){
    // check if pending request meet the tag condition
    TArray<URequest*>	NewActiveRequests;
    //check if active request meet the tag condition
    for(URequest * Request : ActiveRequests){
        ERequestState State = Request->GetState();
        ERequestState NewState = Request->TryActiveRequest();
        Request->MarkState(NewState);
        if(State == ERequestState::Pending){
            if(NewState == ERequestState::Canceled){
                RemoveRequest(Request);
                continue;
            }
            Request->Start();
        }else if(NewState == ERequestState::Canceled){
            Request->Stop();
            RemoveRequest(Request);
            continue;
        }
        Request->Tick(DeltaTime);
        NewActiveRequests.Add(Request);
    }
    ActiveRequests = NewActiveRequests;
}