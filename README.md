# C++ Lab 1. Coffeebeans Management System

这里的项目记录了我在中山大学计算机学院就读时完成的个人c++ lab 项目，以记录学习进度，提升能力

这是一个基于 C++ 的命令行咖啡豆管理系统，用来记录咖啡豆信息、维护冲煮指南，并管理咖啡豆与冲煮方案之间的配对关系。
## 项目概览

| 项目项 | 说明 |
| --- | --- |
| 项目类型 | Windows 控制台应用程序 |
| 开发语言 | C++ |
| 技术栈  | C++ ,stl|
| 标准版本 | C++20 |
| 工程文件 | `coffeemanager.vcxproj`、`coffeemanager.slnx` |
| 主要入口 | `main.cpp` |
| 默认导出文件 | `test.txt` |

## 主要功能

| 功能 | 说明 |
| --- | --- |
| 咖啡豆管理 | 添加、删除、查找、修改咖啡豆信息 |
| 冲煮指南管理 | 添加、删除、查找、修改冲煮参数 |
| 配对管理 | 将指定咖啡豆与指定冲煮指南建立组合关系 |
| 组合查询 | 根据咖啡豆查看对应冲煮方案 |
| 数据导出 | 将咖啡豆、冲煮指南和配对组合保存到文本文件 |
| 输入校验 | 对整数、浮点数输入进行基础校验，并对越界索引抛出错误 |
| 编码处理 | 保存文件时写入 UTF-8 BOM，降低中文乱码概率 |

## 项目结构

| 文件 / 目录 | 作用 |
| --- | --- |
| `main.cpp` | 程序入口，负责命令行菜单、用户输入和功能调用 |
| `Manager.hpp` / `Manager.cpp` | 管理器类，维护咖啡豆列表、冲煮指南列表和配对关系 |
| `CoffeeBean.hpp` / `CoffeeBean.cpp` | 咖啡豆实体类，保存名称、产地、烘焙日期、处理法、风味等信息 |
| `Brewing.hpp` / `Brewing.cpp` | 冲煮指南实体类，保存水温、研磨度、粉水比、滤杯、注水手法、冲煮时间等信息 |
| `coffeemanager.vcxproj` | Visual Studio C++ 项目配置 |
| `coffeemanager.slnx` | Visual Studio 解决方案文件 |
| `test.txt` | 默认导出的示例数据文件 |

## 构建与运行

### 使用 Visual Studio

1. 使用 Visual Studio 打开 `coffeemanager.slnx` 或 `coffeemanager.vcxproj`。
2. 选择构建配置，例如 `Debug | x64`。
3. 构建并运行项目。
4. 程序启动后会进入命令行菜单，根据提示输入编号执行操作。

### 使用 MSBuild

如果本机已经配置 Visual Studio C++ 构建环境，可以在 Developer PowerShell 或 Developer Command Prompt 中执行：

```powershell
msbuild coffeemanager.vcxproj /p:Configuration=Debug /p:Platform=x64
```

构建完成后运行：

```powershell
.\x64\Debug\coffeemanager.exe
```

## 菜单功能

| 编号 | 功能 |
| --- | --- |
| `1` | 添加咖啡豆 |
| `2` | 添加冲煮指南 |
| `3` | 删除咖啡豆 |
| `4` | 删除冲煮指南 |
| `5` | 根据索引查找咖啡豆 |
| `6` | 根据索引查找冲煮指南 |
| `7` | 修改咖啡豆 |
| `8` | 修改冲煮指南 |
| `9` | 根据索引添加咖啡豆与冲煮指南配对 |
| `10` | 根据索引创建配对 |
| `11` | 根据咖啡豆索引删除配对 |
| `12` | 根据咖啡豆名称替换配对 |
| `13` | 根据咖啡豆索引查看组合冲煮方案 |
| `14` | 保存到文件 |
| `Q` / `q` | 退出程序 |

## 测试输入示例

下面的数据会添加一个咖啡豆，保存到默认 `test.txt`，然后退出：

```text
1
埃塞俄比亚 花魁
埃塞俄比亚 古吉
2026-06-26
水洗
3
柑橘
茉莉花
蜂蜜
14

q
```

`14` 后面的空行表示直接回车，使用默认文件名 `test.txt`。
