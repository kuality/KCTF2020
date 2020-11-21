from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import TimeoutException

import time, sqlite3

def driver_init():
	global driver

	chrome_options = Options()
	chrome_options.add_argument('--no-sandbox')
	chrome_options.add_argument('--window-size=1420,1080')
	chrome_options.add_argument('--headless')
	chrome_options.add_argument('--disable-gpu')

	driver = webdriver.Chrome('/home/hyomin/hyomnote/chromedriver', chrome_options=chrome_options)
	driver.implicitly_wait(3)
	driver.set_page_load_timeout(3)

def dict_factory(cursor, row):
	result = {}
	for idx, col in enumerate(cursor.description):
		result[col[0]] = row[idx]
	return result


def set_admin_password():
	global conn
	c = conn.cursor()

	query = "update users set password=? where username='admin'"
	c.execute(query, (admin_password, ))
	conn.commit()

	return True

def get_report_url():
	global conn
	conn.row_factory = dict_factory
	c = conn.cursor()

	query = 'select * from chk_url order by rid limit 1'
	c.execute(query)
	fetch = c.fetchone()

	if fetch:
		rid = fetch['rid']
		c.execute('delete from chk_url where rid={}'.format(rid))
		conn.commit()

		return fetch['url']
	
	return False


if __name__ == '__main__':

    conn = sqlite3.connect('./note.db')
    admin_password = 'admin_ba0bab1024@@'
    driver_init()

    while(1):
        try:
            report_url = get_report_url()
            print(report_url)
            if report_url :
                driver.get('http://localhost:7979/login_form')
                driver.find_element_by_xpath("/html/body/div/div/form/input[1]").send_keys("admin")
                driver.find_element_by_xpath("/html/body/div/div/form/input[2]").send_keys(admin_password)
                time.sleep(0.5)
                driver.find_element_by_xpath('''//*[@id="submit"]''').click()
                time.sleep(0.5)
                alert = driver.switch_to.alert
                alert.accept()
                if report_url.split(":")[0] in ['http', 'https']:
                    driver.get(report_url)
            else:
                time.sleep(1)
        except :
            driver.quit()
            driver = None
            driver_init()
