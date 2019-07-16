#将字典转换成json格式并存储到与源文件相同的文件夹下函数
def dect_to_json(dect_to_json_buf):
    import os, json

    #设置函数状态
    dect_to_json_func_status = True
    
    #获取源文件的路径
    current_path = os.path.abspath(__file__)
    locals_path = os.path.abspath(os.path.dirname(current_path) + os.path.sep + "data.json")

    #将字典保存到json格式的data文件
    f = None
    try:
        with open(locals_path,"w+", encoding="utf-8") as f:
            json.dump(dect_to_json_buf,f,indent=4,ensure_ascii=False)
    except IOError :
        dect_to_json_func_status = False
    
    return dect_to_json_func_status

# 爬取特定网站的某个列表的数据函数
def climb_data(string_url):
    #在爬取前需要安装requests以及lxml的库，否则运行不通过
    import requests
    from lxml import etree
    
    #设置函数状态
    climb_data_func_status = True

    # 获取网页html源码
    html = requests.get(string_url)
    etree_html = etree.HTML(html.text)

    # 解析并获取列表栏的信息新闻标题以及发布时间形成列表的格式
    content_news_title = etree_html.xpath('/html/body/div[4]/div[2]/div[3]/div[1]/ul/li/a/text()')
    content_news_time = etree_html.xpath('/html/body/div[4]/div[2]/div[3]/div[1]/ul/li[not(@class = "list_title")]/span/text()')
    str_title_len = len(content_news_title)
    str_time_len = len(content_news_time)

    #判断是否爬取到信息
    if not (str_title_len and str_time_len):
        climb_data_func_status = False 

    #创建字典，用字典存储新闻数量和新闻标题及发布时间
    dect_buf = {}
    dect_buf["total"] = str_title_len 
    """list_buf和single_news都用于存储news信息的标题和发布时间过渡容器"""
    list_buf = []  
    for i in range(0,str_title_len) :
        single_news = {}
        single_news["title"] = content_news_title[i]
        single_news["date"] = content_news_time[i]
        list_buf.append(single_news)
    dect_buf["news"] = list_buf 

    #将字典存储到json格式并放在与源文件相同的路径下
    if dect_to_json(dect_buf) :
        print("爬取数据并保存成功!")
    else:
        climb_data_func_status = False
        print("爬取失败...")

    return climb_data_func_status
    
if __name__ == "__main__":
    print("此文件为爬取数据文件，不是直接运行文件...")
    print("运行文件为main_function.py")
    quit()
else:
    print("爬取函数调用中...") 