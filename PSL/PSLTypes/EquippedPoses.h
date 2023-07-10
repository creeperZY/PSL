#pragma once

UENUM(BlueprintType)
enum class EEquippedPoseType : uint8
{
	EEPT_RiflePose UMETA(DisplayName = "Rifle Pose"),
	EEPT_PistolPose UMETA(DisplayName = "Pistol Pose"),
	EEPT_MeleePose UMETA(DisplayName = "Melee Pose"),

	EEPT_MAX UMETA(DisplayName = "DefaultMAX")
};