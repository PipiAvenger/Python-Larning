import logging

#logging.basicConfig(filename='system_python.log',level = logging.DEBUG,format='%(asctime)s %(filename)s %(filename)s[line:%(lineno)d] %(message)s',datefmt='%Y-%m-%d %X', filemode = 'a')
logging.basicConfig(filename='system_python.log',level = logging.DEBUG, filemode = 'a')
logging.info('info logging')
logging.debug('debug logging')
logging.warning('warning logging')
logging.error('error logging')
logging.critical('critical logging')
