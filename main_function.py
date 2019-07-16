from climb_data import climb_data
from send_message_module import send_message

def main():
    import getpass
    
    print("开始爬取信息... ")
    if not climb_data("http://www.ipanel.cn/article.php?code=00090001") :
        print("爬取信息失败，请检查网页链接是否为指定链接...")
        exit()

    print("开始发送邮件... ")
    if( not send_message(input("请输入发送人邮件: "), getpass.getpass("请输入对应密码: "), input("请输入收件人邮件: "), '郭志豪Python作业',input('请输入附件本地路径: ') ,'这是作业请查收!')) :
        print("发送邮件失败，请检查函数输入参数个数和登录信息是否正确...")
        exit()
    
    print("邮件已发送，请查收...")
    exit()
    #if status.find('Error') :
    #    print('Error for logining!')

if __name__ == "__main__":
    print("开始运行程序...")
    main()

        

    

