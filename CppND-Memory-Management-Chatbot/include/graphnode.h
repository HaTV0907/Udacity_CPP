#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include "chatbot.h"
#include <memory>

// forward declarations
class GraphEdge;

class GraphNode
{
private:
    // data handles (owned)
    std::vector<std::unique_ptr<GraphEdge>> _upCE;  // edges to subsequent nodes

    // data handles (not owned)
    std::vector<GraphEdge *> _upPE; // edges to preceding nodes 
    ChatBot _chatBot;
    // proprietary members
    int _id;
    std::vector<std::string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _upCE.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _upPE.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *pGraphEdge);
    void AddEdgeToChildNode(std::unique_ptr<GraphEdge> upGraphEdge);

    void MoveChatbotHere(ChatBot chatbot);
    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */