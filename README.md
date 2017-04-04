# project2_mst

图：最小生成树（MST）、贪心算法

本项目为电子科技大学2017年4月**通信网理论基础**第二次Project的代码

教材《算法导论》 第16章——贪心算法 第23章——最小生成树

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
        vertex.minWeightArcToTree.weight=MAX_WEIGHT
        # 初始化非树中节点到树最小权重边指向的树中节点
        vertex.minWeightArcToTree.dst=NULL
    # 设置G.vertexes[0]为treeVertex的第一个节点，树没有边
    treeVertex=[G.vertexes[0]]
    treeArc=[]
    # vertexes[0]作为树的唯一节点，到树距离为0
    G.vertexes[0].minWeightArcToTree.weight=0
    # 循环不变式要求minWeightVertex为上次加入树的节点
    # 此操作在循环开始时更新其余节点到树的距离
    minWeightVertex=G.vertexes[0]
    while treeVertex!=G.vertexes
        # 更新minWeightArc邻接节点到树的距离,邻接节点当然不在树中
        # 虽然图是无向图，但是由邻接链表存储，outArc有指向性，指向dst
        for outArc in minWeightVertex.outArcs
            if outArc.dst not in treeVertex and \
            outArc.weight<outArcs.dst.minWeightArcToTree.weight
                outArc.dst.minWeightArcToTree=outArc.reverse()
        # 找到离树最近的节点，加入树
        minWeightArc=findMinWeightToTreeArc(G.vertex-treeVertex)
        minWeightVertex=minWeightArc.src
        treeArc.push(minWeightArc)
        treeVertex.push(minWeightVertex)
```

#### Prim实现4

> - 与实现#3类似，只是用堆```heapArcToTree```来维护```(G.vertex-treeVertex).minWeight```集合
> - ```findMinWeightToTreeArc()```用最小堆实现
> - ```minWeightArc```添加到```treeArc```、```minWeightVertex```添加到```treeVertex```后，需要在heap中先删除```minWeightArc```，后插入可能因minWeightVertex增加的arc

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
- 简单思路是构建一个装有起始节点和终止节点、权重的边类
- 更方便地可以将邻接链表中某条有向边的指针存到最小堆中
- 两种都不是基本类型，需要自行构造比较规则

#### 构建比较规则的方法

- 重载```operator<```、```operator>```操作符
- 自定义一个比较类，继承自```functional```的```less```或```greater```

(```priority_queue```的详细使用方法可以参考[c++中STL之heap,priority_queue使用](http://blog.csdn.net/longhopefor/article/details/38303545)和[STL之priority_queue_李大宝_新浪博客](http://blog.sina.com.cn/s/blog_959bf1d3010191h1.html))

### 实现

- 利用dfs或bfs对图进行遍历，判断图的连通性



