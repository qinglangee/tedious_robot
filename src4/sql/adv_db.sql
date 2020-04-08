
-- 初始化数据库方法
-- sqlite3  -init adv_db.sql   adv.db 
-- 也可以先命令行登录数据库，用 read 命令执行 sql 脚本
-- sqlite> .read "d:\\workspaces\\vscode_c++\\tedious_robot\\src4\\sql\\adv_db.sql"
CREATE TABLE group_info(  
         ID INT PRIMARY KEY     NOT NULL, 
         NAME           TEXT    NOT NULL, 
         member_count            INT     NOT NULL);
