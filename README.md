# project2_mst

图：最小生成树（MST）、贪心算法

本项目为电子科技大学2017年4月**通信网理论基础**第二次Project的代码

教材《算法导论》 第16章——贪心算法 第23章——最小生成树 第6章——堆排序

## MST问题的定义

> 给定无向加权图𝑮(𝑽,𝑬)，求最小权重生成树𝑻⊆𝑬。
> - 必须是无向图
> - 生成树的权重定义为树上边权重之和
> - 生成树定义为E的子集：必须覆盖V；无环；连通。

### 假设1：输入的图是连通的

> - 否则没有生成树
> - 更一般的情况可以用BFS进行预处理

### 假设2：边权重都不相同

> - 存在相同权重不会影响Prim和Kruskal的正确性
> - 但却“不必要”地加大了证明的难度。


## 设计目标

- 代码实现Prim实现#4（基于堆）
- 代码实现Kruskal实现#2（基于UNION-FIND）
- 设计实验，针对多组相同实例，比较真实运行时间
- 提交实验报告。

## 思路

### Prim伪码

#### Prim实现1
```python
def Prim(G)
    treeVertex=[G.vertexes[0]]
    treeArc=[]
    while treeVertex!=G.vertexes
        minWeightArc=findMinWeightArc(treeVertex,G.vertex-treeVertex)
        treeArc.push(minWeightArc)
        treeVertex.push(minWeightArc.src)
```

#### Prim实现2

> - 用一个数据结构A来维护所有边界边
> - 每次循环只需求A中权重最小者就行了
> - 但是别忘了要对A进行更新。【因为边界在变】

#### Prim实现3

> - 用一个数据结构B来维护所有的边界点
> - 相当于所有边界边被分成不同的小集合
> - 与同一个边界点相关联的那些边只记录一个最小值

```python
def Prim(G)
    for vertex in G.vertexes
        # 初始化所有节点的到树最小权重
        vertex.minWeightArcToTree.weight=WEIGHT_INF
        # 初始化非树中节点到树最小权重边指向的树中节点
        vertex.minWeightArcToTree.dst=NULL
    # 设置G.vertexes[0]为treeVertex的第一个节点，树没有边
    treeVertex=[G.vertexes[0]]
    treeArc=[]
    # vertexes[0]作为树的唯一节点，到树距离为0
    G.vertexes[0].minWeightArcToTree.weight=0
    # 循环不变式要求newAddedVertex为上次加入树的节点
    # 此操作在循环开始时更新其余节点到树的距离
    newAddedVertex=G.vertexes[0]
    while treeVertex!=G.vertexes
        # 更新minWeightArc邻接节点到树的距离,邻接节点当然不在树中
        # 虽然图是无向图，但是由邻接链表存储，outArc有指向性，指向dst
        for outArc in newAddedVertex.outArcs
            if outArc.dst not in treeVertex and \
            outArc.weight<outArcs.dst.minWeightArcToTree.weight
                outArc.dst.minWeightArcToTree=outArc.reverse()
        # 找到离树最近的节点，加入树
        minWeightArc=findMinWeightToTreeArc(G.vertex-treeVertex)
        newAddedVertex=minWeightArc.dst
        treeArc.push(minWeightArc)
        treeVertex.push(newAddedVertex)
```

#### Prim实现4

> - 与实现#3类似，只是用堆```heapArcToTree```来维护```(G.vertex-treeVertex).minWeight```集合
> - ```findMinWeightToTreeArc()```用最小堆实现
> - ```minWeightArc```更新后，需要在heap中先删除，后插入

### 分析

#### 最小堆实现

利用c++stl库中```queue```的```priority_queue```类，使用方法：

```cpp
#include <queue>
#include <functional>

...

priority_queue<double, vector<double>, greater<double>> heap;
for (int i = 0; i < 10; i++)
{
    heap.push(i);
}
cout << endl;
for (int i = 0; i < 10; i++)
{
    cout << heap.top()<<" ";
    heap.pop();
}
```

