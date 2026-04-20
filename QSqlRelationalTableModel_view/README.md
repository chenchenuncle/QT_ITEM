## 简易学生管理系统
一个基于 Qt 的学生信息管理系统，使用 QTableView/QSqlRelationalTableModel实现数据库关系管理，支持学院和专业的级联显示

## 功能特点

- **数据库连接**：支持 SQLite 数据库文件选择
- **关系数据显示**：自动关联学院和专业表，显示名称而非ID
- **数据管理**：支持添加、插入、删除、保存等操作
- **随机ID生成**：自动生成唯一的学生ID
- **用户友好界面**：直观的表格视图和操作按钮

<img width="1910" height="1010" alt="image" src="https://github.com/user-attachments/assets/de194c23-df4e-4e27-967d-ccd6767e94d9" />

## 技术栈

- **框架**：Qt 6.9.2
- **数据库**：SQLite
- **模型**：QSqlRelationalTableModel
- **视图**：QTableView
- **委托**：QSqlRelationalDelegate

## 比较亮点技术
## 随机唯一ID生成
(https://github.com/chenchenuncle/QT_Study_Project/blame/f8ddb25c9de32985d48bf9e73b0451ae0c8f3527/QSqlRelationalTableModel_view/mainwindow.cpp#L13-L31)
