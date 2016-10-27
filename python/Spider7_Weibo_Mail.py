#-*-coding:utf8-*-
__author__ = 'Xingwen'

import smtplib
from email.mime.text import MIMEText
import sys
import requests
import time
import os
from lxml import etree
reload(sys)
sys.setdefaultencoding("utf-8")

class mailSender(object):
    def __init__(self):
        self.mail_host = "smtp.qq.com"
        self.mail_user = "1014592497"
        self.mail_password = ""
        self.mail_postfix = "qq.com"

    def sendMail(self,target_list,subject,content):
        sender = "weiboHelper" + "<" +self.mail_user + "@" + self.mail_postfix
        msg = MIMEText(content,_subtype='plain',_charset='utf-8')
        msg['Subject'] = subject
        msg['From']= sender
        msg['To'] = ";".join(target_list)

        try:
            server = smtplib.SMTP()
            server.connect(self.mail_host)
            server.login(self.mail_user,self.mail_password)
            server.sendmail(sender,target_list,msg.as_string())
            server.close()
            return True
        except Exception, e:
            print str(e)
            return False

class weiboHelper(object):
    def __init__(self):
        #self.url = 'http://weibo.cn/3181253701/profile'
        self.url = 'http://weibo.cn/2951057457/profile'
        self.url_login = 'https://login.weibo.cn/login/'
        self.new_url = self.url_login

    def getSource(self):
        html = requests.get(self.url).content
        return html

    def getData(self,html):
        selector = etree.HTML(html)
        password = selector.xpath('//input[@type="password"]/@name')[0]
        vk = selector.xpath('//input[@name="vk"]/@value')[0]
        action = selector.xpath('//form[@method="post"]/@action')[0]
        self.new_url = self.url_login + action
        data = {
            'mobile':'1014592497@qq.com',
            password:'',
            'remember' : 'on',
            'backURL' : self.url,
            'backTitle' : u'微博',
            'tryCount' : '',
            'vk' : vk,
            'submit' : u'登陆'
        }
        return data

    def getContent(self,data):
        newhtml = requests.post(self.new_url,data=data).content
        new_selector = etree.HTML(newhtml)
        # relay = new_selector.xpath('//span[@class="cmt"]')
        # newrelay = unicode(relay[0].xpath('string(.)'))
        content = new_selector.xpath('//span[@class="ctt"]')
        newcontent = unicode(content[2].xpath('string(.)')).replace('http://','')
        #sendtime = new_selector.xpath('//span[@class="ct"]/text()')[0]
        sendtext = newcontent
        return sendtext

    def tosave(self,text):
        f = open('weibo.txt','a')
        f.write(text+'\n')
        f.close()

    def tocheck(self,data):
        if not os.path.exists('weibo.txt'):
            return True
        else:
            f = open('weibo.txt','r')
            existweibo = f.readlines()
            if data + '\n' in existweibo:
                return False
            else:
                return True



if __name__ == '__main__':
    mailTarget_list = ['@qq.com']
    helper = weiboHelper()
    while True:
        source = helper.getSource()
        data = helper.getData(source)
        content = helper.getContent(data)
        if helper.tocheck(content):
            if mailSender().sendMail(mailTarget_list,u'更新',content):
                print u'发送成功'
            else:
                print u'发送失败'
            helper.tosave(content)
            print content
        else:
            print u"pass"
        time.sleep(30)