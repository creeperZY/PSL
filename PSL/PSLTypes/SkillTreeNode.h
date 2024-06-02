#pragma once


#include "SkillTreeNode.generated.h"

class UGameplayEffect;
class UImage;

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SkillName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentSkillLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxSkillLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText OtherInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> SkillGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SkillId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FromSkillId = 0;

	/*bool operator == (const FSkillInfo& Other) const
	{
		if (Other.SkillId == SkillId)
			return true;
		return false;
	}*/
	//FSkillInfo(int32 SkillId, int32 FromSkillId, int32 CurrentSkillLevel = 0, int32 MaxSkillLevel = 0) :
	//SkillId(SkillId), FromSkillId(FromSkillId){}
};

UCLASS()
class USkillTreeNode : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 FromId = 0;

	UPROPERTY(BlueprintReadOnly)
	FSkillInfo SkillInfo;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Level = 0;

	UPROPERTY(BlueprintReadWrite)
	bool Visited = false;

	UPROPERTY(BlueprintReadOnly)
	TArray<USkillTreeNode*> Children;


	USkillTreeNode(){}
	
	bool operator == (const USkillTreeNode* Other) const
	{
		if (Other->Id == Id)
			return true;
		return false;
	}
	void Initialize(const int32 InId, const int32 InFromId, const FSkillInfo& InSkillInfo)
	{
		Id = InId;
		FromId = InFromId;
		SkillInfo = InSkillInfo;
	}

	
	void AddChild(USkillTreeNode* Child)
	{
		Children.AddUnique(Child);
	}
	
};

UCLASS()
class USkillTreeManager : public UObject
{
	GENERATED_BODY()

public:
	
	USkillTreeManager(){}

	
	USkillTreeNode* BuildTree(TArray<FSkillInfo>& SkillInfosArray);

	//USkillTreeNode* GetRoot() const { return Root; }
	void PrintTreeByLevelInLog(USkillTreeNode* StartNode) const;


private:
	//PROPERTY()
	//USkillTreeNode* Root = nullptr;
	
	
};
