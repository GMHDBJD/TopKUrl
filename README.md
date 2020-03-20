# TopKUrl
Interview of PingCAP

# 要求
100GB的url文件，使用1GB内存计算出出现次数top100的url和出现的次数。

# 截止时间
3月21日晚上24:00前，通过GitHub提交代码链接。

# 实现方案
  - [x] 哈希加最小堆
  - [x] Count-Min Sketch
  - [x] Space Saving

# 实现算法
- 确定性算法：
  - 哈希加最小堆
    > 使用std::hash将url切分到n文件中，使用一个全局最小堆，对每个文件用std::map统计url和对应的数量，遍历哈希表，将结果插入堆中，保持堆大小为K。n次遍历之后堆中存放的即TopK。
    
    总共需要200GB的磁盘读操作和100GB的磁盘写操作。

- 非确定性算法：
  - Count-Min Sketch
    > 类似Bloom filter的思想，采用d个hash函数和m个切分，维护一个m*d的二维向量V，对于每个url，使用d个hash函数依次hash并模m，将V[hash_key][hash_value]的值加一。重新遍历每个url，对于每个url，找到最小的V[hash_key][hash_value]，该值即url的次数，并维护一个大小为K最小堆保存结果

    总共需要100GB的磁盘读操作。输出结果url的出现次数将会略大于实际次数。

  - Space Save
    > 维护一个最小堆，当从数据流中看到一个url时，如果堆中已经存在，则增加url的值，否则就替换掉堆顶元素，并将值设为原堆顶元素的值加1。

    总共需要100GB的磁盘读操作。输出结果url的出现次数将会略大于实际次数。

# 测试结果
由于磁盘空间较小，使用10GB的文件进行测试，并用***unix***的***ulimit -v 100000***将内存限制为100MB;



# 进一步优化（未完成）
- 读取一整块block，再对block的内容处理
- 分布式map_reduce
- 多进程（消耗时间的主要是磁盘IO，故提升应该不大）