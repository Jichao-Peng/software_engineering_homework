#include "algorithm.h"


Algorithm::Algorithm()
{

}

//构造图
bool Algorithm::CreatGraph(vector<QString> &Buffer, vector<Node> &Graph)
{
    vector<QString>::iterator BufferIt;
    for(BufferIt = Buffer.begin(); BufferIt != Buffer.end(); BufferIt++)
    {
        NODE NodeTmp;
        NodeTmp.Name = *BufferIt;
        NodeTmp.FirstLetter = NodeTmp.Name.left(1);
        NodeTmp.LastLetter = NodeTmp.Name.right(1);
        Graph.push_back(NodeTmp);
    }

    vector<Node>::iterator NodeIt;
    for(NodeIt = Graph.begin(); NodeIt != Graph.end(); NodeIt++)
    {
        NODE &NodeOrigin = *NodeIt;

        vector<Node>::iterator NodeItt;
        for(NodeItt = Graph.begin(); NodeItt != Graph.end(); NodeItt++)
        {
            NODE NodeTmp = *NodeItt;
            if(NodeOrigin.LastLetter == NodeTmp.FirstLetter)
            {
                NodeOrigin.Next.push_back(&*NodeItt);
            }
        }
    }
    return true;
}

//递归的DFS遍历算法
void Algorithm::DFS(vector<Node> &Graph, Node* NodeNextPtr, vector<Node> Path, vector<vector<QString>> &PathAll)
{
    vector<Node> PathTmp(Path);
    bool ExistFlag = false;

    vector<Node>::iterator itt = find_if(PathTmp.begin(),PathTmp.end(),Compare_2(*NodeNextPtr));
    if(itt == PathTmp.end())
    {
        PathTmp.push_back(*NodeNextPtr);
    }
    else
    {
        ExistFlag = true;
    }

    if(!NodeNextPtr->Next.empty() && !ExistFlag)
    {
        vector<Node*>::iterator it;
        for(it = NodeNextPtr->Next.begin(); it != NodeNextPtr->Next.end(); it++)
        {
            DFS(Graph,*it,PathTmp,PathAll);
        }
    }

    vector<Node>::iterator ittt;
    vector<QString> PathStringTmp;
    for(ittt = PathTmp.begin(); ittt != PathTmp.end(); ittt++)
    {
        PathStringTmp.push_back(ittt->Name);
    }
    PathAll.push_back(PathStringTmp);//PathALl存储所有的路径
}

