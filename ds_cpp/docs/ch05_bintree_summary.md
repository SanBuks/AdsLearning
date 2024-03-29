# 1. 基本概念
## 1.1 特点性质
- 存储关系上属于半线性结构, 不存在天然直接前驱和直接后继, 加上遍历限定则会确定线性关系
- 逻辑关系上属于分层结构, 点之间存在隶属关系
- 拓扑关系上属于连通无环图(最小连通图/最大无环图), 指定节点为根后是有根树, 每个节点与根之间有路径相连且唯一

## 1.2 重要术语
- 节点深度: 根到节点的边数目, height(root) = root ? 0 : -1
- 节点高度: 子树的所有节点中最大深度
- 祖先: 根到节点(包括节点)的所有节点, 真祖先则排除该节点
- 后代: 子树的所有节点, 真后代则派出根节点
- 叶节点/枝干节点: 无孩子的节点/不是叶子节点
- 真二叉树: 不包含 1 出度节点

## 1.3 数量关系
- 顶点数与边数同阶: n - 1 = e
- n2 与 n1 有关:
  - n = n0 + n1 + n2
  - n = n1 + 2n2 + 1 
  - => n2 + 1 = n0
- 真二叉树: 
  - n1 = 0 => n2 = e/2, 
  - n1 = 0 => n0 = (n + 1)/2
- h 高度二叉树总节点数范围:
  - 单链表: h+1
  - 满二叉树: 2^(h+1)-1
- 深度为 k 二叉树
  - 节点总数最多为 2^k 
  - 宽度与高度成指数形式

## 1.4 表示方法
- 列表 + 父节点索引: 找到某节点的父节点O(1), 找某节点的孩子节点需要遍历O(n)
- 列表 + 父节点索引 + 孩子列表: 找某节点的孩子节点O(r), 修改成本高, 空间成本高
- 长子 + 兄弟法: 减少了上一个方法孩子链表的空间, 二叉树等价表示多叉树

# 2. 二叉编码树
- 背景: 以 {0,1} 编码过程中会发生解码歧义即 某个字符编码是另一个编码的前缀, 为了消除歧义构造二叉编码树
- 构造: 树 T 以根节点(字符串为空)出发, 左孩子字符串追加 0, 右孩子字符串追加 1, 最终叶子节点完成最后编码, 叶子节点的深度即编码的长度
- 原理: 叶子节点不是叶子节点的祖先

# 3. BST 树
# 4. AVL 树

# 总结
- 0144_binary_tree_preorder_traversal    (迭代先序遍历)
- 0094_binary_tree_inorder_traversal     (迭代中序遍历)
- 0145_binary_tree_postorder_traversal   (迭代后序遍历)
- 0102_binary_tree_level_order_traversal (层次遍历)