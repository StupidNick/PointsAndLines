#pragma once

#include "CoreMinimal.h"
#include "Actors/LAP_BaseGameObject.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SphereComponent.h"
#include "LAP_Line.generated.h"


class USplineMeshComponent;



UCLASS(BlueprintType)
class LINESANDPOINTS_API ALAP_Line : public ALAP_BaseGameObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
		TArray<FVector> ControlPoints;

	virtual void OnTimerEnded() override;
	
private:

	UPROPERTY()
		bool bTouchEnter = false;

	UPROPERTY()
		bool bOnSphereTouch = false;

	UPROPERTY()
		FVector ClosestPoint;

public:	
	
	ALAP_Line();

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex) override;
	
	virtual void Initialize(FObjectInfo InObjectInfo) override;

	UFUNCTION()
		void SpawnSplineMeshes();

	UFUNCTION()
		void SpawnNewSegment(const FTransform& InTransform);

	UFUNCTION()
		void CreateControlPoints(const float InSegmentLength);

	UFUNCTION()
		void SetupSphere();

	UFUNCTION()
		void OnSphereTouch(ETouchIndex::Type InFingerIndex, UPrimitiveComponent* InComponent);

	UFUNCTION()
		FVector GetClosestPoint(const FVector InTouchLocation);

	UFUNCTION()
		FVector GetTouchLocation() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spline")
		USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Spline")
		UStaticMesh* SplineMesh;

	UPROPERTY(EditAnywhere, Category = "Spline")
		USphereComponent* Sphere1;

	UPROPERTY(EditAnywhere, Category = "Spline")
		USphereComponent* Sphere2;

	UPROPERTY(EditAnywhere, Category = "Spline")
		TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	UPROPERTY(EditAnywhere, Category = "PlayerIndicator")
		UStaticMeshComponent* Sphere;

	UPROPERTY(EditAnywhere)
		bool bIsConstruction;

	UPROPERTY()
		float MinDistanceToPoint;
};
