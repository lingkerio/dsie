#!/usr/bin/env fish

# 检查是否提供了命令行参数
if test (count $argv) -eq 0
    echo "Usage: $0 <command>"
    exit 1
end

# 要执行的命令
set command $argv

# 运行次数
set iterations 10

# 总时间初始化
set total_time 0

# 执行命令并计算时间
for i in (seq 1 $iterations)
    echo "Running iteration $i..."
    # 执行命令并捕获输出
    set result (eval $command)
    
    # 提取运行时间
    set exec_time (echo $result | grep "Total time to execute all operations" | awk '{print $7}')
    
    # 确保 exec_time 是一个有效的数字
    if test -n "$exec_time"
        # 累加总时间
        set total_time (math "$total_time + $exec_time")
    else
        echo "Warning: Could not extract execution time in iteration $i"
    end
end

# 计算平均时间
set average_time (math "$total_time / $iterations")

echo "Average time over $iterations iterations: $average_time seconds"