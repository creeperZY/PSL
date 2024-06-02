#include "SkillTreeNode.h"



USkillTreeNode* USkillTreeManager::BuildTree(TArray<FSkillInfo>& SkillInfosArray)
{
	SkillInfosArray.Sort([&](const FSkillInfo& Info1, const FSkillInfo& Info2)
	{
		return Info1.FromSkillId < Info2.FromSkillId || Info1.FromSkillId == Info2.FromSkillId && Info1.SkillId < Info2.SkillId;
	});

	TMap<int32, USkillTreeNode*> Nodes;
	USkillTreeNode* RootNode = nullptr;

	
	for (const FSkillInfo& Info : SkillInfosArray)
	{
		const int32 FromId = Info.FromSkillId;
		const int32 Id = Info.SkillId;
		
		if (!Nodes.Contains(Id))
		{
			USkillTreeNode* NewNode = NewObject<USkillTreeNode>();
			NewNode->Initialize(Info.SkillId, Info.FromSkillId, Info);
			Nodes.Add(Id,  NewNode);
		}

		if (FromId == -1)
		{
			RootNode = Nodes[Id];
			RootNode->Level = 0;
		}
		else
		{
			if (!Nodes.Contains(FromId))
			{
				USkillTreeNode* NewNode = NewObject<USkillTreeNode>();
				NewNode->Initialize(Info.SkillId, Info.FromSkillId, Info);
				Nodes.Add(FromId, NewNode);
			}
			Nodes[FromId]->AddChild(Nodes[Id]);
			Nodes[Id]->FromId = FromId;
			Nodes[Id]->Level = Nodes[FromId]->Level + 1;
		}
	}

	Nodes[0]->SkillInfo.SkillName = "xxxxxx";
	UE_LOG(LogTemp, Warning, TEXT(" node 0 fromid: %d"), Nodes[0]->FromId);
	UE_LOG(LogTemp, Warning, TEXT(" node 0 skillfromid: %d"), Nodes[0]->SkillInfo.SkillId);
	UE_LOG(LogTemp, Warning, TEXT(" node 0 skillname: %s"), *Nodes[0]->SkillInfo.SkillName);
	Nodes[0]->SkillInfo.SkillName = "yyyyyy";

	//this->Root = RootNode;
	return RootNode;

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