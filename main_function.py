from send_message_module import send_message
from climb_data import climb_data

def main():
    
    print("开始爬取信息... ")
    if not climb_data("http://www.ipanel.cn/article.php?code=00090001") :
        print("爬取信息失败，请检查网页链接是否为指定链接...")
        exit()
    
    print("开始发送邮件... ")
    if( not send_message('guozh@ipanel.cn', 'Qw@136025', '810170156@qq.com','Python作业','E:\githubcode\Python-Larning\data.json','这是作业请查收!')) :
        print("发送邮件失败，请检查函数输入参数个数和登录信息是否正确...")
        exit()
    
    exit()
    #if status.find('Error') :
    #    print('Error for logining!')

if __name__ == "__main__":
    print("开始运行程序...")
    main()

        

    

