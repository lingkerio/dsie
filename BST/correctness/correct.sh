#!/bin/bash

EXPECTED_HASH="790fa2b9e213216160a6cefc1581c9e22c98495778b94bc70f149d3e280e3ecc" # 4138092 dataset

# 文件路径
FILE="./correctness.csv"

# 计算文件的 SHA-256 哈希值
HASH=$(sha256sum "$FILE" | awk '{ print $1 }')

# 比较哈希值
if [ "$HASH" == "$EXPECTED_HASH" ]; then
    echo "PASS"
else
    echo "FAIL"
fi