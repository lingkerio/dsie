#!/bin/bash

# 检查是否提供了命令行参数
if [ $# -eq 0 ]; then
  echo "Usage: $0 <command>"
  exit 1
fi

# 要执行的命令
command="$@"

# 运行次数
iterations=10

# 总时间初始化
total_time=0

# 执行命令并计算时间
for i in $(seq 1 $iterations); do
  echo "Running iteration $i..."
  # 执行命令并捕获输出
  result=$($command)
  
  # 提取运行时间
  exec_time=$(echo "$result" | grep "Total time to execute all operations" | awk '{print $7}')
  
  # 累加总时间
  total_time=$(echo "scale=6; $total_time + $exec_time" | bc -l)
done

# 计算平均时间
average_time=$(echo "scale=6; $total_time / $iterations" | bc -l)

echo "Average time over $iterations iterations: $average_time seconds"