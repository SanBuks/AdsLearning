# 第五章 二叉树

### 1. 概述
#### 基本概念
- 树属于半线性结构,结合了链表与向量的优点,同时也是分层结构.
- 树构成 : 由顶点(v)和边(e)构成, 等价于**连通无环图**即每个节点与根之间有路径相连且唯一.其中规定一个节点为根节点(r).
- 通路: 节点v通过n条边与节点k相连,构成一条通路形成路经.若节点v与节点k是同一个点则形成环路. 树存在特性为: 为了连通边数不过少,为了无环边数不过大.

#### 术语
|术语|解释|
|---|---|
|祖先/后代|v到r经历的所有节点为祖先,v是这些节点的后代,存在真祖先/真后代|
|孩子/父亲|v是u的祖先且恰好比u的深度少一,v是u的父亲,u是v的孩子,孩子之间互称兄弟|
|叶节点/内部节点|无孩子的节点/不是叶子节点|
|节点深度|v到r所经历的边数目|
|节点度数(出度)|孩子总数,每个节点度数不超过2则为二叉树|
|子树|以v节点为根,其后代与之间联边成为子树|
|树/节点的高度|树T或以节点为根的树 所有节点深度最大的值 单节点树高为0|

#### 数量关系
- 所有树中, 边数 = 总出度 = 顶点数-1, 顶点数与边数同阶
- 二叉树中, 深度为k的节点总数之多为2^k(宽度与高度成指数形式), 高度h则总节点数范围为[ h+1 , 2^(h+1)-1 ]
- 真二叉树中, 所有节点的出度为偶数,0或1


#### 表示方法
|表示方法|性能|补充|
|---|---|---|
|父节点|找到某节点的父节点O(1) 找某节点的孩子节点O(n)|找孩子节点需要改进|
|父节点+孩子节点法|找到某节点的父节点O(1) 找某节点的孩子节点O(r)|插入删除成本高空间容量大|
|长子+兄弟法|找到某节点的父节点O(1) 找某节点的孩子节点O(r)|逻辑上多叉树与二叉树等价,减少了上一个方法孩子链表的空间|

### 2. BinNode类
```c++
#define BNP(T) BinNode<T> *
template<typename T>
class BinNode{
private:
	T data;  // 数值
	BNP(T) parent;  // 父节点指针
	BNP(T) lchild;  // 左孩子指针
	BNP(T) rchild;  // 右孩子指针
	int height;  // 节点高度

public:
	BinNode():parent(nullptr), lchild(nullptr), rchild(nullptr), height(0){}
	BinNode(T e, BNP(T) p=nullptr, BNP(T) lc=nullptr, BNP(T) rc=nullptr, int h=0):data(e), parent(p), lchild(lc), rchild(rc), height(h){}
	int size(){  // 统计后代总数 包括自己
		int s=1;
		if (nullptr!=lchild) s+=lchild->size();
		if (nullptr!=rchild) s+=rchild->size();
		return s;
	}	
	BNP(T) insertAsLC(T const &e){ return lchild=new BinNode(e, this);}  // 作为左孩子插入
	BNP(T) insertAsRC(T const &e){ return rchild=new BinNode(e, this);}  // 作为右孩子插入
};

template <typename T>
class BinTree{
protected:
	int _size;  // 规模
	BNP(T) _root;  // 根节点指针
public:
	BinTree(): _size(0), _root(nullptr) {}
	~BinTree() { if(0<_size) remove(_root); }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BNP(T) root()const { return _root; } // 返回根节点指针
};

```

### 3. 工具函数
```c++
int updateHeight(BNP(T) p){  // 更新 p 所指节点高度 叶子节点 height=-1+1=0
	return p->height=1+max(stature(p->lchild), stature(p->rchild)); 
}
void updateHeightAbove(BNP(T) p){  // 更新 p所指节点及祖先节点高度
	while(p){
		updateHeight(p);
		p=p->parent;
	}
}
template<typename T>
inline int stature(BNP(T) p) { return p? p->height: -1; }  // 返回节点指针高度 空树返回-1

```


### 2. 二叉编码树
- 背景: 以{0,1}\*编码过程中会发生解码歧义即 某个字符编码是另一个字符的前缀,为了消除歧义构造二叉编码树
- 构造: 树T以根节点(字符串为空)出发,左孩子字符串追加0,右孩子字符串追加1,最终叶子节点完成最后编码,叶子节点的深度即编码的长度,只要所有编码对应叶子节点则会消除前缀歧义
- 

