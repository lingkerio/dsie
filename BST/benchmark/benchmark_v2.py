import random
import csv

def generate_delete_operations(inserted_data, delete_size):
    delete_operations = [('delete', value) for value in random.sample(inserted_data, delete_size)]
    return delete_operations

def generate_insert_and_delete_operations(insert_size, delete_size, lower_bound=0, upper_bound=10000):
    inserted_data = []
    operations = []
    
    # 阶段阈值：四分之一、二分之一、四分之三
    thresholds = [insert_size // 4, insert_size // 2, (insert_size * 3) // 4]
    delete_operations_per_stage = delete_size // len(thresholds)
    
    for i in range(insert_size):
        value = random.randint(lower_bound, upper_bound)
        inserted_data.append(value)
        operations.append(('insert', value))
        
        # 在达到每个阈值时插入删除操作
        if i + 1 in thresholds:
            delete_operations = generate_delete_operations(inserted_data, delete_operations_per_stage)
            operations.extend(delete_operations)
            inserted_data = [val for val in inserted_data if val not in [d[1] for d in delete_operations]]
    
    return operations, inserted_data

def generate_search_operations(operations, inserted_data, search_size, lower_bound=0, upper_bound=10000):
    search_operations = []
    
    # 从已经插入的数据中随机选择一部分作为查找操作
    inserted_sample = random.sample(inserted_data, min(search_size // 2, len(inserted_data)))
    search_operations.extend([('search', value) for value in inserted_sample])
    
    # 生成一些随机值作为查找操作，这些值可能不在树中
    search_operations.extend([('search', random.randint(lower_bound, upper_bound)) for _ in range(search_size // 2)])
    
    # 将查找操作随机插入到已有的操作序列中
    for search_op in search_operations:
        insert_index = random.randint(0, len(operations))
        operations.insert(insert_index, search_op)
    
    return operations

def generate_mixed_operations_with_staged_deletes(insert_size, search_size, delete_size, lower_bound=0, upper_bound=10000):
    operations, inserted_data = generate_insert_and_delete_operations(insert_size, delete_size, lower_bound, upper_bound)
    
    # 最后插入查找操作
    final_operations = generate_search_operations(operations, inserted_data, search_size, lower_bound, upper_bound)
    
    return final_operations

def save_operations_to_file(filename, operations):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        for operation, value in operations:
            writer.writerow([operation, value])

# 生成混合操作
mixed_operations = generate_mixed_operations_with_staged_deletes(10000, 10000, 5000)

# 保存到文件
save_operations_to_file('benchmark_operations.csv', mixed_operations)
