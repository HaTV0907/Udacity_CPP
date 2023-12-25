#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode(){}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *pGraphEdge){
    _upPE.push_back(pGraphEdge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> upGraphEdge){ 
    _upCE.push_back(std::move(upGraphEdge));
}

void GraphNode::MoveChatbotHere(ChatBot chatbot){
        _chatBot = std::move(chatbot);
        _chatBot.SetCurrentNode(this);   
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode){
    newNode->MoveChatbotHere(std::move(_chatBot));
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index){
    return _upCE[index].get();
}