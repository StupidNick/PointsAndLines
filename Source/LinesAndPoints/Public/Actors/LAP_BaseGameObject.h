#pragma once

#include "LAP_BaseGameObject.generated.h"



struct FObjectInfo;



UCLASS()
class ALAP_BaseGameObject : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameObjectWasActivatedEvent, ALAP_BaseGameObject*, GameObject, ETouchIndex::Type, Finger);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameObjectWasDestroyed, ALAP_BaseGameObject*, GameObject, bool, bDestroyBecauseTimeIsOver);
	
public:

	virtual void Initialize(FObjectInfo InObjectInfo);

protected:

	UFUNCTION()
		virtual void OnTimerEnded();
	
	UFUNCTION()
		virtual void DisableCollision();
	
public:

	UPROPERTY()
		float LifeTime;

	UPROPERTY()
		float PointsForClick;

	UPROPERTY()
		float PointsForPass;

	UPROPERTY()
		FTimerHandle LifeTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Transforms")
		float MaxDistanceForClick;

	UPROPERTY(EditDefaultsOnly, Category = "Transforms")
		float MaxDistanceToExcellentClick;

	UPROPERTY(EditAnywhere, Category = "Mesh Settings")
		UMaterial* MeshMaterial;

	UPROPERTY()
		FGameObjectWasActivatedEvent OnActivatedEvent;

	UPROPERTY()
		FGameObjectWasDestroyed OnDestroyedEvent;
};


