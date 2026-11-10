// Fill out your copyright notice in the Description page of Project Settings.


#include "UECRPG/Public/Camera/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	DirectionComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Direction"));
	DirectionComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = StartingZoom;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActiveMoveSpeed = DefaultMoveSpeed;
	ActiveMoveLerpSpeed = DefaultMoveLerpSpeed;

	ActiveRotationSpeed = DefaultRotationSpeed;
	ActiveRotationLerpSpeed = DefaultRotationLerpSpeed;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	//InitializeRTSCameraPawn();
}

void ACameraPawn::Initialize()
{
	if (bInitialized) return;

	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		SetActorTickEnabled(false);
		return;
	}

	//Certain variables must be multiplied by negative 1 or else the negative values would need to be entered in the editor.
	StartingPitch = StartingPitch * -1;
	ZoomedOutPitch = ZoomedOutPitch * -1;
	ZoomedInPitch = ZoomedInPitch * -1;
	DragMoveSpeed = DragMoveSpeed * -1;

	SpringArmComponent->SetRelativeLocation(FVector(0, 0, StartingCameraHeight));
	SpringArmComponent->SetRelativeRotation(FRotator(StartingPitch, 0, 0));

	TargetLocation = GetActorLocation();
	StartingCameraZRotation = GetActorRotation().Yaw;

	OriginalZoom = StartingZoom;
	OriginalRotation = SpringArmComponent->GetRelativeRotation();
	OriginalLocation = GetActorLocation();

	TargetLocation = OriginalLocation;
	TargetRotation = OriginalRotation;

	CameraComponent->FieldOfView = StartingFOV;

	LerpRotation = FRotator(StartingPitch, 0, StartingCameraZRotation);
	LerpHeight = StartingCameraHeight;
	LerpFOV = StartingFOV;
	LerpZoom = StartingZoom;
	TargetZoom = StartingZoom;
	TargetHeight = StartingCameraHeight;

	FrameRateMultiplier = 1.0f;

	if (bInitializeCursorAndInputModeSettings)
	{
		PlayerController->bShowMouseCursor = bBeginWithCursorEnabled;
		DefaultInputMode.SetLockMouseToViewportBehavior(MouseLockMode);
		DefaultInputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(DefaultInputMode);
	}

	SetActorTickEnabled(true);

	bInitialized = true;
}

// Tick

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerController) return;

	EdgeScroll();
	FollowActor();
	HeightTrace();
	CameraCollision();
	SetFrameRateMultiplier();

	float AdjustedTime = GetTimeDilationAdjustedTime(DeltaTime);

	//Smoothly move the pawn in the desired direction
	LerpLocation = UKismetMathLibrary::VInterpTo(GetActorLocation(), TargetLocation, AdjustedTime, ActiveMoveLerpSpeed);
	SetActorLocation(LerpLocation);

	if (bInterpolationEnabled)
	{
		LerpHeight = UKismetMathLibrary::FInterpTo(SpringArmComponent->GetRelativeLocation().Z, TargetHeight, AdjustedTime, ActiveMoveLerpSpeed * FrameRateMultiplier);
		SpringArmComponent->SetRelativeLocation(FVector(0, 0, LerpHeight));

		//Zoom the camera to the desired zoom level
		LerpZoom = UKismetMathLibrary::FInterpTo(SpringArmComponent->TargetArmLength, TargetZoom, AdjustedTime * ZoomSpeed, ZoomLerpSpeed * FrameRateMultiplier);
		SpringArmComponent->TargetArmLength = LerpZoom;

		if (bZoomAffectsFOV)
		{
			// Lerp the FOV to the desired FOV
			LerpFOV = UKismetMathLibrary::FInterpTo(CameraComponent->FieldOfView, TargetFOV, AdjustedTime * ZoomSpeed, FOVLerpSpeed * FrameRateMultiplier);
			CameraComponent->FieldOfView = LerpFOV;
		}

		//Smoothly rotate the camera to the desired rotation
		LerpRotation = UKismetMathLibrary::RInterpTo(SpringArmComponent->GetRelativeRotation(), TargetRotation, AdjustedTime, ActiveRotationLerpSpeed * FrameRateMultiplier);
		SpringArmComponent->SetRelativeRotation(FRotator(LerpRotation));
		DirectionComponent->SetRelativeRotation(FRotator(0, LerpRotation.Yaw, 0));
	}
	//If interpolation isn't being used, the values can be set directly. This could be refactored by including bUseInterpolation in every movement function and avoiding the tick, but that might get confusing and there's no meaningful performance hit.
	else
	{
		SpringArmComponent->SetRelativeLocation(FVector(0, 0, TargetHeight));
		SpringArmComponent->TargetArmLength = TargetZoom;
		SpringArmComponent->SetRelativeRotation(FRotator(TargetRotation));
		DirectionComponent->SetRelativeRotation(FRotator(0, TargetRotation.Yaw, 0));

		if (bZoomAffectsFOV)
		{
			CameraComponent->FieldOfView = TargetFOV;
		}
	}
}

