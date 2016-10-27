__author__ = 'Xingwen'
#-*-coding:utf-8-*-

import requests
import re
import sys

reload(sys)
sys.setdefaultencoding("utf-8")

class spider(object):
    def __init__(self):
        print u'begin search and crawl'


    def getsource(self,url):
        html = requests.get(url)
        return html

    def changepage(self,url,total_page):
        now_page = int(re.search('pageNum=(\d+)',url,re.S).group(1))
        page_group=[]
        for i in range(now_page, total_page+1):
            link = re.sub('pageNum=(\d+)','pageNum=%s'%i, url, re.S)
            page_group.append(link)
        return page_group

    def geteverycourse(self,source):
        everycourse = re.findall('(<li deg="".*?</li>)',source, re.S)
        return everycourse

    def getinfo(self,eachcourse):
        info = {}
        info['title'] = re.search('target="_blank">(.*?)</a>',eachcourse,re.S).group(1)
        info['content'] = re.search('</h2><p>(.*?)</p>',eachcourse, re.S).group(1)
        timeandlevel = re.findall('<em>(.*?)</em>',eachcourse, re.S)
        info['coursetime'] = timeandlevel[0]
        info['courselevel'] = timeandlevel[1]
        info['learnnum'] = re.search('"learn-number">(.*?)</em>',eachcourse,re.S).group(1)
        return info

    def saveinfo(self,courseinfo):
        txtfile = open('course.txt',a)
        for each in courseinfo:
            txtfile.writelines('title:'+each['title']+'\n')
            txtfile.writelines('content'+each['content']+'\n')
            txtfile.writelines('coursetime'+each['coursetime']+'\n')
            txtfile.writelines('courselevel'+each['courselevel']+'\n')
            txtfile.writelines('learnnum'+each['learnnum']+'\n')
        txtfile.close()





if __name__ == '__main__':
    courseinfo = []
    url = 'http://www.jikexueyuan.com/course/?pageNum=1'
    JIKESpider = spider()
    all_links = JIKESpider.changepage(url,20)
    for link in all_links:
        print u'is handling the page: '+link
        html = JIKESpider.getsource(link)
        everycourse = JIKESpider.geteverycourse(html)
        for each in everycourse:
            info = JIKESpider.getinfo(each)
            courseinfo.append(info)
    JIKESpider.saveinfo(courseinfo)





