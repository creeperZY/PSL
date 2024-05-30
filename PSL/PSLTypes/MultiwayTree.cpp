#include "MultiwayTree.h"


void UMultiwayTreeNode::AddToSubNodes(const FMultiwayTreeNodeInfo InInfo)
{
	const TObjectPtr<UMultiwayTreeNode> Node = NewObject<UMultiwayTreeNode>();
	Node->Info = InInfo;
	Node->UpperNode = this;
	SubNodes.AddUnique(Node);
}

void UMultiwayTreeNode::AddToThisLevelNodes(const FMultiwayTreeNodeInfo InInfo) const
{
	if (UpperNode)
	{
		const TObjectPtr<UMultiwayTreeNode> Node = NewObject<UMultiwayTreeNode>();
		Node->Info = InInfo;
		Node->UpperNode = UpperNode;
		UpperNode->SubNodes.AddUnique(Node);		
	}
}

UMultiwayTreeManager::UMultiwayTreeManager()
{
	RootNode = NewObject<UMultiwayTreeNode>();
	RootNode->UpperNode = nullptr;
}