// Movement Functions

void ACameraPawn::MoveForward(float AxisValue)
{
	SetMoveAndLerpSpeed(DefaultMoveSpeed, DefaultMoveLerpSpeed);
	TargetLocation = DirectionComponent->GetForwardVector() * AxisValue * DefaultMoveSpeed * FrameRateMultiplier + TargetLocation;
	LocationBounds();
}

void ACameraPawn::MoveRight(float AxisValue)
{
	SetMoveAndLerpSpeed(DefaultMoveSpeed, DefaultMoveLerpSpeed);
	TargetLocation = DirectionComponent->GetRightVector() * AxisValue * DefaultMoveSpeed * FrameRateMultiplier + TargetLocation;
	LocationBounds();
}

void ACameraPawn::MoveUp(float AxisValue)
{
	SetMoveAndLerpSpeed(DefaultMoveSpeed, DefaultMoveLerpSpeed);
	float HeightChange = AxisValue * DefaultMoveSpeed * FrameRateMultiplier;
	TargetHeight = FMath::Clamp(HeightChange + TargetHeight, MinCameraHeight, MaxCameraHeight);
}


void ACameraPawn::DragMoveForward(float AxisValue)
{
	SetMoveAndLerpSpeed(DragMoveSpeed, DragMoveLerpSpeed);
	TargetLocation = DirectionComponent->GetForwardVector() * AxisValue * DragMoveSpeed * FrameRateMultiplier + TargetLocation;
	LocationBounds();
}

void ACameraPawn::DragMoveRight(float AxisValue)
{
	SetMoveAndLerpSpeed(DragMoveSpeed, DragMoveLerpSpeed);
	TargetLocation = DirectionComponent->GetRightVector() * AxisValue * DragMoveSpeed * FrameRateMultiplier + TargetLocation;
	LocationBounds();
}

void ACameraPawn::DragMove(float AxisValueX, float AxisValueY)
{
	DragMoveForward(AxisValueY);
	DragMoveRight(AxisValueX);
}


void ACameraPawn::EdgeScroll()
{
	if (!bCanEdgeScroll) return;
	if (!PlayerController) return;

	float MouseX;
	float MouseY;

	int ScreenSizeX;
	int ScreenSizeY;

	PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);

	// Only run if the mouse position is in the viewport
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		// Normalize mouse position
		float NormalizedMouseX = MouseX / ScreenSizeX;
		float NormalizedMouseY = MouseY / ScreenSizeY;

		if (NormalizedMouseX > (1 - EdgeScrollZone))
		{
			MoveRight(EdgeScrollMoveSpeedMultiplier);
			SetMoveAndLerpSpeed(DefaultMoveSpeed * EdgeScrollMoveSpeedMultiplier, EdgeScrollLerpSpeed);
		}
		else if (NormalizedMouseX < EdgeScrollZone)
		{
			MoveRight(-EdgeScrollMoveSpeedMultiplier);
			SetMoveAndLerpSpeed(DefaultMoveSpeed * EdgeScrollMoveSpeedMultiplier, EdgeScrollLerpSpeed);
		}

		if (NormalizedMouseY > (1 - EdgeScrollZone))
		{
			MoveForward(-EdgeScrollMoveSpeedMultiplier);
			SetMoveAndLerpSpeed(DefaultMoveSpeed * EdgeScrollMoveSpeedMultiplier, EdgeScrollLerpSpeed);

		}
		else if (NormalizedMouseY < EdgeScrollZone)
		{
			MoveForward(EdgeScrollMoveSpeedMultiplier);
			SetMoveAndLerpSpeed(DefaultMoveSpeed * EdgeScrollMoveSpeedMultiplier, EdgeScrollLerpSpeed);
		}
		LocationBounds();
	}

}

