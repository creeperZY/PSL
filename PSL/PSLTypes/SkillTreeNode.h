#pragma once


#include "SkillTreeNode.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* SkillImage;

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

	bool operator == (const FSkillInfo& Other) const
	{
		if (Other.SkillId == SkillId)
			return true;
		return false;
	}
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

	// Notice: parameter is a copy, so just use character's index, it's ok
	USkillTreeNode* BuildTree(TArray<FSkillInfo> SkillInfosArray); 
	USkillTreeNode* GetNodeFromId(const int32 Id);
	// Can partially update SkillInfosArray
	void UpdateInfosArrayFromStartTreeNode(USkillTreeNode* StartNode, TArray<FSkillInfo>& SkillInfosArray); 
	void UpdateInfosArrayFromInternalIdToNodeMap(TArray<FSkillInfo>& SkillInfosArray);
	// Random traversal in tree, to randomly add skill points
	// void RandomTraversalInTree(USkillTreeNode* StartNode, int32 Steps);
	USkillTreeNode* GetRoot() const { return Root; }
	void PrintTreeByLevelInLog(USkillTreeNode* StartNode) const;


private:
	UPROPERTY()
	USkillTreeNode* Root = nullptr;
	UPROPERTY()
	TMap<int32, USkillTreeNode*> IdToNodeMap;
	
};
