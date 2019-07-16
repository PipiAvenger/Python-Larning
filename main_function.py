from send_message_module import send_message

def main():
    
    print("Now to send message: ")
    status = send_message('guozh@ipanel.cn', 'Qw@136025', '810170156@qq.com','Python作业','E:\python experience\helloworld.py','这是作业请查收!')
    
    #if status.find('Error') :
    #    print('Error for logining!')

if __name__ == "__main__":
    main()
    print("now Start to run!")

        

    

