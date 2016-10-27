#coding=utf-8
__author__ = '兴文'
from scipy.special import expit
from scipy import *
from numpy import *

sampleNum = 400
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

#LR

def sigmoid(X):
    g=expit(X)
    return g

def stocGradAscent1(dataMatrix, classLabels, numIter=150):
    m,n = shape(dataMatrix)
    weights = ones(n)   #initialize to all ones
    for j in range(numIter):
        dataIndex = range(m)
        for i in range(m):
            alpha = 4/(1.0+j+i)+0.0001    #apha decreases with iteration, does not
            randIndex = int(random.uniform(0,len(dataIndex)))#go to 0 because of the constant
            h = sigmoid(sum(dataMatrix[randIndex]*weights))
            error = classLabels[randIndex] - h
            weights = weights + alpha * error * dataMatrix[randIndex]
            del(dataIndex[randIndex])
    return weights


def predict(theta,X):
   m, n = X.shape
   p = zeros(shape=(m, 1))
   h = sigmoid(X.dot(theta.transpose()))

   for i in range(0, h.shape[0]):
        if h[i] > 0.5:
            p[i, 0] = 1
        else:
            p[i, 0] = 0
   return p

#VSM
def bagOfWords2VecAll(vocabList,SetofSet):
    returnVec = [0]*len(vocabList)
    for i in range(len(SetofSet)):
        for word in SetofSet[i]:
            if word in vocabList:
                returnVec[vocabList.index(word)]+=1
    return returnVec

def calCosine(targetVec,compVec):
    numerator = sum(targetVec*compVec)
    demo = linalg.norm(targetVec)*linalg.norm(compVec)
    rate = float(numerator)/demo
    #print rate
    return rate

def classifyCosine(hamVec,spamVec,targetVec):
    if calCosine(targetVec,hamVec) >= calCosine(targetVec,spamVec):
        return 0
    else:
        return 1




def vote():
    docList=[]; classList = []; fullText =[]
    classListLR=[]
    hamAll = []
    spamAll = []
    for i in range(1,84):
        wordList = open('G:/data/spam/spamExtract%d.txt' %i).read()
        docList.append(wordList)
        spamAll.append(wordList)
        fullText.extend(wordList)
        classList.append(1)
        classListLR.append([1])
    for i in range(1,541):
        wordList = open('G:/data/ham/hamExtract%d.txt' %i).read()
        docList.append(wordList)
        hamAll.append(wordList)
        fullText.extend(wordList)
        classList.append(0)
        classListLR.append([0])

    vocabList = createVocabList(docList)  #所有的不重复的词的列表
    trainingSet = range(623); testSet=[]



    allTrainSetX=[];allTrainSetY=[]
    for i in trainingSet:
        allVector = bagOfWords2VecMN(vocabList,docList[i])
        allTrainSetX.append(allVector)
        allTrainSetY.append(classListLR[i])
    for i in range(sampleNum):
        randIndex = int(random.uniform(0,len(trainingSet)))
        testSet.append(trainingSet[randIndex])
        del(trainingSet[randIndex])
    testWord = []
    testWordSignal=[]
    for docIndex in testSet:        #classify the remaining items
        wordVector = bagOfWords2VecMN(vocabList, docList[docIndex])
        testWord.append(wordVector)
        yResult = classListLR[docIndex]
        testWordSignal.append(yResult)
    X = array(testWord)
    y = array(testWordSignal)
    #print y.shape
    theta=stocGradAscent1(array(allTrainSetX),array(allTrainSetY),400)
    pLR = predict(array(theta), X)
    #print p.shape
    #print y[where(p==y)].size
    print "Train Accuracy:",((y[where(pLR == y)].size / float(y.size)) * 100.0)



    hamVec = bagOfWords2VecAll(vocabList,hamAll)
    spamVec = bagOfWords2VecAll(vocabList,spamAll)
    errorCount = 0
    pVSM = zeros([len(testSet),1])
    index = 0
    for docIndex in testSet:
        wordVector = bagOfWords2VecMN(vocabList,docList[docIndex])

        pVSM[index,0] = classifyCosine(array(hamVec),array(spamVec),array(wordVector))
        index += 1
        if classifyCosine(array(hamVec),array(spamVec),array(wordVector)) != classList[docIndex]:
            errorCount += 1
            #print "classification error",docList[docIndex].decode('gbk').encode('utf-8')
    print 'the error rate is:', float(errorCount)/len(testSet)






    trainMat=[]; trainClasses = []
    for docIndex in trainingSet:#train the classifier (get probs) trainNB0
        trainMat.append(bagOfWords2VecMN(vocabList, docList[docIndex]))
        trainClasses.append(classList[docIndex])
    p0V,p1V,pSpam = trainNB0(array(trainMat),array(trainClasses))
    errorCount = 0
    pBayes=zeros([len(testSet),1])
    index  = 0
    for docIndex in testSet:        #classify the remaining items
        wordVector = bagOfWords2VecMN(vocabList, docList[docIndex])
        pBayes[index,0]=classifyNB(array(wordVector),p0V,p1V,pSpam)
        index +=1
        if classifyNB(array(wordVector),p0V,p1V,pSpam) != classList[docIndex]:
            errorCount += 1
            #print "classification error",docList[docIndex].decode('gbk').encode('utf-8')
    print 'the error rate is: ',float(errorCount)/len(testSet)

    # print pLR
    # print '########'
    # print pVSM
    # print '########'
    # print pBayes
    #print pLR.size
    p = zeros([len(testSet),1])
    for i in range(len(testSet)):
        if pLR[i,0]== pVSM[i,0]:
            if pLR[i,0] == pBayes[i,0]:
                p[i,0] = pLR[i,0]
        else:
            if 2.0/3*pLR[i,0]+2.0/9*pBayes[i,0]+1.0/9*pVSM[i,0] >=0.6:
                p[i,0] = 1
            else:
                p[i,0] = 0
    print "Train Accuracy:",((y[where(p == y)].size / float(y.size)) * 100.0)
    A=0;B=0;C=0;D=0
    for i in range(len(testSet)):
        if p[i,0]==1 and y[i,0] == 1:
            A+=1
        if p[i,0]==1 and y[i,0] == 0:
            B+=1
        if p[i,0] == 0 and y[i,0] ==1:
            C+=1
        if p[i,0] == 0 and y[i,0] == 0:
            D+=1
    print A,B,C,D
    R = float(A)/(A+C)
    print R
if __name__=='__main__':
    vote()