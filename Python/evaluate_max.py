import json
import copy

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
        { "level":30, "lType":2, "lValue":7000, "uType":1, "uValue":80, "option":[[9], [12], [15]]},
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

indefiniteOption = set()
for option in optionRule:
    for aId in option["aIdList"]:
        indefiniteOption.add(aId)
for option in coefficientRule:
    indefiniteOption.add(option["aId"])
for option in optionGroup:
    for aIdList in option["option"]:
        for aId in aIdList:
            indefiniteOption.add(aId)
print("不定答案项:%s" % (indefiniteOption))

konwnAId = []
konwnQId = []
for option in optionInfo:
    aList = option["aList"]
    #查找选项特殊规则/系数特殊规则/选项分组 如果不涉及该问题项 则可直接根据系数大小确定选择的答案项
    bFound = False
    aId   = aList[0]["aId"]
    value = aList[0]["value"]
    for item in aList:
        iAId = item["aId"]
        if iAId in indefiniteOption:
            bFound = True
            break
        if value<item["value"]:
            aId = iAId
    if bFound:
        continue
    konwnAId.append(aId)
    konwnQId.append(option["qId"])
print("确定的答案项:%s" % (json.dumps(konwnAId)))
print("确定的问题项:%s" % (json.dumps(konwnQId)))

unKonwnAId = []
iPermutationsSize = 0
for option in optionInfo:
    if option["qId"] in konwnQId:
        continue
    aList = option["aList"]
    if 0==len(unKonwnAId):
        for aId in aList:
            unKonwnAId.append([aId["aId"], ])
    else:
        oldLen = len(unKonwnAId)
        for i in range(len(aList)-1):
            for j in range(oldLen):
                unKonwnAId.append(copy.deepcopy(unKonwnAId[j]))
        newLen = len(unKonwnAId)
        for i in range(newLen):
            j = int(i/oldLen)
            unKonwnAId[i].append(aList[j]["aId"])
    iPermutationsSize = len(aList) if 0==iPermutationsSize else iPermutationsSize*len(aList)
print("排列组合个数:%d" % (iPermutationsSize))
for aIdList in unKonwnAId:
    print("排列组合:%s" % (aIdList))
print("排列组合个数:%d" % (len(unKonwnAId)))

