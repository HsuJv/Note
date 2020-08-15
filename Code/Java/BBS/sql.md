

#### 概要
+ 根据对BBS论坛相关的需求分析，将在数据库中共建五张表：
	1. account_table
	2. cata_table
	3. message_table
	4. revert_table
	5. words_table

#### 用戶表account_table
+ 作为存储论坛所有账号信息的表，共建立如下5个字段：
	1. account_account
		- 用户数字账号
		- 主键
		- 由自增机制直接给予，保证不重复
		- 数字类型
	2. account_name
		- 用户账号个性名字
		- 字符类型
	3. account_pass
		- 用户账号密码
		- 字符类型
	4. account_limit
		- 用户账号权限识别码，-1为站长，1为用户
		- 用户所具有的权限为版块id所对应的质数的乘积
		- 数字类型
	5. account_date
		- 用户账号创建日期
		- date类型

+ derby实现代码：
```
create table account_table(
account_account bigint primary key not null generated always as identity,
account_name varchar(30) unique not null,
account_pass varchar(30) not null,         
account_limit int default 1,       
account_date date default CURRENT_DATE    
);
```


#### 版块表cata_table
+ 作为存储论坛所有版块信息的表，共建如下2个字段：
	1. cata_id
		- 版块id
		- 主键
		- 数字类型
	2. cata_name
		- 版块名字
		- 对应版块的课程名
		- 字符类型


+ derby实现代码：
```
create table cata_table(
cata_id smallint primary key not null generated always as identity,
cata_name varchar(30)
);
```



#### 帖子表message_table
+ 作为存储论坛所有主题帖信息的表，共建如下6个字段：
	1. message_account
		- 主题帖发帖人数字账号
		- 对应account_table表的外键
		- 数字类型
	2. message_cata
		- 主题帖所在版块
		- 对应cata_table表的外键
		- 数字类型
	3. message_id
		- 主题帖的id
		- 主键
		- 由自增机制直接给予，保证不重复
		- 数字类型
	4. message_title
		- 主题帖名称
		- 字符类型
	5. message_content
		- 主题的内容
		- 字符类型
	6. message_date
		- 主题帖的发帖日期
		- 由系统直接给予
		- timestamp类型

+ derby实现代码：
```
create table message_table(
message_account bigint not null,
message_cata smallint not null,
message_id bigint primary key not null generated always as identity,
message_title varchar(30) not null,
message_content varchar(300) not null,
message_date timestamp default CURRENT_TIMESTAMP,
constraint fk_message_account_account foreign key(message_account) references account_table(account_account),
constraint fk_message_cata foreign key(message_cata) references cata_table(cata_id)
);
```

#### 回复表revert_table
+ 作为存储论坛所有回复帖信息的表，共建如下5个字段：
	1. revert_account
		- 回复贴的发帖人数字账号
		- 设立对应account表的外键
		- 数字类型
	2. revert_messageid
		- 所回复的主题帖的id
		- 设立对应message表的外键
		- 数字类型
	3. revert_id
		- 回复贴的id主键
		- 由自增机制直接给予，保证不重复
		- 数字类型
	4. revert_content
		- 回复贴的内容
		- 字符类型
	5. revert_date
		- 回复贴的发帖日期
		- 由系统直接给予
		- timestamp类型

+ derby实现代码：
```
create table revert_table(
revert_account bigint not null,
revert_messageid bigint not null,
revert_id bigint primary key not null generated always as identity,
revert_content varchar(300) not null,
revert_date timestamp default CURRENT_TIMESTAMP,
constraint fk_revert_account_account  foreign key(revert_account) references account_table(account_account),
constraint fk_revert_message_id foreign key(revert_messageid)  references message_table(message_id)
);
``` 

#### 留言表words_table
+ 作为存储论坛所有留言信息的表，共建如下6个字段：
	1. words_object
		- 该留言目标的数字账号
		- 设立对应account表的外键
		- 数字类型
	2. words_subject
		- 该留言发起者的数字账号
		- 设立对应account表的外键
		- 数字类型
	3. words_id
		- 留言的id主键
		- 由自增机制直接给予，保证不重复
		- 数字类型
	4. words_content
		- 留言的内容
		- 字符类型
	5. words_new
		- 留言是否已读
		- 数字类型
	6. words_date
		- 留言的日期
		- 由系统直接给予
		- timestamp类型

+ derby实现代码：
```
create table words_table(
words_object bigint not null,
words_subject bigint not null,
words_id bigint primary key not null generated always as identity,
words_content varchar(300) not null,
words_new smallint not null default 1,
words_date timestamp default CURRENT_TIMESTAMP,
constraint fk_words_object_account foreign key(words_object)  references account_table(account_account),
constraint fk_words_subject_account foreign key(words_subject) references account_table(account_account)
);
``` 

#### 插入初始值
```
insert into account_table(account_name, account_pass, account_limit) values('root', 'root', -1)
```
