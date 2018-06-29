#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <map>
#include <list>
#include <stack>
#include <vector>
#include <memory>
#include <QDebug>
#include <QString>

using namespace std;

typedef struct Node
{
    QString Name;
    QString FirstLetter;
    QString LastLetter;
    vector<Node*> Next;
    bool VisitedFlag = false;
}NODE;

class Algorithm
{
public:
    Algorithm();

    bool CreatGraph(vector<QString> &Buffer, vector<Node> &Graph);
    void DFS(vector<Node> &Graph, NODE* NodeNextPtr, vector<Node> Path, vector<vector<QString>> &PathAll);
    bool DFS(vector<Node> &Graph, unsigned int Start, vector<vector<QString>> &OutputPath);
    struct Compare_2
    {
        Compare_2(Node const& node) :  NodeTmp(node){ }

        bool operator () (Node const& Element)
        {
            return (Element.Name == NodeTmp.Name);
        }

        NODE NodeTmp;
    };

    struct Compare_3
    {
        Compare_3(Node const& node) : NodeTmp(node){ }

        bool operator () (std::pair<QString,Node> const& Element)
        {
            return (Element.second.Name == NodeTmp.Name);
        }

        NODE NodeTmp;
    };

};

#endif // ALGORITHM_H
