import json

iStardardPrice = 10000

optionInfo = [
        { "qId":1, "type":1, "confType":1, "aList":[ {"aId":2, "value":40}, {"aId":3, "value":80}, ] },
        { "qId":4, "type":1, "confType":1, "aList":[ {"aId":5, "value":60}, {"aId":6, "value":90}, ] },
        { "qId":7, "type":2, "confType":1, "aList":[ {"aId":8, "value":89}, {"aId":9, "value":91}, ] },
        { "qId":10, "type":2, "confType":2, "aList":[ {"aId":11, "value":90}, {"aId":12, "value":45}, ] },
        { "qId":13, "type":2, "confType":2, "aList":[ {"aId":14, "value":80}, {"aId":15, "value":90}, ] },
        { "qId":16, "type":2, "confType":3, "aList":[ {"aId":17, "value":80}, {"aId":18, "value":10}, ] },
        { "qId":19, "type":2, "confType":3, "aList":[ {"aId":20, "value":40}, {"aId":21, "value":30}, {"aId":22, "value":31}, ] }
    ]

optionRule = [ { "aId":9, "aIdList":[11, 12], "afterAId":12 } ]

coefficientRule = [ { "aId":20, "value":30 } ]

optionGroup = [
        { "level":10, "lType":1, "lValue":30, "uType":1, "uValue":40, "option":[[8,11,14], [9,17,20]]},
        { "level":20, "lType":1, "lValue":50, "uType":1, "uValue":60, "option":[[14,17], [18,21]]},
        { "level":30, "lType":1, "lValue":70, "uType":1, "uValue":80, "option":[[9], [12], [15]]},
        { "level":40, "lType":1, "lValue":75, "uType":1, "uValue":85, "option":[[14], [17], [20]]},
        { "level":50, "lType":1, "lValue":90, "uType":1, "uValue":100, "option":[[15], [18], [21]]},
    ]

print("选项信息:%s" % (json.dumps(optionInfo)))
print("选项规则:%s" % (json.dumps(optionRule)))
print("系数规则:%s" % (json.dumps(coefficientRule)))
print("选项分组:%s" % (json.dumps(optionGroup)))

#排列组合 所有
iPermutationsSize = 0
for option in optionInfo:
    aList = option["aList"]
    iPermutationsSize = len(aList) if 0==iPermutationsSize else iPermutationsSize*len(aList)
print("排列组合个数:%d" % (iPermutationsSize))

aInfo = {}
for option in optionInfo:
    aList = option["aList"]
    for item in aList:
        aInfo[item["aId"]] = {}
        aInfo[item["aId"]]["qId"] = option["qId"]
        aInfo[item["aId"]]["type"] = option["type"]
        aInfo[item["aId"]]["confType"] = option["confType"]
        aInfo[item["aId"]]["value"] = item["value"]
print("答案项信息:%s" % (json.dumps(aInfo)))

konwnAId = []
for option in optionInfo:
    aList = option["aList"]
    #查找选项特殊规则/系数特殊规则/选项分组 如果不涉及该问题项 则可直接根据系数大小确定选择的答案项
    bFound = False
    for item in aList:
        iAId = item["aId"]
        if iAId
