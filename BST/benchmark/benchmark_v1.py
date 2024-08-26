import random
import csv

def generate_insert_and_delete_operations(insert_size, delete_size, lower_bound=0, upper_bound=10000):
    inserted_data = []
    operations = []
    delete_ratio = delete_size / insert_size

    for i in range(insert_size):
        value = random.randint(lower_bound, upper_bound)
        inserted_data.append(value)
        operations.append(('insert', value))

        # 根据删除比例，决定是否立即删除一些数据
        if random.random() < delete_ratio and len(inserted_data) > 0:
            delete_value = random.choice(inserted_data)
            operations.append(('delete', delete_value))
            inserted_data.remove(delete_value)  # 确保删除后不再使用此数据

    return operations, inserted_data

def generate_search_operations(operations, inserted_data, search_size, lower_bound=0, upper_bound=10000):
    search_operations = []
    inserted_sample = random.sample(inserted_data, min(search_size // 2, len(inserted_data)))
    search_operations.extend([('search', value) for value in inserted_sample])
    search_operations.extend([('search', random.randint(lower_bound, upper_bound)) for _ in range(search_size // 2)])

    # 将查找操作随机插入到操作序列中
    for search_op in search_operations:
        insert_index = random.randint(0, len(operations))
        operations.insert(insert_index, search_op)

    return operations

def generate_mixed_operations(insert_size, search_size, delete_size, lower_bound=0, upper_bound=10000):
    operations, inserted_data = generate_insert_and_delete_operations(insert_size, delete_size, lower_bound, upper_bound)
    operations = generate_search_operations(operations, inserted_data, search_size, lower_bound, upper_bound)
    return operations

def save_operations_to_file(filename, operations):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        for operation, value in operations:
            writer.writerow([operation, value])

# 生成混合操作
mixed_operations = generate_mixed_operations(10000, 10000, 5000)

# 保存到文件
save_operations_to_file('benchmark_operations.csv', mixed_operations)
