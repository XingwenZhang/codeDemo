
#-*-coding: UTF-8-*-
__author__='兴文'
from numpy import *

sampleNum = 500
def createVocabList(dataSet):
    vocabSet = set([])  #create empty set
    for document in dataSet:
        vocabSet = vocabSet | set(document) #union of the two sets
    return list(vocabSet)

def trainNB0(trainMatrix,trainCategory):
    numTrainDocs = len(trainMatrix)
    numWords = len(trainMatrix[0])
    pAbusive = sum(trainCategory)/float(numTrainDocs)
    p0Num = ones(numWords); p1Num = ones(numWords)      #change to ones() 
    p0Denom = 2.0; p1Denom = 2.0                        #change to 2.0
    for i in range(numTrainDocs):
        if trainCategory[i] == 1:
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])
    p1Vect = log(p1Num/p1Denom)          #change to log()
    p0Vect = log(p0Num/p0Denom)          #change to log()
    return p0Vect,p1Vect,pAbusive

def classifyNB(vec2Classify, p0Vec, p1Vec, pClass1):
    p1 = sum(vec2Classify * p1Vec) + log(pClass1)    #element-wise mult
    p0 = sum(vec2Classify * p0Vec) + log(1.0 - pClass1)
    if p1 > p0:
        return 1
    else: 
        return 0
    
def bagOfWords2VecMN(vocabList, inputSet):
    returnVec = [0]*len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] += 1
    return returnVec
    
def spamTest():
    docList=[]; classList = []; fullText =[]
    for i in range(1,84):
        wordList = open('G:/data/spam/spamExtract%d.txt' %i).read()
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(1)
    for i in range(1,541):
        wordList = open('G:/data/ham/hamExtract%d.txt' %i).read()
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(0)


    vocabList = createVocabList(docList)#create vocabulary
    trainingSet = range(623); testSet=[]           #create test set
    for i in range(sampleNum):
        randIndex = int(random.uniform(0,len(trainingSet)))
        testSet.append(trainingSet[randIndex])
        del(trainingSet[randIndex])  
    trainMat=[]; trainClasses = []
    for docIndex in trainingSet:#train the classifier (get probs) trainNB0
        trainMat.append(bagOfWords2VecMN(vocabList, docList[docIndex]))
        trainClasses.append(classList[docIndex])
    p0V,p1V,pSpam = trainNB0(array(trainMat),array(trainClasses))
    errorCount = 0
    A=0;B=0;C=0;D=0
    for docIndex in testSet:        #classify the remaining items
        wordVector = bagOfWords2VecMN(vocabList, docList[docIndex])
        if classifyNB(array(wordVector),p0V,p1V,pSpam) != classList[docIndex]:
            errorCount += 1
            #print "classification error",docList[docIndex].decode('gbk').encode('utf-8')
        if classifyNB(array(wordVector),p0V,p1V,pSpam)==1 and classList[docIndex] ==1:
            A+=1
        if classifyNB(array(wordVector),p0V,p1V,pSpam)==1 and classList[docIndex] ==0:
            B+=1
        if classifyNB(array(wordVector),p0V,p1V,pSpam)==0 and classList[docIndex] ==1:
            C+=1
        if classifyNB(array(wordVector),p0V,p1V,pSpam)==0 and classList[docIndex] ==0:
            D+=1
    print 'the error rate is: ',1-float(errorCount)/len(testSet)
    R = float(A)/(A+C)
    print R
    print A,B,C,D
if __name__ =='__main__':
    spamTest()