void ACameraPawn::InterpolatedMoveToLocation(FVector Location, bool bOverrideMoveSpeedValues, float MoveSpeedOverride, float MoveLerpSpeedOverride)
{
	if (bOverrideMoveSpeedValues)
	{
		SetMoveAndLerpSpeed(MoveSpeedOverride, MoveLerpSpeedOverride);
	}
	TargetLocation = Location;
	LocationBounds();
}

void ACameraPawn::SnapToLocation(FVector Location)
{
	TargetLocation = Location;
	LerpLocation = Location;
	SetActorLocation(Location);
	LocationBounds();
}

void ACameraPawn::MoveToLocationUnderCursor(bool bOverrideMoveSpeedValues, float MoveSpeedOverride, float MoveLerpSpeedOverride)
{
	if (!PlayerController) return;

	FHitResult HitResult;

	ETraceTypeQuery Trace = UEngineTypes::ConvertToTraceType(HitUnderCursorTraceChannel);
	bool bHit = PlayerController->GetHitResultUnderCursorByChannel(Trace, true, HitResult);

	if (bHit)
	{
		// Process the hit result, e.g., print information
		FVector HitLocation = HitResult.Location;
		InterpolatedMoveToLocation(HitLocation, bOverrideMoveSpeedValues, MoveSpeedOverride, MoveLerpSpeedOverride);
		LocationBounds();
	}
}

// The below functions override the "ActiveMoveSpeed" and "ActiveMoveLerpSpeed

void ACameraPawn::SetMoveSpeed(float MoveSpeed)
{
	ActiveMoveSpeed = MoveSpeed;
}

void ACameraPawn::SetMoveLerpSpeed(float MoveLerpSpeed)
{
	ActiveMoveLerpSpeed = MoveLerpSpeed;
}

void ACameraPawn::SetMoveAndLerpSpeed(float MoveSpeed, float MoveLerpSpeed)
{
	ActiveMoveSpeed = MoveSpeed;
	ActiveMoveLerpSpeed = MoveLerpSpeed;
}


// Rotation Functions

void ACameraPawn::Rotate(float AxisValue)
{
	SetRotationAndLerpSpeed(DefaultRotationSpeed, DefaultRotationLerpSpeed);

	if (!bInvertHorizontalRotation)
	{
		TargetRotation.Yaw += AxisValue * ActiveRotationSpeed * FrameRateMultiplier;
		return;
	}
	TargetRotation.Yaw += AxisValue * ActiveRotationSpeed * -1 * FrameRateMultiplier;
}

void ACameraPawn::IncrementalRotateRight()
{
	SetRotationAndLerpSpeed(IncrementalRotationSpeed, IncrementalRotationLerpSpeed);

	TargetRotation.Yaw += IncrementalRotationAmount * -1;
	RotationBounds();
}

void ACameraPawn::IncrementalRotateLeft()
{
	SetRotationAndLerpSpeed(IncrementalRotationSpeed, IncrementalRotationLerpSpeed);

	TargetRotation.Yaw += IncrementalRotationAmount;
	RotationBounds();
}

void ACameraPawn::EnableRotation()
{
	bCanRotate = true;
}

void ACameraPawn::DisableRotation()
{
	bCanRotate = false;
}

void ACameraPawn::DragRotateYaw(float AxisValue)
{
	SetRotationAndLerpSpeed(DragRotationSpeed, DragRotationLerpSpeed);

	AxisValue *= DragRotationSpeed;

	if (!bCanRotate) return;
	TargetRotation.Yaw += AxisValue;
}

void ACameraPawn::DragRotatePitch(float AxisValue)
{
	SetRotationAndLerpSpeed(DragRotationSpeed, DragRotationLerpSpeed);

	AxisValue *= DragRotationSpeed;
	float NewPitch = TargetRotation.Pitch;

	TargetRotation = FRotator(NewPitch, TargetRotation.Yaw, 0.f);
	if (bCanRotate && bFreeVerticalPitchEnabled)
	{
		if (TargetRotation.Pitch < (MaxPitch * -1))
		{
			NewPitch = (MaxPitch * -1);
		}
		else if (TargetRotation.Pitch > (MinPitch * -1))
		{
			NewPitch = (MinPitch * -1);
		}

		if (!bInvertCameraPitch)
		{
			TargetRotation.Pitch += AxisValue;
		}
		else
		{
			TargetRotation.Pitch += AxisValue * -1;
		}
		RotationBounds();
	}
}