//非递归的DFS遍历算法，具有方向性，感觉处理起来比较麻烦，目前还不好使
bool Algorithm::DFS(vector<Node> &Graph, unsigned int Start, vector<vector<QString>> &OutputPath)
{
    vector<Node> NodeStack;//用于遍历
    vector<pair<QString,Node>> Path;
    unsigned int Recorder = 0;

    NODE NodeTop;
    NODE NodeStart;
    NODE NodeNext;

    if(Start>(Graph.size()-1))
    {
        qDebug()<<"Error: Can't Find Start Node."<<endl;
    }
    else
    {
        NodeStart = Graph.at(Start);
        NodeStack.push_back(NodeStart);
        Path.push_back(pair<QString,Node>(NodeStart.FirstLetter,NodeStart));
        Recorder++;

        while(!NodeStack.empty())
        {
            NodeTop = NodeStack.back();//这里的NodeTop会按照一定的顺序遍历所有的Node
            NodeStack.pop_back();
            //qDebug()<<"[NodeTop] "<<NodeTop.Name<<endl;

            if(!NodeTop.Next.empty())
            {
                for(unsigned int i = 0; i<NodeTop.Next.size(); i++)
                {
                    NodeNext = *NodeTop.Next.at(i);

                    vector<pair<QString,Node>>::iterator PathItt;
                    PathItt = find_if(Path.begin(),Path.end(),Compare_3(NodeNext));//寻找路径中是否已经存在该node，如果存在不进行处理，直接滤掉该node

                    vector<Node>::iterator NodeIt;
                    NodeIt = find_if(NodeStack.begin(),NodeStack.end(),Compare_2(NodeNext));

                    if((PathItt == Path.end()) && (NodeIt == NodeStack.end()))
                    {
                        NodeStack.push_back(NodeNext);
                    }
                }
            }


            //算法是建议一个以单词第一个字母为key的vector，在遍历的过程中，如果目标的key值不同则插入，如果目标的key
            //值与vector中某一key值相同，则删除key值后面的部分并重新开始插入，如果vector长度超过已记录的最长长度则
            //存入path
            pair<QString, Node> PathLast = Path.back();
            if(PathLast.second.LastLetter == NodeTop.FirstLetter)
            {
                Path.push_back(pair<QString,Node>(NodeTop.FirstLetter,NodeTop));

                //________________________________________________
//                vector<pair<QString,Node>>::iterator it;
//                for(it = Path.begin(); it != Path.end(); it++)
//                {
//                    NODE NodeGood = it->second;
//                    qDebug()<<NodeGood.Name<<" ";
//                }
//                qDebug()<<endl;
                //________________________________________________

                if(Path.size() == Recorder)
                {
                    vector<QString> OutPutPathTmp;
                    Recorder = Path.size();
                    vector<pair<QString,Node>>::iterator PathItt;
                    OutPutPathTmp.clear();
                    for(PathItt = Path.begin(); PathItt != Path.end(); PathItt++)
                    {
                        OutPutPathTmp.push_back(PathItt->second.Name);
                    }
                    OutputPath.push_back(OutPutPathTmp);
                }
                if(Path.size() > Recorder)//记录最长的Path
                {
                    OutputPath.clear();
                    vector<QString> OutPutPathTmp;
                    Recorder = Path.size();
                    vector<pair<QString,Node>>::iterator PathItt;
                    OutPutPathTmp.clear();
                    for(PathItt = Path.begin(); PathItt != Path.end(); PathItt++)
                    {
                        OutPutPathTmp.push_back(PathItt->second.Name);
                    }
                    OutputPath.push_back(OutPutPathTmp);
                }
            }
            else
            {
                vector<pair<QString,Node>>::iterator PathIt;
                vector<pair<QString,Node>>::iterator PathTar;
                for(PathIt = Path.begin(); PathIt != Path.end(); PathIt++)
                {
                    if((PathIt->first == NodeTop.FirstLetter))// && (PathIt->second.Name != NodeTop.Name))
                    {
                        PathTar = PathIt;
                    }
                }
                Path.erase(PathTar,Path.end());
                Path.push_back(pair<QString,Node>(NodeTop.FirstLetter,NodeTop));

                //________________________________________________
//                qDebug()<<"----Erase----";
//                vector<pair<QString,Node>>::iterator it;
//                for(it = Path.begin(); it != Path.end(); it++)
//                {
//                    NODE NodeGood = it->second;
//                    qDebug()<<NodeGood.Name<<" ";
//                }
//                qDebug()<<endl;
                //________________________________________________

                if(Path.size() == Recorder)
                {
                    vector<QString> OutPutPathTmp;
                    Recorder = Path.size();
                    vector<pair<QString,Node>>::iterator PathItt;
                    OutPutPathTmp.clear();
                    for(PathItt = Path.begin(); PathItt != Path.end(); PathItt++)
                    {
                        OutPutPathTmp.push_back(PathItt->second.Name);
                    }
                    OutputPath.push_back(OutPutPathTmp);
                }
                if(Path.size() > Recorder)//记录最长的Path
                {
                    OutputPath.clear();
                    vector<QString> OutPutPathTmp;
                    Recorder = Path.size();
                    vector<pair<QString,Node>>::iterator PathItt;
                    OutPutPathTmp.clear();
                    for(PathItt = Path.begin(); PathItt != Path.end(); PathItt++)
                    {
                        OutPutPathTmp.push_back(PathItt->second.Name);
                    }
                    OutputPath.push_back(OutPutPathTmp);
                }
            }
        }
        //________________________________________________
        qDebug()<<OutputPath.at(0).size()<<endl;
        //________________________________________________

        if(OutputPath.size() == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}





