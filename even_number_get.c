
#include <math.h>
#include <stdlib.h>

struct btnode{
    int startIndex;
    int count;
    int level;//该节点所属层级
    struct btnode * left;
    struct btnode * right;
}btnode;
typedef struct btnode BTnode;

int alreadyHasNode;
int cal;
int isNotFirst;
int fromIndex;
int beginIndex;

void evenSelectNumber(int startIndex,int selectedNumber,int count);
void createBinaryTree(BTnode *head,int totalNumber);
void centerOrder(BTnode *node);
void makeAverageNumer(BTnode head,int totalNumber);
int * indx;
void evenSelectNumber(int startIndex,int selectedNumber,int count){
    
    //要均匀采样的数据总数为count，开始索引为startIndex，采样总数为n, 也即从startIndex开始到startIndex+count-1结束均匀抽取n个数据,并返回n个数据的索引
    
    //倒数第二层应有的数据
    indx=(int *)malloc(sizeof(int)*selectedNumber);
    int subLevel = floor(log2(selectedNumber))+1;//倒数第二层
    alreadyHasNode=pow(2, subLevel-1);
    fromIndex=selectedNumber-alreadyHasNode+(((selectedNumber-alreadyHasNode)%2)?((selectedNumber-alreadyHasNode)/2+1):((selectedNumber-alreadyHasNode)/2));
    
    BTnode head;
    head.startIndex=startIndex;
    head.count=count;
    head.level=1;
    
    isNotFirst=0;
    beginIndex=0;
    cal=0;
    makeAverageNumer(head, selectedNumber);
    
}
void makeAverageNumer(BTnode head,int totalNumber){
    if (pow(2, head.level)>=totalNumber) {
        if (alreadyHasNode<totalNumber) {
            BTnode left;
            BTnode right;
            
            left.startIndex=head.startIndex;
            left.count=head.count%2?(head.count/2+1):(head.count/2);;
            left.level=head.level+1;
            
            right.startIndex=head.startIndex+left.count;
            right.count=head.count-left.count;
            right.level=head.level+1;
            
            alreadyHasNode++;
            
            indx[beginIndex++]=left.startIndex;
            indx[beginIndex++]=right.startIndex;
        }
        return;
    }
    BTnode  left;
    BTnode  right;
    
    left.startIndex=head.startIndex;
    left.count=head.count%2?(head.count/2+1):(head.count/2);;
    left.level=head.level+1;
    
    right.startIndex=head.startIndex+left.count;
    right.count=head.count-left.count;
    right.level=head.level+1;
    
    if (((int)(pow(2, right.level-1)))==8) {
        //在往下一层就多余alreadyHasNode了，故从此进行数据统计
        cal++;
        if (cal>=(((totalNumber-alreadyHasNode)%2)?((totalNumber-alreadyHasNode)/2+1):((totalNumber-alreadyHasNode)/2))) {
            //从此进行统计
            if (cal%2==0||isNotFirst==1) {
                indx[fromIndex++]=left.startIndex;
                indx[fromIndex++]=right.startIndex;
            }
            else{
                isNotFirst=1;
                indx[fromIndex++]=right.startIndex;
            }
        }
    }
    makeAverageNumer(left, totalNumber);
    makeAverageNumer(right, totalNumber);
}
