#!/bin/bash

EXPECTED_HASH="cef681ae08c9896b1e5ee282358f2605e06a255ca230985dd0b65147c2fa13c3"

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