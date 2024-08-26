#!/bin/bash

# 文件路径
FILE1="../../../correctness/correctness.csv"
FILE2="./correctness.csv"

# 计算文件的 SHA-256 哈希值
HASH1=$(sha256sum "$FILE1" | awk '{ print $1 }')
HASH2=$(sha256sum "$FILE2" | awk '{ print $1 }')

# 比较哈希值
if [ "$HASH1" == "$HASH2" ]; then
    echo "PASS"
else
    echo "FAIL"
fi