#pragma once

#include "MultiwayTree.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FMultiwayTreeNodeInfo
{
	GENERATED_BODY()
	
	
	//TSubclassOf<UGameplayEffect> 
};

//first is zero


class UMultiwayTreeManager;


UCLASS()
class UMultiwayTreeNode : public UObject
{
	GENERATED_BODY()
	
public:
	friend class UMultiwayTreeManager;
	FMultiwayTreeNodeInfo Info;
	FMultiwayTreeNodeInfo GetNodeInfo() const { return Info; }

	TArray<TObjectPtr<UMultiwayTreeNode>>& GetSubNodes() { return SubNodes; }
	void AddToSubNodes(FMultiwayTreeNodeInfo InInfo);
	void AddToThisLevelNodes(FMultiwayTreeNodeInfo InInfo) const;
	TObjectPtr<UMultiwayTreeNode> GetUpperNode() const { return UpperNode; }
	int32 GetBranchIndex() const { return BranchIndex; }
	int32 GetNodeLevel() const { return NodeLevel; }
	int32 GetGlobalNodeIndex() const { return GlobalNodeIndex; }

private:
	TObjectPtr<UMultiwayTreeNode> UpperNode;
	TArray<TObjectPtr<UMultiwayTreeNode>> SubNodes;	
	int32 BranchIndex = 0;
	int32 NodeLevel = 0;
	int32 GlobalNodeIndex = 0;
};



UCLASS()
class UMultiwayTreeManager : public UObject
{
	GENERATED_BODY()
	
public:
	bool GetNodeInfoByGlobalIndex(FMultiwayTreeNodeInfo& InInfo, int32 Index);
	//bool GetNodeInfosByLevel(TArray<FMultiwayTreeNodeInfo>& Infos, int32 Level);
	//bool AddNodeToLevel(FMultiwayTreeNodeInfo Info, int32 Level);
	//bool AddNodesToLevel(TArray<FMultiwayTreeNodeInfo>& Infos, int32 Level);
	//bool GetNodeInfoInLevelByIndex(FMultiwayTreeNodeInfo& Info, int32 Level, int32 Index);
	void DumpNodesToArray();
	
	UMultiwayTreeManager();

	TObjectPtr<UMultiwayTreeNode> GetRootNode() { return RootNode; }
private:
	void ArrangeNodeIndices();
	TMap<int32, TObjectPtr<UMultiwayTreeNode>> IndexToMultiwayTreeNodeMap;
	TObjectPtr<UMultiwayTreeNode> RootNode;

	
};
