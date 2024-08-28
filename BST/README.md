感谢提醒，以下是修正后的 `README` 文件内容，改为在构建根目录运行脚本。

---

# README

## Test Dataset Generation Method

To generate a test dataset, run the following command from the root directory of this project:

```bash
python benchmark/benchmark_v4.py --insert_size {desired_value}
```

We recommend setting the `insert_size` to `100,000`. This data volume helps with effective debugging and minimizes errors during performance testing.

### Example Dataset Format

The generated test dataset will have the following format:

```text
findmin,0
insert,61
search,320297
```

The dataset includes the following five operations: `findmin`, `findmax`, `search`, `delete`, and `insert`. The operation count for `findmin` and `findmax` is always `0`.

Make sure that at least these five operations are included when generating the dataset.

## Correctness Testing Method

To verify the correctness of your program, please provide an executable file. After running the test dataset, the program should output a log file containing the following information:

- `insert`: operation count
- `search`: operation count and whether the operation was successful (`true/false`)
- `delete`: operation count and whether the operation was successful (output `null` if it fails)
- `findmin` and `findmax`: the minimum and maximum values found. If the tree is empty, output `null`

This log data should be saved in a file named `correctness.csv`.

After completing the above steps, run the script in the `correctness` folder from the root directory to perform the correctness verification.

We recommend referring to the logic in the existing code for these parts.

### Example Log Data

Below is an example of what the `correctness.csv` file might look like:

```text
insert,61,true
search,320297,false
delete,100,null
findmin,42
findmax,999
findmin,null
```

## Automated Performance Testing

After generating the test dataset and verifying the correctness of your program, you can also measure the performance of your implementation using the `average_time.sh` script located in the `benchmark` folder.

### Benchmark Output Requirements

To ensure compatibility with the automated testing script, your program's benchmark output must include the following line:

```text
Total time to execute all operations: %.6f seconds\n
```

This output will be parsed by the `average_time.sh` script to compute the average execution time of all operations performed in your program.

### Running the Automated Performance Test

To run the performance test, use the following command from the root directory, where `dune exec <executable>` should be replaced with the appropriate command that runs your program:

```bash
./benchmark/average_time.sh dune exec <executable>
```

For instance, if your build system requires a different command, replace `dune exec <executable>` with your specific build command.

### Example Output

Upon execution, the script will run your program multiple times and output the average execution time for all operations. This helps in analyzing the performance and efficiency of your implementation over multiple test runs.

### Important Notes

- Ensure that the benchmark output format strictly follows the requirement mentioned above.
- The performance test script assumes that the necessary environment and dependencies are correctly set up. Make sure to run any necessary environment setup commands before executing the script.
- The `average_time.sh` script will handle the repeated execution and timing of your program automatically, providing a consolidated report at the end.

By following these steps, you can systematically evaluate both the correctness and performance of your implementation.

---

# README (简体中文)

## 测试数据集生成方法

要生成测试数据集，请在项目的根目录中运行以下命令：

```bash
python benchmark/benchmark_v4.py --insert_size {你需要的数值}
```

建议将 `insert_size` 设置为 `100,000`。这个数据量级能够有效帮助你进行故障排除，并在测试性能时降低误差。

### 数据集格式示例

生成的测试数据集将采用以下格式：

```text
findmin,0
insert,61
search,320297
```

该数据集包含以下五种操作：`findmin`、`findmax`、`search`、`delete` 和 `insert`。其中，`findmin` 和 `findmax` 操作的操作数固定为 `0`。

因此，在生成数据集时，请确保至少包括这五种操作。

## 正确性测试方法

为了验证程序的正确性，请提供一个可执行文件。在运行生成的测试数据集后，程序应输出相应的日志文件，日志内容包括以下信息：

- `insert`：操作数
- `search`：操作数以及操作是否成功（`true/false`）
- `delete`：操作数以及操作是否成功（如果失败则输出 `null`）
- `findmin` 和 `findmax`：找到的最小值和最大值。如果树为空，则输出 `null`

这些日志数据应保存为 `correctness.csv` 文件。

完成上述步骤后，从根目录中运行 `correctness` 文件夹中的脚本，以进行正确性验证。

我们推荐参考已有代码的逻辑来实现这些部分。

### 示例日志数据

以下是 `correctness.csv` 文件的示例内容：

```text
insert,61,true
search,320297,false
delete,100,null
findmin,42
findmax,999
findmin,null
```

## 自动化性能测试

在生成测试数据集并验证程序正确性后，您还可以使用位于 `benchmark` 文件夹中的 `average_time.sh` 脚本来衡量您的实现的性能。

### 基准输出要求

为了确保与自动化测试脚本兼容，您的程序基准输出必须包含以下内容：

```text
Total time to execute all operations: %.6f seconds\n
```

此输出将由 `average_time.sh` 脚本解析，以计算程序中所有操作的平均执行时间。

### 运行自动化性能测试

要运行性能测试，请从根目录中使用以下命令，其中 `dune exec <executable>` 应替换为运行程序的相应命令：

```bash
./benchmark/average_time.sh dune exec <executable>
```

例如，如果您的构建系统需要不同的命令，请将 `dune exec <executable>` 替换为您的特定构建命令。

### 输出示例

执行后，脚本将多次运行您的程序，并输出所有操作的平均执行时间。这有助于通过多次测试运行来分析实现的性能和效率。

### 重要提示

- 确保基准输出格式严格遵循上述要求。
- 性能测试脚本假定必要的环境和依赖项已正确设置。请确保在执行脚本之前运行任何必要的环境设置命令。
- `average_time.sh` 脚本将自动处理程序的重复执行和计时，并在最后提供综合报告。

通过遵循这些步骤，您可以系统地评估实现的正确性和性能。
