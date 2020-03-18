# TopKUrl
Interview of PingCAP

# 要求
100GB的url文件，使用1GB内存计算出出现次数top100的url和出现的次数。

# 截止时间
3月21日晚上24:00前，通过GitHub提交代码链接。

# 实现思路
  - [x] 哈希加最小堆
  - [ ] Trie

# 具体实现
  - 哈希加最小堆
    > 使用std::hash将url切分到多个文件中，然后用std::map统计url和对应的数量合并到同个文件中。最后使用最小堆保存次数最多的前K个数，并输出到最后的结果文件中。