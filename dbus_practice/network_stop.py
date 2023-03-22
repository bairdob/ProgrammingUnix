import logging
from datetime import datetime

# create a logger object
logger = logging.getLogger('my_logger')
logger.setLevel(logging.INFO)

# create a file handler and set its level to INFO
fh = logging.FileHandler('network.log')
fh.setLevel(logging.INFO)

# create a formatter for the log messages
formatter = logging.Formatter('%(asctime)s %(levelname)s: %(message)s')

# add the formatter to the file handler
fh.setFormatter(formatter)

# add the file handler to the logger
logger.addHandler(fh)

# log a message with the current timestamp
logger.info('Network stop. Timestamp: %s', datetime.now().strftime('%Y-%m-%d %H:%M:%S'))

