# -*- coding: utf-8 -*
##
# File: mysql.py
# Synopsis: MySQL模块封装，主要处理连接管理问题
# Author: CaseZheng, 764307915@qq.com
# Version: 1.0.0
# Date: 2017-07-21

import os
import sys
import MySQLdb as MYSQL

##
# Synopsis: MySQL封装类
class MySQLClient(object):
    # 类属性
    socket_timeout = 0.5

    ##
    # Synopsis: 初始化MySQLClient，并尝试建立连接
    def __init__(self, *args, **kw):
        self.m_host = kw.get('host');
        self.m_port = kw.get('port');
        self.m_db = kw.get('db');
        self.m_user = kw.get('user');
        self.m_password = kw.get('password');
        self.m_mysql = None;
        self.m_cursor = None;
        self.Connect();
        pass

    def __del__(self):
        if self.m_cursor is not None:
            self.m_cursor.close()
        if self.m_mysql is not None:
            self.m_mysql.close()
        pass

    ##
    # Synopsis: ExceptionHandling 装饰器，用于mysql操作的封装
    #
    # Param: func 传入的操作
    #
    # Return: 返回func操作结果 或出错信息
    def ExceptionHandling(func):
        def function(self, *args, **kw):
            try:
                return func(self, *args, **kw), True
            except BaseException:
                return "error", False
        return function


    ##
    # Synopsis: 连接Mysql
    @ExceptionHandling
    def Connect(self):
        self.m_mysql = MYSQL.connect(host=self.m_host, port=self.m_port, \
                        user=self.m_user, db=self.m_db, passwd=self.m_password, \
                        charset='utf8');
        if self.m_mysql != None:
            return True
        else:
            return False

    ##
    # Synopsis: GetMySQL 得到MySQL游标的唯一出口
    #
    # Return: 返回MySQL连接游标，如果连接不到返回None
    def GetMySQL(self):
        if None == self.m_mysql:
            # 为空，则连接下
            self.Connect();
        return self.m_mysql.cursor()

    ################################ mysql方法封装，需要用哪个命令加入下即可 #################
    #
    @ExceptionHandling
    def Execute(self, sql):
        cursor = self.GetMySQL()
        ret = cursor.execute(sql);
        self.m_mysql.commit();
        cursor.close()
        return ret

    @ExceptionHandling
    def QueryExecute(self, sql):
        cursor = self.GetMySQL()
        ret = cursor.execute(sql);
        self.m_mysql.commit();
        ret = cursor.fetchall();
        self.m_mysql.commit();
        cursor.close()
        return ret
    #
    ################################ mysql方法封装，需要用哪个命令加入下即可 #################


##
# Synopsis: MySQL管理类，通过此管理器管理所有MySQL
class MySQLManager(object):
    def __init__(self, *args, **kw):
        pass

    def __del__(self):
        pass

    def __new__(cls, *args, **kw):
        if not hasattr(cls, '_instance'):
            cls._instance = object.__new__(cls, *args, **kw)
            cls._instance.m_MySQLManager = {}

        name = kw.get('name')
        host = kw.get('host')
        port = kw.get('port')
        db = kw.get('db')
        user = kw.get('user')
        password = kw.get('password')

        # 未传入name，default MySQL还未创建，则将其设置为default MySQL
        if None == name and (not 'default' in cls._instance.m_MySQLManager):
            name = 'default'

        # 未传入name，default已存在，不能创建MySQL，直接返回
        if None == name:
            return cls._instance

        # 创建MySQLClient实例，并加入到MySQLManager中
        mysql = MySQLClient(host=host, port=port, db=db, user=user, password=password)
        mySQLInfo = {}
        if None != mysql.GetMySQL():
            mySQLInfo = {'host':host, 'port':port, 'db':db, 'user':user, \
                         'password':password, 'mysql':mysql}
            cls._instance.m_MySQLManager[name] = mySQLInfo

        return cls._instance

    ##
    # Synopsis: 得到MySQL原生指针，使用原生的MySQL方法操作MySQL，需要自己处理异常
    #           不建议外部直接调用
    @staticmethod
    def GetNativeMySQL(cls, name='default'):
        if hasattr(cls, '_instance'):
            mySQLinfo = cls._instance.m_MySQLManager.get(name)
            if None != mySQLinfo:
                return mySQLinfo.get('mysql').GetMySQL()
        return None

    ##
    # Synopsis: 得到MySQLClient 使用MySQLClient提供的方法操作MySQL
    @staticmethod
    def GetMySQL(cls, name='default'):
        if hasattr(cls, '_instance'):
            mySQLinfo = cls._instance.m_MySQLManager.get(name)
            if None != mySQLinfo:
                return mySQLinfo.get('mysql')
        return None

##
# Synopsis: GetMySQLByName 根据name返回对应的MySQLClient，使用MySQLClient提供的方法操作MySQL，
#
# Param: name
#
# Return:
def GetMySQLByName(name='default'):
    name = 'default' if None==name or ''==name else name
    return MySQLManager.GetMySQL(MySQLManager, name)

##
# Synopsis: GetNativeMySQLByName 根据name返回对应MySQL原生引用，需要自己处理异常，不建议使用
#
# Param: name
#
# Return:
def GetNativeMySQLByName(name='default'):
    name = 'default' if None==name or ''==name else name
    return MySQLManager.GetNativeMySQL(MySQLManager, name)

##
# Synopsis: InitMySQL 用于初始化MySQL模块 可调用多次，初始化多个MySQL
#
# Param: args
# Param: kw
#
# Return:
def InitMySQL(*args, **kw):
    name = kw.get('name')
    host = kw.get('host')
    port = kw.get('port')
    db = kw.get('db')
    user = kw.get('user')
    password = kw.get('password')
    MySQLManager(name=name, host=host, port=port, db=db, user=user, password=password)

# 测试代码
if '__main__' == __name__:
    InitMySQL(host="127.0.0.1", port=3306, user='root', db='mydb', password='167349');
    mysql = GetMySQLByName()
    if mysql != None:
        mysql.Execute("select version();")
        print mysql.Fetchone()
        mysql.Execute("show tables;")
        print mysql.Fetchone()
    print mysql
    sys.stdout.flush()
    pass
