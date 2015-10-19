CREATE DATABASE IF NOT EXISTS click_db DEFAULT CHARACTER SET = utf8;
USE click_db;
CREATE TABLE IF NOT EXISTS user(name varchar(255), pwd varchar(50), last_login_stamp DATETIME);
CREATE TABLE IF NOT EXISTS static_monster(id int primary key auto_increment comment '怪物ID', scene_name varchar(255) comment '章节名称');
