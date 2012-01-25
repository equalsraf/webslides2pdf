#ifndef __WEBSLIDES_APP__
#define __WEBSLIDES_APP__

#include <QtGui>
#include <QtWebKit>

class WebSlidesApp: public QObject
{
	Q_OBJECT
public:
	WebSlidesApp(QWebView *w, QObject *parent=0);
	void setPageSize(const QSize& size) {m_pageSize = size;}
	void setPageCount(int count) { m_pageCount = count;}

protected slots:
	void webviewFinishedLoading(bool ok);
	void printPage();

private:
	QPrinter *m_printer;
	int m_current_page;
	QWebView *m_webview;
	QPainter *m_painter;
	QSize m_pageSize;
	int m_pageCount;
	bool m_initialised;
};

#endif
