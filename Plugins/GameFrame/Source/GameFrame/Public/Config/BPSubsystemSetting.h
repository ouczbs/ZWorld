
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BPSubsystemSetting.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Blueprint Subsystem"))
class GAMEFRAME_API UBPSubsystemSetting :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, Category = "Sub System")
	TArray<TSubclassOf<USubsystem>> Subsystems;
};

