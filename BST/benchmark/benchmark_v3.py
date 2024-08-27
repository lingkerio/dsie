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
insert_operations = [('insert', random.randint(0, 10*insert_size)) for _ in range(insert_size)]

# 随机选择其中三分之一数据作为有序插入操作
sorted_insert_size = insert_size // 3
sorted_insert_operations = random.sample(insert_operations, sorted_insert_size)
sorted_insert_operations.sort(key=lambda x: x[1])

# 从剩余数据中随机选择三分之一作为逆序插入操作
remaining_operations = [op for op in insert_operations if op not in sorted_insert_operations]
reverse_insert_size = insert_size // 3
reverse_insert_operations = random.sample(remaining_operations, reverse_insert_size)
reverse_insert_operations.sort(key=lambda x: x[1], reverse=True)

# 剩余部分作为随机插入操作
random_insert_operations = [op for op in remaining_operations if op not in reverse_insert_operations]
random.shuffle(random_insert_operations)

# 第一阶段
# 在有序插入操作中有放回抽样选择80%的数据作为查找操作
sorted_search_size = sorted_insert_size * 8 // 5
sorted_search_operations = [('search', op[1]) for op in random.choices(sorted_insert_operations, k=sorted_search_size)]

# 将有序插入操作和查找操作混合
phase1_operations = []
insert_index, search_index = 0, 0
while insert_index < len(sorted_insert_operations) and search_index < len(sorted_search_operations):
    phase1_operations.append(sorted_insert_operations[insert_index])
    insert_index += 1
    if search_index < len(sorted_search_operations):
        phase1_operations.append(sorted_search_operations[search_index])
        search_index += 1

# 添加剩余的插入操作
while insert_index < len(sorted_insert_operations):
    phase1_operations.append(sorted_insert_operations[insert_index])
    insert_index += 1

# 添加剩余的查找操作
while search_index < len(sorted_search_operations):
    phase1_operations.append(sorted_search_operations[search_index])
    search_index += 1

# 第二阶段
# 从第一阶段的插入数据中随机抽取40%作为删除操作
phase1_insert_operations = sorted_insert_operations
phase2_delete_size = len(phase1_insert_operations) * 4 // 10
phase2_delete_operations = [('delete', op[1]) for op in random.sample(phase1_insert_operations, phase2_delete_size)]

# 从随机插入操作中抽取查找操作
random_search_size = len(random_insert_operations) * 8 // 5
random_search_operations = [('search', op[1]) for op in random.choices(random_insert_operations, k=random_search_size)]

# 将插入、删除和查找操作混合
phase2_operations = []
insert_index, delete_index, search_index = 0, 0, 0
while insert_index < len(random_insert_operations) and delete_index < len(phase2_delete_operations) and search_index < len(random_search_operations):
    phase2_operations.append(random_insert_operations[insert_index])
    insert_index += 1
    if delete_index < len(phase2_delete_operations):
        phase2_operations.append(phase2_delete_operations[delete_index])
        delete_index += 1
    if search_index < len(random_search_operations):
        phase2_operations.append(random_search_operations[search_index])
        search_index += 1

# 添加剩余的插入操作
while insert_index < len(random_insert_operations):
    phase2_operations.append(random_insert_operations[insert_index])
    insert_index += 1

# 添加剩余的删除操作
while delete_index < len(phase2_delete_operations):
    phase2_operations.append(phase2_delete_operations[delete_index])
    delete_index += 1

# 添加剩余的查找操作
while search_index < len(random_search_operations):
    phase2_operations.append(random_search_operations[search_index])
    search_index += 1

# 第三阶段
# 从第二阶段的插入数据中随机抽取40%作为删除操作
phase2_insert_operations = random_insert_operations
phase3_delete_size = len(phase2_insert_operations) * 4 // 10
phase3_delete_operations = [('delete', op[1]) for op in random.sample(phase2_insert_operations, phase3_delete_size)]

# 从逆序插入操作中抽取查找操作
reverse_search_size = len(reverse_insert_operations) * 8 // 5
reverse_search_operations = [('search', op[1]) for op in random.choices(reverse_insert_operations, k=reverse_search_size)]

# 将插入、删除和查找操作混合
phase3_operations = []
insert_index, delete_index, search_index = 0, 0, 0
while insert_index < len(reverse_insert_operations) and delete_index < len(phase3_delete_operations) and search_index < len(reverse_search_operations):
    phase3_operations.append(reverse_insert_operations[insert_index])
    insert_index += 1
    if delete_index < len(phase3_delete_operations):
        phase3_operations.append(phase3_delete_operations[delete_index])
        delete_index += 1
    if search_index < len(reverse_search_operations):
        phase3_operations.append(reverse_search_operations[search_index])
        search_index += 1

# 添加剩余的插入操作
while insert_index < len(reverse_insert_operations):
    phase3_operations.append(reverse_insert_operations[insert_index])
    insert_index += 1

# 添加剩余的删除操作
while delete_index < len(phase3_delete_operations):
    phase3_operations.append(phase3_delete_operations[delete_index])
    delete_index += 1

# 添加剩余的查找操作
while search_index < len(reverse_search_operations):
    phase3_operations.append(reverse_search_operations[search_index])
    search_index += 1

# 第四阶段
# 从第三阶段的插入数据中随机抽取40%作为删除操作
phase3_insert_operations = reverse_insert_operations
phase4_delete_size = len(phase3_insert_operations) * 4 // 10
phase4_delete_operations = [('delete', op[1]) for op in random.sample(phase3_insert_operations, phase4_delete_size)]

# 从第三阶段的插入数据中随机抽取80%作为查找操作
phase4_search_size = len(phase3_insert_operations) * 8 // 10
phase4_search_operations = [('search', op[1]) for op in random.sample(phase3_insert_operations, phase4_search_size)]

# 将删除和查找操作混合
phase4_operations = []
delete_index, search_index = 0, 0
while delete_index < len(phase4_delete_operations) and search_index < len(phase4_search_operations):
    phase4_operations.append(phase4_delete_operations[delete_index])
    delete_index += 1
    if search_index < len(phase4_search_operations):
        phase4_operations.append(phase4_search_operations[search_index])
        search_index += 1

# 添加剩余的删除操作
while delete_index < len(phase4_delete_operations):
    phase4_operations.append(phase4_delete_operations[delete_index])
    delete_index += 1

# 添加剩余的查找操作
while search_index < len(phase4_search_operations):
    phase4_operations.append(phase4_search_operations[search_index])
    search_index += 1

# 将所有阶段的操作写入CSV文件
all_operations = phase1_operations + phase2_operations + phase3_operations + phase4_operations

# 生成findmin和findmax操作
find_operations = [('findmin', 0) for _ in range(insert_size // 2)] + [('findmax', 0) for _ in range(insert_size // 2)]
random.shuffle(find_operations)

# 随机插入findmin和findmax操作
for find_op in find_operations:
    insert_pos = random.randint(0, len(all_operations))
    all_operations.insert(insert_pos, find_op)

with open('benchmark_operations.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerows(all_operations)