void ACameraPawn::DragFreeRotate(float AxisValueX, float AxisValueY)
{
	DragRotateYaw(AxisValueX);
	DragRotatePitch(AxisValueY);
}

// The below functions override the "ActiveRotationSpeed" and "ActiveRotation LerpSpeed

void ACameraPawn::SetRotationSpeed(float RotationSpeed)
{
	ActiveRotationSpeed = RotationSpeed;
}

void ACameraPawn::SetRotationLerpSpeed(float RotationLerpSpeed)
{
	ActiveRotationLerpSpeed = RotationLerpSpeed;
}

void ACameraPawn::SetRotationAndLerpSpeed(float RotationSpeed, float RotationLerpSpeed)
{
	ActiveRotationSpeed = RotationSpeed;
	ActiveRotationLerpSpeed = RotationLerpSpeed;
}

// Zoom Functions

void ACameraPawn::Zoom(float AxisValue)
{
	if (!bCanZoom) return;

	const float Zoom = AxisValue * ZoomSpeed;
	TargetZoom = FMath::Clamp(Zoom + TargetZoom, MinZoom, MaxZoom);

	//Camera Pitch and Zoom Settings
	if (bPitchUpOnZoomEnabled)
	{
		//A custom pitch up on zoom rotation is nice to have, but it also can make the camera behave unexpectedly if the player zooms and rotates at the same time as this overrides rotation speed values.
		if (bCustomPitchUpOnZoomRotationsEnabled)
		{
			SetRotationAndLerpSpeed(PitchUpOnZoomRotationSpeed, PitchUpOnZoomRotationLerpSpeed);
		}
		else
		{
			SetRotationAndLerpSpeed(DefaultRotationSpeed, DefaultRotationLerpSpeed);
		}

		// Define the pitch thresholds and corresponding pitch values
		float SpringArmLength = SpringArmComponent->TargetArmLength;
		float NewPitch = 0.0f;
		float ZoomRange = MaxZoom - MinZoom;
		float ZoomPitchRange = ZoomedOutPitch - ZoomedInPitch;
		float ZoomedOutPercentage = (TargetZoom - MinZoom) / ZoomRange;

		if (ZoomedOutPercentage <= PitchUpOnZoomThreshold)
		{
			NewPitch = (ZoomedOutPercentage * ZoomPitchRange) / PitchUpOnZoomThreshold + ZoomedInPitch;
		}
		else
		{
			NewPitch = ZoomedOutPitch;
		}
		if (bZoomAffectsFOV)
		{
			if (ZoomedOutPercentage <= FOVZoomThreshold)
			{
				float FOVRange = FMath::Abs(ZoomedOutFOV - ZoomedInFOV);
				float NewFOV = (ZoomedOutPercentage * FOVRange) / FOVZoomThreshold + ZoomedInFOV;
				SetTargetFOV(NewFOV);
			}
			else
			{
				SetTargetFOV(ZoomedOutFOV);
			}
		}
		TargetRotation.Pitch = NewPitch;
	}

	// If pitch up on zoom disabled but Zoom should affect FOV, then calculate the missing variables and otherwise do the same as above.
	else if (bZoomAffectsFOV)
	{
		float ZoomRange = MaxZoom - MinZoom;
		float ZoomedOutPercentage = (TargetZoom - MinZoom) / ZoomRange;
		float FOVRange = FMath::Abs(ZoomedOutFOV - ZoomedInFOV);
		float NewFOV = (ZoomedOutPercentage * FOVRange) / PitchUpOnZoomThreshold + FMath::Min(ZoomedInFOV, ZoomedOutFOV);
		SetTargetFOV(NewFOV);
	}
}

void ACameraPawn::IncrementalZoomIn()
{
	if (bCanZoom)
	{
		float ZoomRange = MaxZoom - MinZoom;
		float ZoomedOutPercentage = (TargetZoom - MinZoom) / ZoomRange;
		float IncrementalZoomAmount = ZoomRange / IncrementalZoomLevels;
		Zoom(IncrementalZoomAmount * -1 / ZoomSpeed);
	}
}

void ACameraPawn::IncrementalZoomOut()
{
	if (bCanZoom)
	{
		float ZoomRange = MaxZoom - MinZoom;
		float ZoomedOutPercentage = (TargetZoom - MinZoom) / ZoomRange;
		float IncrementalZoomAmount = ZoomRange / IncrementalZoomLevels;
		Zoom(IncrementalZoomAmount / ZoomSpeed);
	}
}

