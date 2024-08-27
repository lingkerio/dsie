# README

## Test Dataset Generation Method

To generate a test dataset, run the following command in the `benchmark` folder of this project:

```bash
python benchmark_v3.py --insert_size {desired_value}
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

After completing these steps, navigate to the `correctness` folder within the directory containing this file, and run the script inside to perform the correctness verification.

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

---

# README (简体中文)

## 测试数据集生成方法

要生成测试数据集，请在本项目的 `benchmark` 文件夹中运行以下命令：

```bash
python benchmark_v3.py --insert_size {你需要的数值}
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

完成上述步骤后，在包含该文件的目录下，进入 `correctness` 文件夹并运行其中的脚本，以进行正确性验证。

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
