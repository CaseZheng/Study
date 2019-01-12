# -*- coding: utf-8 -*
##
# File: redis_cli.py
# Synopsis: Redis模块封装 主要处理Redis的连接问题 ，多个Redis的管理，封装redis原始
#           接口，屏蔽异常
# Author: CaseZheng, 764307915@qq.com
# Version: 1.0.0
# Date: 2017-07-21

import redis
import os
import sys

##
# Synopsis: Redis封装类
class RedisClient():
    # 类属性
    socket_timeout = 0.5

    ##
    # Synopsis: 初始化RedisClient，并尝试建立连接
    def __init__(self, *args, **kw):
        self.m_host = kw.get('host');
        self.m_port = kw.get('port');
        self.m_password = kw.get('password');
        self.m_redispool = None;
        self.m_redis = None;
        self.Connect();
        pass

    def __del__(self):
        pass

    ##
    # Synopsis: ExceptionHandling 装饰器，用于redis操作的封装
    #
    # Param: func 传入的操作
    #
    # Return: 返回func操作结果 或出错信息
    def ExceptionHandling(func):
        def function(self, *args, **kw):
            try:
                return func(self, *args, **kw), True
            except redis.ConnectionError:
                return "ConnectionError", False
            except redis.DataError:
                return "DataError", False
            except redis.PubSubError:
                return "PubSubError", False
            except redis.RedisError:
                return "RedisError", False
            except redis.ResponseError:
                return "ResponseError", False
            except redis.TimeoutError:
                return "TimeoutError", False
            except redis.WatchError:
                return "WatchError", False
            except BaseException:
                return "error", False
        return function

    ##
    # Synopsis: 连接Redis 创建RedisPool
    def Connect(self):
        if self.m_password != None \
            and self.m_password != "":
            self.m_redispool = redis.ConnectionPool( \
                host=self.m_host, \
                password=self.m_password, \
                port=self.m_port, \
                socket_timeout=self.socket_timeout, \
                db=0);
        else:
            self.m_redispool = redis.ConnectionPool( \
                host=self.m_host, \
                port=self.m_port, \
                socket_timeout=self.socket_timeout, \
                db=0);
        ret, msg = self.Ping()

        if ret:      # 创建连接池后先连接下
            return True, msg
        else:
            self.m_redispool = None
            return ret, msg

    ##
    # Synopsis: GetRedis 得到Redis连接的唯一出口
    #
    # Return: 返回Redis连接，如果连接不到返回None
    def GetRedis(self):
        if None == self.m_redis:
            # 为空，则连接下
            if None == self.m_redispool:
                self.Connect();

            # 还是为空，返回None
            if None == self.m_redispool:
                return None

            self.m_redis = redis.Redis(connection_pool=self.m_redispool);
        return self.m_redis

    #################################redis方法封装，需要用哪个命令加入下即可##################
    #
    # 对redis方法的封装，返回值为两个，第一个未当前命令是否发送成功 第二个为RedisServer返回信息
    # 例如调用Ping() 成功返回(True, True) 失败返回(False, 失败原因)
    @ExceptionHandling
    def Ping(self):
        return self.GetRedis().ping();

    @ExceptionHandling
    def Get(self, key):
        return self.GetRedis().get(key)

    @ExceptionHandling
    def HGetAll(self, key):
        return self.GetRedis().hgetall(key)

    @ExceptionHandling
    def HDel(self, key1, key2):
        return self.GetRedis().hdel(key1, key2)

    @ExceptionHandling
    def HSet(self, key1, key2, value):
        return self.GetRedis().hset(key1, key2, value)
    #
    #################################redis方法封装，需要用哪个命令加入下即可##################


##
# Synopsis: Redis管理类，通过此管理器管理所有Redis
class RedisManager(object):
    def __init__(self, *args, **kw):
        pass

    def __del__(self):
        pass

    def __new__(cls, *args, **kw):
        if not hasattr(cls, '_instance'):
            cls._instance = object.__new__(cls, *args, **kw)
            cls._instance.m_RedisManager = {}

        name = kw.get('name')
        host = kw.get('host')
        port = kw.get('port')
        password = kw.get('password')

        # 未传入name，default Redis还未创建，则将其设置为default Redis
        if None == name and (not 'default' in cls._instance.m_RedisManager):
            name = 'default'

        # 未传入name，default已存在，不能创建Redis，直接返回
        if None == name:
            return cls._instance

        # 创建RedisClient实例，并加入到RedisManager中
        rc = RedisClient(host=host, port=port, password=password)
        redisinfo = {}
        if None != rc.GetRedis():
            redisinfo = {'host':host, 'port':port, 'password':password, 'redis':rc}
            cls._instance.m_RedisManager[name] = redisinfo

        return cls._instance

    ##
    # Synopsis: 得到redis原生指针，使用原生的redis方法操作redis，需要自己处理异常
    #           不建议外部直接调用
    @staticmethod
    def GetNativeRedis(cls, name='default'):
        if hasattr(cls, '_instance'):
            redisinfo = cls._instance.m_RedisManager.get(name)
            if None != redisinfo:
                return redisinfo.get('redis').GetRedis()
        return None

    ##
    # Synopsis: 得到RedisClient 使用RedisClient提供的方法操作
    @staticmethod
    def GetRedis(cls, name='default'):
        if hasattr(cls, '_instance'):
            redisinfo = cls._instance.m_RedisManager.get(name)
            if None != redisinfo:
                return redisinfo.get('redis')
        return None

##
# Synopsis: GetRedisByName 根据name返回对应的RedisClient，使用RedisClient提供的方法操作redis，
#
# Param: name
#
# Return:
def GetRedisByName(name='default'):
    name = 'default' if None==name or ''==name else name
    return RedisManager.GetRedis(RedisManager, name)

##
# Synopsis: GetNativeRedisByName 根据name返回对应redis原生引用，需要自己处理异常，不建议使用
#
# Param: name
#
# Return:
def GetNativeRedisByName(name='default'):
    name = 'default' if None==name or ''==name else name
    return RedisManager.GetNativeRedis(RedisManager, name)

##
# Synopsis: InitRedis 用于初始化Redis 可调用多次，初始化多个Redis
#
# Param: args
# Param: kw
#
# Return:
def InitRedis(*args, **kw):
    name = kw.get('name')
    host = kw.get('host')
    port = kw.get('port')
    password = kw.get('password')
    RedisManager(name=name, host=host, port=port, password=password)

# 测试代码
if '__main__' == __name__:
    InitRedis(host="192.168.200.143", port=6321, password=None);
    InitRedis(name='1', host="192.168.200.144", port=6321, password=None);
    rm = GetRedisByName()
    print rm.Ping()
    print GetRedisByName(name='1')
    sys.stdout.flush()
    pass
