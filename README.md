# TopKUrl
Interview of PingCAP

# 要求
100GB的url文件，使用1GB内存计算出出现次数top100的url和出现的次数。

# 截止时间
3月21日晚上24:00前，通过GitHub提交代码链接。

# 实现思路
  - [x] 哈希加最小堆
  - [ ] Trie
  - [x] Count-Min Sketch
  - [x] Space Saving

# 具体实现
  - 哈希加最小堆
    > 使用std::hash将url切分到n文件中，使用一个全局最小堆，对每个文件用std::map统计url和对应的数量，遍历哈希表，将结果插入堆中，保持堆大小为K。n次遍历之后堆中存放的即TopK。
  - Count-Min Sketch
    > 类似Bloom filter的思想，采用d个hash函数和m个切分，维护一个m*d的二维向量V，对于每个url，使用d个hash函数依次hash并模m，将V[hash_key][hash_value]的值加一。重新遍历每个url，对于每个url，找到最小的V[hash_key][hash_value]，该值即url的次数，并维护一个大小为K最小堆保存结果
  - Space Saving
    > 维护一个最小堆，当从数据流中看到一个url时，如果堆中已经存在，则增加url的值，否则就替换掉堆顶元素，并将值设为原堆顶元素的值加1。