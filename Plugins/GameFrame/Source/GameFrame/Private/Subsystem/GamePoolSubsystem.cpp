


#include "Subsystem/GamePoolSubsystem.h"

#include "Interface/PoolObjectInterface.h"
#include "Kismet/GameplayStatics.h"


UObject* USubObjectPool::Spawn() {
    UObject* Object;
    if (ObjectsPool.Num() > 0) {
        Object = ObjectsPool.Pop();
    }
    else {
        Object = UGameplayStatics::SpawnObject(ObjectClass, this);
    }
    TScriptInterface<IPoolObjectInterface> PoolInterface(Object);
    PoolInterface->Execute_OnSpawn(Object);
    return  Object;
}

void USubObjectPool::Unspawn(UObject* Object) {
    TScriptInterface<IPoolObjectInterface> PoolInterface(Object);
    PoolInterface->Execute_OnUnspawn(Object);
    ObjectsPool.Add(Object);
}
void UGamePoolSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
}
void UGamePoolSubsystem::Deinitialize() {
    
}

UObject* UGamePoolSubsystem::Spawn(UClass* Class) {
    if(!Class){
        return nullptr;
    }
    const FName Name = Class->GetFName();
    USubObjectPool* SubObjectPool = nullptr;
    if (!ObjectPoolMap.Contains(Name)) {
        SubObjectPool = NewObject<USubObjectPool>(this);
        SubObjectPool->ObjectClass = Class;
        ObjectPoolMap.Add(Name, SubObjectPool);
    }else{
        SubObjectPool = ObjectPoolMap.FindRef(Name);
    }
    return SubObjectPool->Spawn();
}
void UGamePoolSubsystem::Unspawn(UObject* Object) {
    if(!Object){
        return;
    }
    const FName Name = Object->StaticClass()->GetFName();
    if (USubObjectPool* SubObjectPool = ObjectPoolMap.FindRef(Name)) {
        SubObjectPool->Unspawn(Object);
    };
}