void ACameraPawn::EnableZoom()
{
	bCanZoom = true;
}

void ACameraPawn::DisableZoom()
{
	bCanZoom = false;
}


// Camera Location Hotkey Functions

void ACameraPawn::SetCameraLocation(int CameraLocation)
{
	switch (CameraLocation)
	{
	case 1:
		CameraLocation1 = GetActorLocation();
		if (!bCameraLocation1Set)
		{
			bCameraLocation1Set = true;
		}
		break;

	case 2:
		CameraLocation2 = GetActorLocation();
		if (!bCameraLocation2Set)
		{
			bCameraLocation2Set = true;
		}
		break;

	case 3:
		CameraLocation3 = GetActorLocation();
		if (!bCameraLocation3Set)
		{
			bCameraLocation3Set = true;
		}
		break;

	case 4:
		CameraLocation4 = GetActorLocation();
		if (!bCameraLocation4Set)
		{
			bCameraLocation4Set = true;
		}
		break;

	case 5:
		CameraLocation5 = GetActorLocation();
		if (!bCameraLocation5Set)
		{
			bCameraLocation5Set = true;
		}
		break;

	case 6:
		CameraLocation6 = GetActorLocation();
		if (!bCameraLocation6Set)
		{
			bCameraLocation6Set = true;
		}
		break;

	case 7:
		CameraLocation7 = GetActorLocation();
		if (!bCameraLocation7Set)
		{
			bCameraLocation7Set = true;
		}
		break;

	case 8:
		CameraLocation8 = GetActorLocation();
		if (!bCameraLocation8Set)
		{
			bCameraLocation8Set = true;
		}
		break;

	default:
		break;
	}
}

void ACameraPawn::GoToCameraLocation(int CameraLocation)
{
	switch (CameraLocation)
	{
	case 1:
		if (bCameraLocation1Set)
		{
			SnapToLocation(CameraLocation1);
		}
		break;

	case 2:
		if (bCameraLocation2Set)
		{
			SnapToLocation(CameraLocation2);
		}
		break;

	case 3:
		if (bCameraLocation3Set)
		{
			SnapToLocation(CameraLocation3);
		}
		break;

	case 4:
		if (bCameraLocation4Set)
		{
			SnapToLocation(CameraLocation4);
		}
		break;

	case 5:
		if (bCameraLocation5Set)
		{
			SnapToLocation(CameraLocation5);
		}
		break;

	case 6:
		if (bCameraLocation6Set)
		{
			SnapToLocation(CameraLocation6);
		}
		break;

	case 7:
		if (bCameraLocation7Set)
		{
			SnapToLocation(CameraLocation7);
		}
		break;

	case 8:
		if (bCameraLocation8Set)
		{
			SnapToLocation(CameraLocation8);
		}
		break;

	default:
		break;
	}
}

// FOV

void ACameraPawn::SetTargetFOV(float FOV)
{
	TargetFOV = FOV;
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACameraPawn::LocationBounds()
{
	if (bCameraBoundsEnabled) {
		if (TargetLocation.X < (MinXBound))
		{
			TargetLocation.X = MinXBound;
		}
		else if (TargetLocation.X > (MaxXBound))
		{
			TargetLocation.X = MaxXBound;
		}

		if (TargetLocation.Y < (MinYBound))
		{
			TargetLocation.Y = MinYBound;
		}
		else if (TargetLocation.Y > (MaxYBound))
		{
			TargetLocation.Y = MaxYBound;
		}
	}
	TargetLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
}

void ACameraPawn::RotationBounds()
{
	float NewPitch = TargetRotation.Pitch;
	if (TargetRotation.Pitch < (MaxPitch * -1))
	{
		NewPitch = (MaxPitch * -1);
	}
	else if (TargetRotation.Pitch > (MinPitch * -1))
	{
		NewPitch = (MinPitch * -1);
	}
	TargetRotation = FRotator(NewPitch, TargetRotation.Yaw, 0.f);
}

void ACameraPawn::SetFrameRateMultiplier()
{
	if (!bFrameRateSpeedAdjustmentEnabled) return;

	float CurrentRealTimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	float DeltaRealTimeSeconds = CurrentRealTimeSeconds - PreviousRealTimeSeconds;
	PreviousRealTimeSeconds = CurrentRealTimeSeconds;
	FrameRateMultiplier = DeltaRealTimeSeconds * 60;
}


// Follow Actor Functions

void ACameraPawn::StartFollowingActor(AActor* ActorToFollow)
{
	SetMoveAndLerpSpeed(FollowMoveSpeed, FollowMoveLerpSpeed);
	bIsFollowingActor = true;
	FollowTarget = ActorToFollow;
}

void ACameraPawn::StopFollowingActor()
{
	bIsFollowingActor = false;
}

void ACameraPawn::FollowActor()
{
	if (bIsFollowingActor)
	{
		FVector FollowTargetLocation = FollowTarget->GetActorLocation();
		TargetLocation = FVector(FollowTargetLocation.X, FollowTargetLocation.Y, TargetLocation.Z);
		LocationBounds();
	}
}

void ACameraPawn::HeightTrace()
{
	if (bHeightTraceEnabled)
	{
		FVector StartLocation = GetActorLocation() + FVector(0, 0, HeightTraceStartHeight);
		FVector EndLocation = StartLocation + FVector(0, 0, HeightTraceStartHeight * -1 - HeightTraceLength);

		FHitResult HitResult;

		// Set up the trace parameters
		FCollisionQueryParams TraceParams(FName(TEXT("MyTrace")), true, this);
		TraceParams.bTraceComplex = true;

		// Perform the line trace
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, HeightTraceChannel, TraceParams);

		// Handle the hit result as needed
		if (bHit)
		{
			TargetLocation.Z = HitResult.Location.Z;
		}
	}
}

