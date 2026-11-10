// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UECRPG_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** This is called automatically in BeginPlay and it should generally not be needed to be called in Blueprints unless there are specific needs concerning pawns which are not possessed on spawn. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Initialization")
	void Initialize();

	//General Camera Settings

	/** Sets the starting height of the camera's spring arm. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	float StartingCameraHeight = 50.0f;

	/** Sets the starting pitch of the camera's spring arm. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	float StartingPitch = 60.0f;

	/** Sets the starting length of the camera's spring arm. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	float StartingZoom = 4000.0f;

	/** If false, camera cannot rotate. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bCanRotate = true;

	/** If false, camera cannot zoom. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bCanZoom = true;

	/** Determines whether the mouse cursor is displayed on Begin Play(). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bBeginWithCursorEnabled = true;

	/** If true, rotation on the camera's pitch is inverted. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bInvertCameraPitch = false;

	/** Determines whether the camera can edge scroll. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bCanEdgeScroll = true;

	/** Determines whether rotation around the z-axis is inverted. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bInvertHorizontalRotation = false;

	/** Determines whether it is possible to rotate the camera's pitch using input. The camera can still pitch upwards on zoom if this is false. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bFreeVerticalPitchEnabled = false;

	/** Determines whether custom speeds are used when the automatically pitches upward when the player zooms in. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bCustomPitchUpOnZoomRotationsEnabled = true;

	/** Determines whether custom autoamtically pitches upward when the camera zooms in. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|General")
	bool bPitchUpOnZoomEnabled = false;

	/** If true, movement and lerp speeds are adjusted by the frame rate so speeds are more consistent at different frame rates. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Camera Settings|General")
	bool bFrameRateSpeedAdjustmentEnabled = true;

	/** If false, the input mode, cursor lock, and show mouse cursor settings will not be overriden on the PlayerController. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Camera Settings|General")
	bool bInitializeCursorAndInputModeSettings = true;

	/** This is the location the pawn is moved to when approaching the TargetLocation. It is a lerp value that does not need to be accessed directly. */
	FVector LerpLocation = FVector(0, 0, 0);

	/** The starting rotation of the camera. It is automatically set on BeginPlay(). */
	FRotator OriginalRotation = FRotator(0, 0, 0);

	/** The starting location of the camera. It is automatically set on BeginPlay(). */
	FVector OriginalLocation = FVector(0, 0, 0);

	/** The starting zoom level of the camera. It is automatically set on BeginPlay(). */
	float OriginalZoom = 0;

	/** The location the pawn is interpolating towards. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	FVector TargetLocation;

	/** The rotation the pawn is interpolating towards. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Rotation")
	FRotator TargetRotation;

	/** The spring arm length the spring arm is interpolating towards. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Zoom")
	float TargetZoom;

	/** The height the spring arm is interpolating towards. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	float TargetHeight;

	/** If false, interpolation is not used. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	bool bInterpolationEnabled = true;

	/** Sets the starting FOV of the camera. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	float StartingFOV = 60.0f;

	/** Sets the FOV of the camera. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|FOV")
	void SetTargetFOV(float FOV);

	//Movement Settings

	/** Move speeds determine how fast the camera pawn moves. Lerp speeds determine how smooth the movement is.
	Use lower lerp speeds for smoother camera movement.
	Use higher lerp speeds for snappier camera movement. */

	/** The default move speed of the pawn. Intended for use with input based movement (i.e., WSAD movement). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float DefaultMoveSpeed = 150.0f;

	/** The default move lerp speed. Intended for use with input based movement (i.e., WSAD movement). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float DefaultMoveLerpSpeed = 8.0f;

	/** The drag move speed of the pawn. Intended for use with movement caused by dragging the mouse while holding another input. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float DragMoveSpeed = 150.0f;

	/** The drag move lerp speed of the pawn. Intended for use with movement caused by dragging the mouse while holding another input. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float DragMoveLerpSpeed = 8.0f;

	/** Edge scrolling movement speed is equal to the DefaultMoveSpeed multiplied by this multipler. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float EdgeScrollMoveSpeedMultiplier = 1.5f;

	/** The lerp speed of edge scrolling. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float EdgeScrollLerpSpeed = 10.0f;

	/** The threshold at which the edge scrolling begins.
	For example, if you set this to 0.1, the edge scroll would begin when the mouse cursor is in the outer 10% of the screen. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float EdgeScrollZone = 0.01f;

	/** The value of the move speed currently being used. There is no need to edit this unless custom movement behaviors are desired.
	The relevant functions already update the ActiveMoveSpeed to be equal to the applicable move speed.*/
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	float ActiveMoveSpeed = 100.0f;

	/** The value of the move lerp speed currently being used. There is no need to edit this unless custom movement behaviors are desired.
	The relevant functions already update the ActiveMovLerpeSpeed to be equal to the applicable lerp speed.*/
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	float ActiveMoveLerpSpeed = 0.1f;


	//Movement Functions

	/** Moves the camera in the forward vector. Uses DefaultMoveSpeed and DefaultMoveLerpSpeed.
	Intended to receive input axis values between -1 and 1 with backwards movement resulting from a negative input parameter. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void MoveForward(float AxisValue);

	/** Moves the camera in the right vector. Uses DefaultMoveSpeed and DefaultMoveLerpSpeed.
	Intended to receive input axis values between -1 and 1 with leftward movement resulting from a negative input paramete. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void MoveRight(float AxisValue);

	/** Moves the spring arm in the up vector. Uses DefaultMoveSpeed and DefaultMoveLerpSpeed.
	Intended to receive input axis values between -1 and 1 with downward movement resulting from a negative input paramete. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void MoveUp(float AxisValue);

	/** Moves the camera in the forward vector. Uses DragMoveSpeed and DragMoveLerpSpeed.
	Intended for use with movement caused by dragging the mouse while holding another input. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void DragMoveForward(float AxisValue);

	/** Moves the camera in the right vector. Uses DragMoveSpeed and DragMoveLerpSpeed.
	Intended for use with movement caused by dragging the mouse while holding another input. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void DragMoveRight(float AxisValue);

	/** Moves the camera in the forward and right vectors. Uses DragMoveSpeed and DragMoveLerpSpeed.
	Intended for use with movement caused by dragging the mouse while holding another input. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void DragMove(float AxisValueX, float AxisValueY);

	/** Moves the camera pawn to a location.
	*@param Location sets the move location target.
	*@param bOverrideMoveSpeedValues If true, the next two parameters will set the ActiveMoveSpeed and the ActiveLerpSpeed.
	*@param MoveSpeedOverride sets the ActiveMoveSpeed.
	*@param MoveLerpSpeedOverride sets the ActiveMoveLerpSpeed.. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void InterpolatedMoveToLocation(FVector Location, bool bOverrideMoveSpeedValues = false, float MoveSpeedOverride = 4.0f, float MoveLerpSpeedOverride = 4.0f);

	/** Snaps the camera to @param Location immediately with no interpolation. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void SnapToLocation(FVector Location);

	/** Moves the camera pawn to the hit location under the mouse cursor using the HitUnderCursorTraceChannel which can be set in Blueprints.
	*@param Location sets the move location target.
	*@param bOverrideMoveSpeedValues If true, the next two parameters will set the ActiveMoveSpeed and the ActiveLerpSpeed.
	*@param MoveSpeedOverride sets the ActiveMoveSpeed.
	*@param MoveLerpSpeedOverride sets the ActiveMoveLerpSpeed.. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void MoveToLocationUnderCursor(bool bOverrideMoveSpeedValues = false, float MoveSpeedOverride = 4.0f, float MoveLerpSpeedOverride = 4.0f);

	/** Handles edge scrolling movement and is called on tick. */
	void EdgeScroll();

	/** Sets ActiveMoveSpeed to @param MoveSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void SetMoveSpeed(float MoveSpeed);

	/** Sets ActiveMoveLerpSpeed to @param MoveLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void SetMoveLerpSpeed(float MoveLerpSpeed);

	/** Sets ActiveMoveLerpSpeed to @param MoveSpeed and sets ActiveMoveLerpSpeed to @param MoveLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Movement")
	void SetMoveAndLerpSpeed(float MoveSpeed, float MoveLerpSpeed);

	//End of Movement


	//Rotation Settings

	/** The default rotation speed of the pawn. Intended for use with input based movement (i.e., rotating while holding Q or E). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation", meta = (ToolTip = "Sets the rotation speed when using Rotate(), which is intended to be used when holding keys to rotate."))
	float DefaultRotationSpeed = 2.0f;

	/** The default rotation lerp speed of the pawn. Intended for use with input based movement (i.e., rotating while holding Q or E). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation", meta = (ToolTip = "Sets the rotation lerp speed when using Rotate(), which is intended to be used when holding keys to rotate."))
	float DefaultRotationLerpSpeed = 8.0f;

	/** The drag rotation speed of the pawn. Intended for use with rotation caused by dragging the mouse while holding an input key. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float DragRotationSpeed = 2.0f;

	/** The drag rotation lerp speed of the pawn. Intended for use with rotation caused by dragging the mouse while holding an input key. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float DragRotationLerpSpeed = 8.0f;

	/** The value of the rotation speed currently being used. There is no need to edit this unless custom movement behaviors are desired.
	The relevant functions already update the ActiveRotationSpeed to be equal to the applicable move speed.*/
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Rotation")
	float ActiveRotationSpeed = 2.0f;

	/** The value of the rotation lerp speed currently being used. There is no need to edit this unless custom movement behaviors are desired.
	The relevant functions already update the ActiveRotationLerpSpeed to be equal to the applicable move speed.*/
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Rotation")
	float ActiveRotationLerpSpeed = 2.0f;

	/** The minimum pitch of the camera. The camera cannot pitch below this value. Set to zero to allow camera direction to be parallel with the ground */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float MinPitch = 10.0f;

	/** The maximum pitch of the camera. The camera cannot pitch above this value. Set to 90.0f to allow the camera to be fully top-down. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float MaxPitch = 80.0f;

	/** The movement speed when rotating by an incremental amount (i.e., a quarter turn). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float IncrementalRotationSpeed = 2.0f;

	/** The movement lerp speed when rotating by an incremental amount (i.e., a quarter turn). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float IncrementalRotationLerpSpeed = 8.0f;

	/** The amount the camera should rotate when using the incremental rotation functions. As an example, 90.0f would produce a quarter turn. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation")
	float IncrementalRotationAmount = 45.0f;

	/** The initial rotation of the pawn on the z-axis. Stored on BeginPlay() and accessible in camera reset functions. */
	float StartingCameraZRotation = 0.0f;

	/** The rotation speed of the camera when pitching upwards on zoom. Only has an effect if bCustomPitchUpOnZoomRotationsEnabled is true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation", meta = (ToolTip = "Sets the rotation speed when using Rotate(), which is intended to be used when holding keys to rotate."))
	float PitchUpOnZoomRotationSpeed = 6.0f;

	/** The rotation lerp speed of the camera when pitching upwards on zoom. Only has an effect if bCustomPitchUpOnZoomRotationsEnabled is true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Rotation", meta = (ToolTip = "Sets the rotation lerp speed when using Rotate(), which is intended to be used when holding keys to rotate."))
	float PitchUpOnZoomRotationLerpSpeed = 4.0f;


	//Rotation Functions

	/** Rotates the pawn on the z-axis. Uses DefaultRotationSpeed and DefaultRotationLerpSpeed.
	Intende for use with rotation caused by holding an input down (i.e., rotating while holding Q or E). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera. Intended to take an input value of -1 to 1 as a parameter."))
	void Rotate(float AxisValue);

	/** Rotates the pawn to the right by the IncrementalRotationAmount on the z-axis. Uses IncrementalRotationSpeed and IncrementalRotationLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera to the right by the amount set by IncrementalRotationAmount. Intended for things like rotating a quarter turn on a single click."))
	void IncrementalRotateRight();

	/** Rotates the pawn to the left by the IncrementalRotationAmount on the z-axis. Uses IncrementalRotationSpeed and IncrementalRotationLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera to the left by the amount set by IncrementalRotationAmount. Intended for things like rotating a quarter turn on a single click."))
	void IncrementalRotateLeft();

	/** Rotates the pawn on the z-axis.  Uses DragRotationSpeed and DragRotationLerpSpeed.
	Intended for use with rotation caused by dragging the mouse while holding an input key.*/
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera horizontally around the z-axis. Intended to take mouse x as a parameter while holding a key to rotate on mouse movement."))
	void DragRotateYaw(float AxisValue);

	/** Rotates the pitch of the camera.  Uses DragRotationSpeed and DragRotationLerpSpeed.
	Intended for use with rotation caused by dragging the mouse while holding an input key.*/
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera's pitch up and down. Intended to take mouse y as a parameter while holding a key to rotate on mouse movement."))
	void DragRotatePitch(float AxisValue);

	/** Rotates the yaw and pitch of the camera.  Uses DragRotationSpeed and DragRotationLerpSpeed.
	Intended for use with rotation caused by dragging the mouse while holding an input key.*/
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation", meta = (ToolTip = "Rotates the camera's freely. Intended to take mouse x and y as a parameters while holding a key to rotate on mouse movement. Calls DragRotateYaw and DragRotatePitch simultaneously"))
	void DragFreeRotate(float AxisValueX, float AxisValueY);

	/** Sets bCanRotate to true, allowing the camera to rotate. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation")
	void EnableRotation();

	/** Sets bCanRotate to false, prohibiting camera rotation. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation")
	void DisableRotation();

	/** Sets the ActiveRotationSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation")
	void SetRotationSpeed(float RotationSpeed);

	/** Sets the ActiveRotationLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation")
	void SetRotationLerpSpeed(float RotationLerpSpeed);

	/** Sets the ActiveRotationSpeed and the ActiveRotaitonLerpSpeed. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Rotation")
	void SetRotationAndLerpSpeed(float RotationSpeed, float RotationLerpSpeed);

	//End of Rotation


	//Zoom Settings

	/** Sets the speed by which the spring arm length changes when zooming. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float ZoomSpeed = 250.0f;

	/** Sets the lerp speed for changes to the spring arm length when zooming. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float ZoomLerpSpeed = 0.03f;

	/** Sets the minimum spring arm length of the camera. The lower the value, the closer the camera can zoom to the pawn's location. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float MinZoom = 500.0f;

	/** Sets the minimum spring arm length of the camera. The higher the value, the farther the camera can zoom out from the pawn's location. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float MaxZoom = 8000.0f;

	/** Sets the camera's pitch when fully zoomed in, if using optional bPitchUpOnZoom = true setting. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float ZoomedInPitch = 15.0f;

	/** Sets the camera's pitch when fully zoomed out, if using optional bPitchUpOnZoom = true setting. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	float ZoomedOutPitch = 60.0f;

	/** Sets the zoom level at which the camera begins pitching upwards if using bPitchUpOnZoom = true.
	As an example, if this equals 1.0f, the camera begins pitching upwards as soon as it zooms in any amount from the MaxZoom level.
	If this equals 0.5f, the camera will zoom in 50% before it starts pitching upwards. This means if MaxZoom = 10000.0f and MinZoom = 2000.0f, the camera would only pitch up at 6000.0f and below.
	At values above 6000.0f, the camera's pitch would be equal to  ZoomedOutPitch.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom", meta = (ClampMin = "0.0", ClampMax = "1.0"), meta = (ToolTip = "A value between 0 and 1 which determines when the camera starts pitching upwards on zoom if that option is enabled. 1 means it pitches upward as soon as the camera zooms any amount."))
	float PitchUpOnZoomThreshold = 1.0f;

	/** Sets amount of zoom levels if using incremental zoom (i.e., you press one input to zoom in 33.3% if there are four zoom levels. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Zoom")
	int IncrementalZoomLevels = 4;

	/** Determines whether zooming the camera in affects the FOV of the camera */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	bool bZoomAffectsFOV = true;

	/** The FOV of the camera at the minimum zoom level */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	float ZoomedInFOV = 45.0f;

	/** The FOV of the camera at the maximum zoom level */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	float ZoomedOutFOV = 60.0f;

	/** Sets the lerp speed for changes to the FOV. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	float FOVLerpSpeed = 0.02f;

	/** The zoomed in percentage threshold at which zooming starts to affect the camera's FOV. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|FOV")
	float FOVZoomThreshold = 0.25;

	/** Sets the camera's pitch when fully zoomed out, if using optional bPitchUpOnZoom = true setting. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|FOV")
	float TargetFOV = 60.0f;

	//Zoom Functions

	/** Handles camera zoom. Intended for use with mouse scroll wheel. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Zoom")
	void Zoom(float AxisValue);

	/** Handles incremental zoom. Intended for use with clicking one input to zoom in by a specified amount. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Zoom")
	void IncrementalZoomIn();

	/** Handles incremental zoom. Intended for use with clicking one input to zoom out by a specified amount. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Zoom")
	void IncrementalZoomOut();

	/** Sets bCanZoom equal to true, enabling zoom. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Zoom")
	void EnableZoom();

	/** Sets bCanZoom equal to false, disabling zoom. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Zoom")
	void DisableZoom();

	//End of Zoom

	//Reset Camera Functions

	/** Resets camera rotation and zoom to values at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetAllExceptLocation();

	/** Resets camera location to location at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetLocation();

	/** Resets camera location, rotation and zoom to values at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetAll();

	/** Resets camera zoom to zoom value at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetZoom();

	/** Resets camera rotation to rotation value at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetRotation();

	/** Resets camera rotation to rotation value at BeginPlay(), and if that is already equal to such value, then resets zoom to zoom value at begin play. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetRotationThenZoom();

	/** Resets spring arm z-value to value at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetHeight();

	/** Resets spring arm z-value to value at BeginPlay(). */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Reset")
	void ResetFOV();

	//End of Reset Camera


	//Camera Bounds Settings

	/** Sets the minimum x-value to which the camera can travel, if bCameraBoundsEnabled = true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds", meta = (ToolTip = "Min X Bound"))
	float MinXBound = 0.0f;

	/** Sets the maximum x-value to which the camera can travel, if bCameraBoundsEnabled = true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds", meta = (ToolTip = "Max X Bound"))
	float MaxXBound = 10000.0f;

	/** Sets the minimum y-value to which the camera can travel, if bCameraBoundsEnabled = true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds", meta = (ToolTip = "Min Y Bound"))
	float MinYBound = 0.0f;

	/** Sets the maximum y-value to which the camera can travel, if bCameraBoundsEnabled = true. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds", meta = (ToolTip = "Max Y Bound"))
	float MaxYBound = 10000.0f;

	/** Sets the minimum z-value to which the spring arm can travel. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds")
	float MinCameraHeight = 50.0f;

	/** Sets the maximum z-value to which the spring arm can travel. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds")
	float MaxCameraHeight = 5000.0f;

	/** If false, camera XY movement is unbound. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Camera Bounds")
	bool bCameraBoundsEnabled = false;

	//End of Camera Bounds Settings

	//Camera Follow Settings

	/** Sets the move speed when using follow actor functions. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float FollowMoveSpeed = 100.0f;

	/** Sets the move lerp speed when using follow actor functions. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Movement")
	float FollowMoveLerpSpeed = 6.0f;

	/** If true, camera follows the FollowTarget. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	bool bIsFollowingActor = false;

	/** Sets the FollowTarget the camera is following when bIsFollowingActor = true. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Movement")
	AActor* FollowTarget;

	//Camera Follow Functions

	/** Sets FollowActor and sets bIsFollowingActor to true, enabling the camera follow mode. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Follow")
	void StartFollowingActor(AActor* ActorToFollow);

	/** Sets bIsFollowingActor to false, disabling the camera follow mode. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Follow")
	void StopFollowingActor();

	/** Set this to the maximum height you would want to trace downward from. If your terrain is only 2000.0f tall, this can be 2000.0f or some value close to it.
	If this value is set too low, the camera will not detect a hit on height traces that are above the collision trace point set by this variable. */	void FollowActor();

	//End of Camera Follow


	//Height Trace Settings

	/** If false, camera will not adjust height for collisions with the HeightTraceChannel. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	bool bHeightTraceEnabled = true;

	/** Set this to the maximum height you would want to trace downward from. If your terrain is only 2000.0f tall, this can be 2000.0f or some value close to it.
	If this value is set too low, the camera will not detect a hit on height traces that are above the collision trace point set by this variable. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	float HeightTraceStartHeight = 10000.0f;

	/** A buffer variable that ensures the collision trace goes beyond the pawn when tracing downwards from HeightTraceStartHeight. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	float HeightTraceLength = 2000.0f;

	/** The collision channel used for HeightTraces. Can be updated in Blueprints. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	TEnumAsByte <ECollisionChannel> HeightTraceChannel = ECC_WorldStatic;

	//Height Trace Functions

	/** Handles height tracing in tick, if bHeightTraceEnabled = true. */
	void HeightTrace();

	//End of  Height Trace


	//Camera Collision Settings

	/** If false, camera won't collide with anything. Should be disabled in games where camera will never be allowed close enough to terrain/etc. that it needs to collide with. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	bool bEnableCameraCollision = false;

	/** Sets the collision channel for camera collision. Can be set in Blueprints. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	TEnumAsByte <ECollisionChannel> CameraCollisionTraceChannel = ECC_WorldStatic;

	/** Sets the collision channel for MoveToLocationUnderCursor() traces, which can be used to move the camera to the cursor location. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	TEnumAsByte <ECollisionChannel> HitUnderCursorTraceChannel = ECC_WorldStatic;

	/** Sets the camera height avoidance amount. (i.e., how far away from the collision channel the camera should stay on the z-axis)  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	float CameraCollisionOffset = 200;

	/** Sets at which the camera pitches upward to avoid collision. A higher amount will produce a jerkier result but helps to ensure the camera does not clip through anything. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera Settings|Collision")
	float CameraCollisionCorrectionSpeed = 3;

	//Camera Collision Functions

	/** Handles camera collision in tick, if bEnableCameraCollision = true. */
	void CameraCollision();

	//End of Camera Collision

	// Mouse Cursor Items

	/** A stored value for the mouse cursor. Used when the cursor needs to be hidden when doing drag based input or rotation. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera|Cursor")
	FVector2D MouseCursorLocation = FVector2D(0, 0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTS Camera|Cursor")
	EMouseLockMode MouseLockMode = EMouseLockMode::LockAlways;

	/** Hides the cursor and stores its location so it can reappear in the same place after doing drag movement or rotation. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Cursor")
	void HideCursorAndStorePosition();

	/** Restores the mouse cursor as visible at the MouseCursorLocation. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Cursor")
	void RestoreCursor();

	/** Sets the Input Mode to the "Default" mode setup on the pawn. This provides an easy way to restore the Input Mode to GameAndUI without having to reset/toggle mouse lock settings, etc.*/
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Cursor")
	void SetInputModeToDefault();

	//Camera Location Hotkey Functions

	/** Sets the camera location to the current location of the pawn. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Camera Locations")
	void SetCameraLocation(int CameraLocation);

	/** Snaps the pawn's location to the location of the relevant camera hotkey, if it has been set. */
	UFUNCTION(BlueprintCallable, Category = "RTS Camera|Input")
	void GoToCameraLocation(int CameraLocation);

	//End of Camera Location Hotkeys

		//General input booleans

	/** RTS cameras frequently use control, shift, and alt controls, so I have included booleans for whether they are held, but this can be handled as desired using other input methods. */
	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Input")
	bool bControlHeld = false;

	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Input")
	bool bShiftHeld = false;

	UPROPERTY(BlueprintReadWrite, Category = "RTS Camera Settings|Input")
	bool bAltHeld = false;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	float LerpZoom;
	float LerpHeight;
	float LerpFOV;
	FRotator LerpRotation;

