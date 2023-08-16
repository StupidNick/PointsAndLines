#include "Actors/LAP_Line.h"

#include "Assets/LAP_LevelSettingsDA.h"
#include "Kismet/GameplayStatics.h"


void ALAP_Line::OnTimerEnded()
{
	SetHidden(true);
	if (bOnSphereTouch)
	{
		OnDestroyedEvent.Broadcast(this, false);
		return;
	}
	OnDestroyedEvent.Broadcast(this, true);
}

ALAP_Line::ALAP_Line()
{
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Sphere1 = CreateDefaultSubobject<USphereComponent>("Sphere1");
	Sphere2 = CreateDefaultSubobject<USphereComponent>("Sphere2");

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	Sphere->SetWorldScale3D(FVector(.5f, .5f, .5f));
	Sphere->SetVisibility(false);
	Sphere->SetCollisionProfileName("NoCollision");
	
	
	if (IsValid(Spline))
	{
		Spline->SetupAttachment(RootComponent);
	}
	Sphere1->SetupAttachment(Spline);
	Sphere2->SetupAttachment(Spline);
}


void ALAP_Line::BeginPlay()
{
	Super::BeginPlay();
}


void ALAP_Line::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bTouchEnter) return;
	
	const FVector LTouchLocation = GetTouchLocation();
	const FVector LClosestPoint = GetClosestPoint(LTouchLocation);
	const float LNewDistance = FVector::Distance(LClosestPoint, LTouchLocation);

	Sphere->SetWorldLocation(FVector(LTouchLocation.X, LTouchLocation.Y, 10.f));
	if (LClosestPoint == ClosestPoint)
	{
		if (MinDistanceToPoint > LNewDistance)
		{
			MinDistanceToPoint = LNewDistance;
		}
		return;
	}

	if (LClosestPoint != FVector::ZeroVector)
	{
		OnActivatedEvent.Broadcast(this, ETouchIndex::Touch1);
		ControlPoints.Remove(ClosestPoint);
		ClosestPoint = LClosestPoint;
		MinDistanceToPoint = LNewDistance;
	}
}


void ALAP_Line::NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex)
{
	Super::NotifyActorOnInputTouchLeave(FingerIndex);
	if (!bOnSphereTouch) return;

	OnDestroyedEvent.Broadcast(this, false);
}


void ALAP_Line::NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex)
{
	Super::NotifyActorOnInputTouchEnter(FingerIndex);

	if (!bOnSphereTouch) return;

	bTouchEnter = true;
	ClosestPoint = GetClosestPoint(GetTouchLocation());
}


void ALAP_Line::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (bIsConstruction)
	{
		SpawnSplineMeshes();
	}
}


void ALAP_Line::Initialize(FObjectInfo InObjectInfo)
{
	Super::Initialize(InObjectInfo);

	for (int i = 0; i < InObjectInfo.SpawnLineTransforms.Num(); i++)
	{
		if (i == 0)
		{
			Spline->SetLocationAtSplinePoint(0, InObjectInfo.SpawnLineTransforms[i].GetLocation(), ESplineCoordinateSpace::World);
		}
		SpawnNewSegment(InObjectInfo.SpawnLineTransforms[i]);
	}
	SpawnSplineMeshes();
	CreateControlPoints(MaxDistanceForClick);
	PointsForClick = PointsForClick / ControlPoints.Num();
	SetupSphere();
}


void ALAP_Line::SpawnSplineMeshes()
{
	if (!IsValid(Spline)) return;
	
	for (int32 i = 0; i < Spline->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* LSplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		
		LSplineMesh->SetStaticMesh(SplineMesh);
		LSplineMesh->SetMobility(EComponentMobility::Movable);
		LSplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		LSplineMesh->RegisterComponentWithWorld(GetWorld());
		LSplineMesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
	
		const FVector StartPoint = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector StartTangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector EndPoint = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		const FVector EndTangent = Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
	
		LSplineMesh->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);
		
		LSplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		LSplineMesh->SetCollisionProfileName("BlockAllDynamic");
		LSplineMesh->SetGenerateOverlapEvents(true);
	
		LSplineMesh->SetForwardAxis(ForwardAxis);
	
		if (IsValid(MeshMaterial))
		{
			LSplineMesh->SetMaterial(0, MeshMaterial);
		}
	}
}


void ALAP_Line::SpawnNewSegment(const FTransform& InTransform)
{
	Spline->AddSplinePoint(InTransform.GetLocation(), ESplineCoordinateSpace::World);
	Spline->SetSplinePointType(Spline->GetNumberOfSplinePoints(), ESplinePointType::Curve);
}


void ALAP_Line::CreateControlPoints(const float InSegmentLength)
{
	for (int i = 1; i < Spline->GetNumberOfSplinePoints(); i++)
	{
		const FVector LDirection = (Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World) - Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::World)).GetSafeNormal(0.001);

		FVector LPointLocation = Spline->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::World);
		while (FVector::Distance(Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World), LPointLocation) > InSegmentLength)
		{
			ControlPoints.Add(LPointLocation);
			LPointLocation += LDirection * InSegmentLength;
		}
	}
}


void ALAP_Line::SetupSphere()
{
	Sphere1->SetWorldLocation(Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	Sphere2->SetWorldLocation(Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World));

	Sphere1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere1->SetCollisionProfileName("BlockAllDynamic");
	
	Sphere2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere2->SetCollisionProfileName("BlockAllDynamic");

	Sphere1->OnInputTouchBegin.AddDynamic(this, &ALAP_Line::OnSphereTouch);
	Sphere2->OnInputTouchBegin.AddDynamic(this, &ALAP_Line::OnSphereTouch);
}


void ALAP_Line::OnSphereTouch(ETouchIndex::Type InFingerIndex, UPrimitiveComponent* InComponent)
{
	bOnSphereTouch = true;

	Sphere1->DestroyComponent();
	Sphere2->DestroyComponent();

	Sphere->SetWorldLocation(FVector(GetTouchLocation().X, GetTouchLocation().Y, 10.f));
	Sphere->SetVisibility(true);
}


FVector ALAP_Line::GetTouchLocation() const
{
	float XTouch, YTouch;
	FVector LWorldLocation, LWorldDirection;
	bool bIsCurrentlyPressed;
	
	UGameplayStatics::GetPlayerController(this, 0)->GetInputTouchState(ETouchIndex::Touch1, XTouch, YTouch, bIsCurrentlyPressed);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(XTouch, YTouch, LWorldLocation, LWorldDirection);
	LWorldLocation *= 100;
	LWorldLocation.Z = 0.f;
	return LWorldLocation;
}


FVector ALAP_Line::GetClosestPoint(const FVector InTouchLocation)
{
	if (ControlPoints.Num() <= 0) return FVector::ZeroVector;
	
	FVector LClosestPoint = ControlPoints[0];
	float ClosestDistance = MaxDistanceForClick;
	for (FVector LPoint : ControlPoints)
	{
		const float LDistance = FVector::Distance(LPoint, InTouchLocation);
		if (ClosestDistance > LDistance)
		{
			LClosestPoint = LPoint;
			ClosestDistance = LDistance;
		}
	}
	if (ClosestDistance == MaxDistanceForClick)
	{
		return FVector::ZeroVector;
	}
	return LClosestPoint;
}