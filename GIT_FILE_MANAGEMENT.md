# STM32 项目文件管理指南

## 📁 文件分类说明

### ✅ 核心文件（必须版本控制）

#### 1. 源代码 (最重要)
```
Core/Inc/*.h          - 头文件
Core/Src/*.c          - C 源文件
Core/Startup/*.s      - 启动汇编文件
Core/App/*.c/h        - 应用层代码（如果有）
```
**原因**: 这是你编写的代码，是项目的核心

#### 2. HAL 驱动库
```
Drivers/CMSIS/        - ARM CMSIS 标准接口
Drivers/STM32F1xx_HAL_Driver/  - STM32 HAL 库
```
**原因**: 编译必需，虽然体积大但必须包含

#### 3. 配置文件
```
*.ioc                 - STM32CubeMX 配置（⭐ 非常重要）
*.ld                  - 链接脚本
README.md             - 项目文档
```
**原因**: 
- `.ioc` 文件可以重新生成整个项目
- 链接脚本定义内存布局
- 文档说明项目用途

#### 4. 项目文件
```
.project              - Eclipse 项目定义
.cproject             - C/C++ 项目配置
.mxproject            - CubeMX 项目元数据
```
**原因**: IDE 需要这些文件打开项目

---

### ❌ 不需要追踪的文件

#### 1. 编译输出 (最大的垃圾)
```
Debug/                - 调试版本输出目录
Release/              - 发布版本输出目录
*.elf                 - 可执行文件 (几百KB)
*.bin, *.hex          - 烧录文件
*.map                 - 内存映射 (几百KB)
*.o, *.d              - 中间文件
```
**原因**: 
- 可以随时重新编译生成
- 体积大，占用仓库空间
- 每次编译都会变化

#### 2. IDE 临时文件
```
.metadata/            - Eclipse 工作空间元数据
.settings/language.settings.xml  - 自动生成的设置
*.launch              - 调试配置（可选）
```
**原因**: 
- IDE 自动生成
- 包含本地路径信息
- 不同开发者配置不同

#### 3. 系统文件
```
.DS_Store             - macOS 文件夹属性
Thumbs.db             - Windows 缩略图
*.log, *.tmp          - 临时文件
```
**原因**: 操作系统生成，与项目无关

---

## 📊 文件大小对比

### 典型 STM32 项目大小分析

```
完整项目（包含编译输出）:
├── 源代码: ~50KB
├── HAL 驱动: ~15MB
├── 编译输出: ~5-10MB  ⚠️ 不需要
└── 总计: ~20-25MB

仅源代码（推荐追踪）:
├── 源代码: ~50KB
├── HAL 驱动: ~15MB
└── 总计: ~15MB
```

**节省空间**: 忽略编译输出可节省 30-40% 空间

---

## 🎯 推荐策略

### 方案 A: 标准策略（推荐）

**追踪**:
- ✅ 所有源代码
- ✅ HAL 驱动库
- ✅ .ioc 配置文件
- ✅ 项目文件 (.project, .cproject)
- ✅ README.md

**忽略**:
- ❌ Debug/ Release/ 目录
- ❌ 所有编译输出 (*.elf, *.bin, *.hex, *.o, *.d)
- ❌ .metadata/
- ❌ 系统临时文件

**优点**:
- 仓库体积小
- 克隆快速
- 任何人都可以重新编译

---

### 方案 B: 最小化策略（高级）

**追踪**:
- ✅ 源代码
- ✅ .ioc 配置文件
- ✅ README.md
- ❌ HAL 驱动库（通过 CubeMX 重新生成）

**优点**:
- 仓库极小（几十KB）
- 适合多项目管理

**缺点**:
- 需要每个开发者自己生成 HAL 库
- 增加了设置复杂度

**不推荐**，除非你有特殊需求

---

## 🔧 实际操作

### 当前仓库状态检查

```bash
# 检查哪些大文件被追踪
git ls-files | xargs du -h | sort -rh | head -20

# 检查 Debug 目录是否被追踪
git ls-files | grep Debug

# 查看仓库大小
du -sh .git
```

### 清理已追踪的编译文件

如果之前不小心提交了 Debug/ 目录：

```bash
# 从 Git 历史中删除（谨慎操作）
git rm -r --cached Debug/
git rm -r --cached Release/
git commit -m "chore: remove build artifacts from git"
```

---

## 📋 团队协作建议

### .settings/ 目录处理

**选项 1: 忽略（推荐）**
```gitignore
.settings/
```
- 每个开发者使用自己的 IDE 设置
- 避免设置冲突

**选项 2: 部分追踪**
```gitignore
.settings/
!.settings/org.eclipse.core.resources.prefs
!.settings/stm32cubeide.project.prefs
```
- 追踪项目相关设置
- 忽略个人偏好设置

### *.launch 文件处理

**调试配置文件**，包含：
- 调试器设置
- 烧录配置
- 断点信息

**建议**: 
- 单人项目：可以追踪
- 团队项目：建议忽略（每人配置不同）

---

## ✅ 最终推荐配置

你当前的 `.gitignore` 已经更新为最佳实践配置：

```gitignore
# 编译输出
Debug/
Release/
*.elf
*.bin
*.hex
*.map
*.o
*.d

# IDE 临时文件
.metadata/
.settings/language.settings.xml

# 系统文件
.DS_Store
*.log
*.tmp
```

这个配置：
- ✅ 保护核心源代码
- ✅ 忽略编译输出
- ✅ 减少仓库体积
- ✅ 避免冲突
- ✅ 适合团队协作

---

## 🎓 总结

### 记住这个原则：

**追踪**: 人写的代码  
**忽略**: 机器生成的文件

### 核心文件优先级：

1. ⭐⭐⭐ `Core/Src/*.c` - 你的代码
2. ⭐⭐⭐ `*.ioc` - 配置文件
3. ⭐⭐ `Drivers/` - HAL 库
4. ⭐ `.project, .cproject` - 项目文件
5. ❌ `Debug/, *.elf, *.o` - 编译输出

### 快速检查清单：

- [ ] `.gitignore` 包含 `Debug/` 和 `Release/`
- [ ] 没有 `.elf`, `.bin`, `.hex` 文件被追踪
- [ ] `.ioc` 文件已提交
- [ ] `Core/Src/` 目录已提交
- [ ] `README.md` 已更新

---

**遵循这些规则，你的 Git 仓库将保持干净、高效！** ✨
