#pragma once

#include "CoreMinimal.h"
#include "LAP_BaseGameObject.h"
#include "LAP_Point.generated.h"



UCLASS()
class LINESANDPOINTS_API ALAP_Point : public ALAP_BaseGameObject
{
	GENERATED_BODY()
	
public:	
	
	ALAP_Point();
	
	virtual void BeginPlay() override;

	virtual void NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex) override;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Mesh;
};
