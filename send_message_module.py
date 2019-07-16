#辅助函数用于显示收件人格式
def _format_addr(s):
    from email.header import Header
    from email.utils import parseaddr, formataddr
   
    name,addr=parseaddr(s) 
    return formataddr((Header(name,'utf-8').encode(), addr))

#提前文件路径中的文件名
def deal_filename(file_location):
    import os

    deal_str_len = len(file_location)
    file_name = file_location[file_location.rfind(os.path.sep):deal_str_len]

    return file_name

# 发送邮件函数 参数分别为发送人，接受者，邮件标题，附件本地位置，邮件正文内容
def send_message(sender, sender_password, recevier, message_title, file_location, main_content):

    from smtplib import SMTP
    from email.header import Header
    from email.mime.text import MIMEText
    from email.mime.image import MIMEImage
    from email.mime.multipart import MIMEMultipart
    from email.mime.application import MIMEApplication

    import urllib

    #创建一个带附件的邮件消息对象
    message = MIMEMultipart()

    #设置邮件的发送人和接受者
    message['From'] = _format_addr("<%s>" % sender) 
    message['To'] = _format_addr("<%s>" % recevier) 
 
    #创建文本内容
    message['Subject'] = Header(message_title, 'utf-8').encode()
    text_content = MIMEText(main_content, 'plain', 'utf-8')
    message.attach(text_content)

    #读取文件并将文件作为附件添加到邮件消息对象中
    filename = deal_filename(file_location) 
    with open(file_location,"rb") as f_file:
        f_file = MIMEApplication(f_file.read())
        f_file.add_header('Content-Disposition','attachment', filename = filename)
        message.attach(f_file)
        
    #登录SMTP服务器并发送邮件
    bind_smtp = SMTP('smtp.ipanel.cn')
    load_status = bind_smtp.login(sender, sender_password)
    bind_smtp.sendmail(sender, recevier, message.as_string())

    #断开与服务器的连接
    bind_smtp.quit()

    return load_status
