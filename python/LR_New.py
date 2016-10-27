# -*- coding: UTF-8 -*-
__author__='兴文'
from numpy import *
from scipy.special import expit
from scipy import *

sampleNum = 400
def createVocabList(dataSet):
    vocabSet = set([])  #create empty set
    for document in dataSet:
        vocabSet = vocabSet | set(document) #union of the two sets
    return list(vocabSet)

def bagOfWords2VecMN(vocabList, inputSet):
    returnVec = [0]*len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] += 1
    return returnVec
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

def dataHandle():
    docList=[]; classList = []; fullText =[]
    for i in range(1,84):
        wordList = open('G:/data/spam/spamExtract%d.txt' %i).read()
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append([1])
    for i in range(1,541):
        wordList = open('G:/data/ham/hamExtract%d.txt' %i).read()
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append([0])


    vocabList = createVocabList(docList)#create vocabulary
    trainingSet = range(623); testSet=[]           #create test set
    allTrainSetX=[];allTrainSetY=[]
    for i in trainingSet:
        allVector = bagOfWords2VecMN(vocabList,docList[i])
        allTrainSetX.append(allVector)
        allTrainSetY.append(classList[i])
    for i in range(sampleNum):
        randIndex = int(random.uniform(0,len(trainingSet)))
        testSet.append(trainingSet[randIndex])
        del(trainingSet[randIndex])
    allWord = []
    allWordSignal=[]
    for docIndex in testSet:        #classify the remaining items
        wordVector = bagOfWords2VecMN(vocabList, docList[docIndex])
        allWord.append(wordVector)
        yResult = classList[docIndex]
        allWordSignal.append(yResult)
    X = array(allWord)
    y = array(allWordSignal)
    theta=stocGradAscent1(array(allTrainSetX),array(allTrainSetY),400)
    p = predict(array(theta), X)
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


def sigmoid(X):
    g=expit(X)
    return g



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

if __name__ == '__main__':
    dataHandle()