- ```priority_queue```类可以自定义容器、容器所装的数据类型、比较规则


#### 构建比较规则的方法

- 重载```operator<```、```operator>```操作符
- 自定义一个比较类，继承自```functional```的```less```或```greater```

(```priority_queue```的详细使用方法可以参考[c++中STL之heap,priority_queue使用](http://blog.csdn.net/longhopefor/article/details/38303545)和[STL之priority_queue_李大宝_新浪博客](http://blog.sina.com.cn/s/blog_959bf1d3010191h1.html))

#### 堆```heapArcToTree```所容纳的数据类型

数据类型要求：
1. 保存非tree节点的唯一到mst权重最小的边，每个非tree节点有唯一对应边
    1. 包含边的起点，即非tree节点
    1. 包含边的终点，即指向tree中的节点
    1. 包含边的权重，可变，在无连接时权重为无穷大
1. 可以通过非tree节点索引到最小堆中对应的权重最小边，并可以对终点和权重做出改动

数据类型分析：
- 要想不改变节点类
    - 简单思路是将边类作为容器数据类型
    - 更方便地可以将邻接链表中某条有向边的指针存到最小堆中，空指针代表无穷远
    - 两种都不是基本类型，需要自行构造比较规则
    - 但更新非tree节点距离时需要对节点对象在最小堆中对应的权重和边进行操作，以上两种方法都不能由节点找到对应权重，不满足要求2
- 只能改变节点类，增加一个到tree权重最小的边的指针，并以节点类的指针作为```heapArcToTree```的数据类型
    - 此时```heapArcToTree```的比较类就应该构造两个节点的比较方法，比较的是它们最小权重边的权重大小
    - 比较方法中认为空指针权重为无穷大

#### 最小堆```heapArcToTree```的更新

- 初始```heapArcToTree```包含了除tree中唯一节点外的所有非tree节点
- 每个循环```newAddedVertex```加入tree，都可能导致```heapArcToTree```的更新
    1. 树根被删去,对```heapArcToTree```进行一次```top()```操作读取最小权重点，并执行```pop()```操作弹出树根
    1. 遍历从```newAddedVertex```出发的边，可能改变非tree节点到tree的权重或边时，最小堆被打乱
    1. 在权重更新时，可以按ppt的方法先删除，后插入（删除操作如何实现？根据ppt删除和插入的单次复杂度为O(logn)，总共为O(mlog(n))），标准库的```priority_queue```没有删除方法
    1. 为解决最小堆乱序的问题，可以在每次循环结束时重建一次堆，但是复杂度为O(n)
    1. 但是想到，更新权重都是往小的方向更新，只要每次更新都对其进行一次向上冒泡操作即可，复杂度为O(log(n))
    1. 由此不能用```heapArcToTree```，因为它没有实现权值更新的冒泡排序方法
    1. 自己实现一个最小堆，要求可以通过树节点找到堆的节点，用于对更新权值后的堆节点进行冒泡排序，总复杂度为mO(log(n))（p369)。或更新所有```newAddedVertex```邻接节点权值后进行一次建堆操作，总复杂度O(n^2logn)（显然不行）
    1. 考虑堆节点数据类型为树节点的指针，树节点维护一个最小权重边的指针，指针为NULL时表示与tree无连接，同时维护一个堆节点的指针，指针为NULL时表示节点在tree中
    1. 自己实现的最小堆要实现pop()方法，和对某个堆节点进行冒泡排序的方法，更进一步实现对树节点的最小权重边进行更改的方法。初步考虑参考algorithm中heap的实现方法，或直接借用其函数
- 每个循环```newAddedVertex```加入tree，对```newAddedVertex```邻边进行遍历时要判断邻接节点是否属于非tree（堆）
    1. 对每个节点维护一个标志位来指明节点是否属于非tree
    1. 在节点加入tree时更新标志位

### 实现

1. 利用dfs或bfs对图进行遍历，判断图的连通性
2. 构建自己的最小堆，


