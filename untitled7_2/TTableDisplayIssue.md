# TTable 类在中心部件不显示问题分析

## 问题现象
运行程序后，主窗口的中心部件没有显示 TTable 类的内容。

## 代码分析

### 1. MainWindow 构造函数
```cpp
// 在 mainwindow.cpp 中
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ... 其他初始化代码 ...
    
    // 创建 TTable 并设置为中心部件
    table = new TTable(this);
    this->setCentralWidget(table);
}
```
**问题**：TTable 类继承自 `QMainWindow`，而不是 `QWidget` 或 `QTableView`。

### 2. TTable 类定义
```cpp
// 在 ttable.h 中
class TTable : public QMainWindow
{
    Q_OBJECT
    // ...
};
```
**问题**：`QMainWindow` 是**顶级窗口类**，不适合作为另一个 `QMainWindow` 的中心部件。

## 技术原理

### QMainWindow 的特殊性质
`QMainWindow` 是 Qt 提供的顶级窗口类，它包含：
- 菜单栏 (`menuBar()`)
- 工具栏 (`addToolBar()`)
- 状态栏 (`statusBar()`)
- 停靠部件 (`addDockWidget()`)
- 中心部件 (`centralWidget()`)

这些组件构成了完整的窗口结构，当将一个 `QMainWindow` 作为另一个 `QMainWindow` 的中心部件时：
1. 两个顶级窗口结构会产生冲突
2. 子 `QMainWindow` 的布局系统可能无法正确工作
3. 子窗口的组件可能被父窗口的布局系统忽略

### 正确的中心部件类型
适合作为 `QMainWindow` 中心部件的类应该是：
- `QWidget` 或其子类（如 `QTableWidget`, `QTableView`, `QPlainTextEdit` 等）
- 不包含完整窗口结构的类

## 解决方案

### 方案一：修改 TTable 类的基类
将 TTable 类从继承 `QMainWindow` 改为继承 `QWidget` 或 `QTableView`。

#### 1. 修改 ttable.h
```cpp
// 从
class TTable : public QMainWindow
// 改为
class TTable : public QWidget  // 或 QTableView
```

#### 2. 修改 ttable.cpp
```cpp
// 从
TTable::TTable(QWidget *parent) : QMainWindow(parent), ui(new Ui::TTable)
// 改为
TTable::TTable(QWidget *parent) : QWidget(parent), ui(new Ui::TTable)
```

#### 3. 更新 ttable.ui
确保 ttable.ui 文件的基类也相应更新：
- 打开 ttable.ui
- 在右侧属性编辑器中，将 "objectName" 的类名从 QMainWindow 改为 QWidget
- 重新构建项目

### 方案二：使用 QMdiArea 管理多个窗口
如果需要保持 TTable 的 `QMainWindow` 特性，可以使用 `QMdiArea`：

#### 1. 修改 mainwindow.cpp
```cpp
// 在 MainWindow 构造函数中
ui->setupUi(this);

// 创建 QMdiArea 作为中心部件
QMdiArea *mdiArea = new QMdiArea(this);
this->setCentralWidget(mdiArea);

// 创建 TTable 并添加到 MDI 区域
TTable *table = new TTable(this);
mdiArea->addSubWindow(table);
table->show();
```

### 方案三：简化 TTable 实现
如果 TTable 只需要显示表格，可以直接使用 `QTableWidget` 或 `QTableView`：

```cpp
// 在 mainwindow.cpp 中
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 创建 QTableWidget 作为中心部件
    QTableWidget *tableWidget = new QTableWidget(10, 5, this);  // 10行5列
    this->setCentralWidget(tableWidget);
    
    // 设置表格内容
    tableWidget->setHorizontalHeaderLabels(QStringList() << "列1" << "列2" << "列3" << "列4" << "列5");
}
```

## 验证步骤

1. **修改代码**：选择上述方案之一进行修改
2. **重新构建**：在 Qt Creator 中点击 "构建" -> "重新构建项目"
3. **运行程序**：点击 "运行" 按钮
4. **检查结果**：观察主窗口的中心部件是否显示表格内容

## 注意事项

1. **UI 文件同步**：修改类的基类后，必须确保 UI 文件的基类也相应更新
2. **资源释放**：确保所有动态创建的对象都有正确的父对象，以便自动释放资源
3. **布局管理**：如果 TTable 包含多个控件，需要使用布局管理器来正确组织它们
4. **样式继承**：修改基类后，样式和行为可能会发生变化，需要重新测试

## 总结

TTable 类在中心部件不显示的主要原因是它继承自 `QMainWindow`，而 `QMainWindow` 不适合作为另一个 `QMainWindow` 的中心部件。解决方案是将 TTable 类的基类改为 `QWidget` 或 `QTableView`，或者使用 `QMdiArea` 来管理多个窗口。