private:

	/** Called in movement functions to ensure the camera does not move beyond its location bounds. */
	void LocationBounds();

	/** Called in rotation functions to ensure the camera does not rotate beyond its rotation bounds. */
	void RotationBounds();

	/** Responsible for setting the frame rate multiplier to adjust move and lerp speeds for different frame rates, if enabled. */
	void SetFrameRateMultiplier();

	/** Returns a float which is DeltaTime adjusted for current Time Dilation (or 1 if Time Dilation is 0, since camera still moves when paused). */
	float GetTimeDilationAdjustedTime(float DeltaTime);

	//Camera Location Hotkey Settings

	/** Vector locations that store camera location hotkeys. */
	FVector CameraLocation1 = FVector(0, 0, 0);
	FVector CameraLocation2 = FVector(0, 0, 0);
	FVector CameraLocation3 = FVector(0, 0, 0);
	FVector CameraLocation4 = FVector(0, 0, 0);
	FVector CameraLocation5 = FVector(0, 0, 0);
	FVector CameraLocation6 = FVector(0, 0, 0);
	FVector CameraLocation7 = FVector(0, 0, 0);
	FVector CameraLocation8 = FVector(0, 0, 0);

	/** Booleans which track whether camera location hotkeys have been set. */
	bool bCameraLocation1Set = false;
	bool bCameraLocation2Set = false;
	bool bCameraLocation3Set = false;
	bool bCameraLocation4Set = false;
	bool bCameraLocation5Set = false;
	bool bCameraLocation6Set = false;
	bool bCameraLocation7Set = false;
	bool bCameraLocation8Set = false;

	//Camera Initialization Settings

	/** The below include several components and variables initialized by the camera. */

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RTS Camera|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RTS Camera|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> DirectionComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RTS Camera|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RTS Camera|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RTS Camera|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> PlayerController;

	FInputModeGameAndUI DefaultInputMode;

	float PreviousRealTimeSeconds;
	float FrameRateMultiplier;

	bool bInitialized;
};
