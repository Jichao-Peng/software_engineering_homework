#include "wordchain.h"
#include "ui_wordchain.h"

WordChain::WordChain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordChain)
{
    ui->setupUi(this);
    WordChainAlg = new Algorithm;
    File = new OpenFIle;

    connect(File,SIGNAL(OpenSuccess()),this,SLOT(InputFileContent()));
}

WordChain::~WordChain()
{
    delete ui;
}

void WordChain::InputFileContent()
{
    ui->InputEdit->clear();
    ui->InputEdit->append(File->FileContent);
}


void WordChain::on_StartButton_clicked()
{
    QTime Timer;
    Timer.start();//开始计时

    QString InputText = ui->InputEdit->toPlainText();
    QStringList List = InputText.split(" ");
    QString OutputText;
    vector<Node> Graph;
    vector<QString> Buffer;
    vector<vector<QString>> PathMost;
    bool BufferErrorFlag = false;

    for(int i=0; i<List.size(); i++)
    {
        if(List.size() == 1 || List.size() == 0)
        {
            BufferErrorFlag = true;
            OutputText.clear();
            OutputText.append("[Error:There is no chain]");
            ui->OutputEdit->append(OutputText);
            OutputText.clear();
            OutputText.append("[Please clear and input again]");
            ui->OutputEdit->append(OutputText);
        }
        else if(List.at(i).left(1) == List.at(i).right(1))
        {
            BufferErrorFlag = true;
            OutputText.clear();
            OutputText.append("[Error:The head and tail of the input word are the same]");
            ui->OutputEdit->append(OutputText);
            OutputText.clear();
            OutputText.append("[Please clear and input again]");
            ui->OutputEdit->append(OutputText);
        }
        else
        {
            Buffer.push_back(List.at(i));
        }
    }
    if(!BufferErrorFlag)
    {
        bool GraphFlag = WordChainAlg->CreatGraph(Buffer,Graph);
        if(GraphFlag)
        {
            //归的DFS遍历算法调用
            for(unsigned int j = 0;j<Graph.size();j++)
            {
                vector<vector<QString>> PathAll;
                vector<Node> PathInit;

                //调用DFS递归算法
                WordChainAlg->DFS(Graph,(Node*)(&Graph.at(j)),PathInit,PathAll);

                vector<vector<QString>> PathMostTmp;
                vector<vector<QString>>::iterator it;

                //单个起点求得所有路径中最长的路径
                for(it = PathAll.begin(); it != PathAll.end(); it++)
                {
                    if(PathMostTmp.empty())
                    {
                        PathMostTmp.push_back(*it);
                    }
                    else if(it->size() > PathMostTmp.at(0).size())
                    {
                        PathMostTmp.clear();
                        PathMostTmp.push_back(*it);
                    }
                    else if(it->size() == PathMostTmp.at(0).size())
                    {
                        bool SameFlag = false;//判断是否存在相同的路径
                        for(int i =0; i<PathMostTmp.size(); i++)
                        {
                            if(*it == PathMostTmp.at(i))
                            {
                                SameFlag = true;
                            }
                        }

                        if(!SameFlag)
                        PathMostTmp.push_back(*it);
                    }
                    else
                    {}
                }

                //所有起点求得所有路径中最长的路径
                if(PathMost.empty())
                {
                    PathMost.assign(PathMostTmp.begin(),PathMostTmp.end());
                }
                else if(PathMostTmp.at(0).size() > PathMost.at(0).size())
                {
                    PathMost.clear();
                    PathMost.assign(PathMostTmp.begin(),PathMostTmp.end());
                }
                else if(PathMostTmp.at(0).size() == PathMost.at(0).size())
                {
                    PathMost.assign(PathMostTmp.begin(),PathMostTmp.end());
                }
                else
                {}
            }

            float RunningTime;
            RunningTime = Timer.elapsed();//结束计时


            if(PathMost.at(0).size() == 1)
            {
                OutputText.clear();
                OutputText.append("[Sorry! There is no word chain]");
                ui->OutputEdit->append(OutputText);
            }
            else
            {
                OutputText.clear();
                OutputText.append("[The running time is(ms)]    ");
                OutputText.append(QString::number(RunningTime));
                ui->OutputEdit->append(OutputText);
                ui->OutputEdit->append(" ");

                OutputText.clear();
                OutputText.append("[The length of the word chain is]    ");
                OutputText.append(QString::number(PathMost.at(0).size()));
                ui->OutputEdit->append(OutputText);
                ui->OutputEdit->append(" ");

                OutputText.clear();
                OutputText.append("[The number of the word chain is]    ");
                OutputText.append(QString::number(PathMost.size()));
                ui->OutputEdit->append(OutputText);
                ui->OutputEdit->append(" ");


                vector<vector<QString>>::iterator itt;
                for(itt = PathMost.begin(); itt != PathMost.end(); itt++)
                {
                    vector<QString> Tmp = *itt;
                    vector<QString>::iterator ittt;
                    OutputText.clear();
                    OutputText.append("[Result]");
                    OutputText.append("    ");
                    for(ittt = Tmp.begin(); ittt != Tmp.end(); ittt++)
                    {
                        OutputText.append(*ittt);
                        OutputText.append(" ");
                    }
                    ui->OutputEdit->append(OutputText);
                }
            }



        //非递归的DFS遍历算法调用
//        ui->OutputEdit->append("[Creat Graph Success]");
//        for(unsigned int j = 0; j<Graph.size(); j++)
//        {
//            int j = 4;
//            WordChainAlg->DFS(Graph,j,Path);
//            if(PathMost.empty())
//            {
//                PathMost.clear();
//                PathMost.assign(Path.begin(),Path.end());
//            }
//            else if(Path.at(0).size()>PathMost.at(0).size())
//            {
//                PathMost.clear();
//                PathMost.assign(Path.begin(),Path.end());
//            }
//            else
//            {

//            }
//        }
//        vector<vector<QString>>::iterator it;
//        for(it = PathMost.begin(); it != PathMost.end(); it++)
//        {
//            vector<QString> Tmp = *it;
//            vector<QString>::iterator itt;
//            QString OutputText;
//            OutputText.append("[Result]");
//            OutputText.append(" ");
//            for(itt = Tmp.begin(); itt != Tmp.end(); itt++)
//            {
//                //qDebug()<<*itt<<endl;
//                OutputText.append(*itt);
//                OutputText.append(" ");
//            }
//            ui->OutputEdit->append(OutputText);
//        }
        }
    }
}

void WordChain::on_ResetButton_clicked()
{
    ui->InputEdit->clear();
    ui->OutputEdit->clear();
}

void WordChain::on_FileButton_clicked()
{
    File->exec();
}
