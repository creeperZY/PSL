#include "SkillTreeNode.h"



USkillTreeNode* USkillTreeManager::BuildTree(TArray<FSkillInfo> SkillInfosArray)
{
	// Why not using reference of TArray, because we want to randomly use array index in UI and update GAS
	SkillInfosArray.Sort([&](const FSkillInfo& Info1, const FSkillInfo& Info2)
	{
		return Info1.FromSkillId < Info2.FromSkillId || Info1.FromSkillId == Info2.FromSkillId && Info1.SkillId < Info2.SkillId;
	});

	
	IdToNodeMap.Empty();
	USkillTreeNode* RootNode = nullptr;

	
	for (const FSkillInfo& Info : SkillInfosArray)
	{
		const int32 FromId = Info.FromSkillId;
		const int32 Id = Info.SkillId;
		
		if (!IdToNodeMap.Contains(Id))
		{
			USkillTreeNode* NewNode = NewObject<USkillTreeNode>();
			NewNode->Initialize(Info.SkillId, Info.FromSkillId, Info);
			IdToNodeMap.Add(Id,  NewNode);
		}

		if (FromId == -1)
		{
			RootNode = IdToNodeMap[Id];
			RootNode->Level = 0;
		}
		else
		{
			if (!IdToNodeMap.Contains(FromId))
			{
				USkillTreeNode* NewNode = NewObject<USkillTreeNode>();
				NewNode->Initialize(Info.SkillId, Info.FromSkillId, Info);
				IdToNodeMap.Add(FromId, NewNode);
			}
			IdToNodeMap[FromId]->AddChild(IdToNodeMap[Id]);
			IdToNodeMap[Id]->FromId = FromId;
			IdToNodeMap[Id]->Level = IdToNodeMap[FromId]->Level + 1;
		}
	}
	
	//UE_LOG(LogTemp, Warning, TEXT(" node 0 fromid: %d"), Nodes[0]->FromId);

	Root = RootNode;
	
	return RootNode;

}

USkillTreeNode* USkillTreeManager::GetNodeFromId(const int32 Id)
{
	checkf(Root, TEXT("Skill tree is not built!"))
	if (IdToNodeMap.Contains(Id))
	{
		return IdToNodeMap[Id];
	}
	return nullptr;
}

void USkillTreeManager::UpdateInfosArrayFromStartTreeNode(USkillTreeNode* StartNode, TArray<FSkillInfo>& SkillInfosArray)
{
	// Select all infos from a node (branch) to update TArray
	// Level order traversal
	checkf(Root, TEXT("Skill tree is not built!"))
	if (StartNode == nullptr) return;
	
	TArray<USkillTreeNode*> Queue;
	Queue.Push(StartNode);

	TArray<FSkillInfo> LevelOrderSkillInfos;

	while (!Queue.IsEmpty())
	{
		const int LevelSize = Queue.Num(); 

		for (int32 i = 0; i < LevelSize; ++i)
		{
			USkillTreeNode* Node = Queue[0];
			Queue.RemoveAt(0);
			Queue.Shrink();

			LevelOrderSkillInfos.Push(Node->SkillInfo);

			for (USkillTreeNode* Child : Node->Children) 
			{
				Queue.Push(Child);
			}
		}
		
	}
	
	// Update TArray
	for(FSkillInfo& CharacterSkillInfo : SkillInfosArray)
	{
		if (IdToNodeMap.Contains(CharacterSkillInfo.SkillId))
		{
			CharacterSkillInfo = IdToNodeMap[CharacterSkillInfo.SkillId]->SkillInfo;
		}
	}
	
	
}

void USkillTreeManager::UpdateInfosArrayFromInternalIdToNodeMap(TArray<FSkillInfo>& SkillInfosArray)
{
	// Update TArray from internal TMap
	checkf(Root, TEXT("Skill tree is not built!"))
	for(FSkillInfo& CharacterSkillInfo : SkillInfosArray)
	{
		if (IdToNodeMap.Contains(CharacterSkillInfo.SkillId))
		{
			CharacterSkillInfo = IdToNodeMap[CharacterSkillInfo.SkillId]->SkillInfo;
		}
	}
}




void USkillTreeManager::PrintTreeByLevelInLog(USkillTreeNode* StartNode) const
{
	if (StartNode == nullptr) return;
	
	TArray<USkillTreeNode*> Queue;
	Queue.Push(StartNode);

	int CurrentLevel = 0;
	while (!Queue.IsEmpty())
	{
		const int LevelSize = Queue.Num(); 
		TArray<USkillTreeNode*> LevelNodes;

		for (int32 i = 0; i < LevelSize; ++i)
		{
			USkillTreeNode* Node = Queue[0];
			Queue.RemoveAt(0);
			Queue.Shrink();

			LevelNodes.Push(Node);

			for (USkillTreeNode* Child : Node->Children) 
			{
				Queue.Push(Child);
			}
		}
		
		FString PrintString = "Level " + FString::FromInt(CurrentLevel) + " : ";
		for (const USkillTreeNode* Node : LevelNodes)
		{
			FString NodeIdString = FString::FromInt(Node->Id);
			FString NodeFromIdString = FString::FromInt(Node->FromId);
			PrintString += NodeIdString + "(" + NodeFromIdString + ") ";// + Node->SkillInfo.SkillName;
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintString);

		CurrentLevel++;
	}
	
}