void ACameraPawn::CameraCollision()
{
	if (bEnableCameraCollision)
	{
		FVector StartLocation = CameraComponent->GetComponentLocation() + FVector(0, 0, HeightTraceStartHeight);
		FVector EndLocation = StartLocation + FVector(0, 0, HeightTraceStartHeight * -1 + (CameraCollisionOffset) * -1);


		FHitResult HitResult;

		// Set up the trace parameters
		FCollisionQueryParams TraceParams(FName(TEXT("MyTrace")), true, this);
		TraceParams.bTraceComplex = true;

		// Perform the line trace
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, CameraCollisionTraceChannel, TraceParams);

		// Handle the hit result as needed
		if (bHit)
		{
			DragRotatePitch(CameraCollisionCorrectionSpeed * -1);
		}
	}
}

void ACameraPawn::HideCursorAndStorePosition()
{
	if (!PlayerController) return;

	bCanEdgeScroll = false;
	PlayerController->bShowMouseCursor = false;
	PlayerController->GetMousePosition(MouseCursorLocation.X, MouseCursorLocation.Y);
	PlayerController->SetInputMode(FInputModeGameOnly());
}

void ACameraPawn::RestoreCursor()
{
	if (!PlayerController) return;

	bCanEdgeScroll = true;
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetMouseLocation(MouseCursorLocation.X, MouseCursorLocation.Y);
	SetInputModeToDefault();
}

void ACameraPawn::SetInputModeToDefault()
{
	if (!PlayerController) return;

	PlayerController->SetInputMode(DefaultInputMode);
}

// Reset Camera Location and Position Functions

void ACameraPawn::ResetAllExceptLocation()
{
	ResetRotation();
	ResetZoom();
	ResetHeight();
}

void ACameraPawn::ResetLocation()
{
	TargetLocation = OriginalLocation;
}

void ACameraPawn::ResetAll()
{
	ResetRotation();
	ResetZoom();
	ResetHeight();
	ResetLocation();
	ResetFOV();
}

void ACameraPawn::ResetRotation()
{
	TargetRotation = OriginalRotation;
}

void ACameraPawn::ResetZoom()
{
	TargetZoom = StartingZoom;
}

// This function makes it so the first key call of the function resets rotation, and the second resets zoom. Some RTS games have this feature.

void ACameraPawn::ResetRotationThenZoom()
{
	if (TargetRotation != OriginalRotation)
	{
		ResetRotation();
	}
	else
	{
		ResetZoom();
	}
}

void ACameraPawn::ResetHeight()
{
	TargetHeight = StartingCameraHeight;
}

void ACameraPawn::ResetFOV()
{
	TargetFOV = StartingFOV;
}

float ACameraPawn::GetTimeDilationAdjustedTime(float DeltaTime)
{
	float TimeDilationDenominator = UGameplayStatics::GetGlobalTimeDilation(GetWorld());

	if (TimeDilationDenominator == 0)
	{
		TimeDilationDenominator = 1;
	}
	return DeltaTime / TimeDilationDenominator;
}
