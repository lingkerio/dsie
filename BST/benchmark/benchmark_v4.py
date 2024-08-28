import random
import csv
import argparse

# 解析命令行参数
parser = argparse.ArgumentParser(description='生成基准操作')
parser.add_argument('--insert_size', type=int, required=True, help='插入操作的数量')
args = parser.parse_args()

random.seed(42)

insert_size = args.insert_size

# 首先生成全部的insert操作
insert_operations = [('insert', random.randint(0, 10 * insert_size)) for _ in range(insert_size)]

# 随机选择其中三分之一数据作为有序插入操作
sorted_insert_size = insert_size // 3
sorted_insert_operations = random.sample(insert_operations, sorted_insert_size)
sorted_insert_operations.sort(key=lambda x: x[1])

# 从剩余数据中随机选择三分之一作为逆序插入操作
remaining_operations_set = set(insert_operations) - set(sorted_insert_operations)
remaining_operations = list(remaining_operations_set)

reverse_insert_size = insert_size // 3
reverse_insert_operations = random.sample(remaining_operations, reverse_insert_size)
reverse_insert_operations.sort(key=lambda x: x[1], reverse=True)

# 剩余部分作为随机插入操作
random_insert_operations_set = set(remaining_operations) - set(reverse_insert_operations)
random_insert_operations = list(random_insert_operations_set)
random.shuffle(random_insert_operations)

# 第一阶段
sorted_search_size = sorted_insert_size * 8 // 5
sorted_search_operations = [('search', op[1]) for op in random.choices(sorted_insert_operations, k=sorted_search_size)]
phase1_operations = sorted_insert_operations + sorted_search_operations

# 第二阶段
phase2_delete_size = len(sorted_insert_operations) * 4 // 10
phase2_delete_operations = [('delete', op[1]) for op in random.sample(sorted_insert_operations, phase2_delete_size)]
random_search_size = len(random_insert_operations) * 8 // 5
random_search_operations = [('search', op[1]) for op in random.choices(random_insert_operations, k=random_search_size)]
phase2_operations = random_insert_operations + phase2_delete_operations + random_search_operations

# 第三阶段
phase3_delete_size = len(random_insert_operations) * 4 // 10
phase3_delete_operations = [('delete', op[1]) for op in random.sample(random_insert_operations, phase3_delete_size)]
reverse_search_size = len(reverse_insert_operations) * 8 // 5
reverse_search_operations = [('search', op[1]) for op in random.choices(reverse_insert_operations, k=reverse_search_size)]
phase3_operations = reverse_insert_operations + phase3_delete_operations + reverse_search_operations

# 第四阶段
phase4_delete_size = len(reverse_insert_operations) * 4 // 10
phase4_delete_operations = [('delete', op[1]) for op in random.sample(reverse_insert_operations, phase4_delete_size)]
phase4_search_size = len(reverse_insert_operations) * 8 // 10
phase4_search_operations = [('search', op[1]) for op in random.sample(reverse_insert_operations, phase4_search_size)]
phase4_operations = phase4_delete_operations + phase4_search_operations

# 自定义混合操作的顺序
def mix_operations(insert_ops, delete_ops=None, search_ops=None):
    operations = []
    insert_index, delete_index, search_index = 0, 0, 0
    
    while insert_index < len(insert_ops) or \
          (delete_ops and delete_index < len(delete_ops)) or \
          (search_ops and search_index < len(search_ops)):
        
        choices = []
        if insert_index < len(insert_ops):
            choices.append('insert')
        if delete_ops and delete_index < len(delete_ops):
            choices.append('delete')
        if search_ops and search_index < len(search_ops):
            choices.append('search')
        
        next_op = random.choice(choices)
        
        if next_op == 'insert':
            operations.append(insert_ops[insert_index])
            insert_index += 1
        elif next_op == 'delete':
            operations.append(delete_ops[delete_index])
            delete_index += 1
        elif next_op == 'search':
            operations.append(search_ops[search_index])
            search_index += 1
    
    return operations

# 使用自定义混合顺序
phase1_operations = mix_operations(sorted_insert_operations, search_ops=sorted_search_operations)
phase2_operations = mix_operations(random_insert_operations, delete_ops=phase2_delete_operations, search_ops=random_search_operations)
phase3_operations = mix_operations(reverse_insert_operations, delete_ops=phase3_delete_operations, search_ops=reverse_search_operations)
phase4_operations = mix_operations([], delete_ops=phase4_delete_operations, search_ops=phase4_search_operations)

# 将所有阶段的操作合并
all_operations = phase1_operations + phase2_operations + phase3_operations + phase4_operations

# 生成findmin和findmax操作
find_operations = [('findmin', 0) for _ in range(insert_size // 2)] + [('findmax', 0) for _ in range(insert_size // 2)]
random.shuffle(find_operations)

# 随机插入findmin和findmax操作
for find_op in find_operations:
    insert_pos = random.randint(0, len(all_operations))
    all_operations.insert(insert_pos, find_op)

# 将所有操作写入CSV文件
with open('benchmark_operations.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerows(all_operations)
